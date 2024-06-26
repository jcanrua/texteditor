#include "textEditor.h"


void TextEditor::initialize(){
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    
    NodeString::current = new NodeString("", nullptr, nullptr);
    NodeString::first = NodeString::last = NodeString::current;
    
    defaultPosition();
}




