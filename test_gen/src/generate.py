import subprocess
import numpy as np
from dataclasses import dataclass 
from typing import Tuple

import ir_work

@dataclass
class test_insn_t:
    name: str
    ranges: dict[str, list[int]]

@dataclass
class test_info_t:
    test_num: int

    rd_val: bool
    rs1_val: tuple[int, bool] = (None, False)
    rs2_val: tuple[int, bool] = (None, False)
    imm_val: tuple[int, bool] = (None, False)

    core_semantic: str= ""
    cmp_semantic:  str= ""

# Constants
log_file = "tmp/log.txt"
INDENT = "\t"

# ------------------- Input ---------------------
test_insns = [ 
    test_insn_t("add", {"rs1": [-100, 100], "rs2": [-100, 100]}),
    test_insn_t("sub", {"rs1": [-100, 100], "rs2": [-100, 100]}),
]
# -----------------------------------------------

def gen_test_value(insn, ir):
    tests_info: list[test_info_t] = [test_info_t(test_num=0, rd_val=False)]

    if insn.name in ir:
        # TODO: цикл for на количество тестов для одной инструкции 
        insn_metadata = ir[insn.name]

        if ("rs1" in insn_metadata.operands) and ("rs1" in insn.ranges):
            tests_info[0].rs1_val = ( 
                np.random.randint(
                    insn.ranges["rs1"][0],
                    insn.ranges["rs1"][1],
                ), 
                True
            )
        
        if ("rs2" in insn_metadata.operands) and ("rs2" in insn.ranges):
            tests_info[0].rs2_val = (
                np.random.randint(
                    insn.ranges["rs2"][0],
                    insn.ranges["rs2"][1],
                ), 
                True
            )
    
        if ("imm" in insn_metadata.operands) and ("imm" in insn.ranges):
            tests_info[0].imm_val = (
                np.random.randint(
                    insn.ranges["imm"][0],
                    insn.ranges["imm"][1],
                ), 
                True 
            )

        if "rd" in insn_metadata.operands:
            tests_info[0].rd_val = True            

    return tests_info

def gen_tests_asm(insn, tests_info, ir):
    for i, test_info in enumerate(tests_info):
        code = test_info.core_semantic
        code += f"_begin_test_{i}:\n"
        code += f"li{INDENT}gp,{i}\n"
        
        syntax = ir[insn.name].syntax

        print(insn.name, ir[insn.name].operands, insn.ranges)
        
        if test_info.rs1_val[1]: # replace rs1 with register name
            code += f"li a1, {test_info.rs1_val[0]}\n"
            syntax = syntax.replace("rs1", "a1")
        if test_info.rs2_val[1]:
            code += f"li a2, {test_info.rs2_val[0]}\n"
            syntax = syntax.replace("rs2", "a2")
        if test_info.rd_val:
            syntax = syntax.replace("rd", "a4")
        
        code += syntax
        code += "\n"

        test_info.core_semantic = code

def write_asm(insn, tests_info):
    test_file = f"bin_tests/rv32_{insn.name}.s"
    with open(test_file, "w", encoding="utf-8") as f:
        for test_info in tests_info:
            f.write(test_info.core_semantic)
            f.write(test_info.cmp_semantic)

def make_test_elf(ir, insn):
    # collect tests data for this insn 
    tests_info = gen_test_value(insn, ir)

    # make string representation of tests
    gen_tests_asm(insn, tests_info, ir)

    # write to file.s
    write_asm(insn, tests_info)

    # compile .s to .elf
    asm_name = f"bin_tests/rv32_{insn.name}"
    subprocess.run(
        [
            "bin_tests/link.sh", 
            asm_name
        ]
    )

def main():
    ir = ir_work.read_ir("../result/generated/IR.yaml")
    for insn in test_insns:
        make_test_elf(ir, insn)

    # # execute on golden model
    # subprocess.run(
    #     [
    #         "qemu-riscv32",
    #         "-d", "in_asm,cpu",
    #         "-D", log_file,
    #         elf_file
    #     ],
    #     check=True
    # )

    # # parse result of work of golden model 
    # # parse()

    # # add golden model reference values to asm
    # for test in test_arr:
    #     str = make_test_str(test)
    #     add_cmp(str, golden_ref)
    #     # append str to file "bin_tests/<insn.name>"


# direct execution
if __name__ == "__main__":
    main()
