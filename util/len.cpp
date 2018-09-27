//
// Created by user on 2018-09-27.
//

#include "len.h"

namespace std {
    size_t size(IMeasurable *o) {
        return o->size();
    }
}