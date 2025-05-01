#include "Room.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "Player.h"

using namespace std;

void Room::setCoordinates(int x, int y) {
    x_coord = x;
    y_coord = y;
}

double Room::getX() const { return x_coord; }
double Room::getY() const { return y_coord; }

void Room::loadFromFile(const string& filename) {
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        // Check if the line starts with "description:"
        if (line.substr(0, 12) == "description:") {
            description = line.substr(12);
        }
        // Check if the line starts with "items:"
        else if (line.substr(0, 6) == "items:") {
            string itemsLine = line.substr(6);
            stringstream ss(itemsLine);
            string item;
            while (getline(ss, item, ',')) {
                items.push_back(string(item.begin() + (item[0] == ' '), item.end())); // trim leading space
            }
        }
    }
}

void Room::describeRoom() const {cout << description << endl;}

bool Room::takeItem(const string& item, Player& player) {
    auto it = find(items.begin(), items.end(), item);
    if (it != items.end()) {
        player.addItem(item); // Add to player's inventory
        items.erase(it);      // Remove item from room
        cout << "You took the " << item << "." << endl;
        return true;
    }
    cout << "That item isn't here." << endl;
    return false;
}
