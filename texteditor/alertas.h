#ifndef ALERTAS_H
#define ALERTAS_H

#include <iostream>
#include <string>
#include <ncurses/ncurses.h>
#include <curses.h>

class Alertas {
    public:
        Alertas(const std::string& alerta);
        ~Alertas(); 
};

#endif