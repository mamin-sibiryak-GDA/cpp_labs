#include "exceptions.h"

too_much_args::too_much_args(const std::string& message)
{
    message_error = "Too mush args for " + message + '\n';
}

const char* too_much_args::what() const noexcept
{
    return message_error.c_str();
}

too_few_args::too_few_args(const std::string& message)
{
    message_error = "Too few args for " + message + '\n';
}

const char* too_few_args::what() const noexcept
{
    return message_error.c_str();
}

file_open_error::file_open_error()
{
    message_error = "File is not opened.\n";
}

const char* file_open_error::what() const noexcept
{
    return message_error.c_str();
}

file_beginning_error::file_beginning_error()
{
    message_error = "File must start with desc!\n";
}

const char* file_beginning_error::what() const noexcept
{
    return message_error.c_str();
}

unknown_worker::unknown_worker()
{
    message_error = "Discover unknown worker\n";
}

const char* unknown_worker::what() const noexcept
{
    return message_error.c_str();
}

delimiter_error::delimiter_error()
{
    message_error = "Delimiter must be csed\n";
}

const char* delimiter_error::what() const noexcept
{
    return message_error.c_str();
}

description_block_error::description_block_error()
{
    message_error = "Block description error\n";
}

const char* description_block_error::what() const noexcept
{
    return message_error.c_str();
}

description_sequence_error::description_sequence_error(const std::string& msg)
{
    message_error = "Sequence description error" + msg + "\n";
}

const char* description_sequence_error::what() const noexcept
{
    return message_error.c_str();
}
