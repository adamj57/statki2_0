cmake_minimum_required(VERSION 3.12)
project(statki2_0)

set(CMAKE_CXX_STANDARD 17)

add_executable(statki2_0 main.cpp engine/Result.cpp engine/Result.h engine/GridPoint.cpp engine/GridPoint.h util/interface/IStringable.cpp util/interface/IStringable.h util/str.cpp util/str.h engine/Cell.cpp engine/Cell.h engine/Ship.cpp engine/Ship.h util/interface/IMeasurable.cpp util/interface/IMeasurable.h util/len.cpp util/len.h)