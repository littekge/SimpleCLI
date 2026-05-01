#ifndef COMMANDLINE
#define COMMANDLINE

#include "Command.h"
#include <vector>

namespace CLI {

    //defines a command interface
    class Interface {
        private:
            //Commands contained within the CLI
            std::unordered_map<std::string, Command> commands;

            //splits string into vector of arguments
            std::vector<std::string> parse(std::string line);

        public:
            Interface() = default;
            //attempts to execute a command based on the input string
            void execute(std::string input);
            //checks if a command exists in the interface
            bool hasCommand(std::string s);
            //registers a command in the interface
            void registerCommand(Command c);
            //removes a command with name s from the interface
            void removeCommand(std::string s);
            //outputs information about a command in the interface
            std::string what(std::string s);

    };

}


#endif