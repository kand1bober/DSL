// test_execute.cpp
#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>
#include <cstring>
#include "../static/spu.h"
#include "../static/op.h"
#include "../generated/decode.h"
#include "../generated/execute.h"
#include "../static/interpret.h"

// ============================================================================
// Глобальные счётчики для мягкой проверки
// ============================================================================
struct TestStats {
    int passed = 0;
    int failed = 0;
    int total = 0;
    
    void print_summary() {
        std::cout << "\n📊 TEST SUMMARY" << std::endl;
        std::cout << "   Total:  " << total << std::endl;
        std::cout << "   ✅ Passed: " << passed << std::endl;
        std::cout << "   ❌ Failed: " << failed << std::endl;
    }
};

TestStats stats;

// ============================================================================
// Макрос для мягкой проверки
// ============================================================================
#define SOFT_ASSERT(cond, message) \
    do { \
        stats.total++; \
        if (cond) { \
            stats.passed++; \
            std::cout << "  ✅ " << message << std::endl; \
        } else { \
            stats.failed++; \
            std::cout << "  ❌ " << message << " [FAILED]" << std::endl; \
        } \
    } while(0)

// Для проверки значений
#define SOFT_ASSERT_EQ(actual, expected, message) \
    SOFT_ASSERT((actual) == (expected), message << " (got 0x" << std::hex << actual << std::dec << ")")

// Вспомогательные функции для тестов
void reset_cpu(SPU& spu) {
    memset(&spu.cpu.regs, 0, sizeof(spu.cpu.regs));
    spu.cpu.pc = 0;
    memset(&spu.mem.data, 0, sizeof(spu.mem.data));
}

void set_reg(SPU& spu, int reg, uint32_t value) {
    spu.cpu.regs[reg] = value;
}

uint32_t get_reg(SPU& spu, int reg) {
    return spu.cpu.regs[reg];
}

void print_regs(SPU& spu, const std::vector<int>& regs) {
    for (int reg : regs) {
        std::cout << "x" << reg << " = 0x" << std::hex << get_reg(spu, reg) << std::dec << std::endl;
    }
}

// Утилита для создания инструкции
Instruction make_insn(InsnType type, Register arg1 = 0, Register arg2 = 0, Register arg3 = 0) {
    Instruction insn;
    insn.insn_type = type;
    insn.oprnds.arg1 = arg1;
    insn.oprnds.arg2 = arg2;
    insn.oprnds.arg3 = arg3;
    return insn;
}

// ============================================================================
// Тесты для R-type инструкций
// ============================================================================

void test_add(SPU& spu) {
    reset_cpu(spu);
    std::cout << "\n=== Testing ADD ===" << std::endl;
    
    set_reg(spu, 1, 5);
    set_reg(spu, 2, 7);
    
    Instruction insn = make_insn(ADD, 3, 1, 2);  // x3 = x1 + x2
    execute(spu, insn);
    
    SOFT_ASSERT_EQ(get_reg(spu, 3), 12, "ADD x3, x1, x2 (5+7=12)");
    SOFT_ASSERT_EQ(get_reg(spu, 1), 5, "rs1 unchanged");
    SOFT_ASSERT_EQ(get_reg(spu, 2), 7, "rs2 unchanged");
    
    // Тест с нулем
    set_reg(spu, 4, 0);
    set_reg(spu, 5, 42);
    insn = make_insn(ADD, 6, 4, 5);
    execute(spu, insn);
    SOFT_ASSERT_EQ(get_reg(spu, 6), 42, "ADD with zero");
}

