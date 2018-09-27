//
// Created by user on 2018-09-27.
//

#include <iostream>
#include "Cell.h"

Cell::Cell(GridPoint* point) {
    this->pos = point;
}

Cell::Cell(Cell &obj) {
    this->pos = new GridPoint(*obj.pos);
    this->marker = std::string(obj.marker);
    this->checked = obj.checked;
    this->shipCell = obj.shipCell;
}

bool Cell::isChecked() {
    return checked;
}

void Cell::setCheck() {
    checked = true;
}

bool Cell::isShipCell() {
    return shipCell;
}

void Cell::setShipCell() {
    shipCell = true;
}

void Cell::setMarker(std::string marker) {
    this->marker = std::move(marker);
}

std::string Cell::toString() {
    if (marker != "\0") {
        if (shipCell) {
            if (checked) {
                return "V";
            } else {
                return "O";
            }
        } else {
            if (checked) {
                return "X";
            } else {
                return ".";
            }
        }
    } else {
        return marker;
    }
}

bool Cell::operator==(Cell& other) {
    return (shipCell == other.shipCell) && (checked == other.checked);
}


