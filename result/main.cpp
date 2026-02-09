#include <iostream>
#include "op.h"

int main()
{
    SPU spu;

    auto [func, args] = decode(spu, 1);
    
    // Распаковываем кортеж и вызываем функцию
    auto result = std::apply(func, args);
    std::cout << "Result: " << result << std::endl;

    return 0;
}
 