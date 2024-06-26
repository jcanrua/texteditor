#ifndef DISPLAYED_H
#define DISPLAYED_H

#include "textEditor.h"
#include "nodeString.h"
#include <ncurses.h>
#include <vector>
#include <string>

class Display{  
    public:
        // Posicion GLOBAL y
        static int y;

        // Posicion GLOBAL x
        static int x;

        static void defaultPosition();

        static void goToLine(int line);

        // Verificar en el run() que la linea cabe arriba HAY QUE HACER OTRA FUNCION PARA CUANDO NO
        static void deleteLine(); 

        // FUNICONA BIEN (no he probado limites)
        static void deleteChar(); 
        
        // FUNCIONA BIEN (no he probado limites)
        static void addChar(const char ch); 
        
        static void newLine();
        // Movimiento POR LA TERMINAL
        static void moveUp(); 
        static void moveDown(); 
        static void moveLeft(); 
        static void moveRight();

        static void putFileInScreen(std::vector<std::string>);
};


#endif 