//
// Created by user on 2018-09-28.
//

#include <algorithm>
#include <sstream>
#include <cstring>
#include "ShipConfig.h"


ShipConfig::ShipDetails::ShipDetails(int length, int quantity) {
    this->length = length;
    this->quantity = quantity;
}

int ShipConfig::ShipDetails::getQuantity() {
    return quantity;
}

int ShipConfig::ShipDetails::getLength() {
    return length;
}


ShipConfig::ShipConfig(std::string configName) {
    auto c = predefined.find(configName);

    if (c != predefined.end()) {
        config = c->second;
    } else {
        throw ConfigNotFoundException(configName);
    }
}

ShipConfig::ShipConfig()=default;

void ShipConfig::addShipDetails(ShipConfig::ShipDetails* details) {
    config.push_back(details);

}

void ShipConfig::addShipOfLength(int length) {
    for (ShipDetails* ship : config) {
        if (ship->length == length) {
            ship->quantity++;
            return;
        }
    }
    config.push_back(new ShipDetails(length, 1));

}

void ShipConfig::finalize() {
    std::sort(config.begin(), config.end(), [](const auto* lhs, const auto* rhs){
        return lhs->length > rhs->length;
    });
}

ShipConfig::iterator ShipConfig::begin() {
    return config.begin();
}

ShipConfig::iterator ShipConfig::end() {
    return config.end();
}

ShipConfig::const_iterator ShipConfig::begin() const {
    return config.begin();
}

ShipConfig::const_iterator ShipConfig::end() const {
    return config.end();
}

ShipConfig::const_iterator ShipConfig::cbegin() const {
    return config.cbegin();
}

ShipConfig::const_iterator ShipConfig::cend() const {
    return config.cend();
}

ShipConfig::ConfigNotFoundException::ConfigNotFoundException(std::string name) {
    this->name = std::move(name);

}

const char *ShipConfig::ConfigNotFoundException::what() {
    std::ostringstream stream;
    stream << "Config of name " << name << " does not exist!";
    char* dst = new char[strlen(stream.str().c_str())+1];
    strcpy(dst, stream.str().c_str());
    return dst;
}
