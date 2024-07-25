#pragma once

#include <iostream>

#include "workers.h"

class worker_factory
{
public:
    virtual worker* create_worker(std::string args) = 0;
};

class readfile_factory: public worker_factory
{
public:
    worker* create_worker(std::string args) override;
};

class writefile_factory: public worker_factory
{
public:
    worker* create_worker(std::string args) override;
};

class grep_factory: public worker_factory
{
public:
    worker* create_worker(std::string args) override;
};

class sort_factory: public worker_factory
{
public:
    worker* create_worker(std::string args) override;
};

class replace_factory: public worker_factory
{
public:
    worker* create_worker(std::string args) override;
};

class dump_factory: public worker_factory
{
public:
    worker* create_worker(std::string args) override;
};

worker* make_worker(worker_factory* factory, std::string& args);
