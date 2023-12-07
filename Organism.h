#ifndef _Organism_H
#define _Organism_H

#include <iostream>

using namespace std;

class City;

class Organism
{
protected:
	int x;
	int y;
	bool moved;
	City *city;
    char asciiRepresentation;
	enum { WEST, NORTH, EAST, SOUTH, NUM_DIRECTIONS };
    enum { W, N, E, S, NW, NE, SE, SW, Z_NUM_DIRECTIONS };

private:
    bool markedForRemoval;
    bool markedForMutation;

public:
    char organismType;
	Organism();
	Organism( City *city, int x, int y, char organismType, char asciiRepresentation, bool markedForRemoval, bool markedForMutation );
	virtual ~Organism();

	virtual void move() = 0;

    char getOrganismType() const;
	void setPosition( int x, int y );
	void endTurn();
    void markForRemoval();
    bool isMarkedForRemoval() const;
    void markForMutation();
    bool isMarkedForMutation() const;
    int getX() const;
    int getY() const;

	friend ostream& operator<<( ostream &output, Organism *organism );
};

#endif
