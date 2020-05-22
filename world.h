#ifndef WORLD_H
#define WORLD_H
#include "unit.h"

class world {
  private:
    // count the numeber of iterations/generations 
    int ticks;
    // set the size of the world
    const static int SIZE = 15;
    // 2-D array of units as cells
    unit cell[SIZE][SIZE];

  public:  
    // default constructor
    world() {ticks = 0;}
    // function to increment ticks
    void incTicks();
    // fuction to return the number of ticks
    int getTicks();
    // function that returns the number of live neighbors for a cell at a particular coordinate
    int countNeighbors(int x, int y);
    // function that flags whether a cell will live or die in the next generation
    void flagLife();
    // function that reads the flag and triggers cell birth or cell death
    void cycle();
    // prints the 2-D array of cells in ASCII with '0' as alive and '.' as dead
    void printWorld();
    // combines other functions
    void run();
    // returns if a cell is alive for SFML vertex array
    int convertArray(int i, int j);
    // used in testing, returns the number of live neighbors
    void testNeighbors();

    // seed starting states
    void seedBlinkerOscillator();
    void seedSpaceshipGlider();
    void seedLWSS();
    // plan on adding more
};

#endif