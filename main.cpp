//
// Zombies vs Humans: Final Project
// by Cihan Alcin (w0468444)
// 06 DEC 2023
//

#include <iostream>
#include <chrono>
#include <thread>
#include "Organism.h"
#include "City.h"

using namespace std;

void ClearScreen()
{
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

int main() {
    City *city = new City();
    int turnNumber = ITERATIONS;
    chrono:: milliseconds interval(INTERVAL);

    cout << *city;

    do {
        this_thread::sleep_for(interval);
        ClearScreen();
        cout << "============================================================" << endl;
        cout << "                        Turn: " << turnNumber << endl;
        cout << "============================================================" << endl;
        city->turn();
        city->reset();
        cout << *city;
        city->countOrganisms();
        city->deleteOrMutateMarkedOrganisms();
        turnNumber --;
    }
    while (city->hasDiversity() && turnNumber >= 1);

    this_thread::sleep_for(interval);
    ClearScreen();
    cout << "============================================================" << endl;
    cout << "                 Simulation Ended | Turn: " << turnNumber << endl;
    cout << "============================================================" << endl;
    city->turn();
    city->reset();
    cout << *city;
    city->countOrganisms();
    city->deleteOrMutateMarkedOrganisms();

}//end main

