// test_decoder.cpp
#include <iostream>
#include <cassert>
#include <iomanip>
#include <vector>
#include <map>
#include "../generated/decode.h"

// Mock SPU для тестирования
class SPU {
public:
    // Минимальная реализация для тестов
};

// Вспомогательная функция для создания инструкции
Register make_insn(uint32_t opcode, uint32_t rd = 0, uint32_t rs1 = 0, 
                   uint32_t rs2 = 0, uint32_t funct3 = 0, uint32_t funct7 = 0,
                   uint32_t imm = 0) {
    Register insn = 0;
    insn |= (opcode & 0x7F) << 0;
    insn |= (rd & 0x1F) << 7;
    insn |= (funct3 & 0x7) << 12;
    insn |= (rs1 & 0x1F) << 15;
    insn |= (rs2 & 0x1F) << 20;
    insn |= (funct7 & 0x7F) << 25;
    
    // Для I-type immediate
    if (imm != 0) {
        insn |= ((imm >> 0) & 0xFFF) << 20;
        insn |= ((imm >> 11) & 0x1) << 31;
    }
    
    return insn;
}

// Для S-type immediate
Register make_s_insn(uint32_t opcode, uint32_t rs1, uint32_t rs2, 
                     uint32_t funct3, int32_t imm) {
    Register insn = 0;
    insn |= (opcode & 0x7F) << 0;
    insn |= ((imm >> 5) & 0x7F) << 25;
    insn |= (rs2 & 0x1F) << 20;
    insn |= (rs1 & 0x1F) << 15;
    insn |= (funct3 & 0x7) << 12;
    insn |= ((imm >> 0) & 0x1F) << 7;
    return insn;
}

// Для B-type immediate
Register make_b_insn(uint32_t opcode, uint32_t rs1, uint32_t rs2, 
                     uint32_t funct3, int32_t imm) {
    Register insn = 0;
    insn |= (opcode & 0x7F) << 0;
    insn |= ((imm >> 11) & 0x1) << 7;
    insn |= ((imm >> 1) & 0xF) << 8;
    insn |= (funct3 & 0x7) << 12;
    insn |= (rs1 & 0x1F) << 15;
    insn |= (rs2 & 0x1F) << 20;
    insn |= ((imm >> 5) & 0x3F) << 25;
    insn |= ((imm >> 12) & 0x1) << 31;
    return insn;
}

// Для U-type immediate
Register make_u_insn(uint32_t opcode, uint32_t rd, uint32_t imm) {
    Register insn = 0;
    insn |= (opcode & 0x7F) << 0;
    insn |= (rd & 0x1F) << 7;
    insn |= (imm & 0xFFFFF) << 12;
    return insn;
}

// Для J-type immediate
Register make_j_insn(uint32_t opcode, uint32_t rd, int32_t imm) {
    Register insn = 0;
    insn |= (opcode & 0x7F) << 0;
    insn |= (rd & 0x1F) << 7;
    insn |= ((imm >> 12) & 0xFF) << 12;
    insn |= ((imm >> 11) & 0x1) << 20;
    insn |= ((imm >> 1) & 0x3FF) << 21;
    insn |= ((imm >> 20) & 0x1) << 31;
    return insn;
}

// Структура для хранения результата теста
struct TestResult {
    std::string name;
    bool passed;
    std::string error_message;
    uint32_t insn_value;
};

std::vector<TestResult> test_results;

void print_test_result(const std::string& test_name, bool passed, 
                       const std::string& error_msg = "", uint32_t insn_val = 0) {
    test_results.push_back({test_name, passed, error_msg, insn_val});
}

// Обертка для безопасного вызова decode
bool safe_decode(SPU& spu, Register insn, Instruction& result, std::string& error_msg) {
    try {
        result = decode(spu, insn);
        return true;
    } catch (const std::runtime_error& e) {
        error_msg = e.what();
        return false;
    } catch (const std::exception& e) {
        error_msg = e.what();
        return false;
    } catch (...) {
        error_msg = "Unknown exception";
        return false;
    }
}

