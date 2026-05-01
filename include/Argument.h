#ifndef ARGUMENT
#define ARGUMENT

#include <string>
#include <unordered_set>
#include <stdexcept>
namespace CLI {

    //defines a command argument
    class Argument {
        private:
            //argument name
            std::string name;
            //argument aliases
            std::unordered_set<std::string> aliases;
            //argument description
            std::string description;
            //desired arugment position in list of args
            int pos;
            //whether or not the argument needs data
            bool nData;
        public:
            //constructors
            Argument(std::string n, std::unordered_set<std::string> a, std::string d, int p, bool nd);

            //checks if the argument has an alias
            bool hasAlias(std::string s);

            //getter methods for arugments
            std::string getName();
            std::unordered_set<std::string> getAliases();
            std::string getDescription();
            int getPosition();
            bool needsData();

            //methods to output information about the argument
            std::string what() const;
            std::string usage() const;
    };

}

#endif