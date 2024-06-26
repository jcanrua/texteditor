#ifndef NODESTRING_H
#define NODESTRING_H

#include <string>
#include <vector>

class NodeString{  
    public:
        // Points to the previous node
        NodeString *previous;

        // Content of the line
        std::string line;

        // Points to the next node
        NodeString *next;

        // Points to the first node
        static NodeString *first;

        // Points to the last node
        static NodeString *last;

        // Points to the current node
        static NodeString *current;

        // Total number of nodes (lines)
        static int size;

        // Constructor
        NodeString(const std::string &line, NodeString *next, NodeString *previous);

        // Puts the content of a file into the buffer
        static void putFileInBuffer(std::vector<std::string> fileContent);    
        
        // Moves to a specific line and position
        static void goToLine(int y, int line);

        // Deletes a line
        static void deleteLine(); 

        // Deletes a character at a specific position in a line
        static void deleteChar(); 

        // Adds a character to the current line
        static void addChar(const char ch); 
        
        // Creates a new line at a specific position
        static void newLine(int x); 

        // Creates a new line at the end of the buffer
        static void newLine(); 

        // Moves the current line up
        static void moveUp();

        // Moves the current line down
        static void moveDown();
};

#endif 