require_relative "base"
require_relative "var"

module SimInfra
    class Scope
    include GlobalCounter # used for temp variables IDs

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
        
        # stmt adds statement into tree and returns operand[0]? which is scope
        # which result in near all cases
        def stmt(name, operands, attrs= nil);
            @tree << IrStmt.new(name, operands, attrs); operands[0]
        end

        # resolve allows to convert Ruby Integer constants to Constant instance
        def resolve_const(what)
            case what
                when Var, Constant
                    what
                when Integer
                    Constant.new(self, "const_#{next_counter}", what) 
                else 
                    what
            end
            
            # return what if (what.class== Var) or (what.class== Constant) # or other known classes
            # return Constant.new(self, "const_#{next_counter}", what) if (what.class== Integer)
            # return what if (what.)
        end

#-------- Operators in code tree ---------
        def un_op(a, op)
            a = resolve_const(a); 
            stmt(op, [tmpvar(a.type), a])
        end
        def bin_op(a,b, op);
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
         :i8,  :i16,  :i32,
         :'ternary'].each do |op|
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
        [:bit_extract].each do |op|
            define_method(op) { |a, b, c| ternary_op(a, b, c, op)}
        end

    #----- COMPOUND OPS -----
        def slt(a, b); ternary(less_signed(a, b)); end
        def sltu(a, b); ternary(less_unsign(a, b)); end

        def sll(a, b); op_sll(a, bit_extract(b, 4, 0)); end        
        def srl(a, b); op_srl(a, bit_extract(b, 4, 0)); end     
        def sra(a, b); op_sra(a, bit_extract(b, 4, 0)); end

        def mul(a, b); bit_extract(op_mul(i32(a), i32(b)), 31, 0); end
        def mulh(a, b); bit_extract(op_mul(i32(a), i32(b)), 63, 32); end
        def mulhsu(a, b); bit_extract(op_mul(i32(a), ui32(b)), 63, 32); end
        def mulhu(a, b); bit_extract(op_mul(ui32(a), ui32(b)), 63, 32); end

        def div(a, b); op_div_signed(a, b) end
        def divu(a, b); op_div_unsign(a, b) end
        def rem(a, b); op_rem_signed(a, b) end
        def remu(a, b); op_rem_unsign(a, b) end

#-----------------------------------------
    end
end
