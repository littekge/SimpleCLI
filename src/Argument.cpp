#include "Argument.h"

//constructor
CLI::Argument::Argument(std::string n, std::unordered_set<std::string> a, std::string d, int p, bool nd) {
    name = n;
    aliases = a;
    description = d;
    pos = p;
    nData = nd;
}

//checks if the argument has an alias equal to s
bool CLI::Argument::hasAlias(std::string s) {
    return aliases.count(s) == 1;
}

//getter methods
std::string CLI::Argument::getName() {
    return name;
}
std::unordered_set<std::string> CLI::Argument::getAliases() {
    return aliases;
}
std::string CLI::Argument::getDescription() {
    return description;
}
int CLI::Argument::getPosition() {
    return pos;
}
bool CLI::Argument::needsData() {
    return nData;
}

//returns a formatted description of how to call the argument and what it does
std::string CLI::Argument::what() const {
    return usage() + " " + description;
}

//returns a standard description of the arguments usage
std::string CLI::Argument::usage() const {
    std::string out;
    //format for flag type arguments
    if (pos == -1) {
        out = "[";
        //"first" used to ensure that | characters only appear as seperators
        bool first = true;
        for (std::string argName : aliases) {
            if (first == true) {
                out += argName;
                first = false;
            } else {
                out += " | " + argName;
            }
        }
        //additional formatting for option type arguments
        if (nData == true) {
            out += " <" + name + ">";
        }
        out += "]";
        return out;
    //format for positional type arguments
    } else if (pos > -1) {
        out = "<" + name + ">";
        return out;
    //error if argument position is less than -1
    } else {
        throw std::logic_error("Error: argument position cannot be negative");
    }
}