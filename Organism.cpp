#include "Organism.h"
#include "City.h"
#include "GameSpecs.h"

//#include <iostream>
//#include <windows.h>
//#include <conio.h>

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

bool Organism::isTurn()
{
    return !moved;
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

void City::countOrganisms() {
    // Count and display the number of humans and zombies...
}

bool City::checkELE() {
    // Check for ELE (Extinction Level Event)...
}

void City::display() {
    // Display the city grid...
}

int Organism::getX() const {
    return x;
}

int Organism::getY() const {
    return y;
}

//void Coloring(char asciiRepresentation) {
//    int colorNumber = 8;
//    switch (asciiRepresentation) {
//        case HUMAN_CH:
//            colorNumber = HUMAN_COLOR;
//            break;
//        case ZOMBIE_CH:
//            colorNumber = ZOMBIE_COLOR;
//            break;
//        default:
//            colorNumber = 8;
//            break;
//    }
//
//    HANDLE  hConsole;
//    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//    SetConsoleTextAttribute(hConsole, c);
//}

ostream& operator<<(ostream& output, Organism* organism) {
//    Coloring(organism->asciiRepresentation);
    if (organism != nullptr) {
        output << organism->asciiRepresentation;
    } else {
        // Handle the case where organism is a null pointer
        // You might want to print an alternative representation or handle it differently
        output << "NULL_ORGANISM";
    }
//    _getch();
    return output;
}
