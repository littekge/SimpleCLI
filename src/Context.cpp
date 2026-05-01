#include "Context.h"

//adds an argument to the context with data
void CLI::Context::add(Argument a, std::string data) {
    args.insert({a.getName(), data});
    pos_ref.insert({a.getPosition(), &args.at(a.getName())});
}

//adds an argument to the context without data
void CLI::Context::add(Argument a) {
    args.insert({a.getName(), ""});
    pos_ref.insert({a.getPosition(), &args.at(a.getName())});
}

//checks if an argument exists in the context by name or position
bool CLI::Context::exists(std::string s) const {
    return args.count(s) == 1;
}
bool CLI::Context::exists(int p) const {
    return pos_ref.count(p) == 1;
}

//returns the data that is paired to an argument specified by name or position
std::string CLI::Context::access(std::string s) const {
    if (exists(s)) {
        return args.at(s);
    } else {
        throw std::runtime_error("Error: no such argument \"" + s + "\" exists in this context");
    }
}
std::string CLI::Context::access(int p) const {
    if (exists(p)) {
        return *pos_ref.at(p);
    } else {
        throw std::runtime_error("Error: no such argument at position " + std::to_string(p) + " exists in this context");
    }
}