void test_sub(SPU& spu) {
    reset_cpu(spu);
    std::cout << "\n=== Testing SUB ===" << std::endl;
    
    set_reg(spu, 1, 10);
    set_reg(spu, 2, 3);
    
    Instruction insn = make_insn(SUB, 3, 1, 2);  // x3 = x1 - x2
    execute(spu, insn);
    
    SOFT_ASSERT_EQ(get_reg(spu, 3), 7, "SUB x3, x1, x2 (10-3=7)");
    
    // Тест с отрицательным результатом
    set_reg(spu, 4, 5);
    set_reg(spu, 5, 10);
    insn = make_insn(SUB, 6, 4, 5);
    execute(spu, insn);
    SOFT_ASSERT_EQ(get_reg(spu, 6), (uint32_t)-5, "SUB negative result");
}

void test_xor(SPU& spu) {
    reset_cpu(spu);
    std::cout << "\n=== Testing XOR ===" << std::endl;
    
    set_reg(spu, 1, 0b1100);
    set_reg(spu, 2, 0b1010);
    
    Instruction insn = make_insn(XOR, 3, 1, 2);
    execute(spu, insn);
    
    SOFT_ASSERT_EQ(get_reg(spu, 3), (0b1100 ^ 0b1010), "XOR");
}

void test_or(SPU& spu) {
    reset_cpu(spu);
    std::cout << "\n=== Testing OR ===" << std::endl;
    
    set_reg(spu, 1, 0b1100);
    set_reg(spu, 2, 0b1010);
    
    Instruction insn = make_insn(OR, 3, 1, 2);
    execute(spu, insn);
    
    SOFT_ASSERT_EQ(get_reg(spu, 3), (0b1100 | 0b1010), "OR");
}

void test_and(SPU& spu) {
    reset_cpu(spu);
    std::cout << "\n=== Testing AND ===" << std::endl;
    
    set_reg(spu, 1, 0b1100);
    set_reg(spu, 2, 0b1010);
    
    Instruction insn = make_insn(AND, 3, 1, 2);
    execute(spu, insn);
    
    SOFT_ASSERT_EQ(get_reg(spu, 3), (0b1100 & 0b1010), "AND");
}

void test_sll(SPU& spu) {
    reset_cpu(spu);
    std::cout << "\n=== Testing SLL ===" << std::endl;
    
    set_reg(spu, 1, 0x0000000F);
    set_reg(spu, 2, 4);
    
    Instruction insn = make_insn(SLL, 3, 1, 2);
    execute(spu, insn);
    
    SOFT_ASSERT_EQ(get_reg(spu, 3), 0x000000F0, "SLL");
    
    // Сдвиг на 0
    set_reg(spu, 4, 0x12345678);
    set_reg(spu, 5, 0);
    insn = make_insn(SLL, 6, 4, 5);
    execute(spu, insn);
    SOFT_ASSERT_EQ(get_reg(spu, 6), 0x12345678, "SLL shift by 0");
}

void test_srl(SPU& spu) {
    reset_cpu(spu);
    std::cout << "\n=== Testing SRL ===" << std::endl;
    
    set_reg(spu, 1, 0x000000F0);
    set_reg(spu, 2, 4);
    
    Instruction insn = make_insn(SRL, 3, 1, 2);
    execute(spu, insn);
    
    SOFT_ASSERT_EQ(get_reg(spu, 3), 0x0000000F, "SRL");
}

void test_sra(SPU& spu) {
    reset_cpu(spu);
    std::cout << "\n=== Testing SRA ===" << std::endl;
    
    // Положительное число
    set_reg(spu, 1, 0x000000F0);
    set_reg(spu, 2, 4);
    
    Instruction insn = make_insn(SRA, 3, 1, 2);
    execute(spu, insn);
    SOFT_ASSERT_EQ(get_reg(spu, 3), 0x0000000F, "SRA positive");
    
    // Отрицательное число (арифметический сдвиг)
    set_reg(spu, 4, 0x800000F0);  // Старший бит = 1
    set_reg(spu, 5, 4);
    insn = make_insn(SRA, 6, 4, 5);
    execute(spu, insn);
    SOFT_ASSERT_EQ(get_reg(spu, 6), 0xF800000F, "SRA negative (arithmetic shift)");
}