void test_load_instructions() {
    SPU spu;
    std::string error;
    Instruction decoded;
    
    // LB
    {
        Register insn = make_insn(0x3, 0x5, 0x6, 0, 0x0, 0, 0x7F);
        bool ok = safe_decode(spu, insn, decoded, error);
        bool passed = ok && 
                     (decoded.insn_type == LB) && 
                     (decoded.oprnds.arg1 == 0x5) &&
                     (decoded.oprnds.arg2 == 0x6) &&
                     (decoded.oprnds.arg3 == 0x7F);
        print_test_result("LB", passed, error, insn);
    }
    
    // LH
    {
        Register insn = make_insn(0x3, 0x5, 0x6, 0, 0x1, 0, 0x7F);
        bool ok = safe_decode(spu, insn, decoded, error);
        bool passed = ok && (decoded.insn_type == LH);
        print_test_result("LH", passed, error, insn);
    }
    
    // LW
    {
        Register insn = make_insn(0x3, 0x5, 0x6, 0, 0x2, 0, 0x7F);
        bool ok = safe_decode(spu, insn, decoded, error);
        bool passed = ok && (decoded.insn_type == LW);
        print_test_result("LW", passed, error, insn);
    }
    
    // LBU
    {
        Register insn = make_insn(0x3, 0x5, 0x6, 0, 0x4, 0, 0x7F);
        bool ok = safe_decode(spu, insn, decoded, error);
        bool passed = ok && (decoded.insn_type == LBU);
        print_test_result("LBU", passed, error, insn);
    }
    
    // LHU
    {
        Register insn = make_insn(0x3, 0x5, 0x6, 0, 0x5, 0, 0x7F);
        bool ok = safe_decode(spu, insn, decoded, error);
        bool passed = ok && (decoded.insn_type == LHU);
        print_test_result("LHU", passed, error, insn);
    }
}

void test_itype_alu_instructions() {
    SPU spu;
    std::string error;
    Instruction decoded;
    
    // ADDI
    {
        Register insn = make_insn(0x13, 0x5, 0x6, 0, 0x0, 0, 0x7F);
        bool ok = safe_decode(spu, insn, decoded, error);
        bool passed = ok && (decoded.insn_type == ADDI);
        print_test_result("ADDI", passed, error, insn);
    }
    
    // SLTI
    {
        Register insn = make_insn(0x13, 0x5, 0x6, 0, 0x2, 0, 0x7F);
        bool ok = safe_decode(spu, insn, decoded, error);
        bool passed = ok && (decoded.insn_type == SLTI);
        print_test_result("SLTI", passed, error, insn);
    }
    
    // SLTIU
    {
        Register insn = make_insn(0x13, 0x5, 0x6, 0, 0x3, 0, 0x7F);
        bool ok = safe_decode(spu, insn, decoded, error);
        bool passed = ok && (decoded.insn_type == SLTIU);
        print_test_result("SLTIU", passed, error, insn);
    }
    
    // XORI
    {
        Register insn = make_insn(0x13, 0x5, 0x6, 0, 0x4, 0, 0x7F);
        bool ok = safe_decode(spu, insn, decoded, error);
        bool passed = ok && (decoded.insn_type == XORI);
        print_test_result("XORI", passed, error, insn);
    }
    
    // ORI
    {
        Register insn = make_insn(0x13, 0x5, 0x6, 0, 0x6, 0, 0x7F);
        bool ok = safe_decode(spu, insn, decoded, error);
        bool passed = ok && (decoded.insn_type == ORI);
        print_test_result("ORI", passed, error, insn);
    }
    
    // ANDI
    {
        Register insn = make_insn(0x13, 0x5, 0x6, 0, 0x7, 0, 0x7F);
        bool ok = safe_decode(spu, insn, decoded, error);
        bool passed = ok && (decoded.insn_type == ANDI);
        print_test_result("ANDI", passed, error, insn);
    }
    
    // SLLI
    {
        Register insn = make_insn(0x13, 0x5, 0x6, 0, 0x1, 0, 0);
        insn |= (0x1F & 0x1F) << 20;
        bool ok = safe_decode(spu, insn, decoded, error);
        bool passed = ok && (decoded.insn_type == SLLI);
        print_test_result("SLLI", passed, error, insn);
    }
    
    // SRLI
    {
        Register insn = make_insn(0x13, 0x5, 0x6, 0, 0x5, 0, 0);
        insn |= (0x1F & 0x1F) << 20;
        bool ok = safe_decode(spu, insn, decoded, error);
        bool passed = ok && (decoded.insn_type == SRLI);
        print_test_result("SRLI", passed, error, insn);
    }
    
    // SRAI
    {
        Register insn = make_insn(0x13, 0x5, 0x6, 0, 0x5, 0x20, 0);
        insn |= (0x1F & 0x1F) << 20;
        bool ok = safe_decode(spu, insn, decoded, error);
        bool passed = ok && (decoded.insn_type == SRAI);
        print_test_result("SRAI", passed, error, insn);
    }
}

