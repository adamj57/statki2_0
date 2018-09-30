#include <utility>

//
// Created by user on 2018-09-24.
//

#include <sstream>
#include <iostream>
#include <cstring>
#include "GridPoint.h"

GridPoint::GridPoint(int x, int y) {
    if (x < 0 || x > 9){
        throw OutOfRangeException("x", 0, 9, x);
    }
    if (y < 0 || y > 9){
        throw OutOfRangeException("y", 0, 9, y);
    }
    this->x = x;
    this->y = y;
}

GridPoint* GridPoint::move(Direction dir, int times) {
    int x_delta = 0;
    int y_delta = 0;
    switch (dir) {
        case LEFT:
            x_delta -= 1 * times;
            break;
        case RIGHT:
            x_delta += 1 * times;
            break;
        case UP:
            y_delta -= 1 * times;
            break;
        case DOWN:
            y_delta += 1 * times;
            break;
    }
    return new GridPoint(this->x + x_delta, this->y + y_delta);
}

GridPoint* GridPoint::move(Direction dir) {
    return this->move(dir, 1);
}

bool GridPoint::isOn(Direction dir, GridPoint &other) {
    bool ret;
    try {
        ret = other.move(dir) == this;
    } catch (OutOfRangeException& e) {
        return false;
    }
    return ret;
}

bool GridPoint::operator==(GridPoint &other) {
    return (x == other.x) && (y == other.y);
}

std::string GridPoint::toString() {
    std::ostringstream stream;
    stream << "x: " << x << " y: " << y;
    return stream.str();
}

int GridPoint::getX() {
    return x;
}

int GridPoint::getY() {
    return y;
}

GridPoint::GridPoint(GridPoint &point) {
    this->x = point.getX();
    this->y = point.getY();

}

const char* GridPoint::OutOfRangeException::what() const noexcept {
    std::ostringstream stream;
    stream << "OutOfRangeException: Variable \"" << variable << "\", expected " << lb << "<= " << variable << " <= "
            << hb << ", got " << val << " instead.";
    char* dst = new char[strlen(stream.str().c_str())+1];
    strcpy(dst, stream.str().c_str());
    return dst;
}

GridPoint::OutOfRangeException::OutOfRangeException(std::string variable, int lb, int hb, int val) {
    this->val = val;
    this->variable = std::move(variable);
    this->lb = lb;
    this->hb = hb;
}
