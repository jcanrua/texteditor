#include "nodeString.h"
#include "textEditor.h"

void NodeString::addChar(const char ch) {
    NodeString::current->line.insert(TextEditor::x - DEFAULT_X, 1, ch);
}

void TextEditor::addChar(const char ch) {
    if (x == NodeString::current->line.size() + DEFAULT_X) {
        TextEditor::x++;
        mvaddch(TextEditor::y, TextEditor::x, ch);
    } else {
        insch(ch);
        TextEditor::x++;
        move(TextEditor::y ,TextEditor::x);
    }
}

void NodeString::deleteChar() {
    std::string aux = NodeString::current->line;
    if (TextEditor::x == DEFAULT_X) {
        int a = NodeString::current->previous->line.size() + aux.size();
        if (a > getmaxx(stdscr)){
            return; // Cambiar en un futuro
        } else {
            TextEditor::deleteLine();
            NodeString::current->previous->line += aux;
            NodeString::deleteLine();
            addstr(aux.c_str());
        }
    } else {
        // Otherwise, delete the character at the current position
        NodeString::current->line.erase(TextEditor::x - DEFAULT_X - 1, 1);
    }
}
void TextEditor::deleteChar() {
    if (TextEditor::x == DEFAULT_X) {
        // If at the beginning of the line, move to the end of the previous line
        TextEditor::x = NodeString::current->previous->line.size() + DEFAULT_X;
        TextEditor::y--;
        move(TextEditor::y, TextEditor::x);
        NodeString::moveUp();
    } else {
        // Otherwise, move left by one position
        TextEditor::x--;
        mvdelch(TextEditor::y, TextEditor::x);
    }
}

