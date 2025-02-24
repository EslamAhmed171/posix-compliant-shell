#ifndef COMMANDRUNNER_H
#define COMMANDRUNNER_H

#include <string>
#include "CommandParser.h"

class CommandRunner {
public:
    void processCommand(std::string& input);

};

#endif // COMMANDRUNNER_H