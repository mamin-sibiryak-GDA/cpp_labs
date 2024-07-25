#pragma once

#include <stdexcept>
#include <string>

class too_much_args: public std::exception
{
private:
    std::string message_error;
public:
    explicit too_much_args(const std::string& message);

    const char* what() const noexcept override;
};

class too_few_args: public std::exception
{
private:
    std::string message_error;
public:
    explicit too_few_args(const std::string& message);

    const char* what() const noexcept override;
};

class file_open_error: public std::exception
{
private:
    std::string message_error;
public:
    file_open_error();

    const char* what() const noexcept override;
};

class file_beginning_error: public std::exception
{
private:
    std::string message_error;
public:
    file_beginning_error();

    const char* what() const noexcept override;
};

class unknown_worker: public std::exception
{
private:
    std::string message_error;
public:
    unknown_worker();

    const char* what() const noexcept override;
};

class delimiter_error: public std::exception
{
private:
    std::string message_error;
public:
    delimiter_error();

    const char* what() const noexcept override;
};

class description_block_error: public std::exception
{
private:
    std::string message_error;
public:
    description_block_error();

    const char* what() const noexcept override;
};

class description_sequence_error: public std::exception
{
private:
    std::string message_error;
public:
    explicit description_sequence_error(const std::string& msg);

    const char* what() const noexcept override;
};
