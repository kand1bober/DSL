import subprocess
import numpy as np
from dataclasses import dataclass, field
from typing import Tuple
import struct
import re

import ir_work

# ------------------ Classes --------------------
@dataclass
class test_insn_t:
    name: str
    ranges: dict[str, list[int]]

def make_regs_dict():
    skip = {2}
    return {
        i: (True, 0) if (i not in skip) else (False, None)
        for i in range(1, 32)
    }

@dataclass
class test_info_t:
    test_num: int

    # reg_num, need/no need to init, value to set/check
    regs_init: dict[int, tuple[bool, int]] = field(default_factory= make_regs_dict)
    regs_check: dict[int, tuple[bool, int]] = field(default_factory= make_regs_dict)
    imm: tuple[int, bool] = (None, False)

    state_init_semantic: str= ""
    core_semantic: str= ""
    state_check_semantic:  str= ""

# ------------------- Mapping -------------------
asm_ops_map = {
    'rs1': 11, 
    'rs2': 12, 
    'rd' : 14,
}

# ------------------ Constants ------------------
QEMU_LOG_FILE_NAME = "tmp/log.txt" 
TMP_DIR_NAME = "tmp"
RES_DIR_NAME = "bin_tests"
INDENT = "\t"

FILE_HEADER = """
.include "macros.inc"
.section .text
.globl _start
_start:

"""

TMP_FILE_END = """_end:
    li a0, 0
    li a7, 93
    ecall
""" 

FILE_END = """_pass:
    li a0, 0
    li a7, 93
    ecall

_fail:
    mv a0, gp
    li a7, 93
    ecall
"""

# ---------------- User's input -----------------
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
            val = np.random.randint(
                    insn.ranges["rs1"][0],
                    insn.ranges["rs1"][1],
                  )
            tests_info[0].regs_init[asm_ops_map["rs1"]] = [True, val]
            tests_info[0].regs_check[asm_ops_map["rs1"]] = [True, val]
            ir[insn.name].syntax = ir[insn.name].syntax.replace(
                "rs1", f"x{asm_ops_map['rs1']}"
            )

        if ("rs2" in insn_metadata.operands) and ("rs2" in insn.ranges):
            val = np.random.randint(
                    insn.ranges["rs2"][0],
                    insn.ranges["rs2"][1],
                  )
            tests_info[0].regs_init[asm_ops_map["rs2"]] = [True, val]
            tests_info[0].regs_check[asm_ops_map["rs2"]] = [True, val]
            ir[insn.name].syntax = ir[insn.name].syntax.replace(
                "rs2", f"x{asm_ops_map['rs2']}"
            )

        if ("imm" in insn_metadata.operands) and ("imm" in insn.ranges):
            tests_info[0].imm = (
                np.random.randint(
                    insn.ranges["imm"][0],
                    insn.ranges["imm"][1],
                ), 
                True 
            )
            ir[insn.name].syntax = ir[insn.name].syntax.replace(
                "imm", {tests_info[0].imm}
            )

        if "rd" in insn_metadata.operands:
            tests_info[0].regs_init[asm_ops_map["rd"]] = [False, None]
            tests_info[0].regs_check[asm_ops_map["rd"]] = [True, None]
            ir[insn.name].syntax = ir[insn.name].syntax.replace(
                "rd", f"x{asm_ops_map['rd']}"
            )


def state_init(insn, ir, tests_info):
    make_test_values(insn, ir, tests_info)

    tests_info[0].state_init_semantic += "_state_init_:\n"
    for i in range(1, 32):
        pair = tests_info[0].regs_init[i]
        if pair[0]:
            tests_info[0].state_init_semantic += f"{INDENT}li x{i}, {pair[1]}\n"


def state_check(tests_info):
    tests_info[0].state_check_semantic += "_state_check_:\n"
    for i in range(1, 32):
        pair = tests_info[0].regs_check[i]
        if pair[0]:
            tests_info[0].state_check_semantic += f"{INDENT}li x7, {pair[1]}\n"
            tests_info[0].state_check_semantic += f"{INDENT}bne x{i}, x7, _fail\n"


