#include "CommandExecutor.h"
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include <vector>
#include <cstdio>

void CommandExecutor::executeCommand(const std::string& fullPath,
                                     const std::vector<std::string>& args) {
    // Build the argv array: argv[0] is the command name.
    std::vector<char*> argv;
    for (const auto& arg : args) {
        argv.push_back(const_cast<char*>(arg.c_str()));
    }
    argv.push_back(nullptr); // Null-terminate

    pid_t pid = fork();
    if (pid == 0) {
        // Child process: replace the image with the external command.
        if (execv(fullPath.c_str(), argv.data()) == -1) {
            perror("execv failed");
        }
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        // Parent process: wait for the child process to complete.
        int status;
        waitpid(pid, &status, 0);
    } else {
        // Fork failed.
        perror("fork failed");
    }
}
