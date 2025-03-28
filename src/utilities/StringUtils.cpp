#include "../../include/utilities/StringUtils.h"
#include <algorithm>
#include <numeric>

std::string StringUtils::commonPrefix(const std::vector<std::string>& strings) noexcept {
    if (strings.empty()) return "";

    return std::accumulate(strings.begin() + 1, strings.end(), strings[0],
                           [](const std::string& a, const std::string& b) {
                               auto mismatch = std::mismatch(a.begin(), a.end(), b.begin(), b.end());
                               return std::string(a.begin(), mismatch.first);
                           });
}

std::string StringUtils::sanitize(const std::string& input) noexcept {
    std::string clean;
    clean.reserve(input.size());

    std::copy_if(input.begin(), input.end(), std::back_inserter(clean),
                 [](char c) { return c != '\t'; });

    return clean;
}