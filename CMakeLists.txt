cmake_minimum_required(VERSION 3.12)
project(statki2_0)

set(CMAKE_CXX_STANDARD 17)

add_executable(statki2_0 main.cpp engine/base/Result.cpp engine/base/Result.h engine/base/GridPoint.cpp engine/base/GridPoint.h util/interface/IStringable.cpp util/interface/IStringable.h util/str.cpp util/str.h engine/base/Cell.cpp engine/base/Cell.h engine/base/Ship.cpp engine/base/Ship.h util/interface/IMeasurable.cpp util/interface/IMeasurable.h util/len.cpp util/len.h util/random.cpp util/random.h engine/base/Grid.cpp engine/base/Grid.h engine/config/ShipConfig.cpp engine/config/ShipConfig.h simple-cli/SimpleCLI.cpp simple-cli/SimpleCLI.h)

set(CMAKE_EXE_LINKER_FLAGS " -static")