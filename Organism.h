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

private:
    bool markedForRemoval;

public:
    char organismType;
	Organism();
	Organism( City *city, int x, int y, char organismType, char asciiRepresentation, bool markedForRemoval );
	virtual ~Organism();

	virtual void move() = 0;
	//virtual void spawn() = 0;
	//virtual int getSpecies() = 0; //this could also be coded concrete here
	//virtual void getPosition() = 0;

	void setPosition( int x, int y );
	void endTurn();
	bool isTurn();
    void markForRemoval();
    bool isMarkedForRemoval() const;
    int getX() const;
    int getY() const;

	friend ostream& operator<<( ostream &output, Organism *organism );
};

#endif
