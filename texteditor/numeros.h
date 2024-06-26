#ifndef NUMEROS_H
#define NUMEROS_H

#include <iostream>
#include <string>
#include <ncurses/ncurses.h>
#include <curses.h>

class Numeros {
    public:
        Numeros();
        ~Numeros();

        void deleteLine();
        void appendLine(); 
};

#endif