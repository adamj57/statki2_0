//
// Created by user on 2018-10-22.
//

#include <algorithm>
#include "HumanStrategy.h"
#include "../util/random.h"

HumanStrategy::HumanStrategy() {
    mode = HUNT;
}

void HumanStrategy::run(Grid* grid) {
    this->grid = grid;

    while (!grid->isWon()) {
        switch (mode) {
            case HUNT:
                hunt();
                break;
            case DESTROY:
                destroy();
                mode = HUNT;
                break;
        }
    }
}

void HumanStrategy::destroy() {
    gp_list shipPoints = {first};

    gp_list possiblePoints = listOfPossiblePoints(shipPoints);
    GridPoint* nextPoint = findNextPoint(possiblePoints, shipPoints);

    if (nextPoint == nullptr) {
        updateDontCheckPoints(shipPoints);
        return;
    }

    shipPoints.push_back(nextPoint);
    std::vector<Direction> directionOfShip = findDirectionOfShip(shipPoints);

    findRestOfShip(directionOfShip, shipPoints);
    updateDontCheckPoints(shipPoints);


}

HumanStrategy::gp_list HumanStrategy::listOfPossiblePoints(HumanStrategy::gp_list shipPoints) {
    gp_list pointsList;
    GridPoint point = *shipPoints[0];

    for (int i = 0; i < 4; i++) {
        try {
            pointsList.push_back(point.move((Direction) i));
        } catch (GridPoint::OutOfRangeException& e) {

        }

    }
    return pointsList;
}

GridPoint *HumanStrategy::findNextPoint(HumanStrategy::gp_list possiblePoints, HumanStrategy::gp_list shipPoints) {
    while (true) {
        int r = util::random_in_range(0, possiblePoints.size()-1);
        auto* rp = new GridPoint(*possiblePoints[r]); //copy of poss

        possiblePoints.erase(possiblePoints.begin() + r);
        Result result = doCheck(rp);
        if (result % MISS) {
            delete rp;
        } else if (result % HIT) {
            return rp;
        } else if (result % SUNK) {
            shipPoints.push_back(rp);
            return nullptr;
        }
    }
}

std::vector<Direction> HumanStrategy::findDirectionOfShip(HumanStrategy::gp_list shipPoints) {
    GridPoint* first = shipPoints[0];
    GridPoint* second = shipPoints[1];

    if (first->getX() == second->getX()-1 || first->getX() - 1 == second->getX()) {
        return std::vector<Direction>{LEFT, RIGHT};
    } else {
        return std::vector<Direction>{DOWN, UP};
    }
}

void HumanStrategy::findRestOfShip(std::vector<Direction> directions, HumanStrategy::gp_list shipPoints) {
    for (int i = 0; i < 2; i++) {
        bool isShipCell = true;
        GridPoint* point;

        int r = util::random_in_range(0, directions.size());
        Direction direction = directions[r];
        directions.erase(directions.begin() + r);

        if (shipPoints[0]->isOn(direction, *shipPoints[1])) {
            point = shipPoints[0];
        } else {
            point = shipPoints[1];
        }

        while (isShipCell) {
            try {
                point = point->move(direction);
                Result result = doCheck(point);
                if (result % MISS) {
                    isShipCell = false;
                } else if (result % HIT) {
                    isShipCell = true;
                    shipPoints.push_back(point);
                } else if (result % SUNK) {
                    shipPoints.push_back(point);
                    return;
                }
            } catch (GridPoint::OutOfRangeException& e){
                //pass
            }
        }
    }
}

void HumanStrategy::hunt() {
    auto* point = new GridPoint(util::random_in_range(0, 9), util::random_in_range(0, 9));
    Result result = doCheck(point);

    if (result % MISS) {
        mode = HUNT;
    } else if (result % HIT) {
        mode = DESTROY;
        first = point;
    } else if (result % SUNK) {
        updateDontCheckPoints(gp_list{point});
        mode = HUNT;
    }
}

void HumanStrategy::updateDontCheckPoints(HumanStrategy::gp_list points) {
    std::vector<int> xOffsets = {-1, 0, 1};
    std::vector<int> yOffsets = xOffsets;

    for (GridPoint* point : points) {
        for (int x : xOffsets) {
            for (int y : yOffsets) {
                try {
                    auto* tmp = new GridPoint(point->getX() + x, point->getY() + y);
                    bool foundInDontCheck =
                            std::find_if(dontCheck.begin(), dontCheck.end(), [&tmp](GridPoint* gp){
                                return *gp == *tmp;
                            }) != dontCheck.end();

                    if (!grid->isChecked(tmp) && !foundInDontCheck) {
                        dontCheck.push_back(point);
                        grid->mark(point, "*");
                    } else {
                        delete tmp;
                    }
                } catch (GridPoint::OutOfRangeException& e) {

                }
            }
        }
    }
}

Result HumanStrategy::doCheck(GridPoint *point) {
    bool foundInDontCheck =
            std::find_if(dontCheck.begin(), dontCheck.end(), [&point](GridPoint* gp){
                return *gp == *point;
            }) != dontCheck.end();
    if (!grid->isChecked(point) && !foundInDontCheck) {
        return grid->check(point);
    }
    return Result(MISS);
}