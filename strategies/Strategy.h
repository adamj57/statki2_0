//
// Created by user on 2018-10-22.
//

#ifndef STATKI2_0_STRATEGY_H
#define STATKI2_0_STRATEGY_H


#include "../engine/base/Grid.h"

class Strategy {
public:
    virtual void run(Grid* grid) = 0;
};


#endif //STATKI2_0_STRATEGY_H
