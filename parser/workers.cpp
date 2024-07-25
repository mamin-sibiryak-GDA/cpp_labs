#include "workers.h"

bool worker::is_input() const
{
    return input;
}

bool worker::is_output() const
{
    return output;
}

readfile::readfile(const std::string& argv): worker()
{
    input = false;
    output = true;
    int i = 0;
    filename.clear();
    for (; argv[i] == ' ' && i < argv.size(); i++);
    if (i == argv.size())
        throw too_few_args("readfile");
    for (; argv[i] != ' ' && i < argv.size(); i++)
        filename += argv[i];
    if (i < argv.size())
        throw too_much_args("readfile");
}

void readfile::execute(std::vector<std::string>& text)
{
    std::ifstream in(filename);
    while (!in.eof())
    {
        std::string buf;
        std::getline(in, buf);
        text.push_back(buf);
    }
    in.close();
}

writefile::writefile(const std::string& argv): worker()
{
    input = true;
    output = false;
    int i = 0;
    filename.clear();
    for (; argv[i] == ' ' && i < argv.size(); i++);
    if (i == argv.size())
        throw too_few_args("writefile");
    for (; argv[i] != ' ' && i < argv.size(); i++)
        filename += argv[i];
    if (i < argv.size())
        throw too_much_args("writefile");
}

void writefile::execute(std::vector<std::string>& text)
{
    std::ofstream out(filename);
    for (auto& str: text)
        out << str << '\n';
    text.clear();
    out.close();
}

grep::grep(const std::string& argv): worker()
{
    input = true;
    output = true;
    int i = 0;
    word.clear();
    for (; argv[i] == ' ' && i < argv.size(); i++);
    if (i == argv.size())
        throw too_few_args("grep");
    for (; argv[i] != ' ' && i < argv.size(); i++)
        word += argv[i];
    if (i < argv.size())
        throw too_much_args("grep");
}

void grep::execute(std::vector<std::string>& text)
{
    std::vector<std::string> res;
    std::regex reg("(.*)" + word + "(.*)");
    std::smatch match_str;
    for (auto const& str: text)
        if (std::regex_search(str, match_str, reg))
            res.push_back(match_str.str(0));
    text.clear();
    text = res;
}

sort::sort(const std::string& argv)
{
    input = true;
    output = true;
}

void sort::execute(std::vector<std::string>& text)
{
    std::sort(text.begin(), text.end());
}

replace::replace(const std::string& argv)
{
    input = true;
    output = true;
    int i = 0;
    word1.clear();
    for (; argv[i] == ' ' && i < argv.size(); i++);
    if (i == argv.size())
        throw too_few_args("replace");
    for (; argv[i] != ' ' && i < argv.size(); i++)
        word1 += argv[i];
    word2.clear();
    for (; argv[i] == ' ' && i < argv.size(); i++);
    if (i == argv.size())
        throw too_few_args("replace");
    for (; argv[i] != ' ' && i < argv.size(); i++)
        word2 += argv[i];
    if (i < argv.size())
        throw too_much_args("replace");
}

void replace::execute(std::vector<std::string>& text)
{
    std::regex reg(word1);
    for (auto& str: text)
        str = std::regex_replace(str, reg, word2);
}

dump::dump(const std::string& argv)
{
    input = true;
    output = true;
    int i = 0;
    filename.clear();
    for (; argv[i] == ' ' && i < argv.size(); i++);
    if (i == argv.size())
        throw too_few_args("dump");
    for (; argv[i] != ' ' && i < argv.size(); i++)
        filename += argv[i];
    if (i < argv.size())
        throw too_much_args("dump");
}

void dump::execute(std::vector<std::string>& text)
{
    std::ofstream out(filename);
    for (auto& str: text)
        out << str << '\n';
    out.close();
}
