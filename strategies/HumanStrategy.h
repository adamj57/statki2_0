//
// Created by user on 2018-10-22.
//

#ifndef STATKI2_0_HUMANSTRATEGY_H
#define STATKI2_0_HUMANSTRATEGY_H


#include "Strategy.h"

class HumanStrategy: Strategy {
public:
    HumanStrategy();
    void run(Grid* grid) override;

private:
    typedef std::vector<GridPoint*> gp_list;
    enum Mode {HUNT, DESTROY};

    void hunt();
    void destroy();

    gp_list listOfPossiblePoints(gp_list shipPoints);
    GridPoint* findNextPoint(gp_list possiblePoints, gp_list shipPoints);
    std::vector<Direction> findDirectionOfShip(gp_list shipPoints);
    void findRestOfShip(std::vector<Direction> directions, gp_list shipPoints);
    void updateDontCheckPoints(gp_list points);
    Result doCheck(GridPoint* point);

    Grid* grid;
    Mode mode;
    gp_list dontCheck;
    GridPoint* first;

};


#endif //STATKI2_0_HUMANSTRATEGY_H
