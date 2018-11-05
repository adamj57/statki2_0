//
// Created by user on 2018-10-29.
//

#include <algorithm>
#include "AnalyticalStrategy.h"
#include "../util/random.h"
#include "../util/len.h"

AnalyticalStrategy::AnalyticalStrategy() {
    mode = HUNT;
    aliveShips = {};
    for (ShipConfig::ShipDetails* detail : *(grid->sc)) {
        aliveShips.insert(std::make_pair(detail->getLength(), detail->getQuantity()));
    }
}

void AnalyticalStrategy::run(Grid *grid) {
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

void AnalyticalStrategy::destroy() {
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

AnalyticalStrategy::gp_list AnalyticalStrategy::listOfPossiblePoints(AnalyticalStrategy::gp_list shipPoints) {
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

GridPoint* AnalyticalStrategy::findNextPoint(AnalyticalStrategy::gp_list possiblePoints, AnalyticalStrategy::gp_list shipPoints) {
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
            markSunk(std::size(&result))
            shipPoints.push_back(rp);
            return nullptr;
        }
    }
}

std::vector<Direction> AnalyticalStrategy::findDirectionOfShip(AnalyticalStrategy::gp_list shipPoints) {
    GridPoint* first = shipPoints[0];
    GridPoint* second = shipPoints[1];

    if (first->getX() == second->getX()-1 || first->getX() - 1 == second->getX()) {
        return std::vector<Direction>{LEFT, RIGHT};
    } else {
        return std::vector<Direction>{DOWN, UP};
    }
}

void AnalyticalStrategy::findRestOfShip(std::vector<Direction> directions, AnalyticalStrategy::gp_list shipPoints) {
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
                    markSunk(std::size(&result))
                    return;
                }
            } catch (GridPoint::OutOfRangeException& e){
                //pass
            }
        }
    }
}

void AnalyticalStrategy::updateDontCheckPoints(AnalyticalStrategy::gp_list points) {
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

void AnalyticalStrategy::hunt() {
    auto* point = pickMostProbableHuntPoint();
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

GridPoint *AnalyticalStrategy::pickMostProbableHuntPoint() {
    probabilityGrid pg{};
    for (int i = 0; i < 10; i++) {
        std::array<int, 10> tmpArr{};
        std::fill(tmpArr.begin(), tmpArr.end(), 0);
        pg[i] = tmpArr;
    }

    for (auto& [length, quantity] : aliveShips) {
        if (quantity != 0) {
            for (Direction direction : {RIGHT, DOWN}) {
                for (int x = 0; x < 10; x++) {
                    for (int y = 0; y < 10; y++) {
                        GridPoint pointToCheck(x, y);

                        bool foundInDontCheck =
                                std::find_if(dontCheck.begin(), dontCheck.end(), [&pointToCheck](GridPoint* gp){
                                    return *gp == pointToCheck;
                                }) != dontCheck.end();

                        if (grid->isChecked(&pointToCheck) || foundInDontCheck) {
                            continue;
                        }
                        test(direction, length, x, y, &pg);
                    }
                }
            }
        }
    }

    return reduceProbabilityGrid(&pg);

}

void AnalyticalStrategy::test(Direction direction, int length, int x, int y, AnalyticalStrategy::probabilityGrid *pg) {
    try {
        GridPoint tmp(x, y);
        tmp.move(direction, length - 1);
    } catch (GridPoint::OutOfRangeException& e) {
        return;
    }

    for (int delta = 0; delta < length; delta++) {
        GridPoint pointToCheck(x, y);
        pointToCheck.move(direction, delta);

        bool foundInDontCheck =
                std::find_if(dontCheck.begin(), dontCheck.end(), [&pointToCheck](GridPoint* gp){
                    return *gp == pointToCheck;
                }) != dontCheck.end();

        if (grid->isChecked(&pointToCheck) || foundInDontCheck) {
            return;
        }
    }

    for (int delta = 0; delta < length; delta++) {
        GridPoint pointToAdd(x, y);
        pointToAdd.move(direction, delta);

        (*pg)[pointToAdd.getY()][pointToAdd.getX()] += 1;
    }
}

GridPoint *AnalyticalStrategy::reduceProbabilityGrid(AnalyticalStrategy::probabilityGrid *pg) {
    int maxX = 0, maxY = 0;

    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            if ((*pg)[y][x] > (*pg)[maxY][maxX]) {
                maxX = x;
                maxY = y;
            }
        }
    }

    return new GridPoint(maxX, maxY);
}

Result AnalyticalStrategy::doCheck(GridPoint *point) {
    bool foundInDontCheck =
            std::find_if(dontCheck.begin(), dontCheck.end(), [&point](GridPoint* gp){
                return *gp == *point;
            }) != dontCheck.end();
    if (!grid->isChecked(point) && !foundInDontCheck) {
        return grid->check(point);
    }
    return Result(MISS);
}

void AnalyticalStrategy::markSunk(int length) {
    aliveShips[length] -= 1;
}






