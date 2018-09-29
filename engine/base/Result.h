//
// Created by user on 2018-09-24.
//

#ifndef STATKI2_0_RESULT_H
#define STATKI2_0_RESULT_H

#include <string>
#include "../../util/interface/IStringable.h"

enum CheckResult {MISS, HIT, SUNK};

std::ostream& operator<<(std::ostream &strm, const CheckResult &state);

class Result: public IStringable {
public:
    explicit Result(CheckResult r);
    Result(CheckResult r, int l);
    bool operator%(CheckResult r);
    std::string toString() override;
private:
    CheckResult state;
    int length;

};


#endif //STATKI2_0_RESULT_H
