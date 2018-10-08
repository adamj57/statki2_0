//
// Created by user on 2018-09-27.
//

#ifndef STATKI2_0_GRID_H
#define STATKI2_0_GRID_H

#include <array>
#include <vector>
#include "GridPoint.h"
#include "Cell.h"
#include "Result.h"
#include "Ship.h"
#include "../config/ShipConfig.h"

class Grid: public IStringable {
public:
    class ShipPlacementException: public std::exception {
    public:
        explicit ShipPlacementException(std::string desc);
        const char * what() const noexcept override;

    private:
        std::string desc;
    };
    Grid();
    explicit Grid(ShipConfig* config);

    void placeShip(GridPoint* p0, Direction direction, int length);
    void placeRandomShip(int length);
    Result check(GridPoint* point);
    void mark(GridPoint* point, std::string marker);

    bool isChecked(GridPoint* point);
    bool isWon();

    std::string toString() override;

private:
    std::array<std::array<Cell*, 10>, 10> generateBlankGrid();

    void checkShipNearby(GridPoint* point);
    void checkOffset(GridPoint* point, int x_offset, int y_offset);

    Cell* cellAt(GridPoint* point);

    std::array<std::array<Cell*, 10>, 10> grid;
    std::vector<Ship*> ships;
    int checkedCells;
    int checkedShipCells;

};

#endif //STATKI2_0_GRID_H
