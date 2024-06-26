#include "nodeString.h"
#include "textEditor.h"

NodeString *NodeString::first = nullptr;
NodeString *NodeString::last = nullptr;
NodeString *NodeString::current = nullptr;

int NodeString::size = 0;


NodeString::NodeString(const std::string &line, NodeString *next, NodeString *previous) {    
    this->line = line;
    this->next = next;
    this->previous = previous;
    size++;
}

void NodeString::deleteLine() {
    if (current->previous != nullptr) {
        current->previous->next = current->next;
    }
    if (current->next != nullptr) {
        current->next->previous = current->previous;
    }
    if (current == last) {
        last = current->previous;
    }
    NodeString *temp = current;
    current = current->previous;
    delete temp;
    size--;
}

void TextEditor::deleteLine() {
    deleteln();
    TextEditor::y--;
    TextEditor::x = NodeString::current->previous->line.size() + DEFAULT_X + 1; 
    move(TextEditor::y, TextEditor::x);
}


void TextEditor::displaceLine() {
    mvaddch(TextEditor::y, getmaxx(stdscr) - 1, ACS_VLINE);
    move(TextEditor::y, TextEditor::x);

}


void TextEditor::run() {
    int ch;
    while ((ch = getch()) != Ctrl_X) {
        switch (ch) {
            default:
                NodeString::addChar(ch);
                TextEditor::addChar(ch);
                break;
            case KEY_UP:
                if (TextEditor::y == 0  || NodeString::current->previous == nullptr)
                    break;
                TextEditor::moveUp();
                NodeString::moveUp();
                break;
            case KEY_DOWN:
                if (TextEditor::y == NodeString::size || NodeString::current->next == nullptr)
                    break;
                TextEditor::moveDown();
                NodeString::moveDown();
                break;
            case KEY_LEFT:
                if (TextEditor::y == 0 && TextEditor::x == DEFAULT_X)
                    break;
                TextEditor::moveLeft();
                break;
            case KEY_RIGHT:
                if (NodeString::current->next == nullptr && TextEditor::x == NodeString::current->line.size() + DEFAULT_X)
                    break;
                TextEditor::moveRight();
                break;
            case Ctrl_S:
                TextEditor::saveFile(TextEditor::fileName);
                break;
            case KEY_BACKSPACE:
                if (TextEditor::x == DEFAULT_X && TextEditor::y == 0)
                    break;
                NodeString::deleteChar();
                TextEditor::deleteChar();
                break;
        }
    }
} 