void test_slt(SPU& spu) {
    reset_cpu(spu);
    std::cout << "\n=== Testing SLT ===" << std::endl;
    
    set_reg(spu, 1, 5);
    set_reg(spu, 2, 10);
    
    Instruction insn = make_insn(SLT, 3, 1, 2);  // 5 < 10 -> 1
    execute(spu, insn);
    SOFT_ASSERT_EQ(get_reg(spu, 3), 1, "SLT 5 < 10");
    
    insn = make_insn(SLT, 4, 2, 1);  // 10 < 5 -> 0
    execute(spu, insn);
    SOFT_ASSERT_EQ(get_reg(spu, 4), 0, "SLT 10 < 5");
    
    insn = make_insn(SLT, 5, 1, 1);  // 5 < 5 -> 0
    execute(spu, insn);
    SOFT_ASSERT_EQ(get_reg(spu, 5), 0, "SLT 5 < 5");
}

void test_sltu(SPU& spu) {
    reset_cpu(spu);
    std::cout << "\n=== Testing SLTU ===" << std::endl;
    
    // Беззнаковое сравнение: -1 (0xFFFFFFFF) > 10
    set_reg(spu, 1, (uint32_t)-1);  // 0xFFFFFFFF
    set_reg(spu, 2, 10);
    
    Instruction insn = make_insn(SLTU, 3, 1, 2);  // -1 < 10? -> false (0)
    execute(spu, insn);
    SOFT_ASSERT_EQ(get_reg(spu, 3), 0, "SLTU 0xFFFFFFFF < 10");
    
    insn = make_insn(SLTU, 4, 2, 1);  // 10 < -1? -> true (1)
    execute(spu, insn);
    SOFT_ASSERT_EQ(get_reg(spu, 4), 1, "SLTU 10 < 0xFFFFFFFF");
}

// ============================================================================
// Тесты для I-type инструкций
// ============================================================================

void test_addi(SPU& spu) {
    reset_cpu(spu);
    std::cout << "\n=== Testing ADDI ===" << std::endl;
    
    set_reg(spu, 1, 5);
    
    Instruction insn = make_insn(ADDI, 2, 1, 7);  // x2 = x1 + 7
    execute(spu, insn);
    
    SOFT_ASSERT_EQ(get_reg(spu, 2), 12, "ADDI positive");
    SOFT_ASSERT_EQ(get_reg(spu, 1), 5, "rs1 unchanged");
    
    // С отрицательным immediate (знаковое расширение)
    insn = make_insn(ADDI, 3, 1, (uint32_t)-5);  // x3 = x1 + (-5)
    execute(spu, insn);
    SOFT_ASSERT_EQ(get_reg(spu, 3), 0, "ADDI with negative immediate");

    // test_9: 0x7fffffff + 0 = 0x7fffffff
    set_reg(spu, 10, 0x7FFFFFFF);  // a1 = 0x7FFFFFFF
    set_reg(spu, 11, 0);           // a2 = 0
    
    insn = make_insn(ADD, 12, 10, 11);  // a4 = a1 + a2
    execute(spu, insn);
    
    SOFT_ASSERT_EQ(get_reg(spu, 12), 0x7FFFFFFF, "a4 = 0x7FFFFFFF + 0");
    
    // Проверка с ожидаемым значением из теста (t2 = 0x7FFFFFFF)
    set_reg(spu, 7, 0x7FFFFFFF);  // t2 = 0x7FFFFFFF
    
    // BNE проверка (эмулируем условие теста)
    insn = make_insn(BNE, 12, 7, 0);  // if a4 != t2, branch
    execute(spu, insn);
    
    // BNE не должен сработать, так как значения равны
    SOFT_ASSERT_EQ(spu.cpu.pc, 0, "BNE not taken (a4 == t2)");
}

