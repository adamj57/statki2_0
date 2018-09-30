//
// Created by user on 2018-09-27.
//

#ifndef STATKI2_0_SHIP_H
#define STATKI2_0_SHIP_H

#include <vector>
#include "Cell.h"
#include "../../util/interface/IMeasurable.h"

class Ship: public IMeasurable {
public:
    class SunkException: public std::exception {
    public:
        const char * what() const noexcept override;
    };

    class NotInShipException: public std::exception {
    public:
        explicit NotInShipException(GridPoint* point);
        const char * what() const noexcept override;

    private:
        GridPoint* point;
    };

    //TODO: add const noexcept to what
    //TODO: add __LINE__ and __FILE__ to the exception throwers

    explicit Ship(std::vector<Cell*> cells);

    bool hasPoint(GridPoint* point);
    void hit(GridPoint* point);
    bool isSunk();

    size_t size() override;

private:
    bool evaluateSunk();

    std::vector<Cell*> cells;
    bool sunk;
};


#endif //STATKI2_0_SHIP_H
