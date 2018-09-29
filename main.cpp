#include <iostream>
#include <string>
#include "engine/base/Result.h"
#include "engine/base/GridPoint.h"
#include "util/str.h"
#include "engine/base/Cell.h"
#include "util/interface/IStringable.h"
#include "engine/base/Ship.h"
#include "engine/config/ShipConfig.h"

int main() {
    auto* r1 = new Result(SUNK);
    std::cout << std::to_string(r1) << std::endl;
    auto* r2 = new Result(HIT, 2);
    std::cout << std::to_string(r2) << std::endl;

    auto* gp1 = new GridPoint(1, 1);
    std::cout << std::to_string(gp1) << std::endl;

    auto* c1 = new Cell(gp1);
    auto* c2 = new Cell(*c1);
    auto* c3 = new Cell(new GridPoint(1, 2));

    std::cout << (*c1 == *c2) << std::endl;
    std::vector<Cell*> arr = {c1, c3};

    auto* s1 = new Ship(arr);
    s1->hit(new GridPoint(1, 2));
    std::cout << s1->isSunk() << std::endl;
    s1->hit(new GridPoint(1, 1));
    std::cout << s1->isSunk() << std::endl;

    auto* sc1 = new ShipConfig();
    sc1->addShipDetails(new ShipConfig::ShipDetails(1, 2));
    sc1->addShipDetails(new ShipConfig::ShipDetails(2, 1));
    sc1->addShipDetails(new ShipConfig::ShipDetails(6, 1));
    sc1->addShipDetails(new ShipConfig::ShipDetails(3, 1));

    sc1->finalize();


    try {
        auto* gp2 = new GridPoint(1, 10);
        std::cout << std::to_string(gp2) << std::endl;
    } catch (GridPoint::OutOfRangeException& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }


}