#include <iostream>
#include <iomanip>
#include "op.h"
#include "interpret.h"

int main(int argc, char* argv[])
{
    SPU spu{0};

    if (argc != 2) {
        std::cout << "Correct usage: sim executables/<filename>" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    spu.load_elf(argv[1]);

    spu.run();

    return 0;
}
