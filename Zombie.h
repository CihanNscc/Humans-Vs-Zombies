#ifndef Zombie_H
#define Zombie_H

#include "Organism.h"

class Zombie : public Organism {
private:
    int breedCounter;
    int starveCounter;

public:
    Zombie();
    Zombie(City* city, int x, int y);
    ~Zombie() override;

    void move() override;
    void breed();
    void starve();
    bool checkAdjacentHumans();
    void eat();
    void moveRandom();
};

#endif