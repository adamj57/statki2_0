//
// Created by user on 2018-10-29.
//

#ifndef STATKI2_0_ANALYTICALSTRATEGY_H
#define STATKI2_0_ANALYTICALSTRATEGY_H


#include "Strategy.h"

class AnalyticalStrategy: Strategy {
public:
    AnalyticalStrategy();
    void run(Grid* grid) override;

private:
    typedef std::vector<GridPoint*> gp_list;
    typedef std::array<std::array<int, 10>, 10> probabilityGrid;
    enum Mode {HUNT, DESTROY};

    void hunt();
    void destroy();

    gp_list listOfPossiblePoints(gp_list shipPoints);
    GridPoint *findNextPoint(gp_list possiblePoints, gp_list shipPoints);
    std::vector<Direction> findDirectionOfShip(gp_list shipPoints);
    void findRestOfShip(std::vector<Direction> directions, gp_list shipPoints);
    void updateDontCheckPoints(gp_list pointsToCheckAround);
    GridPoint* pickMostProbableHuntPoint();
    void test(Direction direction, int length, int x, int y, probabilityGrid* pg);
    GridPoint* reduceProbabilityGrid(probabilityGrid* pg);
    Result doCheck(GridPoint* point);
    void markSunk(int length);


    Grid* grid;
    Mode mode;
    gp_list dontCheck;
    GridPoint* first;
    std::map<int, int> aliveShips;
};


#endif //STATKI2_0_ANALYTICALSTRATEGY_H