void test_xori(SPU& spu) {
    reset_cpu(spu);
    std::cout << "\n=== Testing XORI ===" << std::endl;
    
    set_reg(spu, 1, 0b1100);
    
    Instruction insn = make_insn(XORI, 2, 1, 0b1010);
    execute(spu, insn);
    
    SOFT_ASSERT_EQ(get_reg(spu, 2), (0b1100 ^ 0b1010), "XORI");
}

void test_ori(SPU& spu) {
    reset_cpu(spu);
    std::cout << "\n=== Testing ORI ===" << std::endl;
    
    set_reg(spu, 1, 0b1100);
    
    Instruction insn = make_insn(ORI, 2, 1, 0b1010);
    execute(spu, insn);
    
    SOFT_ASSERT_EQ(get_reg(spu, 2), (0b1100 | 0b1010), "ORI");
}

void test_andi(SPU& spu) {
    reset_cpu(spu);
    std::cout << "\n=== Testing ANDI ===" << std::endl;
    
    set_reg(spu, 1, 0b1100);
    
    Instruction insn = make_insn(ANDI, 2, 1, 0b1010);
    execute(spu, insn);
    
    SOFT_ASSERT_EQ(get_reg(spu, 2), (0b1100 & 0b1010), "ANDI");
}

void test_slli(SPU& spu) {
    reset_cpu(spu);
    std::cout << "\n=== Testing SLLI ===" << std::endl;
    
    set_reg(spu, 1, 0x0000000F);
    
    Instruction insn = make_insn(SLLI, 2, 1, 4);
    execute(spu, insn);
    
    SOFT_ASSERT_EQ(get_reg(spu, 2), 0x000000F0, "SLLI");
}

void test_srli(SPU& spu) {
    reset_cpu(spu);
    std::cout << "\n=== Testing SRLI ===" << std::endl;
    
    set_reg(spu, 1, 0x000000F0);
    
    Instruction insn = make_insn(SRLI, 2, 1, 4);
    execute(spu, insn);
    
    SOFT_ASSERT_EQ(get_reg(spu, 2), 0x0000000F, "SRLI");
}

void test_srai(SPU& spu) {
    reset_cpu(spu);
    std::cout << "\n=== Testing SRAI ===" << std::endl;
    
    set_reg(spu, 1, 0x800000F0);
    
    Instruction insn = make_insn(SRAI, 2, 1, 4);
    execute(spu, insn);
    
    SOFT_ASSERT_EQ(get_reg(spu, 2), 0xF800000F, "SRAI");
}

void test_slti(SPU& spu) {
    reset_cpu(spu);
    std::cout << "\n=== Testing SLTI ===" << std::endl;
    
    set_reg(spu, 1, 5);
    
    Instruction insn = make_insn(SLTI, 2, 1, 10);
    execute(spu, insn);
    SOFT_ASSERT_EQ(get_reg(spu, 2), 1, "SLTI 5 < 10");
    
    insn = make_insn(SLTI, 3, 1, 5);
    execute(spu, insn);
    SOFT_ASSERT_EQ(get_reg(spu, 3), 0, "SLTI 5 < 5");
}

void test_sltiu(SPU& spu) {
    reset_cpu(spu);
    std::cout << "\n=== Testing SLTIU ===" << std::endl;
    
    set_reg(spu, 1, (uint32_t)-1);  // 0xFFFFFFFF
    
    Instruction insn = make_insn(SLTIU, 2, 1, 10);
    execute(spu, insn);
    SOFT_ASSERT_EQ(get_reg(spu, 2), 0, "SLTIU 0xFFFFFFFF < 10");
    
    insn = make_insn(SLTIU, 3, 1, (uint32_t)-2);
    execute(spu, insn);
    SOFT_ASSERT_EQ(get_reg(spu, 3), 0, "SLTIU 0xFFFFFFFF < 0xFFFFFFFE");
    
    set_reg(spu, 4, 5);
    insn = make_insn(SLTIU, 5, 4, 10);
    execute(spu, insn);
    SOFT_ASSERT_EQ(get_reg(spu, 5), 1, "SLTIU 5 < 10");
}

