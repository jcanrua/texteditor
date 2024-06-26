#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include "nodeString.h"
#include "keymap.h"
#include <ncurses.h>
#include <string>
#include <fstream>
#include <vector>
#include <iostream>

// Class representing a text editor
class TextEditor {
    public:
        // Current Y position in the editor
        static int y;
        
        // Current X position in the editor
        static int x;

        // Name of the file being edited
        static std::string fileName; 

        // Open a file for editing
        static void openFile(const std::string &fileName);

        // Save the contents of the editor to a file
        static void saveFile(const std::string &filename);

        // Close the currently opened file
        static void closeFile();

        // Run the text editor
        static void run();

        // Set the default position in the editor
        static void defaultPosition();

        // Display the contents of the file on the screen
        static void putFileInScreen(std::vector<std::string>);

        // Go to a specific line in the file
        static void goToLine(int line);

        // Delete the current line 
        static void deleteLine(); 

        // Delete the character at the current position
        static void deleteChar(); 
        
        // Add a character at the current position
        static void addChar(const char ch); 
        
        // Insert a new line at the current position
        static void newLine();

        static void displaceLine();

        // Move the cursor up
        static void moveUp(); 

        // Move the cursor down
        static void moveDown(); 

        // Move the cursor left
        static void moveLeft(); 

        // Move the cursor right
        static void moveRight();
};

#endif