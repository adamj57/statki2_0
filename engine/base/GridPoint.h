//
// Created by user on 2018-09-24.
//

#ifndef STATKI2_0_GRIDPOINT_H
#define STATKI2_0_GRIDPOINT_H


#include <string>
#include "../../util/interface/IStringable.h"

enum Direction {
    LEFT, RIGHT, UP, DOWN
};

class GridPoint: public IStringable {
public:
    GridPoint(int x, int y);
    GridPoint(GridPoint& point);

    GridPoint* move(Direction dir, int times);
    GridPoint* move(Direction dir);

    int getX();
    int getY();

    bool isOn(Direction dir, GridPoint &other);

    bool operator==(GridPoint &other);
    std::string toString() override;

    class OutOfRangeException : std::exception{
    public:
        OutOfRangeException(std::string variable, int lb, int hb, int val);
        const char* what() const noexcept override;

    private:
        int lb, hb, val;
        std::string variable;
    };

private:
    int x, y;
};


#endif //STATKI2_0_GRIDPOINT_H