// ============================================================================
// Тесты для M-extension (умножение и деление)
// ============================================================================

void test_mul(SPU& spu) {
    reset_cpu(spu);
    std::cout << "\n=== Testing MUL ===" << std::endl;
    
    set_reg(spu, 1, 5);
    set_reg(spu, 2, 7);
    
    Instruction insn = make_insn(MUL, 3, 1, 2);
    execute(spu, insn);
    
    SOFT_ASSERT_EQ(get_reg(spu, 3), 35, "MUL 5*7=35");
    
    set_reg(spu, 4, 1000);
    set_reg(spu, 5, 1000);
    insn = make_insn(MUL, 6, 4, 5);
    execute(spu, insn);
    SOFT_ASSERT_EQ(get_reg(spu, 6), 1000000, "MUL 1000*1000=1000000");
}

void test_mulh(SPU& spu) {
    reset_cpu(spu);
    std::cout << "\n=== Testing MULH (signed high word) ===" << std::endl;
    
    // Тест 1: отрицательное * положительное
    set_reg(spu, 1, 0x80000000);  // -2^31
    set_reg(spu, 2, 2);
    Instruction insn = make_insn(MULH, 3, 1, 2);
    execute(spu, insn);
    SOFT_ASSERT_EQ(get_reg(spu, 3), 0xFFFFFFFF, "(-2^31) * 2");
    
    // Тест 2: положительное * положительное (без переполнения)
    set_reg(spu, 4, 0x40000000);  // 2^30
    set_reg(spu, 5, 2);
    insn = make_insn(MULH, 6, 4, 5);
    execute(spu, insn);
    SOFT_ASSERT_EQ(get_reg(spu, 6), 0x0, "(2^30) * 2");
    
    // Тест 3: отрицательное * отрицательное
    set_reg(spu, 7, 0x80000000);  // -2^31
    set_reg(spu, 8, 0xFFFFFFFF);  // -1
    insn = make_insn(MULH, 9, 7, 8);
    execute(spu, insn);
    SOFT_ASSERT_EQ(get_reg(spu, 9), 0x0, "(-2^31) * (-1)");
    
    // Тест 4: максимальное положительное * максимальное положительное
    set_reg(spu, 10, 0x7FFFFFFF);  // 2^31-1
    set_reg(spu, 11, 0x7FFFFFFF);  // 2^31-1
    insn = make_insn(MULH, 12, 10, 11);
    execute(spu, insn);
    uint64_t product = (uint64_t)0x7FFFFFFF * 0x7FFFFFFF;
    uint32_t expected = product >> 32;
    SOFT_ASSERT_EQ(get_reg(spu, 12), expected, "(2^31-1) * (2^31-1) high word");
}

void test_div(SPU& spu) {
    reset_cpu(spu);
    std::cout << "\n=== Testing DIV ===" << std::endl;
    
    set_reg(spu, 1, 20);
    set_reg(spu, 2, 7);
    
    Instruction insn = make_insn(DIV, 3, 1, 2);
    execute(spu, insn);
    
    SOFT_ASSERT_EQ(get_reg(spu, 3), 2, "DIV 20/7");
    
    // Деление на ноль (должно вернуть -1)
    set_reg(spu, 4, 10);
    set_reg(spu, 5, 0);
    insn = make_insn(DIV, 6, 4, 5);
    execute(spu, insn);
    SOFT_ASSERT_EQ(get_reg(spu, 6), (uint32_t)-1, "DIV by zero");
}

