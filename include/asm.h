#pragma once
#ifndef ASSMEMBLER_H
#define ASSMEMBLER_H

#include <string>
#include <vector>
#include <map>

class Assembler
{
    using Inst = uint32_t;
    std::vector<Inst> PPC(std::wstring source);

private:
    std::map<std::wstring, uint32_t> labels;
}; // class Assembler

#endif