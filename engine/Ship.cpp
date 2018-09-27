//
// Created by user on 2018-09-27.
//

#include "Ship.h"

Ship::Ship(Cell* cells[], int cellsLength) {
    this->cells = cells;
    this->cellsLength = cellsLength;
    sunk = false;
}

bool Ship::hasPoint(GridPoint *point) {
    for (int i = 0; i < cellsLength; i++) {
        if (*(cells[i]->pos) == *point){
            return true;
        }
    }
    return false;
}

void Ship::hit(GridPoint *point) {
    if (sunk) {
        throw SunkExeption();
    }
    for (int i = 0; i < cellsLength; i++) {
        if (*(cells[i]->pos) == *point){
            cells[i]->setCheck();
            sunk = evaluateSunk();
            return;
        }
    }
    throw "AAAAAAAAA";
    //TODO: Create NotInShipException and throw it here
}

bool Ship::evaluateSunk() {
    for (int i = 0; i < cellsLength; i++) {
        if (!cells[i]->isChecked()) {
            return false;
        }
    }
    return true;
}

bool Ship::isSunk() {
    return sunk;
}

int Ship::len() {
    return cellsLength;
}

const char* Ship::SunkExeption::what() const noexcept {
    return "This ship did already sunk!";
}
