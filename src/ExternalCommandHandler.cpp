#include "ExternalCommandHandler.h"
#include "CommandUtils.h"
#include "RedirectionHandler.h"
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include <vector>
#include <cstdio>
#include <iostream>

void ExternalCommandHandler::handleCommand(const std::string& commandName,
                                           const std::vector<std::string>& args,
                                           const std::vector<Redirection>& redirections) {
    std::string fullPath = CommandUtils::getCommandDirectory(commandName, std::getenv("PATH"));
    if (fullPath.empty()) {
        std::cerr << commandName << ": command not found" << std::endl;
        return;
    }

    pid_t pid = fork();
    if (pid == 0) {
        RedirectionHandler rh;
        rh.apply(redirections);

        std::vector<char*> argv;
        argv.push_back(const_cast<char*>(commandName.c_str()));
        for (const auto& arg : args) {
            argv.push_back(const_cast<char*>(arg.c_str()));
        }
        argv.push_back(nullptr);

        execv(fullPath.c_str(), argv.data());
        perror("execv failed");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
    } else {
        perror("fork failed");
    }
}