void test_stype_instructions() {
    SPU spu;
    std::string error;
    Instruction decoded;
    int32_t imm = 0x7F;
    
    // SB
    {
        Register insn = make_s_insn(0x23, 0x6, 0x7, 0x0, imm);
        bool ok = safe_decode(spu, insn, decoded, error);
        bool passed = ok && (decoded.insn_type == SB);
        print_test_result("SB", passed, error, insn);
    }
    
    // SH
    {
        Register insn = make_s_insn(0x23, 0x6, 0x7, 0x1, imm);
        bool ok = safe_decode(spu, insn, decoded, error);
        bool passed = ok && (decoded.insn_type == SH);
        print_test_result("SH", passed, error, insn);
    }
    
    // SW
    {
        Register insn = make_s_insn(0x23, 0x6, 0x7, 0x2, imm);
        bool ok = safe_decode(spu, insn, decoded, error);
        bool passed = ok && (decoded.insn_type == SW);
        print_test_result("SW", passed, error, insn);
    }
}

void test_rtype_instructions() {
    SPU spu;
    std::string error;
    Instruction decoded;
    
    // ADD
    {
        Register insn = make_insn(0x33, 0x5, 0x6, 0x7, 0x0, 0x0);
        bool ok = safe_decode(spu, insn, decoded, error);
        bool passed = ok && (decoded.insn_type == ADD);
        print_test_result("ADD", passed, error, insn);
    }
    
    // SUB
    {
        Register insn = make_insn(0x33, 0x5, 0x6, 0x7, 0x0, 0x20);
        bool ok = safe_decode(spu, insn, decoded, error);
        bool passed = ok && (decoded.insn_type == SUB);
        print_test_result("SUB", passed, error, insn);
    }
    
    // SLL
    {
        Register insn = make_insn(0x33, 0x5, 0x6, 0x7, 0x1, 0x0);
        bool ok = safe_decode(spu, insn, decoded, error);
        bool passed = ok && (decoded.insn_type == SLL);
        print_test_result("SLL", passed, error, insn);
    }
    
    // SLT
    {
        Register insn = make_insn(0x33, 0x5, 0x6, 0x7, 0x2, 0x0);
        bool ok = safe_decode(spu, insn, decoded, error);
        bool passed = ok && (decoded.insn_type == SLT);
        print_test_result("SLT", passed, error, insn);
    }
    
    // SLTU
    {
        Register insn = make_insn(0x33, 0x5, 0x6, 0x7, 0x3, 0x0);
        bool ok = safe_decode(spu, insn, decoded, error);
        bool passed = ok && (decoded.insn_type == SLTU);
        print_test_result("SLTU", passed, error, insn);
    }
    
    // XOR
    {
        Register insn = make_insn(0x33, 0x5, 0x6, 0x7, 0x4, 0x0);
        bool ok = safe_decode(spu, insn, decoded, error);
        bool passed = ok && (decoded.insn_type == XOR);
        print_test_result("XOR", passed, error, insn);
    }
    
    // SRL
    {
        Register insn = make_insn(0x33, 0x5, 0x6, 0x7, 0x5, 0x0);
        bool ok = safe_decode(spu, insn, decoded, error);
        bool passed = ok && (decoded.insn_type == SRL);
        print_test_result("SRL", passed, error, insn);
    }
    
    // SRA
    {
        Register insn = make_insn(0x33, 0x5, 0x6, 0x7, 0x5, 0x20);
        bool ok = safe_decode(spu, insn, decoded, error);
        bool passed = ok && (decoded.insn_type == SRA);
        print_test_result("SRA", passed, error, insn);
    }
    
    // OR
    {
        Register insn = make_insn(0x33, 0x5, 0x6, 0x7, 0x6, 0x0);
        bool ok = safe_decode(spu, insn, decoded, error);
        bool passed = ok && (decoded.insn_type == OR);
        print_test_result("OR", passed, error, insn);
    }
    
    // AND
    {
        Register insn = make_insn(0x33, 0x5, 0x6, 0x7, 0x7, 0x0);
        bool ok = safe_decode(spu, insn, decoded, error);
        bool passed = ok && (decoded.insn_type == AND);
        print_test_result("AND", passed, error, insn);
    }
}

