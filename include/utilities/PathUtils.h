#ifndef PATH_UTILS_H
#define PATH_UTILS_H
#pragma once
#include <filesystem>
#include <algorithm>
#include <vector>
#include <string>

namespace fs = std::filesystem;

class PathUtils {
public:
    static std::string findExecutablePath(const std::string& command) noexcept;
    static std::vector<std::string> findCommandsInPath(const std::string& prefix) noexcept;

private:
    static std::vector<std::string> parsePathEnv(const char* pathEnv) noexcept;
};
#endif //PATH_UTILS_H
