require_relative "../../Generic/base.rb"
require 'yaml'

module DecodeTree
    @allowed_classes = [
        Symbol,
        SimInfra::Field,
        SimInfra::ImmParts,
        SimInfra::Var,
        SimInfra::XReg,
        SimInfra::Imm,
        SimInfra::Scope,
        SimInfra::IrStmt,
        SimInfra::IrExpr,
        SimInfra::Constant,
        SimInfra::PC,
    ]
    
    def self.make_tree(insns)
        data = YAML.safe_load(File.read('result/IR.yaml'), permitted_classes: @allowed_classes, aliases: true)
        
        #select instructions from 'insns' argument
        selected_insns = data.select { |insn| insns.include?(insn[:name]) }
        
        lead_bits = []
        selected_insns.map do |insn| 
            lead_bits << {insn_name: insn[:name], bits: insn[:lead_bits]}
        end

        tree = make_head(lead_bits)

        # dump tree
        File.write('result/decode_tree.yaml', tree.to_yaml)

        puts "decode tree made in 'result/decode_tree.yaml'"
    end

    INSN_BIT_LEN = 32

    # lead_bits == opcode, funct3, funct7
    def self.make_head(lead_bits)
        msb, lsb = get_maj_range(lead_bits) # major range, most/least significant bits
        return {} unless msb && lsb  # ранний выход
        width = msb - lsb + 1
        
        window = (1 << width) - 1
        separ_mask = {
            value: window << lsb, 
            msb: msb, 
            lsb: lsb,
        }

        tree = {
            range: [msb, lsb],
            separ_mask: separ_mask[:value],
            nodes: {} # here subtree is added
        }

        node = 0
        while (node <= window)
            actual_node = node << lsb
            
            is_leaf, leaf, subtree = make_child(actual_node,
                                                separ_mask,
                                                lead_bits)

            if (is_leaf == true)
                tree[:nodes][actual_node] = leaf[:insn_name]
            elsif (subtree)
                tree[:nodes][actual_node] = subtree
            end

            node += 1
        end

        return tree
    end

    def self.make_child(node, separ_mask, lead_bits) 
        sublist = filter_insns(lead_bits, node, separ_mask)
        
    # this node is leaf
        if sublist.empty?
            return [nil, nil, nil]
        elsif sublist.length == 1 
            return [true, sublist[0], nil]
        end

    # this node has more instructions   
        # remove previous lead_bits from consideration by overwriting with 'x'
        new_lead_bits = get_lead_bits(sublist, separ_mask)
        msb, lsb = get_maj_range(new_lead_bits)
        return {} unless msb && lsb  # ранний выход
        width = msb - lsb + 1
        
        new_mask = {
            value: separ_mask[:value] | ((1<<width)-1 << lsb), 
            msb: msb,
            lsb: lsb,
        }
        
        cur_subtree = {
            range: [msb, lsb],
            separ_mask: new_mask[:value],  
            nodes: {},
        }

        new_node = 0
        while (new_node <= (1 << width) - 1)
            actual_node = node | (new_node << lsb)

            is_leaf, leaf, child_subtree = make_child(actual_node,
                                        new_mask,
                                        sublist)

            if (is_leaf == true)
                cur_subtree[:nodes][new_node << lsb] = leaf[:insn_name]
            elsif (child_subtree)
                cur_subtree[:nodes][new_node << lsb] = child_subtree
            end

            new_node += 1
        end

        if cur_subtree[:nodes].empty?
            return [nil, nil, nil]
        else
            return [nil, nil, cur_subtree]
        end
    end

    # return is list of hash with :insn_name and :lead_bits 
    def self.filter_insns(lead_bits, node, separ_mask)
        sublist = [] 
        lead_bits.each do |item|
            msb = separ_mask[:msb]
            lsb = separ_mask[:lsb]
            width = msb - lsb + 1
            from = INSN_BIT_LEN - 1 - msb
            
            if (item[:bits][from, width] == (node & separ_mask[:value]).to_s(2).rjust(INSN_BIT_LEN, '0')[from, width]) 
                # puts "lead_bits: #{item[:bits]}\n"
                # puts "item[:bits][from, width]: #{item[:bits][from, width]}"
                # puts "node: #{node}"
                # puts "node & separ_mask[:value]: #{node & separ_mask[:value]}"
                # puts "to_s(2).rjust: #{(node & separ_mask[:value]).to_s(2).rjust(INSN_BIT_LEN, '0')}"
                # puts "[]: #{(node & separ_mask[:value]).to_s(2).rjust(INSN_BIT_LEN, '0')[from, width]}"
                
                sublist << item
            end
        end
        return sublist
    end
    
    def self.get_lead_bits(lead_bits, separ_mask)    
        lead_bits.each do |item|
            from = INSN_BIT_LEN - 1 - separ_mask[:msb]
            width = separ_mask[:msb] - separ_mask[:lsb] + 1 
            item[:bits][from, width] = 'x' * width
        end
        return lead_bits
    end

    def self.get_maj_range(lead_bits)
        maj_ranges = []

        i = 0
        while i < INSN_BIT_LEN
            # check that there is no 'x' in all rows at i position
            if lead_bits.all? { |item| item[:bits][i] != 'x' }
                j = i
                # until there is an 'x' in all rows at j position
                while j < INSN_BIT_LEN && lead_bits.all? { |item| item[:bits][j] != 'x' }
                    j += 1
                end
                maj_ranges << {msb: INSN_BIT_LEN - 1 - i, lsb: INSN_BIT_LEN - j}
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
end

module DecodeTree
    include SimInfra
    
    make_tree(ALL_INSNS)
end