#ifndef CITY_H

#include <iostream>

using namespace std;

class Organism;

const int GRID_WIDTH = 20;
const int GRID_HEIGHT = 20;

class City
{
protected:
	Organism *grid[GRID_HEIGHT][GRID_WIDTH];

public:
	City();
	virtual ~City();

	Organism *getOrganism( int x, int y );
	void setOrganism( Organism *organism, int x, int y );

	void turn();
    void reset();
    void countOrganisms();
    bool checkELE();
    void display();

	friend ostream& operator<<( ostream &output, City &city );

};

#endif

