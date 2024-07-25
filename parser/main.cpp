#include <iostream>
#include <vector>
#include <string>

#include "parser.h"

int main()
{
    setlocale(LC_ALL, "Russian");
    std::vector<std::string> text;
    try
    {
        parser p(R"(C:\Users\User\Desktop\labs2\lab2\testing_files\workflow.txt)");
        p.parse();
        auto sequence = p.get_sequence();
        auto blocks = p.get_blocks();
        for (auto id: sequence)
            blocks[id]->execute(text);
    }
    catch (std::exception& exp)
    {
        std::cerr << exp.what();
    }
    return 0;
}
