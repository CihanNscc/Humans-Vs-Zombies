#include "Zombie.h"
#include "Gamespecs.h"

Zombie::Zombie() : Organism(nullptr, 0, 0, 'Z', ZOMBIE_CH), breedCounter(0), starveCounter(0) {}

Zombie::Zombie(City* city, int width, int height) : Organism(city, width, height, 'Z', ZOMBIE_CH), breedCounter(0), starveCounter(0) {}

Zombie::~Zombie() = default;

void Zombie::move() {
    // Move to an adjacent cell containing a human and eat the human
    // If no human is present, move to an empty position
    // Implement the logic for eating humans and moving here

    // After moving/eating, check if breedCounter needs to be incremented
    breedCounter++;
    if (breedCounter == ZOMBIE_BREED) {
        breed();
        breedCounter = 0; // Reset the breed counter
    }

    // Check if starveCounter needs to be incremented
    starveCounter++;
    if (starveCounter == ZOMBIE_STARVE) {
        starve();
        starveCounter = 0; // Reset the starve counter
    }

    moved = true;
}

void Zombie::breed() {
    // Convert a randomly selected adjacent human into a zombie
    // Implement the logic for converting a human into a zombie here
}

void Zombie::starve() {
    // Convert the zombie to a human if it has not eaten any humans within three time-steps
    // Implement the logic for converting a zombie to a human here
}