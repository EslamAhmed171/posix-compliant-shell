#include "../../include/redirection/RedirectionHandler.h"
#include <stdexcept>

RedirectionHandler::~RedirectionHandler() {
    // Auto-restore if user forgot to call restore()
    if (!managed_fds_.empty()) {
        restore();
    }
}

void RedirectionHandler::apply(const std::vector<Redirection>& redirections) {
    // Clear previous state
    if (!managed_fds_.empty()) {
        restore();
    }

    // Process new redirections
    for (const auto& redir : redirections) {
        setupSingleRedirection(redir);
    }
}

void RedirectionHandler::restore() {
    for (auto& [target_fd, info] : managed_fds_) {
        if (info.backup_fd != -1) {
            dup2(info.backup_fd, target_fd);
            close(info.backup_fd);
        }
    }
    managed_fds_.clear();
}

void RedirectionHandler::setupSingleRedirection(const Redirection& redir) {
    // Save original fd if not already saved
    if (managed_fds_.find(redir.fd) == managed_fds_.end()) {
        managed_fds_[redir.fd] = {redir.fd, dup(redir.fd)};
    }

    int flags = O_WRONLY | O_CREAT;
    flags |= (redir.mode == Redirection::TRUNCATE) ? O_TRUNC : O_APPEND;

    int file_fd = open(redir.filename.c_str(), flags, 0666);
    if (file_fd == -1) {
        throw std::runtime_error("Failed to open file: " + redir.filename);
    }

    if (dup2(file_fd, redir.fd) == -1) {
        close(file_fd);
        throw std::runtime_error("Failed to redirect file descriptor");
    }
    close(file_fd);
}