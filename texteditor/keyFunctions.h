#ifndef KEYFUNCTIONS_H
#define KEYFUNCTIONS_H

#include <string>
#include <ncurses/ncurses.h>
#include <curses.h>
#include "NodeString.h"

class KeyFunctions{  
    public:
        static void deleteLineW(int y);
        static void deleteCharW(int y, int x);

        static void enterW(int y);
};


#endif