//
// Created by user on 2018-09-27.
//

#include <sstream>
#include <cstring>
#include "Grid.h"
#include "../../util/len.h"
#include "../../util/str.h"
#include "../../util/random.h"

Grid::Grid() {
    grid = generateBlankGrid();
    checkedCells = 0;
    checkedShipCells = 0;

}

Grid::Grid(ShipConfig *config): Grid() {
    for (ShipConfig::ShipDetails* shipDetail : *config) {
        for (int i = 0; i < shipDetail->getQuantity(); i++) {
            placeRandomShip(shipDetail->getLength());
        }
    }
}

std::array<std::array<Cell*, 10>, 10> Grid::generateBlankGrid() {
    std::array<std::array<Cell*, 10>, 10> arr{};
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            arr[i][j] = new Cell(new GridPoint(j, i));
        }
    }
    return arr;
}

void Grid::placeShip(GridPoint* p0, Direction direction, int length) {
    std::vector<GridPoint*> valid_coords;
    for (int i = 0; i < length; i++) {
        checkShipNearby(p0);
        valid_coords.push_back(p0);
        p0 = p0->move(direction);
    }
    std::vector<Cell*> cells;
    for (GridPoint* point : valid_coords) {
        Cell* cell = cellAt(point);
        cell->setShipCell();
        cells.push_back(cell);

    }
    Ship* ship = new Ship(cells);
    ships.push_back(ship);
}

void Grid::placeRandomShip(int length) {
    bool shipPlaced = false;
    int triesCount = 0;

    while(!shipPlaced && triesCount < 50){
        GridPoint point(random(0, 9), random(0, 9));
        auto direction = static_cast<Direction>(random(0, 3));

        try {
            placeShip(&point, direction, length);
            shipPlaced = true;
        } catch (ShipPlacementException&) {
            (void)0; // NOP
        }

        triesCount++;
    }

    if (!shipPlaced) {
        std::ostringstream stream;
        stream << "Ship of length: " << length << " could not be matched to the random created board after 50 tries -"
                                               << " you have bad luck!";
        throw ShipPlacementException(stream.str());
    }
}

void Grid::checkShipNearby(GridPoint* point) {

    std::array<int, 3> x_offsets = {-1, 0, 1};
    std::array<int, 3> y_offsets = x_offsets;

    for (int x : x_offsets) {
        for (int y : y_offsets) {
            checkOffset(point, x, y);
        }
    }

}

void Grid::checkOffset(GridPoint* point, int x_offset, int y_offset) {
    if ((point->getX() + x_offset < 0) || (point->getX() + x_offset > 9)) {
        return;
    }
    if ((point->getY() + y_offset < 0) || (point->getY() + y_offset > 9)) {
        return;
    }
    if (cellAt(new GridPoint(point->getX() + x_offset, point->getY() + y_offset))->isShipCell()) {
        std::ostringstream stream;
        stream << "The ship is placed nearby - you can't place ship cell there (x: " << point->getX() << ", y: "
        << point->getY() << ") according to the rules!";
        throw ShipPlacementException(stream.str());
    }
}

Cell* Grid::cellAt(GridPoint *point) {
    return grid[point->getY()][point->getX()];
}

Result Grid::check(GridPoint* point) {
    auto ret = Result(MISS);
    if (cellAt(point)->isShipCell()) {
        checkedShipCells++;
        for (Ship* ship : ships) {
            if (ship->hasPoint(point)) {
                ship->hit(point);
                if (ship->isSunk()) {
                    ret = Result(SUNK, std::size(ship));
                } else {
                    ret = Result(HIT);
                }
            }
        }
    }
    cellAt(point)->setCheck();
    checkedCells++;
    return ret;
}

bool Grid::isChecked(GridPoint* point) {
    return cellAt(point)->isChecked();
}

bool Grid::isWon() {
    for (Ship* ship : ships) {
        if (!ship->isSunk()) {
            return false;
        }
    }
    return true;
}

void Grid::mark(GridPoint* point, std::string marker) {
    cellAt(point)->setMarker(std::move(marker));
}

std::string Grid::toString() {
    std::string str = "  0 1 2 3 4 5 6 7 8 9\n";
    for (size_t i = 0; i < grid.size(); i++) {
        str += std::to_string(i);
        str += " ";
        for (Cell* cell : grid[i]) {
            str += std::to_string(cell) + " ";
        }
        str += "\n";
    }
    return str;
}

Grid::ShipPlacementException::ShipPlacementException(std::string desc) {
    this->desc = std::move(desc);

}

const char *Grid::ShipPlacementException::what() {
    std::ostringstream stream;
    stream << "ShipPlacementException: " << desc << std::endl;
    char* dst = new char[strlen(stream.str().c_str())+1];
    strcpy(dst, stream.str().c_str());
    return dst;
}
