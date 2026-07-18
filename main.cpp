// main.cpp
// Entry point for the ELIZA simulation. Contains ONLY the top-level
// conversation loop; all real functionality (regex dispatch, response
// tracking, pronoun reflection, etc.) lives in Eliza and the per-topic
// component files, as required by the assignment.
#include <iostream>
#include <string>
#include "Eliza.h"

int main() {
    Eliza eliza;

    std::cout << eliza.greeting() << std::endl;

    std::string line;
    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, line)) {
            // EOF (e.g. input piped from a file) -- end gracefully.
            std::cout << std::endl << eliza.farewell() << std::endl;
            break;
        }

        if (eliza.isExitCommand(line)) {
            std::cout << eliza.farewell() << std::endl;
            break;
        }

        std::cout << eliza.respond(line) << std::endl;
    }

    return 0;
}
