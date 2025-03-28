#ifndef STRING_UTILS_H
#define STRING_UTILS_H
#pragma once
#include <string>
#include <vector>

class StringUtils {
public:
    static std::string commonPrefix(const std::vector<std::string>& strings) noexcept;
    static std::string sanitize(const std::string& input) noexcept;
};
#endif //STRING_UTILS_H
