import yaml
from dataclasses import dataclass 
from typing import Tuple

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
        insn_name, ops_part = asm.split(None, 1)
        ops = tuple(x.strip() for x in ops_part.split(","))
        table[name] = insn_metadata_t(
            syntax= asm, 
            operands= ops
        )

    return table
