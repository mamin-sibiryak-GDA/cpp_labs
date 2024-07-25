#include "parser.h"

parser::parser(const char* filename)
{
    fin.open(filename);
    if (!fin)
        throw file_open_error();
    readfile_factory_units = new readfile_factory;
    writefile_factory_units = new writefile_factory;
    grep_factory_units = new grep_factory;
    sort_factory_units = new sort_factory;
    replace_factory_units = new replace_factory;
    dump_factory_units = new dump_factory;
}

std::vector<int> parser::get_sequence()
{
    return command_sequence;
}

std::map<int, worker*> parser::get_blocks()
{
    return blocks;
}

std::vector<std::string> parser::parse_block(const std::string& buffer)
{
    std::vector<std::string> res(3);
    int i = 0;
    for (; buffer[i] == ' ' && i < buffer.size(); i++);
    if (i == buffer.size())
        throw description_block_error();
    res[0].clear();
    for (; std::isdigit(buffer[i]) && i < buffer.size(); i++)
        res[0] += buffer[i];
    if (i < buffer.size() - 3 && buffer[i] == ' ' && buffer[i + 1] == '='
        && buffer[i + 2] == ' ')
        i += 3;
    else
        throw description_block_error();
    res[1].clear();
    for (; buffer[i] != ' ' && i < buffer.size(); i++)
        res[1] += buffer[i];
    for (; buffer[i] == ' ' && i < buffer.size(); i++);
    res[2] = buffer.substr(i);
    return res;
}

std::vector<int> parser::parse_sequence(const std::string& buffer)
{
    std::vector<int> res;
    int i = 0;
    bool prevOut = false;
    for (; buffer[i] == ' ' && i < buffer.size(); i++);
    if (i == buffer.size())
        throw description_sequence_error("1");
    while (i < buffer.size())
    {
        if (!std::isdigit(buffer[i]))
            throw description_sequence_error("2");
        int blockNum = 0;
        for (; std::isdigit(buffer[i]) && i < buffer.size(); i++)
            blockNum = blockNum * 10 + buffer[i] - '0';
        if (blocks[blockNum]->is_input() == prevOut)
            prevOut = blocks[blockNum]->is_output();
        else
            throw description_sequence_error("3");
        res.push_back(blockNum);
        if (i < buffer.size() - 4 && buffer[i] == ' ' && buffer[i + 1] == '-'
            && buffer[i + 2] == '>' && buffer[i + 3] == ' ')
            i += 4;
        else if (i < buffer.size())
            throw description_sequence_error("4");
    }
    return res;
}

void parser::parse()
{
    parser_state state = wait;
    while (!fin.eof())
    {
        std::getline(fin, buffer);
        if (state == wait)
        {
            if (buffer.substr(0, 4) == "desc")
            {
                state = open;
                continue;
            }
            else
                throw file_beginning_error();
        }
        if (state == open)
        {
            if (buffer == "csed")
            {
                state = close;
                continue;
            }
            else
            {
                std::vector<std::string> block = parse_block(buffer);
                int number = std::stoi(block[0]);
                if (block[1] == "readfile")
                    blocks[number] = make_worker(readfile_factory_units, block[2]);
                else if (block[1] == "writefile")
                    blocks[number] = make_worker(writefile_factory_units, block[2]);
                else if (block[1] == "grep")
                    blocks[number] = make_worker(grep_factory_units, block[2]);
                else if (block[1] == "sort")
                    blocks[number] = make_worker(sort_factory_units, block[2]);
                else if (block[1] == "replace")
                    blocks[number] = make_worker(replace_factory_units, block[2]);
                else if (block[1] == "dump")
                    blocks[number] = make_worker(dump_factory_units, block[2]);
                else
                    throw unknown_worker();
            }
        }
        if (state == close)
        {
            state = end;
            command_sequence = parse_sequence(buffer);
        }
    }
    if (state != end)
        throw delimiter_error();
    fin.close();
}
