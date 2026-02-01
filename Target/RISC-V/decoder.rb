require_relative "../../Generic/base.rb"
require 'yaml'

def make_head(insns)
    lead_bits = get_lead_bits(insns) # opcode, funct3, funct7
    maj_bits = get_maj_bits(lead_bits) # major range

    lsb, msb = maj_bits[0], maj_bits[-1] # most/least significant bits
    width = msb - lsb + 1
    
    
end

def make_child(node, separ_mask, insns, cur_subtree) 

end

def get_lead_bits(insns)

end

def get_maj_bits(lead_bits)

end