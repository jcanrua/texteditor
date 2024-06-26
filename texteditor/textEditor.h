#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <ncurses/ncurses.h>
#include <curses.h>
#include "NodeString.h"

class TextEditor {
    private:
        std::string fileName;
    public:
        static WINDOW *numbers;
        static WINDOW *text;

        TextEditor(const std::string& fileName);
        ~TextEditor();

        void openFile(const std::string& fileName);
        void saveFileAs(const std::string& fileName);
        void closeFile();
        void run(); 
};

#endif
