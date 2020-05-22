#include "world.h"
int world::getTicks() { return ticks; }
void world::incTicks() { ticks++; }


int world::countNeighbors(int i, int j) {
    int neighbors = 0;
    for (int row = (i - 1); row <= (i + 1); row++) {
        if ((row == -1) || (row == SIZE)) {}
        else
            for (int column = (j - 1); column <= (j + 1); column++) {
                if ((column == -1) || (column == SIZE)) {}
                else
                    if ((row == i) && (column == j)) {}
                    else {
                        if (cell[row][column].isAlive()) {
                            neighbors++;
                        }
                    }
            }
    }
    return neighbors;
}

void world::flagLife() {
    for (int row = 0; row < SIZE; row++) {
        for (int column = 0; column < SIZE; column++) {
            cell[row][column].flagDie();
            // if the cell has 3 neighors, stays alive or becomes alive
            if (countNeighbors(row, column) == 3) {
                cell[row][column].flagLive();
            }
            else
                // if the cell is alive and has 2 neighbors it lives
                if (cell[row][column].isAlive()) {
                    if (countNeighbors(row, column) == 2) {
                        cell[row][column].flagLive();
                    }
                }
                else {}
        }
    }
}

void world::cycle() {
    for (int row = 0; row < SIZE; row++) {
        for (int column = 0; column < SIZE; column++) {
            if (cell[row][column].getFlag()) {
                cell[row][column].live();
            }
            else {
                cell[row][column].die();
            }
        }
    }
    world::incTicks();
}

void world::printWorld() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (cell[i][j].isAlive()) {
                cout << "0 ";
            }
            else {
                cout << ". ";
            }
        }
        cout << endl;
    }
    cout << endl << " Ticks = " << getTicks();
}

void world::run() {
    world::flagLife();
    world::cycle();
    world::printWorld();
}

void world::testNeighbors() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cout << world::countNeighbors(i, j);
            cout << " ";
        }
        cout << endl;
    }
    cout << endl;
}


int world::convertArray(int i, int j) {
    int life = 0;
    if (cell[i][j].isAlive()) {
        life = 1;
    }
    return life;
}



void world::seedBlinkerOscillator() {
    cell[5][5].live();
    cell[6][5].live();
    cell[7][5].live();
    cell[8][5].live();
    cell[9][5].live();
    cell[5][7].live();
    cell[9][7].live();
    cell[5][9].live();
    cell[6][9].live();
    cell[7][9].live();
    cell[8][9].live();
    cell[9][9].live();
}

void world::seedSpaceshipGlider() {
    cell[0][2].live();
    cell[1][0].live();
    cell[1][2].live();
    cell[2][1].live();
    cell[2][2].live();
}

void world::seedLWSS() {
    cell[1][11].live();
    cell[2][10].live();
    cell[3][10].live();
    cell[4][10].live();
    cell[4][11].live();
    cell[4][12].live();
    cell[4][13].live();
    cell[1][14].live();
    cell[3][14].live();
}