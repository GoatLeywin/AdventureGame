#pragma once
#include <vector>
#include <string>

using namespace std;

class Player {
private:
    int x_coord;
    int y_coord;
    int health;
    vector<string> inventory;

public:
    Player(int x = 0, int y = 0, int health = 100)
        : x_coord(x), y_coord(y), health(health) {}

    // Getter methods for coordinates, health, and inventory
    int getX() const { return x_coord; }
    int getY() const { return y_coord; }
    int getHealth() const { return health; }
    const vector<string>& getInventory() const { return inventory; }

    // Setter methods for coordinates and health
    void setCoordinates(int x, int y) { x_coord = x; y_coord = y; }
    void setHealth(int h) { health = h; }

    // Inventory manipulation methods
    void addItem(const string& item) { inventory.push_back(item); }
    bool removeItem(const string& item);
    bool hasItem(const string& item) const;

    // Health manipulation methods
    void heal(int amount) { health += amount; }
    void takeDamage(int amount) { health -= amount; }

    // Can the player move to the direction?
    bool canMove(const string& direction);
};
