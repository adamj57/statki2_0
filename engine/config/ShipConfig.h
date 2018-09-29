//
// Created by user on 2018-09-28.
//

#ifndef STATKI2_0_SHIPCONFIG_H
#define STATKI2_0_SHIPCONFIG_H


#include <string>
#include <vector>
#include <map>


class ShipConfig {
public:
    class ShipDetails {
        friend ShipConfig;
    public:
        ShipDetails(int length, int quantity);

    private:
        int length;
        int quantity;
    };

    ShipConfig();
    explicit ShipConfig(std::string configName);

    void addShipDetails(ShipDetails* details);
    void addShipOfLength(int length);

    void finalize();

    typedef std::vector<ShipDetails*> ship_config;
    typedef std::map<std::string, ship_config> predefined_config_map;

    using iterator = ship_config::iterator;
    using const_iterator = ship_config::const_iterator;

    iterator begin();
    iterator end();

    const_iterator begin() const;
    const_iterator end() const;

    const_iterator cbegin() const;
    const_iterator cend() const;

private:

    ship_config config;
    predefined_config_map predefined = {{"polish", ship_config{new ShipDetails(4, 1), new ShipDetails(3, 2),
                                                               new ShipDetails(2, 3), new ShipDetails(1, 4)}}};

};




#endif //STATKI2_0_SHIPCONFIG_H
