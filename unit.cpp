#include "unit.h"

unit::unit() {
    alive = false;
    flag = false;
    numNeighbors = 0;
}

bool unit::isAlive() { return alive; }

void unit::setNumNeighbors(int n) {
  numNeighbors = n;
}

int unit::getNumNeighbors() {
  return numNeighbors;
}

void unit::die() {alive = false;}
void unit::live() {alive = true;}
void unit::flagLive() {flag = true;}
void unit::flagDie() {flag = false;}
bool unit::getFlag() {return flag;}
