#include "Exceptions.h"

textureError::textureError(const std::string &message) : appError("Texture loading failed: " + message) {}

fontError::fontError(const std::string &message) : appError("Font loading failed: " + message) {}

entityError::entityError(const std::string &message) : appError("Entity creation failed: " + message) {}

playerError::playerError(const std::string &message) : appError("Player creation failed: " + message) {}

enemyError::enemyError(const std::string &message) : appError("Enemy creation failed: " + message) {}

bossError::bossError(const std::string &message) : appError("Boss creation failed: " + message) {}
