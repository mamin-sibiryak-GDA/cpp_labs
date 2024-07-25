#include "factories.h"

worker* readfile_factory::create_worker(std::string args)
{
    return new readfile(args);
}

worker* writefile_factory::create_worker(std::string args)
{
    return new writefile(args);
}

worker* grep_factory::create_worker(std::string args)
{
    return new grep(args);
}

worker* sort_factory::create_worker(std::string args)
{
    return new sort(args);
}

worker* replace_factory::create_worker(std::string args)
{
    return new replace(args);
}

worker* dump_factory::create_worker(std::string args)
{
    return new dump(args);
}

worker* make_worker(worker_factory* factory, std::string& args)
{
    return factory->create_worker(args);
}
