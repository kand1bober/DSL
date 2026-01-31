require_relative "base"
require_relative "var"

module SimInfra
    class Scope
    include GlobalCounter # used for temp variables IDs
    # include SimInfra 

        attr_reader :tree, :vars, :parent
        def initialize(parent); @tree = []; @vars = {}; end

#---------- Objects in code tree ---------        
        def var(name, type)
            @vars[name] = Var.new(self, name, type) # return var
            
            # making methods. example: method rd return @vars[:rd]
            instance_eval("def #{name.to_s}(); return @vars[:#{name.to_s}]; end")
            
            stmt(:new_var, [@vars[name]]) # returns @vars[name]
        end

        private def tmpvar(type); var("_tmp#{next_counter}".to_sym, type); end
        
        # stmt adds statement into tree and returns operand[0], which is name
        # which result in near all cases
        def stmt(name, operands, attrs= nil);
            @tree << IrStmt.new(name, operands, attrs); 
            return operands[0] 
            # it is appropriate to add method nested_stmt(), 
            # that will return not a first operand, but itself, like expression
        end
        def expr(name, operands, attrs=nil)
            @tree << IrExpr.new(name, operands, attrs); 
            return @tree.last #returns itself
        end

        # resolve allows to convert Ruby Integer constants to Constant instance
        def resolve_const(what)
            case what
                when Var, Constant
                    what
                when Integer
                    Constant.new(self, "const_#{next_counter}", what) 
                else #stmt or expr
                    what
            end
        end

#-------- Operators in code tree ---------
        def un_op(a, op)
            a = resolve_const(a); 
            expr(op, [a])
        end
        def bin_op(a, b, op);
            a = resolve_const(a); b = resolve_const(b)
            # TODO: check constant size <= bitsize(var)
            # assert(a.type== b.type|| a.type == :iconst || b.type== :iconst)
            stmt(op, [tmpvar(a.type), a, b])
        end
        def ternary_op(a, b, c, op)
            a = resolve_const(a); b = resolve_const(b); c = resolve_const(c)
            stmt(op, [tmpvar(a.type), a, b, c])
        end

        #----- BASIC OPS ------ кирпичики, из которых строятся ВСЕ операции, они идут code tree
        # redefine! add & sub will never be the same
        
        # unary
        [:ui8, :ui16, :ui32,
        :i8,  :i16,  :i32].each do |op|
            define_method(op) { |a| un_op(a, op) }
        end     
        
        # binary 
        [:add, :sub,      # instruction and operation have same representation,
        :xor, :or, :and, # but in their case it is not a problem
        
        :'op_mul', :'op_div_signed', :'op_div_unsign',
        :'op_rem_signed', :'op_rem_unsign', # '*', '/signed', '/unsign', '%signed', '%unsign'
        :'op_sll', :'op_srl', :'op_sra', # '<<', '>>', '>>>'
        :'equ', :'not_equ', # '==' '!=' 
        :se, :ze, # sign, unsign extension
        :'less_signed', :'less_unsign', 
         :'more_equal_signed', :'more_equal_unsign'].each do |op|
            define_method(op) { |a, b| bin_op(a, b, op) }
        end
        
        # ternary
        [:bit_extract, :ternary].each do |op|
            define_method(op) { |a, b, c| ternary_op(a, b, c, op)}
        end

        # enumeration operator
        def list_op(attrs= nil, &block)
            self.instance_eval(&block)
        end
        
        # conditional operator
        def cond_op(attrs= nil, a, &block)
            a = resolve_const(a)
            self.instance_eval(&block)
            #this is based on the fact, that :let operation is the last in code tree at this moment
            stmt(:cond_op, [a, @tree.last], attrs)   
        end
        
        #----- COMPOUND OPS -----
        #----- R -----
        def slt(a, b) ternary(less_signed(a, b), 1, 0) end
        def sltu(a, b) ternary(less_unsign(a, b), 1, 0) end
        
        def sll(a, b) op_sll(a, bit_extract(b, 4, 0)) end        
        def srl(a, b) op_srl(a, bit_extract(b, 4, 0)) end     
        def sra(a, b) op_sra(a, bit_extract(b, 4, 0)) end

        def mul(a, b) bit_extract(op_mul(i32(a), i32(b)), 31, 0) end
        def mulh(a, b) bit_extract(op_mul(i32(a), i32(b)), 63, 32) end
        def mulhsu(a, b) bit_extract(op_mul(i32(a), ui32(b)), 63, 32) end
        def mulhu(a, b) bit_extract(op_mul(ui32(a), ui32(b)), 63, 32) end

        def div(a, b) op_div_signed(a, b) end
        def divu(a, b) op_div_unsign(a, b) end
        def rem(a, b) op_rem_signed(a, b) end
        def remu(a, b) op_rem_unsign(a, b) end
        
        #----- I -----
            #--- I_ALU ---
        def addi(a, b) add(a, se(b, 12)) end
        def xori(a, b) xor(a, se(b, 12)) end
        def ori(a, b) send(:or, a, se(b, 12)) end
        def andi(a, b) send(:and, a, se(b, 12)) end

        def slti(a, b) slt(a, se(b, 12)) end
        def sltiu(a, b) sltu(a, se(b, 12)) end
            #--- I_SHIFT ---
        def slli(a, b) end
        def srli(a, b) end
        def srai(a, b) end
            #--- I_MEM ---
        # these operations can also be described as 'op(a, imm, b)' but without 
        # 'list_op()' and 'rd[]=' parts by writing 'rd=' in field 'code' in Target  
        # def lb(a, imm, b) list_op() { rd[]= } end 
        # def lh(a, imm, b) end
        # def lw(a, imm, b) end
        # def lbu(a, imm, b) end
        # def lhu(a, imm, b) end
            #--- I_JUMP ---
        def jalr(a, imm, b, pc) list_op() { rd[]= add(pc, 4) 
                                            pc[]= send(:and, add(b, se(imm, 12)), ~0x1)} end

        #----- S -----
        def sb(a, imm, b) end
        def sh(a, imm, b) end
        def sw(a, imm, b) end

        #----- B -----
        def beq(a, b, imm, pc) cond_op(equ(a, b)) { pc.add_assign se(op_sll(imm, 1), 12) } end

        def bne(a, b, imm, pc) cond_op(not_equ(a, b)) { pc.add_assign se(op_sll(imm, 1), 12) } end

        def blt(a, b, imm, pc) cond_op(less_signed(a, b)) { pc.add_assign se(op_sll(imm, 1), 12) } end

        def bge(a, b, imm, pc) cond_op(more_equal_signed(a, b)) { pc.add_assign se(op_sll(imm, 1), 12) } end

        def bltu(a, b, imm, pc) cond_op(less_unsign(a, b)) { pc.add_assign se(op_sll(imm, 1), 12) } end
                                 
        def bgeu(a, b, imm, pc) cond_op(more_equal_unsign(a, b)) { pc.add_assign se(op_sll(imm, 1), 12) } end

        #----- U -----
        def lui(imm, pc) op_sll(imm, 12) end
        def auipc(imm, pc) add(pc, op_sll(imm, 12)) end

        #----- J -----
        def jal(a, imm, pc) list_op() { rd[]= add(pc, 4)
                                        pc.add_assign se(op_sll(imm, 1), 20)} end

#-----------------------------------------
    end
end