void test_divu(SPU& spu) {
    reset_cpu(spu);
    std::cout << "\n=== Testing DIVU ===" << std::endl;
    
    set_reg(spu, 1, 20);
    set_reg(spu, 2, 7);
    
    Instruction insn = make_insn(DIVU, 3, 1, 2);
    execute(spu, insn);
    
    SOFT_ASSERT_EQ(get_reg(spu, 3), 2, "DIVU 20/7");
    
    // Деление на ноль (должно вернуть все единицы)
    set_reg(spu, 4, 10);
    set_reg(spu, 5, 0);
    insn = make_insn(DIVU, 6, 4, 5);
    execute(spu, insn);
    SOFT_ASSERT_EQ(get_reg(spu, 6), 0xFFFFFFFF, "DIVU by zero");
}

void test_rem(SPU& spu) {
    reset_cpu(spu);
    std::cout << "\n=== Testing REM ===" << std::endl;
    
    set_reg(spu, 1, 20);
    set_reg(spu, 2, 7);
    
    Instruction insn = make_insn(REM, 3, 1, 2);
    execute(spu, insn);
    
    SOFT_ASSERT_EQ(get_reg(spu, 3), 6, "REM 20 % 7");
}

void test_remu(SPU& spu) {
    reset_cpu(spu);
    std::cout << "\n=== Testing REMU ===" << std::endl;
    
    set_reg(spu, 1, 20);
    set_reg(spu, 2, 7);
    
    Instruction insn = make_insn(REMU, 3, 1, 2);
    execute(spu, insn);
    
    SOFT_ASSERT_EQ(get_reg(spu, 3), 6, "REMU 20 % 7");
}

// ============================================================================
// Тесты для Load/Store инструкций
// ============================================================================

void test_lb_lbu_sb(SPU& spu) {
    reset_cpu(spu);
    std::cout << "\n=== Testing Load/Store Byte ===" << std::endl;
    
    // SB: запись байта
    set_reg(spu, 1, 0x42);  // данные
    set_reg(spu, 2, 100);   // адрес
    
    Instruction insn = make_insn(SB, 2, 1, 0);  // sb x1, 0(x2) -> mem[100] = 0x42
    execute(spu, insn);
    
    // LB: чтение со знаковым расширением
    set_reg(spu, 3, 100);
    insn = make_insn(LB, 4, 3, 0);  // lb x4, 0(x3)
    execute(spu, insn);
    SOFT_ASSERT_EQ(get_reg(spu, 4), 0x42, "LB positive");
    
    // LB отрицательного значения
    writeMem8(spu, 100, 0xFE);  // -2 в байте
    insn = make_insn(LB, 5, 3, 0);
    execute(spu, insn);
    SOFT_ASSERT_EQ(get_reg(spu, 5), 0xFFFFFFFE, "LB negative");
    
    // LBU (беззнаковое чтение)
    insn = make_insn(LBU, 6, 3, 0);
    execute(spu, insn);
    SOFT_ASSERT_EQ(get_reg(spu, 6), 0xFE, "LBU unsigned");
}

void test_lh_lhu_sh(SPU& spu) {
    reset_cpu(spu);
    std::cout << "\n=== Testing Load/Store Halfword ===" << std::endl;
    
    // SH: запись полуслова
    set_reg(spu, 1, 0x1234);
    set_reg(spu, 2, 200);
    
    Instruction insn = make_insn(SH, 2, 1, 0);  // sh x1, 0(x2)
    execute(spu, insn);
    
    // Проверка выравнивания (адрес должен быть четным)
    SOFT_ASSERT_EQ(readMem16(spu, 200), 0x1234, "SH memory write");
    
    // LH со знаком
    set_reg(spu, 3, 200);
    insn = make_insn(LH, 4, 3, 0);
    execute(spu, insn);
    SOFT_ASSERT_EQ(get_reg(spu, 4), 0x1234, "LH positive");
    
    // LH отрицательного
    writeMem16(spu, 200, 0xFEDC);
    insn = make_insn(LH, 5, 3, 0);
    execute(spu, insn);
    SOFT_ASSERT_EQ(get_reg(spu, 5), 0xFFFFFEDC, "LH negative");
    
    // LHU без знака
    insn = make_insn(LHU, 6, 3, 0);
    execute(spu, insn);
    SOFT_ASSERT_EQ(get_reg(spu, 6), 0xFEDC, "LHU unsigned");
}

