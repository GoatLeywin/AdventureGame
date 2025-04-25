#pragma once
#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>
#include "Player.h" // Include Player class

class Room {
private:
    double x_coord;
    double y_coord;
    std::string description;
    std::vector<std::string> items;

public:
    void setCoordinates(int, int);
    double getX() const;
    double getY() const;

    void loadFromFile(const std::string& filename);
    void describeRoom() const;
    bool takeItem(const std::string& item, Player& player);
    Room getRoomFromCoordinates(int x, int y);  // Get room based on coordinates
};

#endif
