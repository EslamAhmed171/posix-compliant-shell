#ifndef REDIRECTION_H
#define REDIRECTION_H

#include <string>

struct Redirection {
    int fd;
    enum Mode { TRUNCATE, APPEND } mode;
    std::string filename;
};

#endif // REDIRECTION_H