#pragma once
#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>
#include <map>
#include "Player.h"

class Room {
private:
    double x_coord;
    double y_coord;
    std::string description;
    std::vector<std::string> items;
    std::map<std::string, std::pair<std::string, std::string>> usableItems;
    std::vector<std::string> exits;

public:
    void setCoordinates(int, int);
    double getX() const;
    double getY() const;

    void loadFromFile(const std::string& filename);
    void describeRoom() const;
    bool takeItem(const std::string& item, Player& player);
    bool useItem(const std::string& item, Player& player);
    
    bool canExit(const std::string& direction) const;
    void unlockExit(const std::string& direction);
};

#endif