void test_m_extension_instructions() {
    SPU spu;
    std::string error;
    Instruction decoded;
    
    // MUL
    {
        Register insn = make_insn(0x33, 0x5, 0x6, 0x7, 0x0, 0x1);
        bool ok = safe_decode(spu, insn, decoded, error);
        bool passed = ok && (decoded.insn_type == MUL);
        print_test_result("MUL", passed, error, insn);
    }
    
    // MULH
    {
        Register insn = make_insn(0x33, 0x5, 0x6, 0x7, 0x1, 0x1);
        bool ok = safe_decode(spu, insn, decoded, error);
        bool passed = ok && (decoded.insn_type == MULH);
        print_test_result("MULH", passed, error, insn);
    }
    
    // MULHSU
    {
        Register insn = make_insn(0x33, 0x5, 0x6, 0x7, 0x2, 0x1);
        bool ok = safe_decode(spu, insn, decoded, error);
        bool passed = ok && (decoded.insn_type == MULHSU);
        print_test_result("MULHSU", passed, error, insn);
    }
    
    // MULHU
    {
        Register insn = make_insn(0x33, 0x5, 0x6, 0x7, 0x3, 0x1);
        bool ok = safe_decode(spu, insn, decoded, error);
        bool passed = ok && (decoded.insn_type == MULHU);
        print_test_result("MULHU", passed, error, insn);
    }
    
    // DIV
    {
        Register insn = make_insn(0x33, 0x5, 0x6, 0x7, 0x4, 0x1);
        bool ok = safe_decode(spu, insn, decoded, error);
        bool passed = ok && (decoded.insn_type == DIV);
        print_test_result("DIV", passed, error, insn);
    }
    
    // DIVU
    {
        Register insn = make_insn(0x33, 0x5, 0x6, 0x7, 0x5, 0x1);
        bool ok = safe_decode(spu, insn, decoded, error);
        bool passed = ok && (decoded.insn_type == DIVU);
        print_test_result("DIVU", passed, error, insn);
    }
    
    // REM
    {
        Register insn = make_insn(0x33, 0x5, 0x6, 0x7, 0x6, 0x1);
        bool ok = safe_decode(spu, insn, decoded, error);
        bool passed = ok && (decoded.insn_type == REM);
        print_test_result("REM", passed, error, insn);
    }
    
    // REMU
    {
        Register insn = make_insn(0x33, 0x5, 0x6, 0x7, 0x7, 0x1);
        bool ok = safe_decode(spu, insn, decoded, error);
        bool passed = ok && (decoded.insn_type == REMU);
        print_test_result("REMU", passed, error, insn);
    }
}

void test_btype_instructions() {
    SPU spu;
    std::string error;
    Instruction decoded;
    int32_t imm = 0x7FF;
    
    // BEQ
    {
        Register insn = make_b_insn(0x63, 0x6, 0x7, 0x0, imm);
        bool ok = safe_decode(spu, insn, decoded, error);
        bool passed = ok && (decoded.insn_type == BEQ);
        print_test_result("BEQ", passed, error, insn);
    }
    
    // BNE
    {
        Register insn = make_b_insn(0x63, 0x6, 0x7, 0x1, imm);
        bool ok = safe_decode(spu, insn, decoded, error);
        bool passed = ok && (decoded.insn_type == BNE);
        print_test_result("BNE", passed, error, insn);
    }
    
    // BLT
    {
        Register insn = make_b_insn(0x63, 0x6, 0x7, 0x4, imm);
        bool ok = safe_decode(spu, insn, decoded, error);
        bool passed = ok && (decoded.insn_type == BLT);
        print_test_result("BLT", passed, error, insn);
    }
    
    // BGE
    {
        Register insn = make_b_insn(0x63, 0x6, 0x7, 0x5, imm);
        bool ok = safe_decode(spu, insn, decoded, error);
        bool passed = ok && (decoded.insn_type == BGE);
        print_test_result("BGE", passed, error, insn);
    }
    
    // BLTU
    {
        Register insn = make_b_insn(0x63, 0x6, 0x7, 0x6, imm);
        bool ok = safe_decode(spu, insn, decoded, error);
        bool passed = ok && (decoded.insn_type == BLTU);
        print_test_result("BLTU", passed, error, insn);
    }
    
    // BGEU
    {
        Register insn = make_b_insn(0x63, 0x6, 0x7, 0x7, imm);
        bool ok = safe_decode(spu, insn, decoded, error);
        bool passed = ok && (decoded.insn_type == BGEU);
        print_test_result("BGEU", passed, error, insn);
    }
}

