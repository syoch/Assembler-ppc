#include <asm.h>
#include <strutil.h>

void split_lines(std::wstring source, std::vector<std::wstring> &dest)
{
    std::wstring buffer;
    for (auto ch : source)
    {
        if (ch == '\n')
        {
            dest.emplace_back(buffer);
            buffer.clear();
        }
        else
        {
            buffer += ch;
        }
    }
}
void split_args(std::wstring source, std::vector<std::wstring> &dest)
{
    std::wstring buffer;
    for (auto ch : source)
    {
        if (ch == ',')
        {
            dest.emplace_back(buffer);
            buffer.clear();
        }
        else if (ch == ' ')
        {
        }
        else
        {
            buffer += ch;
        }
    }
    if (!buffer.empty())
    {
        dest.emplace_back(buffer);
    }
}
#include <iostream>
std::vector<Inst> Assembler::PPC(std::wstring source)
{
    std::vector<std::wstring> lines;
    split_lines(source, lines);

    // remove comments
    for (auto iter = lines.begin(); iter != lines.end();)
    {
        if ((*iter)[0] == '#')
        {
            iter = lines.erase(iter);
        }
        else
        {
            ++iter;
        }
    }

    uint32_t ip = 0; // Instruction pointer.

    // get all label (& remove)
    std::vector<Inst> mCode;
    for (auto iter = lines.begin(); iter != lines.end();)
    {
        const auto line = *iter;
        if (line[line.length() - 1] == ':')
        {
            labels[line.substr(0, line.length() - 1)] = ip;
            iter = lines.erase(iter);
        }
        else
        {
            ip += 4;
            ++iter;
        }
    }
    ip = 0;
    std::wcout << std::hex;
    for (auto line : lines)
    {
        std::wstring mnemonic = line.substr(0, line.find(L' '));
        std::wstring _arguments = line.substr(line.find(' ') + 1);
        std::vector<std::wstring> arguments;
        split_args(_arguments, arguments);
        if (mnemonic == L"li")
        {
            std::wcout << li(arguments) << std::endl;
        }
        else if (mnemonic == L"stwu")
        {
            std::wcout << stwu(arguments) << std::endl;
        }
        else if (mnemonic == L"mflr")
        {
            std::wcout << line << std::endl;
            std::wcout << mflr(arguments) << std::endl;
        }
        else if (mnemonic == L"stw")
        {
            std::wcout << stw(arguments) << std::endl;
        }
        else if (mnemonic == L"lwz")
        {
            std::wcout << lwz(arguments) << std::endl;
        }
        else
        {
            std::wcout << "Not Defined:" << mnemonic << std::endl;
        }
    }
    return mCode;
}
Inst Assembler::li(std::vector<std::wstring> args)
{
    auto regno = util::_toInt(args[0].substr(1));
    auto value = util::_toInt(args[1]);
    return 14 << (16 + 5 + 5) |
           regno << (16 + 5) |
           value;
}
Inst Assembler::stwu(std::vector<std::wstring> args)
{
    auto regno = util::_toInt(args[0].substr(1));
    uint16_t imm = util::_toInt(args[1].substr(0, args[1].find(L'(')));
    auto srcRegno = util::_toInt(args[1].substr(args[1].find(L'(') + 2, args[1].find(L')') - args[1].find(L'(') - 2));
    return 37 << (16 + 5 + 5) |
           regno << (16 + 5) |
           srcRegno << (16) |
           imm;
}
Inst Assembler::mflr(std::vector<std::wstring> args)
{
    auto regno = util::_toInt(args[0].substr(1));
    return 0x7c0802a6 |
           regno << 21;
}
Inst Assembler::stw(std::vector<std::wstring> args)
{
    auto regno = util::_toInt(args[0].substr(1));
    uint16_t imm = util::_toInt(args[1].substr(0, args[1].find(L'(')));
    auto srcRegno = util::_toInt(args[1].substr(args[1].find(L'(') + 2, args[1].find(L')') - args[1].find(L'(') - 2));
    return 36 << (16 + 5 + 5) |
           regno << (16 + 5) |
           srcRegno << (16) |
           imm;
}
Inst Assembler::lwz(std::vector<std::wstring> args)
{
    auto regno = util::_toInt(args[0].substr(1));
    uint16_t imm = util::_toInt(args[1].substr(0, args[1].find(L'(')));
    auto srcRegno = util::_toInt(args[1].substr(args[1].find(L'(') + 2, args[1].find(L')') - args[1].find(L'(') - 2));
    return 32 << (16 + 5 + 5) |
           regno << (16 + 5) |
           srcRegno << (16) |
           imm;
}