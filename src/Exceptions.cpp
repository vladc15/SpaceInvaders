#include "../include/Exceptions.h"

entityError::entityError(const std::string &message) : appError(std::string("Entity creation failed: ") + message) {}

loadingError::loadingError(const std::string &message) : appError(std::string("Loading of a file failed: ") + message) {}
