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

    # insn_syntax: str
    # TODO: как вытащить синтакисис из IR в виде <insn> rd, rs1, rs3 и 
    # преобразовать в конкретные номера регистров x1, x2, ... 

# Constants
elf_file = "tmp/tmp.elf"
log_file = "tmp/log.txt"
test_header = "<_begin_test>:"
test_insns = [ 
    test_insn_t("add", {"rs1": [0, 10], "rs2": [0, 10]}),
    test_insn_t("sub", {"rs1": [0, 10], "rs2": [0, 10]}),
]

def gen_tests(test_insns):
    test_arr = []
    test = test_values_t()

    ir = ir_work.read_ir()
    insn_metadata = ir_work.insn_metadata_t() 

    for insn in test_insns:
        if insn.name in ir:
            # TODO: цикл for на количество тестов для одной инструкции 
            insn_metadata = ir[insn.name]

            if "rs1" in insn_metadata.operands & "rs1" in insn.ranges:
                test.rs1_val = np.random.randint(
                    insn["rs1"][0],
                    insn["rs1"][1],
                )
            
            if "rs2" in insn_metadata.operands & "rs1" in insn.ranges:
                test.rs2_val = np.random.randint(
                    insn["rs2"][0],
                    insn["rs2"][1],
                )

            
            if "imm" in insn_metadata.operands & "imm" in insn.ranges:
                test.imm_val = np.random.randint(
                    insn["imm"][0],
                    insn["imm"][1],
                )
            
            test_arr.append(test)
    return test_arr

def main():
    test_arr = gen_tests(test_insns)

    # execute on golden model
    subprocess.run(
        [
            "qemu-riscv32",
            "-d", "in_asm,cpu",
            "-D", log_file,
            elf_file
        ],
        check=True
    )

    # parse result of work of golden model 
    
    # add golden model reference values to asm


# direct execution
if __name__ == "__main__":
    main()
