#include <iostream>
#include <vector>
#include <string>
#include "Room.h"
#include "Player.h"

using namespace std;

int main() {
    // Create the player with initial coordinates and health
    Player player(0, 0, 100);

    // Initialize the room
    Room library;
    library.setCoordinates(0, 0);
    library.loadFromFile("Rooms/library.txt");

    Room garden;
    garden.setCoordinates(0, 0);
    library.loadFromFile("Rooms/library.txt");



    // Describe the current room
    library.describeRoom();

    string command;
    while (true) {
        cout << "\n> ";
        getline(cin, command);

        // Check if the command is "quit"
        if (command == "quit") {
            break;
        }
        // Check if the command starts with "take "
        else if (command.substr(0, 5) == "take ") {
            string item = command.substr(5);
            library.takeItem(item, player);
        }
        // Check if the command starts with "go "
        else if (command.substr(0, 3) == "go ") {
            string direction = command.substr(3);

            // Check if the player can move in the specified direction
            if (!player.canMove(direction)) {
                cout << "You cannot walk this way." << endl;
                continue;
            }

            // Store the old coordinates before moving
            int oldX = player.getX();
            int oldY = player.getY();

            // Update coordinates based on direction
            if (direction == "north") player.setCoordinates(player.getX(), player.getY() + 1);
            else if (direction == "south") player.setCoordinates(player.getX(), player.getY() - 1);
            else if (direction == "east") player.setCoordinates(player.getX() + 1, player.getY());
            else if (direction == "west") player.setCoordinates(player.getX() - 1, player.getY());
            else {
                cout << "Unknown direction." << endl;
                continue;
            }

            // Get the room from the new coordinates
            Room newRoom = library.getRoomFromCoordinates(player.getX(), player.getY());

            // If the room exists, allow the player to enter and describe it
            if (newRoom.getX() != -1 && newRoom.getY() != -1) {
                cout << "You move " << direction << "." << endl;
                newRoom.describeRoom();
                library = newRoom;  // Update the library to the new room
            }
            else {
                // If no room exists, inform the player they cannot go in that direction
                cout << "You cannot walk this way." << endl;

                // Restore the original coordinates (stay in the same room)
                player.setCoordinates(oldX, oldY);
            }
        }
        // Check if the command is "inventory"
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

    return 0;
}
