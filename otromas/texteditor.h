#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <ncurses/ncurses.h>
#include <curses.h>

class TextEditor {
private:
    std::string fileName;
    std::vector<std::string> lines;


public:

    TextEditor();
    TextEditor(const std::string& fileName);
    ~TextEditor();

    void openFile(const std::string& fileName);
    void saveFileAs(const std::string& fileName);
    void closeFile();
    void displayFile();
    void run(); 
};

#endif
