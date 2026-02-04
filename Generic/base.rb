
module SimInfra
    # @@instructions # -array of instruction description

    # saves instruction description to 'IR.yaml' if called from standalone,
    # or prints to terminal, if called from IRB 
    def self.serialize(msg= nil)
        return @@instructions if Object.const_defined?(:IRB)

        require 'yaml'
        yaml_data = YAML.dump(@@instructions.map(&:to_h))

        File.open("result/IR.yaml", "w") do |file|
            file.write(yaml_data)
        end

        puts "IR made in 'result/IR.yaml'"
    end

    # reset state
    def siminfra_reset_module_state; @@instructions = []; end

    # mixin for global counter, function returns 0,1,2,....
    module GlobalCounter
        @@counter = -1
        def next_counter; @@counter += 1; end
    end

    # new data types(classes)
    Field = Struct.new(:name, :from, :to, :value)
    ImmFieldPart = Struct.new(:name, :from, :to, :order) #left are hi, right are lo

    def field(name, from, to, value = nil)
        Field.new(name, from, to, value).freeze
    end
    def imm_field_part(from, to, order = nil)
        ImmFieldPart.new(:immpart, from, to, order).freeze 
    end

    def assert(condition, msg = nil); raise msg if !condition; end
end

module SimInfra
    R_TYPE_INSNS = [:add, :sub, :xor, :or, :and, 
    :slt, :sltu, :sll, :srl, :sra, 
    :mul, :mulh, :mulhsu, :mulhu, 
    :div, :divu, :rem, :remu]
    
    I_ALU_TYPE_INSNS = [:addi, :xori, :ori, :andi, 
    :slti, :sltiu]
    I_SHIFT_TYPE_INSNS = [:slli, :srli, :srai]
    I_MEM_TYPE_INSNS = [:lb, :lh, :lw, :lbu, :lhu]
    I_JUMP_TYPE_INSNS = [:jalr]
    
    S_TYPE_INSNS = [:sb, :sh, :sw]
    
    B_TYPE_INSNS = [:beq, :bne, :blt, :bge, :bltu, :bgeu]
    
    U_TYPE_INSNS = [:lui, :auipc]
    
    J_TYPE_INSNS = [:jal]

    ALL_INSNS = R_TYPE_INSNS + R_TYPE_INSNS + I_SHIFT_TYPE_INSNS + 
                I_MEM_TYPE_INSNS + I_JUMP_TYPE_INSNS + S_TYPE_INSNS +
                B_TYPE_INSNS + U_TYPE_INSNS + J_TYPE_INSNS
end
