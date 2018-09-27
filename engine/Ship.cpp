//
// Created by user on 2018-09-27.
//

#include "Ship.h"

Ship::Ship(std::vector<Cell*> cells) {
    this->cells = std::move(cells);
    sunk = false;
}

bool Ship::hasPoint(GridPoint *point) {
    for (Cell* cell : cells) {
        if (*(cell->pos) == *point){
            return true;
        }
    }
    return false;
}

void Ship::hit(GridPoint *point) {
    if (sunk) {
        throw SunkException();
    }
    for (Cell* cell : cells){
        if (*(cell->pos) == *point) {
            cell->setCheck();
            sunk = evaluateSunk();
            return;
        }
    }
    throw "AAAAAAAAA";
    //TODO: Create NotInShipException and throw it here
}

bool Ship::evaluateSunk() {
    for (Cell* cell : cells) {
        if (!(cell->isChecked())) {
            return false;
        }
    }
    return true;
}

bool Ship::isSunk() {
    return sunk;
}

size_t Ship::size() {
    return cells.size();
}

const char* Ship::SunkException::what() const noexcept {
    return "This ship did already sunk!";
}
