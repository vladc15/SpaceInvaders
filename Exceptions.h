#pragma once

#include <stdexcept>

class appError : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

class textureError : public appError {
public:
    explicit textureError(const std::string& message);
};

class fontError : public appError {
public:
    explicit fontError(const std::string& message);
};

class entityError : public appError {
public:
    explicit entityError(const std::string& message);
};

class playerError : public appError {
public:
    explicit playerError(const std::string& message);
};

class enemyError : public appError {
public:
    explicit enemyError(const std::string& message);
};

class bossError : public appError {
public:
    explicit bossError(const std::string& message);
};