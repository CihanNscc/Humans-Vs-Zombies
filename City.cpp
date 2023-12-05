#include "City.h"
#include "Organism.h"
#include "Gamespecs.h"
#include "Human.h"
#include "Zombie.h"

#include <vector>
#include <algorithm> // for std::shuffle
#include <random>    // for std::default_random_engine
#include <set>

City::City() {
    // Initialize the grid with nullptr (empty)
    for (int i = 0; i < GRID_HEIGHT; ++i) {
        for (int j = 0; j < GRID_WIDTH; ++j) {
            grid[i][j] = nullptr;
        }
    }

    // Populate the city with initial zombies in each quadrant
    for (int i = 0; i < ZOMBIE_START_COUNT; ++i) {
        int quadrant = i % 4;
        int x = rand() % (GRID_WIDTH / 2) + (quadrant % 2) * GRID_WIDTH / 2;
        int y = rand() % (GRID_HEIGHT / 2) + (quadrant / 2) * GRID_HEIGHT / 2;

        if (grid[y][x] == nullptr) {
            grid[y][x] = new Zombie(this, x, y);
        } else {
            --i;
        }
    }

    // Populate the city with initial humans without overriding zombies
    for (int i = 0; i < HUMAN_START_COUNT; ++i) {
        int x = rand() % GRID_WIDTH;
        int y = rand() % GRID_HEIGHT;

        if (grid[y][x] == nullptr) {
            grid[y][x] = new Human(this, x, y);
        } else {
            --i;
        }
    }
}

City::~City() {
    // Clean up memory for organisms
    for (int i = 0; i < GRID_HEIGHT; ++i) {
        for (int j = 0; j < GRID_WIDTH; ++j) {
            delete grid[i][j];
        }
    }
}

Organism* City::getOrganism(int x, int y) {
    // Return the organism at the specified location
    if (x >= 0 && x < GRID_WIDTH && y >= 0 && y < GRID_HEIGHT) {
        return grid[y][x];
    }
    return nullptr;
}

void City::setOrganism(Organism* organism, int x, int y) {
    // Set the organism at the specified location
    if (x >= 0 && x < GRID_WIDTH && y >= 0 && y < GRID_HEIGHT) {
        grid[y][x] = organism;
    }
}

void City::deleteOrMutateMarkedOrganisms() {
    // Use a set to keep track of unique organisms to delete
    std::set<Organism*> organismsToDelete;

    // Erase-remove idiom to remove and delete marked organisms
    organisms.erase(std::remove_if(organisms.begin(), organisms.end(),
                                   [this, &organismsToDelete](Organism* organism) {
                                       bool markedForRemoval = organism->isMarkedForRemoval();
                                       bool markedForMutation = organism->isMarkedForMutation();

                                       // Check if the organism is marked for removal
                                       if (markedForRemoval) {
                                           int x = organism->getX();
                                           int y = organism->getY();

                                           // Check if the organism is not already in the set
                                           if (organismsToDelete.find(organism) == organismsToDelete.end()) {
                                               organismsToDelete.insert(organism);

                                               // Check if the organism is marked for mutation
                                               if (markedForMutation) {
                                                   // Convert the organism into a zombie
                                                   grid[y][x] = new Zombie(this, x, y);
                                                   // cout << "An organism mutated into a zombie." << endl;
                                               } else {
                                                   // Delete the organism
                                                   delete organism;
                                                   // cout << "An organism deleted." << endl;
                                                   grid[y][x] = nullptr; // Update grid to nullptr
                                               }
                                           }
                                       }

                                       return markedForRemoval;
                                   }),
                    organisms.end());
}

void City::turn() {
    // Collect all organisms in the city
    organisms.clear();
    for (int i = 0; i < GRID_HEIGHT; ++i) {
        for (int j = 0; j < GRID_WIDTH; ++j) {
            if (grid[i][j] != nullptr) {
                organisms.push_back(grid[i][j]);
            }
        }
    }

    // do something to clear marked organisms

    // Move organisms in the city
    for (Organism* organism : organisms) {
        organism->move();
    }

}

ostream& operator<<(ostream& output, City& city) {
    // Print the city grid
    for (int i = 0; i < GRID_HEIGHT; ++i) {
        for (int j = 0; j < GRID_WIDTH; ++j) {
            if (city.grid[i][j] != nullptr) {
                output << city.grid[i][j];
            } else {
                output << SPACE_CH;
            }
        }
        output << endl;
    }
    return output;
}
