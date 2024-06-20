#ifndef NODESTRING_H
#define NODESTRING_H

#include <string>
#include <vector>
#include <cmath>

// ¡SOLO ES EL BUFFER! ¡NADA VISUAL!
// No se si se llama buffer lo que estoy haciendo

class NodeString{  
    private:
        // Apunta al nodo pasado 
        NodeString *previous;

        // Contenido de la linea
        std::string line;

        // Apunta al nodo siguiente
        NodeString *next;

    public:
        // Apunta al primer nodo
        static NodeString *first;

        // Apunta al último nodo
        static NodeString *last;

        // Nodos totales (lineas)
        static int size;

        // Hacer update del first y last en caso de que haga falta desde fuera
        // Hacer current al nuevo desde fuera 
        NodeString(const std::string &line, NodeString *next, NodeString *previous);

        static void putFileInBuffer(std::vector<std::string> fileContent);

        static void goToLine(NodeString *&current, int y, int line);

        static void deleteLine(NodeString *&current, int type); 

        static void deleteChar(NodeString *&current, int y, int x); 

        static void addChar(NodeString *&current, int x, const char ch); 
        
        static void enter(NodeString *&current, int x); 

        // Movimiento POR EL BUFFER
        static void moveUp(NodeString *&current); 
        static void moveDown(NodeString *&current); 
        static void moveLeft(NodeString *&current, int x); 
        static void moveRight(NodeString *&current, int x);
};


#endif 