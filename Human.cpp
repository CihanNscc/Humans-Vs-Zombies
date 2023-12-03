#include "Human.h"
#include "City.h"
#include "Gamespecs.h"

Human::Human() : Organism(nullptr, 0, 0, 'H', HUMAN_CH), recruitCounter(0) {}

Human::Human(City* city, int width, int height) : Organism(city, width, height, 'H', HUMAN_CH), recruitCounter(0) {}

Human::~Human() = default;

void Human::move() {
    // Check if the human has survived for three time-steps
    if (recruitCounter == HUMAN_BREED) {
        recruitNewHuman();
        recruitCounter = 0; // Reset the recruit counter
    } else {
        // Randomly select a direction (0: West, 1: North, 2: East, 3: South)
        int direction = rand() % NUM_DIRECTIONS;

        // Calculate new coordinates based on the selected direction
        int newX = x;
        int newY = y;

        switch (direction) {
            case WEST:
                newX = x - 1;
                break;
            case NORTH:
                newY = y - 1;
                break;
            case EAST:
                newX = x + 1;
                break;
            case SOUTH:
                newY = y + 1;
                break;
        }

        // Check if the new coordinates are within the city boundaries
        if (newX >= 0 && newX < GRID_WIDTH && newY >= 0 && newY < GRID_HEIGHT) {
            // Check if the neighboring cell is empty
            if (city->getOrganism(newX, newY) == nullptr) {
                // Move the human to the new cell
                city->setOrganism(nullptr, x, y); // Clear the current cell
                x = newX;
                y = newY;
                city->setOrganism(this, x, y); // Set the human in the new cell
                recruitCounter++; // Increment the recruit counter
            }
            // If the neighboring cell is occupied, the human stays in the current cell
        }
        // If the new coordinates are outside the city boundaries, the human stays in the current cell

        moved = true;
    }
}

void Human::recruitNewHuman() {
    // Find an empty adjacent cell for recruiting
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if ((i == 0 || j == 0) && (i != 0 || j != 0)) { // Exclude diagonal cells
                int newX = x + i;
                int newY = y + j;

                // Check if the adjacent cell is within the city boundaries
                if (newX >= 0 && newX < GRID_WIDTH && newY >= 0 && newY < GRID_HEIGHT) {
                    // Check if the adjacent cell is empty
                    if (city->getOrganism(newX, newY) == nullptr) {
                        // Recruit a new human in the adjacent cell
                        Human* newHuman = new Human(city, 1, 1);
                        newHuman->setPosition(newX, newY);
                        city->setOrganism(newHuman, newX, newY);
                        return; // Exit the function after recruiting
                    }
                }
            }
        }
    }
}
