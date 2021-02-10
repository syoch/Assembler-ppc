#include <asm.h>

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

std::vector<Assembler::Inst> Assembler::PPC(std::wstring source)
{
    std::vector<std::wstring> lines;
    split_lines(source, lines);
}