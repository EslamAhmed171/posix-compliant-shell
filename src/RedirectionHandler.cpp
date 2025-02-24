#include "RedirectionHandler.h"
#include <fcntl.h>
#include <unistd.h>
#include <cstdio>

void RedirectionHandler::apply(const std::vector<Redirection>& redirections) {
    for (const auto& redir : redirections) {
        int fd = redir.fd;
        if (original_fds.find(fd) == original_fds.end()) {
            original_fds[fd] = dup(fd);
            if (original_fds[fd] == -1) {
                perror("dup");
                continue;
            }
        }

        int flags = O_WRONLY | O_CREAT;
        flags |= (redir.mode == Redirection::TRUNCATE) ? O_TRUNC : O_APPEND;

        int file_fd = open(redir.filename.c_str(), flags, 0666);
        if (file_fd == -1) {
            perror("open");
            continue;
        }

        if (dup2(file_fd, fd) == -1) {
            perror("dup2");
        }

        close(file_fd);
    }
}

void RedirectionHandler::restore() {
    for (const auto& pair : original_fds) {
        int target_fd = pair.first;
        int saved_fd = pair.second;

        if (dup2(saved_fd, target_fd) == -1) {
            perror("dup2 restore");
        }
        close(saved_fd);
    }
    original_fds.clear();
}