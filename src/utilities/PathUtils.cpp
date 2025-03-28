#include "../../include/utilities/PathUtils.h"

std::string PathUtils::findExecutablePath(const std::string& command) noexcept {
    const char* pathEnv = getenv("PATH");

    for (const auto& dir : parsePathEnv(pathEnv)) {
        try {
            const fs::path dirPath(dir);
            const fs::path candidate = dirPath / command;

            if (fs::exists(candidate)) {
                return candidate.string();
            }
        } catch (const fs::filesystem_error&) {
            // Ignore invalid directories
        }
    }
    return "";
}

std::vector<std::string> PathUtils::findCommandsInPath(const std::string& prefix) noexcept {
    std::vector<std::string> matches;
    const char* pathEnv = std::getenv("PATH");

    for (const auto& dir : parsePathEnv(pathEnv)) {
        try {
            for (const auto& entry : fs::directory_iterator(dir)) {
                const std::string filename = entry.path().filename().string();
                if (filename.find(prefix) == 0) {
                    matches.push_back(filename);
                }
            }
        } catch (const fs::filesystem_error&) {
            // Ignore invalid directories
        }
    }

    std::sort(matches.begin(), matches.end());
    matches.erase(std::unique(matches.begin(), matches.end()), matches.end());
    return matches;
}

std::vector<std::string> PathUtils::parsePathEnv(const char* env) noexcept {
    std::vector<std::string> paths;
    if (!env) {
        return paths;
    }
    std::istringstream iss(env);
    std::string token;
    while (std::getline(iss, token, ':')) {
        paths.push_back(token);
    }
    return paths;
}
