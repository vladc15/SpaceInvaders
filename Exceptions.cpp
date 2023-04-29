#include "Exceptions.h"

textureError::textureError(const std::string &message) : appError(std::string("Texture loading failed: ") + message) {}

fontError::fontError(const std::string &message) : appError(std::string("Font loading failed: ") + message) {}

entityError::entityError(const std::string &message) : appError(std::string("Entity creation failed: ") + message) {}

playerError::playerError(const std::string &message) : appError(std::string("Player creation failed: ") + message) {}

enemyError::enemyError(const std::string &message) : appError(std::string("Enemy creation failed: ") + message) {}

bossError::bossError(const std::string &message) : appError(std::string("Boss creation failed: ") + message) {}
