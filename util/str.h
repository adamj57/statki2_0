//
// Created by user on 2018-09-27.
//

#ifndef STATKI2_0_STR_H
#define STATKI2_0_STR_H

#include <string>
#include "interface/IStringable.h"
#include "../engine/base/GridPoint.h"

namespace std {
    std::string to_string(IStringable* o);
    std::string to_string(Direction o);
}

#endif //STATKI2_0_STR_H
