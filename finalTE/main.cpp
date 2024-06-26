#include "textEditor.h"
#include "nodeString.h"

int main(int argc, char *argv[]) {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    
    NodeString::current = new NodeString("", nullptr, nullptr);
    NodeString::first = NodeString::last = NodeString::current;
    
    TextEditor::defaultPosition();

    if (argc > 1) {
        TextEditor::fileName = argv[1];
        TextEditor::openFile(TextEditor::fileName);
    } else {
        TextEditor::openFile(TextEditor::fileName);
    }

    TextEditor::run();
    TextEditor::closeFile();
    return 0;
}