def make_res_asm(insn, tests_info):
    # make string representation of cmp part of tests
    state_check(tests_info)

    # write to file.s
    test_file = f"{RES_DIR_NAME}/rv32_{insn.name}.s"
    with open(test_file, "w", encoding="utf-8") as f:
        f.write(FILE_HEADER)

        for test_info in tests_info:
            # state init
            f.write(test_info.state_init_semantic + "\n")
            # main logic
            f.write(test_info.core_semantic + "\n\n")
            # cmp with golden
            f.write(test_info.state_check_semantic + "\n")
            
        # call exit
        f.write(FILE_END)

    # compile .s to .elf
    asm_name = f"{RES_DIR_NAME}/rv32_{insn.name}"
    subprocess.run(
        [
            "utility/link.sh", 
            asm_name
        ]
    )

import re


def parse_qemu_log(log_file, target_insn, target_reg):
    with open(log_file, "r") as f:
        lines = f.readlines()

    steps = []
    current_step = []

    # --- collect steps ---
    for line in lines:
        if line.startswith("IN:"):
            if current_step:
                steps.append(current_step)
            current_step = [line]
        else:
            current_step.append(line)

    if current_step:
        steps.append(current_step)

    # --- regex for instruction line ---
    insn_pattern = re.compile(
        rf"0x[0-9a-fA-F]+:\s+[0-9a-fA-F]+\s+{re.escape(target_insn)}\b"
    )

    # --- regex for register value ---
    reg_pattern = re.compile(
        rf"x{target_reg}/[^\s]+\s+([0-9a-fA-F]+)"
    )

    results = []

    for i, step in enumerate(steps):
        step_text = "".join(step)

        # --- check if this step contains the target instruction ---
        if not insn_pattern.search(step_text):
            continue

        # --- ensure next step exists ---
        if i + 1 >= len(steps):
            continue

        next_step_text = "".join(steps[i + 1])

        # --- extract register value from next step ---
        match = reg_pattern.search(next_step_text)
        if not match:
            continue

        value = int(match.group(1), 16)
        results.append(value)

    if not results:
        raise ValueError("Instruction not found in log")

    return results


def get_golden_ref(insn, tests_info):
    # execute on golden model
    elf_file = f"{TMP_DIR_NAME}/rv32_{insn.name}.elf"
    subprocess.run(
        [
            "qemu-riscv32",
            "-D", QEMU_LOG_FILE_NAME,
            "-d", "in_asm,cpu",
            "-singlestep",
            elf_file
        ],
        check=True
    )

    # parse and get reference values
    vals = parse_qemu_log(QEMU_LOG_FILE_NAME, insn.name, asm_ops_map['rd'])

    for i, test in enumerate(tests_info):
        test.regs_check[asm_ops_map['rd']] = (True, vals[i])


def make_tmp_asm(ir, insn, tests_info):
    # collect tests data for this insn
    state_init(insn, ir, tests_info)

    # make string representation of tests
    for i, test_info in enumerate(tests_info):
        # code += f"_begin_test_{i}:\n"
        # code += f"{INDENT}li gp,{i}\n"
        test_info.core_semantic = INDENT + ir[insn.name].syntax

    # write to file.s
    test_file = f"{TMP_DIR_NAME}/rv32_{insn.name}.s"
    with open(test_file, "w", encoding="utf-8") as f:
        f.write(FILE_HEADER)

        for test_info in tests_info:
            # state init
            f.write(test_info.state_init_semantic + "\n")
            # main logic
            f.write(test_info.core_semantic + "\n\n")

        # call exit
        f.write(TMP_FILE_END)

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
        tests_info: list[test_info_t] = [test_info_t(test_num=0)]
        make_tmp_asm(ir, insn, tests_info)
        get_golden_ref(insn, tests_info)
        make_res_asm(insn, tests_info)

# direct execution
if __name__ == "__main__":
    main()
