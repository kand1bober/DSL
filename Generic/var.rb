require_relative "base"

module SimInfra
    IrStmt = Struct.new(:name, :oprnds, :attrs)
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
    #
    class Var
        [:add, :sub, :and, :or, :xor].each do |op|
            define_method(op) do |other|
              @scope.public_send(op, self, other)
            end
          end
          
        
        def sll(other); @scope.sll(self, other); end
        def srl(other); @scope.srl(self, other); end
        def sra(other); @scope.sra(self, other); end
        
        def slt(other); @scope.slt(self, other); end
        def sltu(other); @scope.sltu(self, other); end

        def mul(other); @scope.mul(self, other); end
        def mulh(other); @scope.mulh(self, other); end
        def mulhsu(other); @scope.mulhsu(self, other); end
        def mulhu(other); @scope.mulhu(self, other); end
        def div(other); @scope.div(self, other); end
        def divu(other); @scope.divu(self, other); end
        def rem(other); @scope.rem(self, other); end
        def remu(other); @scope.remu(self, other); end        
    end
end
