#pragma once
#ifndef ASSMEMBLER_H
#define ASSMEMBLER_H

#include <string>
#include <vector>
#include <map>

using Inst = uint32_t;

class Assembler
{

public:
    std::vector<Inst> PPC(std::wstring source);
    uint32_t getAddr(std::wstring label);

    Inst li(std::vector<std::wstring> args);
    Inst stwu(std::vector<std::wstring> args);
    Inst mflr(std::vector<std::wstring> args);
    Inst stw(std::vector<std::wstring> args);
    Inst lwz(std::vector<std::wstring> args);
    Inst add(std::vector<std::wstring> args);
    Inst lis(std::vector<std::wstring> args);
    Inst ori(std::vector<std::wstring> args);
    Inst mullw(std::vector<std::wstring> args);
    Inst divw(std::vector<std::wstring> args);
    Inst cmplwi(std::vector<std::wstring> args);
    Inst cmplw(std::vector<std::wstring> args);
    Inst beq(std::vector<std::wstring> args);
    Inst b(std::vector<std::wstring> args);
    Inst addi(std::vector<std::wstring> args);
    Inst blt(std::vector<std::wstring> args);
    Inst mtlr(std::vector<std::wstring> args);
    Inst blr(std::vector<std::wstring> args);
    Inst mtctr(std::vector<std::wstring> args);
    Inst bctrl(std::vector<std::wstring> args);
    Inst mr(std::vector<std::wstring> args);
    Inst Or(std::vector<std::wstring> args);

private:
    std::map<std::wstring, uint32_t> labels;
    uint32_t ip;
}; // class Assembler

#endif