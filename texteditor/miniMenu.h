#ifndef MINIMENU_H
#define MINIMENU_H

#include <iostream>
#include <string>
#include <ncurses/ncurses.h>
#include <curses.h>

class MiniMenu {
    public:
        MiniMenu();
        ~MiniMenu();

        void execute();
        void inputError(); 
};

#endif