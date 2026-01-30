require_relative "base"

module SimInfra
    IrStmt = Struct.new(:name, :oprnds, :attrs)
    class IrExpr
        attr_reader :name, :oprnds, :attrs

        def initialize(name, oprnds, attrs)
            @name, @oprnds, @attrs = name, oprnds, attrs
        end

        def type()
            cur = @oprnds[0]
            while (cur.class != Var)
                cur = cur.oprnds[0]
            end

            return cur.type
        end
    end

    class Var
        attr_reader :scope, :name, :type
        def initialize(scope, name, type)
            @scope = scope; @name = name; @type = type;
        end
        
        # Syntax "var[]=value" is used to assign variable
        # it's similar to "var[hi:lo]=value" for partial assignment
        def []=(other); @scope.stmt(:let, [self, other]); end
        
        # dumps states and disables @scope dump
        def inspect; "#{@name}:#{@type} (#{@scope.object_id})"; end
    end
end

module SimInfra
    # constant resolution (type check, initialization of constant type/value)
    class Constant
        attr_reader :scope, :name, :type, :value
        def initialize(scope, name, value);
            @const = value; @scope = scope; @type = :iconst; @value = value
            @scope.stmt(:new_const, [@const]);
        end
        def let(other); raise "Assign to constant"; end
        def inspect; "#{@name}:#{@type} (#{@scope.object_id}) {=#{@const}}"; end
    end
end

module SimInfra 
    class Var
    include SimInfra

        (R_ALU_TYPE_INSNS + I_ALU_TYPE_INSNS).each do |op|
            define_method(op) { |other| @scope.public_send(op, self, other) }
        end

        B_TYPE_INSNS.each do |op| 
            define_method(op) { |a, b, c, pc| @scope.public_send(op, a, b, c, pc) }
        end

        
    end
end
