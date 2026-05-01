#include "Command.h"
        
//constructor
CLI::Command::Command(std::string n, std::string d, std::function<void(Context ctx)> f) {
    name = n;
    description = d;
    funct = f;
}

//running the function contained in the command with the provided context
void CLI::Command::run(Context ctx) const {
    funct(ctx);
}

//chekcs if the command has an argument based on alias or position
bool CLI::Command::hasArg(std::string s) const {
    return name_ref.count(s) == 1;
}
bool CLI::Command::hasArg(int p) const {
    return pos_ref.count(p) == 1;
}

//adds an argument to the command
void CLI::Command::addArgument(Argument a) {
    //checking for unique name
    for (std::string alias : a.getAliases()) {
        if (hasArg(alias)) {
            throw std::logic_error("Error: argument with name/alias \"" + alias + "\" is already defined in command \"" + name + "\"");
        }
    }
    //checking for unique position
    if (hasArg(a.getPosition())) {
        throw std::logic_error("Error: positional argument with position \"" + std::to_string(a.getPosition()) + "\" is already defined in command \"" + name + "\"");
    }
    //position and name are unique, adding argument to command
    args.insert({a.getName(), a});
    //adding aliases
    for (std::string alias : a.getAliases()) {
        name_ref.insert({alias, &args.at(a.getName())});
    }
    //adding position
    if (a.getPosition() > -1) {
        pos_ref.insert({a.getPosition(), &args.at(a.getName())});
    }
}

//adds an argument using the properties of a flag
void CLI::Command::addFlag(std::string n, std::unordered_set<std::string> a, std::string d) {
    addArgument(Argument(n, a, d, -1, false));
}

//adds an argument using the properties of an option
void CLI::Command::addOption(std::string n, std::unordered_set<std::string> a, std::string d) {
    addArgument(Argument(n, a, d, -1, true));
}

//adds an argument using the properties of a positional
void CLI::Command::addPositional(std::string n, std::string d, int p) {
    addArgument(Argument(n, {}, d, p, false));
}

//attempts to remove an argument from the command by either name or position
void CLI::Command::removeArg(std::string s) {
    if (hasArg(s)) {
        //getting arg name from name reference
        std::string argName = name_ref.at(s)->getName();
        //removing pointers
        for (std::string alias : name_ref.at(s)->getAliases()) {
            name_ref.erase(alias);
        }
        if(args.at(argName).getPosition() >= 0) {
            pos_ref.erase(args.at(argName).getPosition());
        }
        //erasing original object
        args.erase(argName);
    } else {
        throw std::runtime_error("Error: removal failed; argument with alias \"" + s + "\" does not exist in command \"" + name + "\"");
    }
}
void CLI::Command::removeArg(int p) {
    if (hasArg(p)) {
        //removing name references
        for (std::string alias : pos_ref.at(p)->getAliases()) {
            name_ref.erase(alias);
        }
        //remoiving original object
        args.erase(pos_ref.at(p)->getName());
        //removing position reference
        pos_ref.erase(p);
    } else {
        throw std::runtime_error("Error: removals failed; argument with position\"" + std::to_string(p) + "\" does not exist in command \"" + name + "\"");
    }
}

//attempts to resturn an argument in the command by either name or position
CLI::Argument CLI::Command::getArg(std::string s) const {
    if (hasArg(s)) {
        return *name_ref.at(s);
    } else {
        throw std::runtime_error("Error: retrieval failed; argument with alias \"" + s + "\" does not exist in command \"" + name + "\"");
    }
}
CLI::Argument CLI::Command::getArg(int p) const {
    if (hasArg(p)) {
        return *pos_ref.at(p);
    } else {
        throw std::runtime_error("Error: removals failed; argument with position \"" + std::to_string(p) + "\" does not exist in command \"" + name + "\"");
    }
}

//getter methods
std::string CLI::Command::getName() const {
    return name;
}
std::string CLI::Command::getDescription() const {
    return description;
}

//outputs a full description of the command, including usage, description, and argument descriptions
std::string CLI::Command::what() const {
    std::string out;
    //outputting command usage and description
    out = "\n" + usage() + "\n" + description + "\n";
    //outputting argument descriptions
    for (auto p : args) {
        out += "\n    " + p.second.what();
    }
    out += "\n\n";
    return out;
} 

//outputs a usage description of the command
std::string CLI::Command::usage() const {
    std::string out = "Usage: " + name;
    //outputting positionals
    if (!pos_ref.empty()) {
        for (int i = 0; i <= pos_ref.rbegin()->first; i++) {
            if (hasArg(i)) {
                out += " " + pos_ref.at(i)->usage();
            } else {
                out += " <>";
            }
        }
    }
    //outputting options and flags
    for (auto p : args) {
        if (p.second.getPosition() == -1) {
            out += " " + p.second.usage();
        }
    }
    return out;
}