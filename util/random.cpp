//
// Created by user on 2018-09-29.
//

#include <random>
#include "random.h"


thread_local std::mt19937 gen{std::random_device{}()};

template<typename T>
T random(T min, T max) {
    return std::uniform_int_distribution<T>{min, max}(gen);
}