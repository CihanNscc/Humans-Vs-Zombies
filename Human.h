#ifndef _Human_H

#include "Organism.h"

class Human : public Organism
{private:
    int recruitCounter;
public:
	Human(); 
	Human( City *city, int x, int y );
	~Human() override;

    void move() override;
	void recruitNewHuman();
};

#endif
