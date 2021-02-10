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

    uint32_t ip=0; // Instruction pointer.
    
    // get all label (& remove)
    std::vector<Inst> mCode;
    for (auto iter = lines.begin(); iter != lines.end();){
        const auto line=*iter;
        if(line[line.length()-1]==':'){
            labels[line.substr(0,line.length()-1)]=ip;
            iter=lines.erase(iter);
        }else{
            ip+=4;
            ++iter;
        }
    }
    ip=0;

    for(auto line: lines){
        std::wstring mnemonic = line.substr(0,line.find(L' '));
        std::wstring _arguments = line.substr(line.find(' ')+1);
        std::vector<std::wstring> arguments;
        if(mnemonic==L"li"){
            li(line);
        }else{
            std::wcout<<"Not Defined:"<<mnemonic<<std::endl;
        }
    }
    return mCode;
}
Inst Assembler::li(std::wstring code){
    std::wcout<<code<<std::endl;
}