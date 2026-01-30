module SimInfra
    class XReg
        attr_reader :name
        def initialize(name)
            @name = name
            return name
        end

        # String representation for asm output
        def to_s
            @name.to_s
        end
    end
    def XReg(name); XReg.new(name); end

    class Imm
        attr_reader :name, :len
        def initialize()
            @name = :imm
            return name
        end

        def to_s
            return @name
        end
    end
    def Imm(); Imm.new(); end

    class PC
        attr_reader :name
        def initialize()
            @name = :pc
            return @name
        end

        # String representation for asm output
        def to_s
            @name.to_s
        end
    end
    def PC(); PC.new(); end
end
