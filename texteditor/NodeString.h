#ifndef NODESTRING_H
#define NODESTRING_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <ncurses/ncurses.h>
#include <curses.h>
#include "numeros.h"

class NodeString{  
    private:
        NodeString *previous;
        std::string line;
        NodeString *next;

    public:
        static int size;
        NodeString(const std::string &line, NodeString *nextprev, int type);
        NodeString(const std::string &line, NodeString *next, NodeString *previous);

        static void goToLine(NodeString *first, NodeString *&aux, int y, int &x);
        static void deleteLine(NodeString *aux, int y); //solo buffer, pantalla va aparte (en deleteChar, por ejemplo)
        static void deleteChar(NodeString *aux, int &y, int &x); //pantalla y buffer

        static void addChar(NodeString *&aux, int &y, int &x, const char ch); //pantalla y buffer PASAR POR REFERENCIA NO HECHO
        static void enter(NodeString *&aux, int &y, int &x); //pantalla y buffer 

        static void moveUp(NodeString *aux, int y, int x); //pantalla y buffer
        static void moveDown(NodeString *aux, int y, int x); //pantalla y buffer
        static void moveLeft(NodeString *aux, int y, int x); 
        static void moveRight(NodeString *aux, int y, int x);
};


#endif 