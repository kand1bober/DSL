#!/usr/bin/ruby
require_relative "Generic/base"
require_relative "Generic/builder"
require_relative "Target/RISC-V/32IM.rb"

SimInfra.serialize

# generate interpreter
require_relative "Target/RISC-V/interpreter.rb"

# generate decoder
require_relative "Target/RISC-V/decode_tree.rb"
require_relative "Target/RISC-V/decoder.rb"
