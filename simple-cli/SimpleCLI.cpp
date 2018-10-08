//
// Created by user on 2018-10-01.
//

#include <iostream>
#include <vector>
#include <iterator>
#include <sstream>
#include "SimpleCLI.h"
#include "../util/str.h"

int SimpleCLI::run() {
    start();
    return loop();
}

void SimpleCLI::start() {
    std::cout << "Statki 2.0" << std::endl << "Simple CLI, Copyright Adam Jachowicz 2018" << std::endl <<
    "Type 'help' to get help." << std::endl;
}

int SimpleCLI::loop() {
    bool running = true;
    std::string command;

    while (running){
        std::cout << "()> ";
        std::getline(std::cin, command);
        running = interpretCMD(command);
    }

    return 0;

}

bool SimpleCLI::interpretCMD(std::string cmd) {
    std::vector<std::string> tokens;
    std::istringstream iss(cmd);

    std::copy(std::istream_iterator<std::string>(iss),
              std::istream_iterator<std::string>(),
              std::back_inserter(tokens));

    for (auto mapping : mappings) {
        if (mapping.first == tokens[0]) {
            cmdFunc f = mapping.second;
            return (*this.*f)(tokens); //calling a member function f
        }
    }
    std::cout << "Syntax error in \"" << tokens[0] << "\". Check and try again." << std::endl;
    return true;
}

bool SimpleCLI::CMD_exit(std::vector<std::string> tokens) {
    std::cout << "Called exit - exiting!" << std::endl;
    std::cout << "Deleting grid object..." << std::endl;
    ifExistsDelete();
    std::cout << "grid object deleted!" << std::endl;
    return false;
}

bool SimpleCLI::CMD_grid(std::vector<std::string> tokens) {
    if (std::size(tokens) < 2) {
        std::cout << "Usage: grid new [random [configname]]\n       grid str\n       grid won\n       grid check x y" << std::endl;
        return true;
    }
    if (tokens[1] == "new") {
        if (std::size(tokens) == 2) {
            std::cout << "Generating new, blank grid..." << std::endl;
            ifExistsDelete();
            grid = new Grid();
            std::cout << "Grid succesfully generated." << std::endl;
            return true;
        } else if (std::size(tokens) == 3) {
            if (tokens[2] == "random") {
                std::cout << "Trying to randomly populate grid using default config (polish)..." << std::endl;
                try {
                    ifExistsDelete();
                    grid = new Grid(new ShipConfig("polish"));
                } catch (Grid::ShipPlacementException& e) {
                    std::cout << "During random placement an error occured:" << std::endl << e.what() << std::endl;
                    return true;
                }
                std::cout << "Grid succesfully generated and populated." << std::endl;
                return true;
            }
        } else if (std::size(tokens) == 4) {
            if (tokens[2] == "random") {
                std::cout << "Trying to randomly populate grid using " << tokens[3] << "config..." << std::endl;
                try {
                    ifExistsDelete();
                    grid = new Grid(new ShipConfig(tokens[3]));
                } catch (Grid::ShipPlacementException& e) {
                    std::cout << "During random placement an error occured:" << std::endl << e.what() << std::endl;
                    return true;
                } catch (ShipConfig::ConfigNotFoundException& e) {
                    std::cout << "Ship config not found: " << std::endl << e.what() << std::endl;
                    return true;
                }
                std::cout << "Grid succesfully generated and populated." << std::endl;
                return true;
            }
        } else {
            std::cout << "Incorrect syntax: too many tokens in the command. Check syntax and try again." << std::endl;
        }
    } else if (tokens[1] == "str") {
        if (grid != nullptr) {
            std::cout << "Graphical representation of a grid object: " << std::endl;
            std::cout << std::to_string(grid) << std::endl;
            std::cout << "Done." << std::endl;
            return true;
        } else {
            std::cout << "No grid object is present. Create one using 'grid new' commandset." << std::endl;
            return true;
        }
    } else if (tokens[1] == "won") {
        if (grid != nullptr) {
            if (grid->isWon()) {
                std::cout << "Game is won!" << std::endl;
                return true;
            } else {
                std::cout << "Game is not won" << std::endl;
                return true;
            }
        } else {
            std::cout << "No grid object is present. Create one using 'grid new' commandset." << std::endl;
            return true;
        }
    } else if (tokens[1] == "check") {
        if (grid != nullptr) {
            if (std::size(tokens) == 4) {
                int x = std::stoi(tokens[2]);
                int y = std::stoi(tokens[3]);
                GridPoint* gp;
                try {
                    gp = new GridPoint(x, y);
                    Result result = grid->check(gp);

                    std::cout << "Result of check in x: " << x << ", y: " << y << ": " << std::to_string(&result) << std::endl;
                    return true;
                } catch (GridPoint::OutOfRangeException& e) {
                    std::cout << e.what() << std::endl;
                    return true;
                }
            }
        } else {
            std::cout << "No grid object is present. Create one using 'grid new' commandset." << std::endl;
            return true;
        }
    }
}

void SimpleCLI::ifExistsDelete() {
    if (grid != nullptr) {
        delete grid;
        grid = nullptr;
    }
}

bool SimpleCLI::CMD_help(std::vector<std::string> tokens) {
    std::cout << "Available commands: " << std::endl << std::endl;
    for (auto mapping : mappings) {
        std::cout << mapping.first << std::endl;
    }
    std::cout << std::endl;
    return true;
}


