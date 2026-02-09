#include <iostream>
#include "op.h"

int main()
{
    SPU spu;

    std::vector<Register> program;

    spu.run(program);

    return 0;
}
 