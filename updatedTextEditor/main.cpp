#include "textEditor.h"
#include <iostream>

int main(int argc, char *argv[]) {
    // Initialize the text editor
    TextEditor::initialize();

    // Check if a file is passed as an argument to open
    if (argc > 1) {
        TextEditor::fileName = argv[1];
        TextEditor::openFile(TextEditor::fileName);
    } else {
        TextEditor::fileName = "untitled.txt";
        TextEditor::openFile(TextEditor::fileName );
    }

    // Run the text editor
    TextEditor::run();

    // Close the text editor
    TextEditor::closeFile();

    return 0;
}