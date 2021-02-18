#include <asm.h>
#include <iostream>

int main(int argc, char const *argv[])
{
    Assembler assembler;
    auto mCode = assembler.PPC(
        std::wstring(
            L""
            "stwu r1, -32(r1)\n"
            "mflr r0\n"
            "stw r0, 36(r1)\n"
            "stw r13, 28(r1)\n"
            "stw r14, 24(r1)\n"
            "stw r15, 20(r1)\n"
            "bl str_0\n"
            ".word 34\n"
            ".word 104\n"
            ".word 105\n"
            ".word 34\n"
            "str_0:\n"
            "mflr r14\n"
            "stw r14, 16(r1)\n"
            "lwz r14, 24(r1)\n"
            "lwz r15, 20(r1)\n"
            "__ret:\n"
            "lwz r0, 36(r1)\n"
            "lwz r13, 28(r1)\n"
            "mtlr r0\n"
            "addi r1, r1, 32\n"
            "blr\n"));
    bool flag = false;
    std::wcout << std::hex;
    for (auto inst : mCode)
    {
        std::wcout << inst;
        std::wcout << (flag ? '\n' : ' ');
        flag ^= 1;
    }
    return 0;
}
