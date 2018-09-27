//
// Created by user on 2018-09-27.
//

#ifndef STATKI2_0_SHIP_H
#define STATKI2_0_SHIP_H

#include <vector>
#include "Cell.h"
#include "../util/interface/IMeasurable.h"

class Ship: public IMeasurable {
public:
    class SunkException: public std::exception {
    public:
        const char* what() const noexcept override;
    };

    explicit Ship(std::vector<Cell*> cells);

    bool hasPoint(GridPoint* point);
    void hit(GridPoint* point);
    bool isSunk();

    size_t size() override;

private:
    bool evaluateSunk();

    std::vector<Cell*> cells;
    bool sunk;
};


#endif //STATKI2_0_SHIP_H
