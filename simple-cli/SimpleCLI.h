//
// Created by user on 2018-10-01.
//

#ifndef STATKI2_0_SIMPLECLI_H
#define STATKI2_0_SIMPLECLI_H


#include <string>
#include <map>
#include <vector>
#include "../engine/base/Grid.h"

class SimpleCLI {
public:
    typedef bool(SimpleCLI::*cmdFunc)(std::vector<std::string>);
    int run();

private:
    void start();
    int loop();
    bool interpretCMD(std::string cmd);
    void ifExistsDelete();

    bool CMD_exit(std::vector<std::string> tokens);
    bool CMD_grid(std::vector<std::string> tokens);
    bool CMD_help(std::vector<std::string> tokens);

    Grid* grid = nullptr;

    std::map<std::string, cmdFunc> mappings = {{"exit", &SimpleCLI::CMD_exit}, {"grid", &SimpleCLI::CMD_grid},
                                               {"help", &SimpleCLI::CMD_help}};
};


#endif //STATKI2_0_SIMPLECLI_H
