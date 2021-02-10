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

private:
    std::map<std::wstring, uint32_t> labels;
}; // class Assembler

#endif