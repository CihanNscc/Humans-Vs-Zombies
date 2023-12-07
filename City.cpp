#define WIN32_LEAN_AND_MEAN

#include "City.h"
#include "Organism.h"
#include "Gamespecs.h"
#include "Human.h"
#include "Zombie.h"

#include <algorithm>
#include <set>
#include <windows.h>

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

                                       if (!markedForRemoval) {
                                           // Check if the organism is marked for mutation
                                           if (organism->isMarkedForMutation()) {
                                               int x = organism->getX();
                                               int y = organism->getY();

                                               if (organism->getOrganismType() == 'H') {
                                                   grid[y][x] = new Zombie(this, x, y);
                                               }
                                               else if (organism->getOrganismType() == 'Z') {
                                                   grid[y][x] = new Human(this, x, y);
                                               }
                                           }
                                       }
                                       else {
                                           int x = organism->getX();
                                           int y = organism->getY();

                                           // Check if the organism is not already in the set
                                           if (organismsToDelete.find(organism) == organismsToDelete.end()) {
                                               organismsToDelete.insert(organism);
                                               // Delete the organism
                                               delete organism;
                                               grid[y][x] = nullptr;
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
                output << ' ';
                output << city.grid[i][j];
                output << ' ';
            } else {
                HANDLE  hConsole;
                hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
                output << " - ";
            }
        }
        output << endl;
    }
    return output;
}

void City::countOrganisms() {
    int zombieCount = 0;
    int humanCount = 0;

    // Count zombies and humans in the city
    for (int i = 0; i < GRID_HEIGHT; ++i) {
        for (int j = 0; j < GRID_WIDTH; ++j) {
            if (grid[i][j] != nullptr) {
                if (grid[i][j]->getOrganismType() == 'Z') {
                    ++zombieCount;
                } else if (grid[i][j]->getOrganismType() == 'H') {
                    ++humanCount;
                }
            }
        }
    }

    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, BOARD_COLOR);
    // Output the counts
    cout << "============================================================" << endl;
    cout << "                Zombies: " << zombieCount << " |====| Humans: " << humanCount << endl;
    cout << "============================================================" << endl;
}

bool City::hasDiversity() {
    int zombieCount = 0;
    int humanCount = 0;

    // Count zombies and humans in the city
    for (int i = 0; i < GRID_HEIGHT; ++i) {
        for (int j = 0; j < GRID_WIDTH; ++j) {
            if (grid[i][j] != nullptr) {
                if (grid[i][j]->getOrganismType() == 'Z') {
                    ++zombieCount;
                } else if (grid[i][j]->getOrganismType() == 'H') {
                    ++humanCount;
                }
            }
        }
    }

    if (zombieCount == 0 || humanCount == 0) {
        return false;
    } else {
        return true;
    }

}

void City::reset() {
    // Reset movement flags for all organisms
    for (int i = 0; i < GRID_HEIGHT; ++i) {
        for (int j = 0; j < GRID_WIDTH; ++j) {
            if (grid[i][j] != nullptr) {
                grid[i][j]->endTurn();
            }
        }
    }
}
