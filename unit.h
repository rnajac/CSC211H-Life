#ifndef UNIT_H
#define UNIT_H
#include <iostream>
using namespace std;

class unit {
private:
  bool alive;   // cell state
  bool flag;    // for marking a cell to stay alive
  int numNeighbors; // number of live neighbors

public:
  unit();
  bool isAlive();
  //int getX() const;
  //int getY() const;
  //void set(int x, int y);
  //void print() const;
  void setNumNeighbors(int n);
  int getNumNeighbors();
  void die();
  void live();
  void flagLive();
  void flagDie();
  bool getFlag();
};
#endif