void test_utype_instructions() {
    SPU spu;
    std::string error;
    Instruction decoded;
    
    // LUI
    {
        Register insn = make_u_insn(0x37, 0x5, 0x12345);
        bool ok = safe_decode(spu, insn, decoded, error);
        bool passed = ok && (decoded.insn_type == LUI);
        print_test_result("LUI", passed, error, insn);
    }
    
    // AUIPC
    {
        Register insn = make_u_insn(0x17, 0x5, 0x12345);
        bool ok = safe_decode(spu, insn, decoded, error);
        bool passed = ok && (decoded.insn_type == AUIPC);
        print_test_result("AUIPC", passed, error, insn);
    }
}

void test_jtype_instructions() {
    SPU spu;
    std::string error;
    Instruction decoded;
    
    // JAL
    {
        Register insn = make_j_insn(0x6F, 0x5, 0x7FF);
        bool ok = safe_decode(spu, insn, decoded, error);
        bool passed = ok && (decoded.insn_type == JAL);
        print_test_result("JAL", passed, error, insn);
    }
    
    // JALR
    {
        Register insn = make_insn(0x67, 0x5, 0x6, 0, 0x0, 0, 0x7F);
        bool ok = safe_decode(spu, insn, decoded, error);
        bool passed = ok && (decoded.insn_type == JALR);
        print_test_result("JALR", passed, error, insn);
    }
}

void test_unknown_instruction() {
    SPU spu;
    std::string error;
    Instruction decoded;
    
    // Тест 1: полностью невалидная инструкция
    {
        Register insn = 0xFFFFFFFF;
        bool ok = safe_decode(spu, insn, decoded, error);
        bool passed = !ok;  // должно не пройти
        print_test_result("Unknown instruction (all ones)", passed, error, insn);
    }
    
    // Тест 2: несуществующий opcode
    {
        Register insn = make_insn(0x7F, 0, 0, 0, 0, 0, 0);  // opcode 0x7F не существует
        bool ok = safe_decode(spu, insn, decoded, error);
        bool passed = !ok;
        print_test_result("Unknown instruction (invalid opcode)", passed, error, insn);
    }
}

void print_summary() {
    int passed = 0;
    int failed = 0;
    
    std::cout << "\n" << std::string(80, '=') << std::endl;
    std::cout << "TEST SUMMARY" << std::endl;
    std::cout << std::string(80, '=') << std::endl;
    
    for (const auto& result : test_results) {
        if (result.passed) {
            passed++;
        } else {
            failed++;
            std::cout << "\n❌ FAILED: " << result.name << std::endl;
            std::cout << "   Instruction: 0x" << std::hex << std::setw(8) << std::setfill('0') 
                     << result.insn_value << std::dec << std::endl;
            if (!result.error_message.empty()) {
                std::cout << "   Error: " << result.error_message << std::endl;
            }
        }
    }
    
    std::cout << "\n" << std::string(80, '-') << std::endl;
    std::cout << "Total: " << (passed + failed) 
              << " | ✅ PASSED: " << passed 
              << " | ❌ FAILED: " << failed << std::endl;
    std::cout << std::string(80, '=') << "\n" << std::endl;
}

int main() {
    std::cout << "\n=== RISC-V 32IM Decoder Unit Tests ===\n" << std::endl;
    
    std::cout << "--- Load Instructions ---" << std::endl;
    test_load_instructions();
    
    std::cout << "\n--- I-type ALU Instructions ---" << std::endl;
    test_itype_alu_instructions();
    
    std::cout << "\n--- S-type Instructions ---" << std::endl;
    test_stype_instructions();
    
    std::cout << "\n--- R-type Instructions ---" << std::endl;
    test_rtype_instructions();
    
    std::cout << "\n--- M-extension Instructions ---" << std::endl;
    test_m_extension_instructions();
    
    std::cout << "\n--- B-type Instructions ---" << std::endl;
    test_btype_instructions();
    
    std::cout << "\n--- U-type Instructions ---" << std::endl;
    test_utype_instructions();
    
    std::cout << "\n--- J-type Instructions ---" << std::endl;
    test_jtype_instructions();
    
    std::cout << "\n--- Error Handling ---" << std::endl;
    test_unknown_instruction();
    
    print_summary();
    
    return 0;
}