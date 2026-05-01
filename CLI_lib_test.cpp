#include "Interface.h"
#include <iostream>

int main() {

    CLI::Interface i;

    CLI::Command c = CLI::Command("test", "description", [](CLI::Context ctx){
        std::cout << "command called";
    });
    c.addFlag("force", {"-f", "--force"}, "forces command to execute");
    i.registerCommand(c);

    CLI::Command help = CLI::Command("help", "Outputs information related to commands in this interface.", [&i](CLI::Context ctx){
        std::cout << i.what(ctx.access("alias"));
    });
    help.addPositional("alias", "The alias of the command to be queried", 0);
    help.addFlag("testflag", {"-t", "--test"}, "testflag description");
    i.registerCommand(help);

    std::string in;
    while (true) {
        getline(std::cin, in);
        try {
            i.execute(in);
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }
    
    return 0;
}