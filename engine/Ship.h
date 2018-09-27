//
// Created by user on 2018-09-27.
//

#ifndef STATKI2_0_SHIP_H
#define STATKI2_0_SHIP_H


#include "Cell.h"

class Ship {
public:
    class SunkExeption: public std::exception {
    public:
        const char* what() const noexcept override;
    };
    explicit Ship(Cell* cells[], int cellsLength);
    bool hasPoint(GridPoint* point);
    void hit(GridPoint* point);
    bool isSunk();
    int len();

private:
    bool evaluateSunk();
    Cell** cells;
    int cellsLength;
    bool sunk;
};


#endif //STATKI2_0_SHIP_H
