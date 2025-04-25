#include "Player.h"
#include <algorithm>

using namespace std;

bool Player::removeItem(const string& item) {
    auto it = find(inventory.begin(), inventory.end(), item);
    if (it != inventory.end()) {
        inventory.erase(it);
        return true;
    }
    return false;
}

bool Player::hasItem(const string& item) const {
    return find(inventory.begin(), inventory.end(), item) != inventory.end();
}

bool Player::canMove(const string& direction) {
    // This is just an example to restrict movement in certain directions
    // You can add more logic here based on the game's rules.
    return direction == "north" || direction == "south" || direction == "east" || direction == "west";
}
