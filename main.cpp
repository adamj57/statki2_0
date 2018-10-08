#include <iostream>
#include <string>
#include "engine/base/Result.h"
#include "engine/base/GridPoint.h"
#include "util/str.h"
#include "engine/base/Cell.h"
#include "util/interface/IStringable.h"
#include "engine/base/Ship.h"
#include "engine/config/ShipConfig.h"
#include "engine/base/Grid.h"
#include "simple-cli/SimpleCLI.h"

int main() {
    return SimpleCLI().run();
    auto* r1 = new Result(SUNK);
    std::cout << "Result r1: " << std::to_string(r1) << std::endl;
    auto* r2 = new Result(HIT, 2);
    std::cout << "Result r2: " << std::to_string(r2) << std::endl;

    auto* gp1 = new GridPoint(1, 1);
    std::cout << "GridPoint gp1: " << std::to_string(gp1) << std::endl;

    auto* c1 = new Cell(gp1);
    auto* c2 = new Cell(*c1);
    auto* c3 = new Cell(new GridPoint(1, 2));

    std::cout << std::boolalpha << "c1 == c2?: " << (*c1 == *c2) << std::endl;
    std::vector<Cell*> arr = {c1, c3};

    auto* s1 = new Ship(arr);
    s1->hit(new GridPoint(1, 2));
    std::cout << "s1 sunk after x=1, y=2 hit: " << s1->isSunk() << std::endl;
    s1->hit(new GridPoint(1, 1));
    std::cout << "s1 sunk after x=1, y=1 hit: " << s1->isSunk() << std::endl;

    auto* sc1 = new ShipConfig("polish");

    auto* g1 = new Grid(sc1);

    std::cout << std::to_string(g1);


//    try {
//        auto* gp2 = new GridPoint(1, 10);
//        std::cout << std::to_string(gp2) << std::endl;
//    } catch (GridPoint::OutOfRangeException& e) {
//        std::cerr << e.what() << std::endl;
//        return -1;
//    }


}