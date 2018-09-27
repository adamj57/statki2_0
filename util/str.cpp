//
// Created by user on 2018-09-27.
//

#include "str.h"

namespace std {
    std::string to_string(IStringable* o){
        return o->toString();
    }
}


