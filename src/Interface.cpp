#include "Interface.h"

//parses input from the command line
std::vector<std::string> CLI::Interface::parse(std::string line) {

    //checking for empty input
    if (line.empty()) {
        throw std::runtime_error("Error: input string cannot be empty");
    }

    //variables
    std::vector<std::string> result;
    bool quoted = false;
    std::string word;
    
    //iterating over each character
    for (size_t i = 0; i < line.size(); i++) {
        //if unquoted and a space is found, add next word to final result
        if ((line[i] == ' ' || line[i] == '\t') && !quoted) {
            //check if word has characters before adding
            if (!word.empty()) {
                result.push_back(word);
                word.clear();
            }
        //else if a quote is detected set/unset the quoted flag
        } else if (line[i] == '\"') {
            quoted = !quoted;
        //otherwise a regular character is detected and is added to the current word
        } else {
            word.push_back(line[i]);
        }
    }
    //if the quoted flag is true once the input is complete, the command input is invalid and throws an error.
    if (quoted) {
        throw std::runtime_error("Error: incomplete input; ensure that all quotes are closed");
    //if quoted flag is false add the last word and return
    } else {
        if (!word.empty()) {
            result.push_back(word);
            word.clear();
        }
    }
    return result;
}

//attempts to execute a command
void CLI::Interface::execute(std::string input) {
    std::vector<std::string> parsedCommand = parse(input);
    std::string keyword = parsedCommand[0];
    std::vector<std::string> inputArgs(parsedCommand.begin() + 1, parsedCommand.end());
    if (commands.count(keyword) == 1) {
        //run command
        //parsing arguments one by one and adding them to context
        Context ctx;
        for (int i = 0; i < inputArgs.size(); i++) {
            //checking positionals
            if (commands.at(keyword).hasArg(i)) {
                //adding positional argument if found
                ctx.add(commands.at(keyword).getArg(i), inputArgs[i]);
            //checking flags and options
            } else if (commands.at(keyword).hasArg(inputArgs[i])) {
                //if the input arg is an option, get additional data
                if (commands.at(keyword).getArg(inputArgs[i]).needsData()) {
                    //ensure that additonal data exists
                    if (i != inputArgs.size() - 1) {
                        ctx.add(commands.at(keyword).getArg(inputArgs[i]), inputArgs[i+1]);
                        i++;
                    } else {
                        throw std::runtime_error("Error: no data provided for option \"" + inputArgs[i] + "\"");
                    }
                //otherwise add the flag
                } else {
                    ctx.add(commands.at(keyword).getArg(inputArgs[i]));
                }
            } else {
                throw std::runtime_error("Error: no such argument \"" + inputArgs[i] + "\" exists in command \"" + keyword + "\""); 
            }
        }
        //if everything is successful, run the command with the completed context
        commands.at(keyword).run(ctx);
    } else {
        //throw error
        throw std::runtime_error("Error: no such command \"" + keyword + "\" exists\nType \"help\" for a list of valid commands");
    }
}

//checks if the interface has a command
bool CLI::Interface::hasCommand(std::string s) {
    return commands.count(s) == 1;
}

//registers a new command to the interface
void CLI::Interface::registerCommand(Command c) {
    if (!hasCommand(c.getName())) {
        commands.insert({c.getName(), c});
    } else {
        throw std::logic_error("Error: command with name \"" + c.getName() + "\" already exists in this interface");
    }
}

//attempts to remove a command from the interface
void CLI::Interface::removeCommand(std::string s) {
    if (hasCommand(s)) {
        commands.erase(s);
    } else {
        throw std::logic_error("Error: removal failed; command with name \"" + s + "\" does not exist in this interface");
    }
}

//attempts to output the description for a command specifed by name
std::string CLI::Interface::what(std::string s) {
    if (hasCommand(s)) {
        return commands.at(s).what();
    } else {
        throw std::runtime_error("Error: command with name \"" + s + "\" does not exist in this interface");
    }
}