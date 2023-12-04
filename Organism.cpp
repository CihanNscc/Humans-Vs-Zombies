#include "Organism.h"
#include "City.h"
#include "GameSpecs.h"

//#include <iostream>
//#include <windows.h>
//#include <conio.h>

using namespace std;

Organism::Organism() : x(0), y(0), moved(false), city(nullptr), organismType('U'), asciiRepresentation('U') {}

Organism::Organism(City* city, int x, int y, char organismType, char asciiRepresentation)
        : x(x), y(y), moved(false), city(city), organismType(organismType), asciiRepresentation(asciiRepresentation) {}

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
    output << organism->asciiRepresentation;
//    _getch();
    return output;
}
