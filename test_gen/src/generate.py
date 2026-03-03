import subprocess
import numpy as np
from dataclasses import dataclass 
from typing import Tuple

import ir_work

# ------------------ Classes --------------------
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

# ------------------ Constants ------------------
QEMU_LOG_FILE_NAME = "tmp/log.txt" 
TMP_DIR_NAME = "tmp"
RES_DIR_NAME = "bin_tests"
INDENT = "\t"

# ------------------- Input ---------------------
TEST_INSNS = [ 
    test_insn_t("add", {"rs1": [-100, 100], "rs2": [-100, 100]}),
    test_insn_t("sub", {"rs1": [-100, 100], "rs2": [-100, 100]}),
]

# ----------------- Functions -------------------
def make_test_values(insn, ir, tests_info):
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

def parse_golden(log_file_name):
    return

# -----------------------------------------------
def make_res_asm(insn, tests_info):
    # RES_DIR_NAME

    return

def get_golden_ref(insn, tests_info):
    # execute on golden model
    elf_file = f"{TMP_DIR_NAME}/rv32_{insn.name}.elf"
    subprocess.run(
        [
            "qemu-riscv32",
            "-d", "in_asm,cpu",
            "-D", QEMU_LOG_FILE_NAME,
            elf_file
        ],
        check=True
    )

    # parse result of work of golden model 
    parse_golden(QEMU_LOG_FILE_NAME)

    # # add golden model reference values to asm
    # for test in test_arr:
    #     str = make_test_str(test)
    #     add_cmp(str, golden_ref)
    #     # append str to file "bin_tests/<insn.name>"

def make_tmp_asm(ir, insn, tests_info):
    # collect tests data for this insn 
    make_test_values(insn, ir, tests_info)

    # make string representation of tests
    for i, test_info in enumerate(tests_info):
        code = test_info.core_semantic
        code += f"_begin_test_{i}:\n"
        code += f"li{INDENT}gp,{i}\n"
        
        syntax = ir[insn.name].syntax
        
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

    # write to file.s
    test_file = f"{TMP_DIR_NAME}/rv32_{insn.name}.s"
    with open(test_file, "w", encoding="utf-8") as f:
        for test_info in tests_info:
            f.write(test_info.core_semantic)
            f.write(test_info.cmp_semantic)

            f.write("j _end\n")
            f.write("_end:\n")

            f.write("li a0, 0\n")
            f.write("li a7, 93\n")
            f.write("ecall\n")

    # compile .s to .elf
    asm_name = f"{TMP_DIR_NAME}/rv32_{insn.name}"
    subprocess.run(
        [
            "utility/link.sh", 
            asm_name
        ]
    )

    return tests_info

# -----------------------------------------------
def main():
    ir = ir_work.read_ir("../result/generated/IR.yaml")
    for insn in TEST_INSNS:
        # insn -- object of 'test_insn_t'
        tests_info: list[test_info_t] = [test_info_t(test_num=0, rd_val=False)]
        make_tmp_asm(ir, insn, tests_info)
        get_golden_ref(insn, tests_info)
        make_res_asm(insn, tests_info)

# direct execution
if __name__ == "__main__":
    main()
