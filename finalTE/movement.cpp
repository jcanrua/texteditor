#include "nodeString.h"
#include "textEditor.h"

int TextEditor::y = 0;
int TextEditor::x = DEFAULT_X; 

// Set the default position of the text editor
void TextEditor::defaultPosition() {
    TextEditor::y = 0;
    TextEditor::x = DEFAULT_X;
    move(TextEditor::y, TextEditor::x);
}

// Move the current node pointer up
void NodeString::moveUp() {
    current = current->previous;
}

// Move the current node pointer down
void NodeString::moveDown() {
    current = current->next;
}

// Move the cursor up in the text editor
void TextEditor::moveUp() {
    TextEditor::y--;

    // Adjust the x position if it exceeds the length of the previous line
    if (TextEditor::x > NodeString::current->previous->line.size() + DEFAULT_X){
        TextEditor::x = NodeString::current->previous->line.size() + DEFAULT_X;
        move(TextEditor::y, TextEditor::x);
    } else {
        move(TextEditor::y, TextEditor::x);
    }
}

// Move the cursor down in the text editor
void TextEditor::moveDown() {
    TextEditor::y++;

    // Adjust the x position if it exceeds the length of the next line
    if (TextEditor::x > NodeString::current->next->line.size() + DEFAULT_X){
        TextEditor::x = NodeString::current->next->line.size() + DEFAULT_X;
        move(TextEditor::y, TextEditor::x);
    } else {
        move(TextEditor::y, TextEditor::x);
    }
}

// Move the cursor left in the text editor
void TextEditor::moveLeft() {
    if (TextEditor::x == DEFAULT_X){
        // If at the beginning of the line, move to the end of the previous line
        TextEditor::x = NodeString::current->previous->line.size() + DEFAULT_X;
        TextEditor::y--;
        move(TextEditor::y, TextEditor::x);
        NodeString::moveUp();
    } else {
        // Otherwise, move left by one position
        TextEditor::x--;
        move(TextEditor::y, TextEditor::x);
    }
}

// Move the cursor right in the text editor
void TextEditor::moveRight() {
    if (TextEditor::x == NodeString::current->line.size() + DEFAULT_X) {
        // If at the end of the line, move to the beginning of the next line
        TextEditor::x = DEFAULT_X;
        TextEditor::y++;
        move(TextEditor::y, TextEditor::x);
        NodeString::moveDown();
    } else {
        // Otherwise, move right by one position
        TextEditor::x++;
        move(TextEditor::y, TextEditor::x);
    }
}
