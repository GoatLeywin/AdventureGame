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

    if (!file.is_open()) {
        cout << "Error opening file: " << filename << endl;
        return;
    }

    bool inUsableItemsSection = false;

    while (getline(file, line)) {
        // Check if the line starts with "description:"
        if (line.substr(0, 12) == "description:") {
            description = line.substr(12);
        }
        
        else if (line.substr(0, 6) == "exits:") {
        string exitsLine = line.substr(6);
        stringstream ss(exitsLine);
        string exit;
        while (getline(ss, exit, ',')) {
            // trim leading spaces
            exit.erase(exit.begin(), find_if(exit.begin(), exit.end(), [](unsigned char ch) {
            return !isspace(ch);
        }));
        exits.push_back(exit);
        }
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
        // Check if the line starts with "usable_items:"
        else if (line.substr(0, 13) == "usable_items:") {
            inUsableItemsSection = true;
        }
        // If we are in the "usable_items:" section, parse each item
        else if (inUsableItemsSection) {
            // Expect lines in the form of item_name: description -> action
            size_t delimiterPos = line.find(":");
            if (delimiterPos != string::npos) {
                string itemName = line.substr(0, delimiterPos);
                // Replace underscores with spaces
                for (char& c : itemName) {
                    if (c == '_') c = ' ';
                }
                string itemDescription = line.substr(delimiterPos + 1);

                // Find the action part
                size_t actionPos = itemDescription.find("->");
                if (actionPos != string::npos) {
                    string action = itemDescription.substr(actionPos + 2); // Get the action part after "->"
                    itemDescription = itemDescription.substr(0, actionPos); // Update the description part
                    usableItems[itemName] = make_pair(itemDescription, action); // Store description and action
                }
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

void Room::useItem(const string& itemName, Player& player) {
    auto it = usableItems.find(itemName);
    if (it != usableItems.end()) {
        cout << " " << it->second.first << endl; // Description when item is used

        string effects = it->second.second;
        stringstream ss(effects);
        string singleEffect;

        while (getline(ss, singleEffect, '-')) {
            if (!singleEffect.empty() && singleEffect[0] == '>') {
                singleEffect = singleEffect.substr(1);
            }
            singleEffect.erase(0, singleEffect.find_first_not_of(" \t"));
            singleEffect.erase(singleEffect.find_last_not_of(" \t") + 1);

            if (singleEffect.substr(0, 9) == "add_item:") {
                string newItem = singleEffect.substr(9);
                items.push_back(newItem);
                cout << "A new item appeared: " << newItem << "!" << endl;
            }
            else if (singleEffect.substr(0, 17) == "unlock_direction:") {
                string direction = singleEffect.substr(17);
                exits.push_back(direction);
                cout << "You can now go " << direction << "!" << endl;
            }
            else {
                cout << "Nothing happens..." << endl;
            }
        }
    }
    else {
        cout << "You can't use that here." << endl;
    }
}

bool Room::canExit(const std::string& direction) const {
    return std::find(exits.begin(), exits.end(), direction) != exits.end();
}

void Room::unlockExit(const std::string& direction) {
    if (!canExit(direction)) {
        exits.push_back(direction);
    }
}

