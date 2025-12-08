require_relative "base"
require_relative "var"

module SimInfra
    class Scope

        include GlobalCounter# used for temp variables IDs
        attr_reader :tree, :vars, :parent
        def initialize(parent); @tree = []; @vars = {}; end
        # resolve allows to convert Ruby Integer constants to Constant instance

        def var(name, type)
            @vars[name] = SimInfra::Var.new(self, name, type) # return var
            instance_eval "def #{name.to_s}(); return @vars[:#{name.to_s}]; end"
            stmt :new_var, [@vars[name]] # returns @vars[name]
        end

        def add_var(name, type); var(name, type); self; end

        def resolve_const(what)
            return what if (what.class== Var) or (what.class== Constant) # or other known classes
            return Constant.new(self, "const_#{next_counter}", what) if (what.class== Integer)
        end

        def binOp(a,b, op);
            a = resolve_const(a); b = resolve_const(b)
            # TODO: check constant size <= bitsize(var)
            # assert(a.type== b.type|| a.type == :iconst || b.type== :iconst)

            stmt op, [tmpvar(a.type), a, b]
        end

        # redefine! add & sub will never be the same
        def add(a,b); binOp(a,b, :add); end
        def sub(a,b); binOp(a,b, :sub); end
        def and(a,b); binOp(a,b, :and); end
        def or(a,b); binOp(a,b, :or); end
        def xor(a,b); binOp(a,b, :xor); end
        def mul(a,b); binOp(a,b, :mul); end
        def div(a,b); binOp(a,b, :div); end
        def sll(a,b); binOp(a,b, :sll); end
        def slt(a,b); binOp(a,b, :slt); end
        def sltu(a,b); binOp(a,b, :sltu); end
        def srl(a,b); binOp(a,b, :srl); end
        def sra(a,b); binOp(a,b, :sra); end

        private def tmpvar(type); var("_tmp#{next_counter}".to_sym, type); end
        # stmtadds statement into tree and retursoperand[0]
        # which result in near all cases
        def stmt(name, operands, attrs= nil);
            @tree << IrStmt.new(name, operands, attrs); operands[0]
        end
    end
end
