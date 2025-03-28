#include "../../../include/execution/executions/ExternalStrategy.h"
#include "../../../include/utilities/PathUtils.h"
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>

int ExternalStrategy::execute(const std::vector<std::string>& args) {
    if (args.empty()) return EXIT_FAILURE;

    const std::string& cmd = args[0];
    const std::string path = PathUtils::findExecutablePath(cmd);

    if (path.empty()) {
        std::cerr << cmd << ": command not found\n";
        return EXIT_FAILURE;
    }

    return forkAndExecute(args);
}

int ExternalStrategy::forkAndExecute(const std::vector<std::string>& args) const {
    pid_t pid = fork();
    if (pid == 0) {
        setupChildProcess(args);
    } else if (pid > 0) {
        return monitorChildProcess(pid);
    }
    std::cerr << "fork: " << strerror(errno) << '\n';
    return EXIT_FAILURE;
}

void ExternalStrategy::setupChildProcess(const std::vector<std::string>& args) const {
    std::vector<char*> argv;
    argv.reserve(args.size() + 1);
    for (const auto& arg : args) {
        argv.push_back(const_cast<char*>(arg.c_str()));
    }
    argv.push_back(nullptr);
    const std::string path = PathUtils::findExecutablePath(argv[0]);

    execv(path.c_str(), argv.data());
    std::cerr << "execv: " << strerror(errno) << '\n';
    _exit(EXIT_FAILURE);
}

int ExternalStrategy::monitorChildProcess(pid_t pid) const {
    int status;
    do {
        waitpid(pid, &status, 0);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));

    return WIFEXITED(status) ? WEXITSTATUS(status) : EXIT_FAILURE;
}