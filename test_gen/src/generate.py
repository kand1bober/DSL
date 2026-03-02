import subprocess
import numpy as np
from dataclasses import dataclass 
from typing import Tuple

import ir_work

# вместо: 
# insns = ["""
# li	gp,2
# li	a1,0
# li	a2,0
# add	a4,a1,a2
# li	t2,0
# bne	a4,t2,80000670 <fail>
# """, 
# ]

# делаем так: 
test_insns = ["""
2 # номер теста -- надо добавлять автоматически
0 # значение первого операнда -- автоматически
0 # значение второго операнда -- автоматически
add	# инструкция -- вручную
"""
]

# здесь запуск и парсинг golden модели 

test_check = """
li	t2, 0 # значение из golden модели 
bne	a4,t2,80000670 <fail>
"""

#------------------------------------------------     

@dataclass
class test_insn_t:
    name: str
    ranges: dict[str, list[int]]

class test_values_t:
    test_num: int

    rs1_val: int
    rs2_val: int
    imm_val: int

    core_semantic: str
    cmp_semantic:  str

# Constants
log_file = "tmp/log.txt"
test_header = "<_begin_test>:"

test_insns = [ 
    test_insn_t("add", {"rs1": [0, 10], "rs2": [0, 10]}),
    test_insn_t("sub", {"rs1": [0, 10], "rs2": [0, 10]}),
]

def gen_test_value(insn, ir):
    test_values = test_values_t()
    # insn_metadata = ir_work.insn_metadata_t() 

    if insn.name in ir:
        # TODO: цикл for на количество тестов для одной инструкции 
        insn_metadata = ir[insn.name]

        if ("rs1" in insn_metadata.operands) & ("rs1" in insn.ranges):
            test_values.rs1_val = np.random.randint(
                insn.ranges["rs1"][0],
                insn.ranges["rs1"][1],
            )
        
        if ("rs2" in insn_metadata.operands) & ("rs2" in insn.ranges):
            test_values.rs2_val = np.random.randint(
                insn.ranges["rs2"][0],
                insn.ranges["rs2"][1],
            )
    
        if ("imm" in insn_metadata.operands) & ("imm" in insn.ranges):
            test_values.imm_val = np.random.randint(
                insn.ranges["imm"][0],
                insn.ranges["imm"][1],
            )
    return test_values

def make_test_elf(ir, insn):
    # test_arr = []

    # собрать данные для нескольких тестов одной инструкции(пока один тест на инструкцию)
    test_values = gen_test_value(insn, ir)

    # у каждого теста есть набор данных и строковая репрезентация, также строку со сравнением с голденом можно добавить как отдельное поле   
    # str = ""
    # str.apppend()
    
    # write to file.asm
    test_file = f"bin_tests/rv32_{insn.name}.s"
    with open(test_file, "w", encoding="utf-8") as f:
        f.write(test_header + "\n")

    # compile .asm to .elf
    asm_name = f"bin_tests/rv32_{insn.name}"
    subprocess.run(
        [
            "link.sh", 
            asm_name
        ]
    )

def main():
    ir = ir_work.read_ir("../result/generated/IR.yaml")
    for insn in test_insns:
        make_test_elf(ir, insn)


    # test_arr = gen_test_values(test_insns)
    # for test in test_arr:
    #     str = make_test_str(test)
    #     # append str to file elf_file

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
