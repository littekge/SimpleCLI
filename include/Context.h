#ifndef CONTEXT
#define CONTEXT

#include "Argument.h"
#include <stdexcept>
#include <unordered_map>

namespace CLI {
    
    //serves as a runtime list of arguments that can be passed to a command to run it.
    class Context {
        private:
            std::unordered_map<std::string, std::string> args;
            std::unordered_map<int, std::string*> pos_ref;
        public:
            //constructor
            Context() = default;
            //adds an argument to the context
            void add(Argument a, std::string data);
            void add(Argument a);
            //checks if an argument exists in this context
            bool exists(std::string s) const;
            bool exists(int p) const;
            //accesses the value tied to the argument in this context
            std::string access(std::string s) const;
            std::string access(int p) const;
    };
} 

#endif