void test_lw_sw(SPU& spu) {
    reset_cpu(spu);
    std::cout << "\n=== Testing Load/Store Word ===" << std::endl;
    
    // SW: запись слова
    set_reg(spu, 1, 0xDEADBEEF);
    set_reg(spu, 2, 300);
    
    Instruction insn = make_insn(SW, 2, 1, 0);  // sw x1, 0(x2)
    execute(spu, insn);
    
    // Проверка выравнивания (адрес должен быть кратен 4)
    SOFT_ASSERT_EQ(readMem32(spu, 300), 0xDEADBEEF, "SW memory write");
    
    // LW
    set_reg(spu, 3, 300);
    insn = make_insn(LW, 4, 3, 0);
    execute(spu, insn);
    SOFT_ASSERT_EQ(get_reg(spu, 4), 0xDEADBEEF, "LW read");
}

// ============================================================================
// Тесты для U-type инструкций
// ============================================================================

void test_lui(SPU& spu) {
    reset_cpu(spu);
    std::cout << "\n=== Testing LUI ===" << std::endl;
    
    Instruction insn = make_insn(LUI, 1, 0x12345, 0);  // x1 = 0x12345 << 12
    execute(spu, insn);
    
    SOFT_ASSERT_EQ(get_reg(spu, 1), 0x12345000, "LUI");
}

void test_auipc(SPU& spu) {
    reset_cpu(spu);
    std::cout << "\n=== Testing AUIPC ===" << std::endl;
    
    spu.cpu.pc = 0x1000;
    Instruction insn = make_insn(AUIPC, 1, 0x12345, 0);  // x1 = pc + (0x12345 << 12)
    execute(spu, insn);
    
    SOFT_ASSERT_EQ(get_reg(spu, 1), 0x1000 + 0x12345000, "AUIPC");
}

// ============================================================================
// Тесты для Branch инструкций
// ============================================================================

void test_branch(SPU& spu) {
    reset_cpu(spu);
    std::cout << "\n=== Testing Branch Instructions ===" << std::endl;
    
    uint32_t old_pc = 0x1000;
    spu.cpu.pc = old_pc;
    
    // BEQ
    set_reg(spu, 1, 10);
    set_reg(spu, 2, 10);
    
    Instruction insn = make_insn(BEQ, 1, 2, 8);  // if x1 == x2, pc += 8
    execute(spu, insn);
    SOFT_ASSERT_EQ(spu.cpu.pc, old_pc + 16, "BEQ taken");
    
    // BEQ not taken
    spu.cpu.pc = old_pc;
    set_reg(spu, 2, 11);
    execute(spu, insn);
    SOFT_ASSERT_EQ(spu.cpu.pc, old_pc, "BEQ not taken");
    
    // BNE
    spu.cpu.pc = old_pc;
    set_reg(spu, 1, 10);
    set_reg(spu, 2, 11);
    insn = make_insn(BNE, 1, 2, 8);
    execute(spu, insn);
    SOFT_ASSERT_EQ(spu.cpu.pc, old_pc + 16, "BNE");
    
    // BLT
    spu.cpu.pc = old_pc;
    set_reg(spu, 1, 5);
    set_reg(spu, 2, 10);
    insn = make_insn(BLT, 1, 2, 8);
    execute(spu, insn);
    SOFT_ASSERT_EQ(spu.cpu.pc, old_pc + 16, "BLT");
    
    // BGE
    spu.cpu.pc = old_pc;
    set_reg(spu, 1, 10);
    set_reg(spu, 2, 5);
    insn = make_insn(BGE, 1, 2, 8);
    execute(spu, insn);
    SOFT_ASSERT_EQ(spu.cpu.pc, old_pc + 16, "BGE");
    
    // BLTU
    spu.cpu.pc = old_pc;
    set_reg(spu, 1, (uint32_t)-1);  // 0xFFFFFFFF
    set_reg(spu, 2, 10);
    insn = make_insn(BLTU, 1, 2, 8);
    execute(spu, insn);
    SOFT_ASSERT_EQ(spu.cpu.pc, old_pc, "BLTU not taken");
    
    // BGEU
    spu.cpu.pc = old_pc;
    set_reg(spu, 1, (uint32_t)-1);
    set_reg(spu, 2, 10);
    insn = make_insn(BGEU, 1, 2, 8);
    execute(spu, insn);
    SOFT_ASSERT_EQ(spu.cpu.pc, old_pc + 16, "BGEU taken");
}

