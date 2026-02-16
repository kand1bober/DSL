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
        # only for expressions, because it doesn't create tmp variable, 
        # to connect with previous and following statements like statements do
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
        # it is possible to make unary operations with the choice of constants, 
        # then you need another type of operation.
        [:ui8, :ui16, :ui32, :ui64,
         :i8,  :i16,  :i32,  :i64].each do |op|
            define_method(op) { |a| un_op(a, op) }
        end     

        [8, 16, 32].each do |num| 
            readMem = 'readMem' + num.to_s
            writeMem = 'writeMem' + num.to_s
            define_method(readMem) { |addr| un_op(addr, readMem) }
            define_method(writeMem) { |addr, val| bin_op(addr, val, writeMem) }
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
        
        #----- COMPOUND OPS -----
        #----- R -----
        def slt(a, b) ternary(less_signed(a, b), 1, 0) end
        def sltu(a, b) ternary(less_unsign(a, b), 1, 0) end
        
        def sll(a, b) op_sll(a, bit_extract(b, 4, 0)) end        
        def srl(a, b) op_srl(a, bit_extract(b, 4, 0)) end     
        def sra(a, b) op_sra(a, bit_extract(b, 4, 0)) end

        # def mul(a, b) bit_extract(op_mul(i64(a), i64(b)), 31, 0) end
        # def mulh(a, b) bit_extract(op_mul(i64(a), i64(b)), 63, 32) end
        # def mulhsu(a, b) bit_extract(op_mul(i64(a), ui64(b)), 63, 32) end
        # def mulhu(a, b) bit_extract(op_mul(ui64(a), ui64(b)), 63, 32) end

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
        def slli(a, b) op_sll(a, bit_extract(b, 4, 0)) end
        def srli(a, b) op_srl(a, bit_extract(b, 4, 0)) end
        def srai(a, b) op_sra(a, bit_extract(b, 4, 0)) end

#-----------------------------------------
    end
end
