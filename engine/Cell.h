//
// Created by user on 2018-09-27.
//

#ifndef STATKI2_0_CELL_H
#define STATKI2_0_CELL_H


#include "GridPoint.h"

class Cell: public IStringable {
public:
    explicit Cell(GridPoint* point);
    Cell(Cell& obj);

    bool isChecked();
    void setCheck();

    bool isShipCell();
    void setShipCell();

    void setMarker(std::string marker);

    std::string toString() override;
    bool operator==(Cell& other);

    GridPoint* pos;

private:
    bool shipCell, checked;
    std::string marker = "\0";
};


#endif //STATKI2_0_CELL_H
