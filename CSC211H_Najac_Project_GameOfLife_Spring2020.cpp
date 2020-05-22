// CSC211H_Najac_Project_GameOfLife_Spring2020.cpp

#include <iostream>
#include <stdexcept>            // Need for exceptions
#include <windows.h>            // Needed to clear console
#include <SFML/Graphics.hpp>    // SMFL
#include "world.h"              // world header file
using namespace std;

// function to recieve an int from user
// this function has built in exception handling
int getInt();

// borrowed from cplusplus.com user: Duthomhas
void ClearScreen();

int main() {

    world myWorld;                      // instance of the world object containing the cells and rules of Life
    bool quit = false;                  // flag to break the control loop
    int choice;                         // variable to hold the value from user input
    sf::VertexArray grid;               // vertex array from SFML to represent cells
    grid.setPrimitiveType(sf::Quads);   // sets the objects in the vertex array to rectangles
    const int SIZE = 15;                // length and width of the grid
    int tileSize = 32;                  // size (in pixels?) of rectangles
    grid.resize(SIZE * SIZE * 4);       // sets the correct size of the grid in the window

    // main menu
    cout << "\n Welcome to John Conway's Game of Life!" << endl;
    cout << " Life is a cellular automaton and zero-player 'game'." << endl;
    cout << " Just seed the initial state configuration of live and dead cells..." << endl;
    cout << " and every cell follows the same set of rules in which they live and die." << endl << endl;

    cout << " Please select one of the following states:" << endl;
    cout << " 1 - Spaceship Glider" << endl;
    cout << " 2 - Blinker Oscillator" << endl;
    cout << " 3 - Lightweight Spaceship" << endl;
    cout << " 4 - Spaceship Glider and Blinker Oscillator" << endl;
    cout << " 5 - Lightweight Spaceship and Blinker Oscillator" << endl;
    cout << " 6 - Spaceship Glider and Lightweight Spaceship" << endl;

    // menu commands
    choice = getInt();
    switch (choice) {
    case 1:
        myWorld.seedSpaceshipGlider();
        break;
    case 2:
        myWorld.seedBlinkerOscillator();
        break;
    case 3:
        myWorld.seedLWSS();
        break;
    case 4:
        myWorld.seedSpaceshipGlider();
        myWorld.seedBlinkerOscillator();
        break;
    case 5:
        myWorld.seedLWSS();
        myWorld.seedBlinkerOscillator();
        break;
    case 6:
        myWorld.seedSpaceshipGlider();
        myWorld.seedLWSS();
        break;
    default:
        cout << " Invalid entry!" << endl << "Exiting program..." << endl;
        exit(1);
    }

    // create the window for SFML vertex array animation
    sf::RenderWindow window(sf::VideoMode(480, 480), "Game of Life");

    // run the loop
    while (window.isOpen() && (quit == false)) {
        // populate the vertex array, with one quad per tile
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                // get the current cell state
                bool cellState = myWorld.convertArray(i, j);

                // get a pointer to the current tile's quad
                sf::Vertex* quad = &grid[(i + j * SIZE) * 4];

                // define its 4 corners
                quad[0].position = sf::Vector2f(i * tileSize, j * tileSize);
                quad[1].position = sf::Vector2f((i + 1) * tileSize, j * tileSize);
                quad[2].position = sf::Vector2f((i + 1) * tileSize, (j + 1) * tileSize);
                quad[3].position = sf::Vector2f(i * tileSize, (j + 1) * tileSize);

                // if the cell is alive, the quad is black.
                if (cellState) {
                    quad[0].color = sf::Color::Black;
                    quad[1].color = sf::Color::Black;
                    quad[2].color = sf::Color::Black;
                    quad[3].color = sf::Color::Black;
                }

                // if the cell is dead, the quad is white
                else {
                    quad[0].color = sf::Color::White;
                    quad[1].color = sf::Color::White;
                    quad[2].color = sf::Color::White;
                    quad[3].color = sf::Color::White;
                }
            }
        }
        // refresh and animate the window
        window.clear();
        window.draw(grid);
        window.display();

        // refresh the console 
        ClearScreen();

        // iterator
        myWorld.run();

        cout << "\n Press the ESC key anytime to exit..." << endl;
        if (GetAsyncKeyState(VK_ESCAPE)) {
                quit = true;
        }

        // pause between frames
        Sleep(300);

        // handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }
    cout << "\n Thanks for playing! Goodbye!" << endl;
    return 0;
}

int getInt() {
    int n;
    try {
        cin >> n;
        if (!cin) {
            throw runtime_error("an invalid input!");
        }
        else
            if (n < 0) {
                throw runtime_error("a negative number !");
            }
            else
                if (n > 6) {
                    throw runtime_error("a number greater than 6!");
                }
                else {}
    }

    catch (runtime_error& excpt) {
        cerr << "You have entered " << excpt.what() << endl;
        cerr << "Please try again." << endl;
        cin.clear();
        cin.ignore(9999, '\n');
        return getInt();
    }
    return n;
}
void ClearScreen()
{
    HANDLE                     hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD                      count;
    DWORD                      cellCount;
    COORD                      homeCoords = { 0, 0 };

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdOut == INVALID_HANDLE_VALUE) return;

    /* Get the number of cells in the current buffer */
    if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    /* Fill the entire buffer with spaces */
    if (!FillConsoleOutputCharacter(
        hStdOut,
        (TCHAR)' ',
        cellCount,
        homeCoords,
        &count
    )) return;

    /* Fill the entire buffer with the current colors and attributes */
    if (!FillConsoleOutputAttribute(
        hStdOut,
        csbi.wAttributes,
        cellCount,
        homeCoords,
        &count
    )) return;

    /* Move the cursor home */
    SetConsoleCursorPosition(hStdOut, homeCoords);
}
