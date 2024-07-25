#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <regex>
#include <algorithm>

#include "exceptions.h"

class worker
{
protected:
    bool input;
    bool output;
public:
    virtual void execute(std::vector<std::string>& text) = 0;

    bool is_input() const;

    bool is_output() const;
};

class readfile: public worker
{
private:
    std::string filename;
public:
    explicit readfile(const std::string& argv);

    void execute(std::vector<std::string>& text) override;
};

class writefile: public worker
{
private:
    std::string filename;
public:
    explicit writefile(const std::string& argv);

    void execute(std::vector<std::string>& text) override;
};

class grep: public worker
{
private:
    std::string word;
public:
    explicit grep(const std::string& argv);

    void execute(std::vector<std::string>& text) override;
};

class sort: public worker
{
public:
    explicit sort(const std::string& argv);

    void execute(std::vector<std::string>& text) override;
};

class replace: public worker
{
private:
    std::string word1, word2;
public:
    explicit replace(const std::string& argv);

    void execute(std::vector<std::string>& text) override;
};

class dump: public worker
{
private:
    std::string filename;
public:
    explicit dump(const std::string& argv);

    void execute(std::vector<std::string>& text) override;
};
