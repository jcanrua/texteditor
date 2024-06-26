#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include "nodeString.h"
#include "displayed.h"
#include "ascii.h"
#include "keymap.h"
#include <ncurses.h>
#include <string>
#include <fstream>

class TextEditor {
    public:
        
        static std::string fileName;

        static void initialize();

        static void openFile(const std::string &fileName);

        static void saveFile(const std::string &filename);

        static void saveCloseFile(const std::string &filename);

        static void closeFile();

        static void run();
};

#endif