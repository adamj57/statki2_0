//
// Created by user on 2018-09-27.
//

#include "str.h"

std::string str(IStringable* o){
    return o->toString();
}
