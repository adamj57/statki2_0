//
// Created by user on 2018-09-24.
//

#include <sstream>
#include "Result.h"

std::ostream& operator<<(std::ostream &strm, const CheckResult &state) {
    std::string result;
    switch (state){
        case HIT:
            result = "HIT";
            break;
        case MISS:
            result = "MISS";
            break;
        case SUNK:
            result = "SUNK";
            break;
    }

    return strm << result;
}

Result::Result(CheckResult r) {
    length = 1;
    state = r;
}

Result::Result(CheckResult r, int l) {
    length = l;
    state = r;
}

bool Result::operator%(CheckResult r) {
    return r == state;
}

std::string Result::toString() {
    std::ostringstream stringStream;
    stringStream << state;
    if (state == SUNK) {
        stringStream << "," << length;
        return stringStream.str();
    } else {
        return stringStream.str();
    }
}
