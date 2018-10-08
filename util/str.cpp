//
// Created by user on 2018-09-27.
//

#include "str.h"

namespace std {
    std::string to_string(IStringable* o){
        return o->toString();
    }

    std::string to_string(Direction o) {
        switch (o){
            case UP:
                return "UP";
            case DOWN:
                return "DOWN";
            case LEFT:
                return "LEFT";
            case RIGHT:
                return "RIGHT";
        }
    }
}


