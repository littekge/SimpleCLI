#ifndef COMMAND
#define COMMAND

#include "Argument.h"
#include "Context.h"

#include <string>
#include <functional>

#include <map>
#include <set>

namespace CLI {

    //Defines a commmand to be stored in the interface.
    class Command {
        private:
            //command metadata
            std::string name;
            std::string description;
            //user-defined function that the command will run. The context object lets the command know what arugments the user specified.
            std::function<void(Context ctx)> funct; 
            //unordered map holding pointers to command metadata referenced by the argument name.
            std::map<std::string, Argument> args;
            std::map<std::string, Argument* const> name_ref;
            std::map<int, Argument* const> pos_ref;

            //generic argument addition method
            void addArgument(Argument a);
            
        public:
            //constructor(s)
            Command(std::string n, std::string d, std::function<void(Context ctx)> f);
            
            //runs the command in the provided context
            void run(Context ctx) const;

            //check if the command has a specified argument
            bool hasArg(std::string s) const;
            bool hasArg(int p) const;
            
            //addition methods
            void addOption(std::string n, std::unordered_set<std::string> a, std::string d);
            void addFlag(std::string n, std::unordered_set<std::string> a, std::string d);
            void addPositional(std::string n, std::string d, int p);

            //removal method
            void removeArg(std::string s);
            void removeArg(int p);

            //argument retrieval methods
            Argument getArg(std::string s) const;
            Argument getArg(int p) const;

            //generic getter methods
            std::string getName() const;
            std::string getDescription() const;

            //outputs command metadata as a string
            std::string what() const;
            std::string usage() const;
    };
    
}

#endif