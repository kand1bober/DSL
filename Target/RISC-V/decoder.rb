require_relative "../../Generic/base.rb"
require 'yaml'

make_head(ALL_INSNS)

def make_head(insns)
    lead_bits = get_lead_bits(insns) # opcode, funct3, funct7
    msb, lsb = get_maj_bits(lead_bits) # major range, most/least significant bits
    width = msb - lsb + 1
    
    tree = {
        :range = [msb, lsb],
        :node = {} # here subtree is added
    }

    window = (1 << width) - 1
    shifted_window = window << lsb

    node_val = 0
    while (node_val <= window)
        actual_node = node_val << lsb
        subtree = {}
        
        is_leaf, result = MAKE_CHILD(actual_node,
                                     shifted_window,
                                     lead_bits, 
                                     subtree)

        if (is_leaf == true)
            tree[:node][:node_value] = result
        elsif (subtree)
            tree[:node][:node_value] = subtree
        end
    end
end

def make_child(node, separ_mask, insns, cur_subtree) 
    # sublist = FILTER_INSTRUCTIONS(instructions, node, separ_mask)

    # IF sublist empty: RETURN None, None

    # IF len(sublist) == 1: RETURN True, sublist

    # lead_bits = GET_LEAD_BITS(sublist, separ_mask)
    # maj_range = GET_MAJ_RANGE(lead_bits)
    # msb, lsb = maj_range[-1], maj_range[0]
    # width = msb - lsb + 1

    # current_subtree["range"] = (msb, lsb)
    # current_subtree["nodes"] = {}

    # new_mask = separ_mask | ((1<<width)-1 << lsb)

    # FOR node_value FROM 0 TO (1 << width) - 1:
    #     actual_node = node | (node_value << lsb)
    #     child_subtree = {}

    #     is_leaf, result = MAKE_CHILD(actual_node,
    #                                 new_mask,
    #                                 sublist,
    #                                 child_subtree)

    #     IF is_leaf == True:
    #     current_subtree["nodes"]["node_value] = result
    #     ELSE IF child_subtree != {}:
    #     current_subtree["nodes"]["node_value] = subtree

    # RETURN None, None
end

def get_lead_bits(insns)
    data = YAML.load_file('instructions.yml')
    
    #select instructions from 'insns' argument
    selected_insns = data.select { |insn| insns.include?(insn[:name]) }

    lead_bits = []
    selected_insns.map do |insn| 
        lead_bits << {insn_name: insn[:name], bits: insn[:lead_bits]}
    end

    return lead_bits
end

def get_maj_bits(insn_bit_len= 32, lead_bits)
    maj_ranges = []

    i = 0
    while i < insn_bit_len
        # check that there is no 'x' in all rows at i position
        if lead_bits.all? { |item| item[:bits][i] != 'x' }
            j = i
            # until there is an 'x' in all rows at j position
            while j < insn_bit_len && lead_bits.all? { |item| item[:bits][j] != 'x' }
                j += 1
            end
            maj_ranges << {msb: i, lsb: j - 1}
            i = j
        else            
            i += 1
        end
    end

    # find a range with a largest width
    if maj_ranges.any?
        largest = maj_ranges.max_by { |range| range[:lsb] - range[:msb] + 1 }
        return [largest[:msb], largest[:lsb]]
    else
        return [nil, nil]
    end
end
