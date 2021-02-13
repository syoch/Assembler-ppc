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

    ip = 0;

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
        else if (mnemonic == L"add")
        {
            std::wcout << add(arguments) << std::endl;
        }
        else if (mnemonic == L"lis")
        {
            std::wcout << lis(arguments) << std::endl;
        }
        else if (mnemonic == L"ori")
        {
            std::wcout << ori(arguments) << std::endl;
        }
        else if (mnemonic == L"mullw")
        {
            std::wcout << mullw(arguments) << std::endl;
        }
        else if (mnemonic == L"divw")
        {
            std::wcout << divw(arguments) << std::endl;
        }
        else if (mnemonic == L"cmplwi")
        {
            std::wcout << cmplwi(arguments) << std::endl;
        }
        else if (mnemonic == L"cmplw")
        {
            std::wcout << cmplw(arguments) << std::endl;
        }
        else if (mnemonic == L"beq")
        {
            std::wcout << beq(arguments) << std::endl;
        }
        else if (mnemonic == L"b")
        {
            std::wcout << b(arguments) << std::endl;
        }
        else if (mnemonic == L"addi")
        {
            std::wcout << addi(arguments) << std::endl;
        }
        else if (mnemonic == L"blt")
        {
            std::wcout << blt(arguments) << std::endl;
        }

        else
        {
            std::wcout << "Not Defined:" << mnemonic << std::endl;
        }
        ip += 4;
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
Inst Assembler::add(std::vector<std::wstring> args)
{
    auto D = util::_toInt(args[0].substr(1));
    auto A = util::_toInt(args[1].substr(1));
    auto B = util::_toInt(args[2].substr(1));
    return 31 << (26) | D << (21) | A << (16) | B << (11) | 0x214;
}
Inst Assembler::lis(std::vector<std::wstring> args)
{
    auto D = util::_toInt(args[0].substr(1));
    auto SIMM = util::_toInt(args[1]);
    return 15 << (26) | D << (21) | SIMM;
}
Inst Assembler::ori(std::vector<std::wstring> args)
{
    auto A = util::_toInt(args[0].substr(1));
    auto S = util::_toInt(args[1].substr(1));
    auto UIMM = util::_toInt(args[2]);
    return 24 << (26) | S << (21) | A << (16) | UIMM;
}
Inst Assembler::mullw(std::vector<std::wstring> args)
{
    auto D = util::_toInt(args[0].substr(1));
    auto A = util::_toInt(args[1].substr(1));
    auto B = util::_toInt(args[2].substr(1));
    return 31 << (26) | D << (21) | A << (16) | B << (11) | 0x1d6;
}
Inst Assembler::divw(std::vector<std::wstring> args)
{
    auto D = util::_toInt(args[0].substr(1));
    auto A = util::_toInt(args[1].substr(1));
    auto B = util::_toInt(args[2].substr(1));
    return 31 << (26) | D << (21) | A << (16) | B << (11) | 0x3d6;
}
Inst Assembler::cmplwi(std::vector<std::wstring> args)
{
    int i = 0;
    int D = 0, A = 0;
    uint16_t UIMM;
    if (args.size() == 3)
    {
        D = util::_toInt(args[i++].substr(2)); // cr<n>
    }
    A = util::_toInt(args[i++].substr(1));
    UIMM = util::_toInt(args[i++]);

    return 10 << (26) | D << (23) | A << (16) | UIMM;
}
Inst Assembler::cmplw(std::vector<std::wstring> args)
{
    int i = 0;
    int D = 0, A = 0;
    uint16_t UIMM;
    if (args.size() == 3)
    {
        D = util::_toInt(args[i++].substr(2)); // cr<n>
    }
    A = util::_toInt(args[i++].substr(1));
    UIMM = util::_toInt(args[i++]);

    return 10 << (26) | D << (23) | A << (16) | UIMM;
}
Inst Assembler::beq(std::vector<std::wstring> args)
{
    return 0x41820000 | (uint16_t)(labels[args[0]] - ip);
}
Inst Assembler::b(std::vector<std::wstring> args)
{
    return 0xf8000000 | (uint16_t)labels[args[0]];
}
Inst Assembler::addi(std::vector<std::wstring> args)
{
    auto D = util::_toInt(args[0].substr(1));
    auto A = util::_toInt(args[1].substr(1));
    auto SIMM = util::_toInt(args[2]);
    return 14 << (26) | D << (21) | A << (16) | SIMM;
}
Inst Assembler::blt(std::vector<std::wstring> args)
{
    return 0x41800000 | (uint16_t)(labels[args[0]] - ip);
}