#pragma once

#include <stdexcept>
#include <string>

class appError : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

class loadingError : public appError {
public:
    explicit loadingError(const std::string& message);
};

class entityError : public appError {
public:
    explicit entityError(const std::string& message);
};