#include "Human.h"
#include "City.h"
#include "Gamespecs.h"

#include <algorithm>
#include <random>

Human::Human() : Organism(nullptr, 0, 0, 'H', HUMAN_CH, false, false), recruitCounter(0) {}

Human::Human(City* city, int x, int y) : Organism(city, x, y, 'H', HUMAN_CH, false, false), recruitCounter(0) {}

Human::~Human() = default;

void Human::move() {
    // Check if the human has survived for three time-steps
    if (recruitCounter == HUMAN_BREED) {
        recruitNewHuman();
        recruitCounter = 0; // Reset the recruit counter
    } else {
        // Generate a random order for directions
        std::vector<int> directions = {WEST, NORTH, EAST, SOUTH};
        std::shuffle(directions.begin(), directions.end(), std::default_random_engine(std::random_device{}()));

        for (int i = 0; i < NUM_DIRECTIONS; ++i) {
            // Calculate new coordinates based on the selected direction
            int direction = directions[i];
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
                    moved = true;
                    return; // Exit the function after successful move
                }
            }
        }

        // If all directions are occupied or outside the city boundaries, the human stays in the current cell
        moved = true;
        // Increment recruit counter even if no move is made (adjust this as needed)
        recruitCounter++;
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
