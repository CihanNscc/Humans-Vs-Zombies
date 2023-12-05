#include "Zombie.h"
#include "City.h"
#include "Gamespecs.h"

#include <algorithm>
#include <random>

Zombie::Zombie() : Organism(nullptr, 0, 0, 'Z', ZOMBIE_CH, false), breedCounter(0), starveCounter(0) {}

Zombie::Zombie(City* city, int x, int y) : Organism(city, x, y, 'Z', ZOMBIE_CH, false), breedCounter(0), starveCounter(0) {}

Zombie::~Zombie() = default;

void Zombie::move() {
    if (starveCounter >= ZOMBIE_STARVE){
        starve();
    } else {
        if (checkAdjacentHumans()) {
            if (breedCounter >= ZOMBIE_BREED) {
               // breed();
                breedCounter = 0;
            } else {
                eat();
            }
        } else {
            starveCounter ++;
            moveRandom();
        }
    }

    breedCounter++;
    moved = true;
}

void Zombie::breed() {
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if ((i == 0 || j == 0) && (i != 0 || j != 0)) { // Exclude the current cell
                int newX = x + i;
                int newY = y + j;

                // Check if the adjacent cell is within the city boundaries
                if (newX >= 0 && newX < GRID_WIDTH && newY >= 0 && newY < GRID_HEIGHT) {
                    // Check if the adjacent cell contains a human
                    Organism* adjacentOrganism = city->getOrganism(newX, newY);
                    cout << "Value at (" << newX << ", " << newY << "): " << adjacentOrganism << endl;

                    if (adjacentOrganism != nullptr && adjacentOrganism->organismType == 'H') {
                        // Convert the adjacent human into a zombie
                        delete adjacentOrganism;
                        city->setOrganism(new Zombie(city, newX, newY), newX, newY);
                        breedCounter = 0;
                        return;
                    }
                }
            }
        }
    }
}





void Zombie::starve() {
    markForRemoval();
}

bool Zombie::checkAdjacentHumans() {
    // Check for adjacent humans in all directions (vertically, horizontally, and diagonally)
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if ((i == 0 || j == 0) && (i != 0 || j != 0)) { // Exclude the current cell
                int newX = x + i;
                int newY = y + j;

                // Check if the adjacent cell is within the city boundaries
                if (newX >= 0 && newX < GRID_WIDTH && newY >= 0 && newY < GRID_HEIGHT) {
                    // Check if the adjacent cell contains a human
                    if (city->getOrganism(newX, newY) != nullptr &&
                        city->getOrganism(newX, newY)->organismType == 'H') {
                        // Human found adjacent, return true
                        return true;
                    }
                }
            }
        }
    }
    // No adjacent humans found
    return false;
}

void Zombie::moveRandom() {
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
                // Move the zombie to the new cell
                city->setOrganism(nullptr, x, y); // Clear the current cell
                x = newX;
                y = newY;
                city->setOrganism(this, x, y); // Set the zombie in the new cell
                return; // Exit the function after successful move
            }
        }
    }

    // If all directions are occupied or outside the city boundaries, the zombie stays in the current cell
}

void Zombie::eat() {
    // Find an adjacent human and convert it into a zombie
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if ((i == 0 || j == 0) && (i != 0 || j != 0)) { // Exclude the current cell
                int newX = x + i;
                int newY = y + j;

                // Check if the adjacent cell is within the city boundaries
                if (newX >= 0 && newX < GRID_WIDTH && newY >= 0 && newY < GRID_HEIGHT) {
                    // Check if the adjacent cell contains a human
                    Organism* adjacentOrganism = city->getOrganism(newX, newY);
                    if (adjacentOrganism != nullptr && adjacentOrganism->organismType == 'H') {
                        // Mark the adjacent human for removal
                        adjacentOrganism->markForRemoval();
                        cout << "A human got eaten." << endl;
                        starveCounter = 0;
                        return; // Exit the function after successful "eat"
                    }
                }
            }
        }
    }
    // No adjacent humans found to eat
}
