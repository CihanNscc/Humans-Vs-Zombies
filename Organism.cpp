#define WIN32_LEAN_AND_MEAN
#include "Organism.h"
#include "City.h"

#include <windows.h>

using namespace std;

Organism::Organism() : x(0), y(0), moved(false), city(nullptr), organismType('U'), asciiRepresentation('U'), markedForRemoval(false), markedForMutation(false) {}

Organism::Organism(City* city, int x, int y, char organismType, char asciiRepresentation, bool markedForRemoval, bool markedForMutation)
        : x(x), y(y), moved(false), city(city), organismType(organismType), asciiRepresentation(asciiRepresentation), markedForRemoval(false), markedForMutation(false) {}

Organism::~Organism() = default;

void Organism::setPosition(int xCoordinate, int yCoordinate)
{
    this->x = xCoordinate;
    this->y = yCoordinate;
}

void Organism::endTurn()
{
    moved = false;
}

char Organism::getOrganismType() const {
    return organismType;
}

void Organism::markForRemoval() {
    markedForRemoval = true;
}

bool Organism::isMarkedForRemoval() const {
    return markedForRemoval;
}

void Organism::markForMutation() {
    markedForMutation = true;
}

bool Organism::isMarkedForMutation() const {
    return markedForMutation;
}

int Organism::getX() const {
    return x;
}

int Organism::getY() const {
    return y;
}

void Coloring(char asciiRepresentation) {
    int colorNumber = 8;
    switch (asciiRepresentation) {
        case HUMAN_CH:
            colorNumber = HUMAN_COLOR;
            break;
        case ZOMBIE_CH:
            colorNumber = ZOMBIE_COLOR;
            break;
        default:
            colorNumber = 8;
            break;
    }

    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, colorNumber);
}

ostream& operator<<(ostream& output, Organism* organism) {
    Coloring(organism->asciiRepresentation);
    if (organism != nullptr) {
        output << organism->asciiRepresentation;
        HANDLE  hConsole;
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
    }

    return output;
}
