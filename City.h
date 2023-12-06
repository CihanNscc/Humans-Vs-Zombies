#ifndef CITY_H
#define CITY_H

#include "Gamespecs.h"

#include <iostream>
#include <vector>

using namespace std;

class Organism;

const int GRID_WIDTH = GRID_SIZE;
const int GRID_HEIGHT = GRID_SIZE;

class City
{
protected:
	Organism *grid[GRID_HEIGHT][GRID_WIDTH];
    vector<Organism*> organisms;

public:
	City();
	virtual ~City();

	Organism *getOrganism( int x, int y );
	void setOrganism( Organism *organism, int x, int y );
	void deleteOrMutateMarkedOrganisms();

	void turn();
    void reset();
    void countOrganisms();
    bool hasDiversity();

	friend ostream& operator<<( ostream &output, City &city );

};

#endif

