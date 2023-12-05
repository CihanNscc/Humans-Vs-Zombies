#ifndef GAMESPECS_H

#include <string>

const int GRID_SIZE = 20; // size of the square grid
const int HUMAN_START_COUNT = 100; // initial Humans 100
const int ZOMBIE_START_COUNT = 5; //initial Zombie count
const int HUMAN_BREED = 3; // steps until a Human breeds
const int ZOMBIE_BREED = 2; // steps until an Zombie breeds
const int ZOMBIE_STARVE = 3; // steps until a Zombie starves and converts back
const char HUMAN_CH = 72;// "H"// ascii for Human
const char SPACE_CH = 45; // "-" ascii dash for empty elements
const char ZOMBIE_CH = 90;//90 "Z"// ascii for zombie
const double PAUSE_SECONDS = .09; // pause between steps
const int ITERATIONS = 1000; // max number of steps

//Colors
//0  = black				//9  = bright blue
//1  = blue					//10 = bright green
//2  = green				//11 = bright turquoise
//3  = turquise				//12 = bright red
//4  = red					//13 = bright pink
//5  = pink					//14 = bright yellow
//6  = yellow				//15 = bright white
//7  = white regular		//16+ = solid blocks
//8  = white pale

const int HUMAN_COLOR = 3; // turquoise
const int ZOMBIE_COLOR = 14; // bright yellow

#endif