//
// Created by user on 2018-10-22.
//

#include "RandomStrategy.h"
#include "../util/random.h"

void RandomStrategy::run(Grid* grid) {
    while (!grid->isWon()) {
        GridPoint coords(util::random_in_range(0, 9), util::random_in_range(0, 9));
        if (!grid->isChecked(&coords)) {
            grid->check(&coords);
        }
    }
}
