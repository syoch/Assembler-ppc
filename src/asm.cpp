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
#include <iostream>
std::vector<Assembler::Inst> Assembler::PPC(std::wstring source)
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

    uint32_t ip=0; // Instruction pointer.
    
    // get all label
    std::vector<Inst> mCode;
    for(auto line: lines){
        if(line[line.length()-1]==':'){
            labels[line.substr(0,line.length()-1)]=ip;
        }else{
            ip+=1;
        }
    }
    ip=0;
    
    return mCode;
}