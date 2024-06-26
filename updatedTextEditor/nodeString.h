#ifndef NODESTRING_H
#define NODESTRING_H

#include <string>
#include <vector>
#include <cmath>

// ¡SOLO ES EL BUFFER! ¡NADA VISUAL!
// No se si se llama buffer lo que estoy haciendo

class NodeString{  
    public:
        // Apunta al nodo pasado 
        NodeString *previous;

        // Contenido de la linea
        std::string line;

        // Apunta al nodo siguiente
        NodeString *next;

        // Apunta al primer nodo
        static NodeString *first;

        // Apunta al último nodo
        static NodeString *last;

        // Apunta al nodo actual
        static NodeString *current;

        // Nodos totales (lineas)
        static int size;

        NodeString(const std::string &line, NodeString *next, NodeString *previous);

        static void putFileInBuffer(std::vector<std::string> fileContent);

        static void goToLine(int y, int line);

        static void deleteLine(int type); 

        static void deleteChar(int y, int x); 

        static void addChar(int x, const char ch); 
        
        static void newLine(int x); 

        static void newLine(); 

        // Movimiento POR EL BUFFER
        static void moveUp();

        static void moveDown();

        static void moveLeft(int x); 
        
        static void moveRight(int x);
};


#endif 