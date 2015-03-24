/*
 * Final Project
 * Main driver program
 * Steven Mike & Brian Mann
 */

#include <iostream>
#include <SDL2/SDL.h>
#include <algorithm>
#include <iterator>
#include <string>
#include <fstream>
#include <cmath>
#include "Player.h"
using namespace std;

int main(){

        Player p = Player();
        cout << endl << "X position: " << p.getX();
        cout << endl << "Y position: " << p.getY();
        cout << endl << "Health: " << p.getHealth() << endl;

        p.setX(1.2);
        p.setY(2.3);
        p.setHealth(7);

        cout << endl << "X position: " << p.getX();
        cout << endl << "Y position: " << p.getY();
        cout << endl << "Health: " << p.getHealth();
}
