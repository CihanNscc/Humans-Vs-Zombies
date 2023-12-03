#ifndef Zombie_H
#define Zombie_H

#include "Organism.h"

class Zombie : public Organism {
private:
    int breedCounter;
    int starveCounter;

public:
    Zombie();
    Zombie(City* city, int width, int height);
    ~Zombie() override;

    void move() override;
    void breed();
    void starve();
};

#endif