//
// Created by user on 2018-09-29.
//

#include <random>
#include <chrono>
#include "random.h"

namespace util {
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 mt {seed};
    thread_local static std::uniform_int_distribution<int> pick;

    int random_in_range(int min, int max) {

        return pick(mt, decltype(pick)::param_type{min, max});
    }
}
