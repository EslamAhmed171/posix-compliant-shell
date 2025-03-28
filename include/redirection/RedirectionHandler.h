#ifndef REDIRECTION_HANDLER_H
#define REDIRECTION_HANDLER_H

#include "./data-structures/Redirection.h"
#include <unordered_map>
#include <fcntl.h>
#include <unistd.h>
#include <vector>

class RedirectionHandler {
public:
    RedirectionHandler() = default;
    ~RedirectionHandler();

    void apply(const std::vector<Redirection>& redirections);
    void restore();

private:
    struct FdInfo {
        int original_fd;
        int backup_fd = -1;
    };

    std::unordered_map<int, FdInfo> managed_fds_;

    void setupSingleRedirection(const Redirection& redir);
};

#endif // REDIRECTION_HANDLER_H