// ============================================================================
// Тесты для Jump инструкций
// ============================================================================

void test_jal(SPU& spu) {
    reset_cpu(spu);
    std::cout << "\n=== Testing JAL ===" << std::endl;
    
    spu.cpu.pc = 0x1000;
    
    // JAL без сохранения (rd = x0)
    Instruction insn = make_insn(JAL, 0, 20, 0);  // pc += 20
    execute(spu, insn);
    SOFT_ASSERT_EQ(spu.cpu.pc, 0x1000 + 40, "JAL without link");
    
    // JAL с сохранением
    spu.cpu.pc = 0x1000;
    insn = make_insn(JAL, 1, 8, 0);  // x1 = pc+4, pc += 8
    execute(spu, insn);
    SOFT_ASSERT_EQ(get_reg(spu, 1), 0x1000 + 4, "JAL link register");
    SOFT_ASSERT_EQ(spu.cpu.pc, 0x1000 + 16, "JAL with link");
}

void test_jalr(SPU& spu) {
    reset_cpu(spu);
    std::cout << "\n=== Testing JALR ===" << std::endl;
    
    spu.cpu.pc = 0x1000;
    set_reg(spu, 2, 0x2000);
    
    // JALR x1, x2, 8: x1 = pc+4, pc = x2 + 8
    Instruction insn = make_insn(JALR, 1, 2, 8);
    execute(spu, insn);
    
    SOFT_ASSERT_EQ(get_reg(spu, 1), 0x1000 + 4, "JALR link register");
    SOFT_ASSERT_EQ(spu.cpu.pc, 0x2008, "JALR target");
}

// ============================================================================
// Main test runner
// ============================================================================

int main() {
    SPU spu;
    
    std::cout << "\n========================================" << std::endl;
    std::cout << "RISC-V Execute Stage Tests (Soft Assert)" << std::endl;
    std::cout << "========================================\n" << std::endl;
    
    // R-type
    test_add(spu);
    test_sub(spu);
    test_xor(spu);
    test_or(spu);
    test_and(spu);
    test_sll(spu);
    test_srl(spu);
    test_sra(spu);
    test_slt(spu);
    test_sltu(spu);
    
    // I-type
    test_addi(spu);
    test_xori(spu);
    test_ori(spu);
    test_andi(spu);
    test_slli(spu);
    test_srli(spu);
    test_srai(spu);
    test_slti(spu);
    test_sltiu(spu);
    
    // M-extension
    test_mul(spu);
    test_mulh(spu);
    test_div(spu);
    test_divu(spu);
    test_rem(spu);
    test_remu(spu);
    
    // Load/Store
    test_lb_lbu_sb(spu);
    test_lh_lhu_sh(spu);
    test_lw_sw(spu);
    
    // U-type
    test_lui(spu);
    test_auipc(spu);
    
    // Branch
    test_branch(spu);
    
    // Jump
    test_jal(spu);
    test_jalr(spu);
    
    std::cout << "\n========================================" << std::endl;
    stats.print_summary();
    std::cout << "========================================\n" << std::endl;
    
    return stats.failed == 0 ? 0 : 1;
}