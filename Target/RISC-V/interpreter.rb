require_relative "encoding"
require_relative "regfile"
require_relative '../../Generic/builder.rb'
require_relative '../../Generic/base.rb'
require_relative '../../Generic/scope.rb'
require 'yaml'

# Разрешаем загрузку нужных классов из YAML
allowed_classes = [
    Symbol,
    SimInfra::Field,
    SimInfra::ImmFieldPart,
    SimInfra::Var,
    SimInfra::XReg,
    SimInfra::Imm,
    SimInfra::Scope,
    SimInfra::IrStmt,
    SimInfra::IrExpr,
    SimInfra::Constant,
    SimInfra::PC,
]

BASE_OPS = {
    natural: {
        add: '+',
        sub: '-',
        and: '&',
        or:  '|',
        xor: '^', 

        op_mul: '*',

        op_sll: '<<',
        op_srl: '>>',
        
        equ: '==',
        not_equ: '!=',
    },    
    self_realized: {
        op_div_signed: 'div_signed',
        op_div_unsign: 'div_unsign',
        op_rem_signed: 'rem_signed',
        op_rem_unsign: 'rem_unsign',
        
        se: 'sign_extend',
        ze: 'zero_extend',
        
        bit_extract: 'bit_extract',
        op_sra: 'op_sra',
        
        less_signed: 'less_signed',
        less_unsign: 'less_unsign',
        more_equal_signed: 'more_equal_signed',
        more_equal_unsign: 'more_equal_unsign',
    },
    special: {
        ternary: 'ternary',
        cond_op: 'if',
    },
    unary: { # --- here are expressions, not statement
        ui8:  'uint8_t', 
        ui16: 'uint16_t', 
        ui32: 'Register', 
        i8:   'int8_t', 
        i16:  'int16_t',
        i32:  'SignedRegister',
    }
}


#return category and string representation
def find_op(sym)
    BASE_OPS.each do |category, mapping|
        return [category, mapping[sym]] if mapping.has_key?(sym)
    end
    nil
end

# op_type - always sym, op_val - string(watch BASE_OPS)
def interpret_result(code, op_type, op_val)
    str = String.new()
    case op_type 
        when :natural
            dst = get_operand_val(code.oprnds[0])
            a = get_operand_val(code.oprnds[1])
            b = get_operand_val(code.oprnds[2])
            str = "#{dst} = (#{a} #{op_val} #{b})"
        when :special
            case op_val.to_sym
                when :ternary 
                    str = "#{get_operand_val(code.oprnds[0])} = " + 
                           "((bool)#{get_operand_val(code.oprnds[1])}) ? " + 
                           "(#{get_operand_val(code.oprnds[2])}) : " + 
                           "(#{get_operand_val(code.oprnds[3])})"
                when :if
                    str = "#{op_val} ((bool)#{get_operand_val(code.oprnds[0])}) {\n" +
                          "\t#{get_stmt_val(code.oprnds[1])}\n" +  
                          "\t}"
            end
        when :self_realized
            dst = get_operand_val(code.oprnds[0])
            str = "#{dst} = #{op_val}(cpu#{get_call_params(code)})"
    end
    return str
end

# get info about operand. returns string with value
def get_operand_val(oprnd)
    case oprnd
        when SimInfra::Var
            return oprnd.name.to_s
        when SimInfra::Constant
            return oprnd.value.to_s
        when SimInfra::IrExpr
            #recursion untill Var/Const
            op_type, op_val = find_op(oprnd.name.to_sym)
            if (op_type == :unary)
                return "(#{op_val})(#{get_operand_val(oprnd.oprnds[0])})"
            else 
                raise "Undefined behaviour"    
            end
    end
end

# returns string 
def get_stmt_val(stmt)
    str = String.new()
    case stmt.name
        when :let
            str = "\t#{get_operand_val(stmt.oprnds[0])} = #{get_operand_val(stmt.oprnds[1])};"
        else 
            raise "Unknown statemnt in 'get_stmt_val': #{stmt.name}"
    end
    return str
end

def get_call_params(stmt) 
    params = String.new() 
    stmt[:oprnds][1..-1].each do |oprnd|
        params << ", #{get_operand_val(oprnd)}"
    end
    return params
end

def get_formal_params(insn)
    params = String.new() 
    insn[:args].each do |arg|
        if (arg.name != :pc)
            params << ", Register par_#{arg.name.to_s}"
        end        
    end
    return params
end

# load YAML
ir_list = YAML.safe_load(File.read('result/IR.yaml'), permitted_classes: allowed_classes, aliases: true)

# generate C++
File.open("result/interpret.cpp", "w") do |f|
    f.puts("#include \"op.h\"\n\n")

    # for each insn from IR tree
    ir_list.each do |insn|
        name = insn[:name].to_s
        f.puts("void exec_#{name}(CPU &cpu#{get_formal_params(insn)}) {")

        # 0th -- save :let stmt ids, that are used in cond_op, to skip interpreting them on 1st cycle 
        # 2nd -- interpret setting of registers (:setpc, :setreg for :rd)
        saved_let_id_arr = Array.new() # saved ids of :let statements
        (0..2).each do |i| 
            # for each stmt from code tree of this insn 
            insn[:code].tree.each do |code| # code is either stmt of expr
            if (code.class == SimInfra::IrStmt)
                    case code.name
                        when :getpc
                            if (i == 1)
                                f.puts("\t#{code.oprnds[1]} = cpu.#{code.oprnds[0].name.to_s};")                                
                            end
                        when :getimm 
                            if (i == 1)  
                                f.puts("\t#{code.oprnds[0]} = par_#{code.oprnds[1].name.to_s};") 
                            end
                        when :getreg
                            if (i == 1) 
                                f.puts("\t#{code.oprnds[0]} = cpu.regs[par_#{code.oprnds[1].name.to_s}];")
                            end
                        when :let
                            if (i == 1)
                                # checking to see if another statement links to this one :let
                                # if it links, skip it 
                                if !saved_let_id_arr.include?(code.object_id)
                                    f.puts("\t#{get_operand_val(code.oprnds[0])} = #{get_operand_val(code.oprnds[1])};")
                                end
                            end
                        when :new_var
                            if (i == 1)
                                f.puts("\tRegister #{code.oprnds[0].name};")
                            end
                        when :new_const 
                            # skip
                        when :setreg
                            if (i == 2)
                                f.puts("\tcpu.regs[par_#{code.oprnds[0].name.to_s}] = #{code.oprnds[1]};")
                            end
                        when :setpc
                            if (i == 2)
                                f.puts("\tcpu.#{code.oprnds[0].name.to_s} = #{code.oprnds[1]};")
                            end
                        else # special operations
                            if ((code.name != :cond_op && i == 1) || 
                                (code.name == :cond_op && i == 2)) 

                                if (result = find_op(code.name))
                                    f.puts("\t#{interpret_result(code, *result)};")                
                                else 
                                    raise("Unknown statement in code tree: #{code.name}")
                                end
                            elsif (code.name == :cond_op && i == 0)
                                saved_let_id_arr << code.oprnds[1].object_id
                            end
                    end   
            elsif (code.class == SimInfra::IrExpr)
                # skip
            else 
                puts "Unknown piece of code, it is not a statement nor expression"
            end
                
            end
        end
        f.puts("}\n\n")
    end
end

puts("C++ interpreter generated in interpret.cpp")
