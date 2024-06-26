#ifndef KEYFUNCTIONS_H
#define KEYFUNCTIONS_H

#include <string>
#include <ncurses/ncurses.h>

class KeyFunctions{  
    public:
        static void addChar(int y, int x, const char ch);
        static void enter(int y);

        static void deleteLine(int y);
        static void deleteChar(int y, int x);


};


#endif