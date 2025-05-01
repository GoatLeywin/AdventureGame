#include <iostream>
#include <vector>
#include <string>
#include "Room.h"
#include "Player.h"

using namespace std;

// New function to search for a room by coordinates
Room* getRoomFromCoordinates(const vector<Room>& rooms, int x, int y) {
    for (const auto& room : rooms) {
        if (room.getX() == x && room.getY() == y) {
            return new Room(room); // Return a copy (you could also return pointer to const Room to avoid allocation)
        }
    }
    return nullptr; // No matching room found
}

int main() {
    vector<Room> rooms;
    
    // Initialize the rooms
    Room library;
    library.setCoordinates(0, 0);
    library.loadFromFile("library.txt");
    rooms.push_back(library);

    Room garden;
    garden.setCoordinates(1, 0);
    garden.loadFromFile("garden.txt");
    rooms.push_back(garden);
    
    // Create the player
    Player player(0, 0, 100);

    // Get the starting room
    Room* currentRoom = getRoomFromCoordinates(rooms, player.getX(), player.getY());
    if (currentRoom) {
        currentRoom->describeRoom();
    } else {
        cout << "Starting room not found!" << endl;
        return 1;
    }

    string command;
    while (true) {
        cout << "\n> ";
        getline(cin, command);

        if (command == "quit") {
            break;
        }
        else if (command.substr(0, 5) == "take ") {
            string item = command.substr(5);
            currentRoom->takeItem(item, player);
        }
        else if (command.substr(0, 3) == "go ") {
            string direction = command.substr(3);

            if (!player.canMove(direction)) {
                cout << "You cannot walk this way." << endl;
                continue;
            }

            int oldX = player.getX();
            int oldY = player.getY();

            // Update player coordinates temporarily
            if (direction == "north") player.setCoordinates(player.getX(), player.getY() + 1);
            else if (direction == "south") player.setCoordinates(player.getX(), player.getY() - 1);
            else if (direction == "east") player.setCoordinates(player.getX() + 1, player.getY());
            else if (direction == "west") player.setCoordinates(player.getX() - 1, player.getY());
            else {
                cout << "Unknown direction." << endl;
                continue;
            }

            // Try to find the new room
            Room* newRoom = getRoomFromCoordinates(rooms, player.getX(), player.getY());

            if (newRoom) {
                cout << "You move " << direction << "." << endl;
                delete currentRoom; // Free the old current room
                currentRoom = newRoom;
                currentRoom->describeRoom();
            }
            else {
                cout << "You cannot walk this way." << endl;
                player.setCoordinates(oldX, oldY); // Go back
            }
        }
        else if (command == "inventory") {
            cout << "Inventory: ";
            for (const string& item : player.getInventory()) {
                cout << item << ", ";
            }
            cout << endl;
        }
        else {
            cout << "Unknown command." << endl;
        }
    }

    delete currentRoom; // Clean up memory when exiting
    return 0;
}
