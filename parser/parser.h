#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

#include "factories.h"

enum parser_state
{
    wait, open, close, end
};

class parser
{
private:
    std::ifstream fin;
    std::string buffer;
    std::vector<int> command_sequence;
    std::map<int, worker*> blocks;
    readfile_factory* readfile_factory_units;
    writefile_factory* writefile_factory_units;
    grep_factory* grep_factory_units;
    sort_factory* sort_factory_units;
    replace_factory* replace_factory_units;
    dump_factory* dump_factory_units;

    std::vector<std::string> parse_block(const std::string& buffer);

    std::vector<int> parse_sequence(const std::string& buffer);

public:
    explicit parser(const char* filename);

    void parse();

    std::vector<int> get_sequence();

    std::map<int, worker*> get_blocks();
};
