import yaml
from dataclasses import dataclass 
from typing import Tuple
import re

@dataclass
class insn_metadata_t:
    syntax: str
    operands: Tuple[str, ...]

# ------------ work with yaml -------------------
class RubySafeLoader(yaml.SafeLoader):
    pass

RubySafeLoader.add_multi_constructor(
    "!",
    lambda l, t, n: {
        yaml.ScalarNode: l.construct_scalar,
        yaml.SequenceNode: l.construct_sequence,
        yaml.MappingNode: l.construct_mapping,
    }[type(n)](n),
)

def sym(s: object) -> object:
    return s[1:] if isinstance(s, str) and s.startswith(":") else s
# -----------------------------------------------

def read_ir(filename):
    with open(filename, encoding="utf-8") as f:
        data = yaml.load(f, Loader=RubySafeLoader)

    table: dict[str, insn_metadata_t] = {}
    for x in data:
        name = sym(x.get(":name"))
        asm = x.get(":asm") or ""
        if not isinstance(name, str):
            continue  # или raise

        # splitting 'asm' field into operands
        # print(asm)

        parts = asm.split(None, 1)
        # insn_name = parts[0]
        if len(parts) == 2:
            ops = tuple(
                x.strip()
                for x in re.split(r"[(),]", parts[1])
                if x.strip()
            )
        else:
            ops = ()

        table[name] = insn_metadata_t(
            syntax=asm,
            operands=ops
        )

    return table
