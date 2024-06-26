#include "displayed.h"

// Constants for better readability
const int DEFAULT_X = 5;
const int LINE_OFFSET = 5; 

int Display::y = 0;
int Display::x = DEFAULT_X;

void Display::defaultPosition() {
    y = 0;
    x = DEFAULT_X;
    move(y,x);
}

void Display::goToLine(int line) {
    y = line;
    x = NodeString::current->line.size() + LINE_OFFSET;
    move(y,x);
}

// Esto no va a ir
void Display::deleteLine() {
    if (NodeString::current->line.size() > 0) {
        std::string removedLine = NodeString::current->line;
        clrtoeol();
        x = NodeString::current->previous->line.size() + LINE_OFFSET;
        mvaddstr(--y, x, removedLine.c_str());
    } else {
        clrtoeol();

    }
}

void Display::deleteChar() {
    if (x == DEFAULT_X && y == 0){
        return;
    } else if (x == DEFAULT_X && y != 0){
        deleteLine();
    } else {    
        mvdelch(y, --x);
    }
}

void Display::addChar(const char ch) {
    if (x == getmaxx(stdscr) - 1) {
        NodeString::newLine(999999); // Para que no salte lo otro 
        x = DEFAULT_X;
        mvaddch(++y, x, ch);
    } else {
        mvaddch(y, x++, ch);
    }
}


void Display::newLine() {
    std::string newLine;
    if (x < NodeString::current->line.size()) {
        newLine = NodeString::current->line.substr(x);
        NodeString::current->line.erase(x);  

        clrtoeol();  

        x = DEFAULT_X;  
        mvaddstr(++y, x, newLine.c_str());  
    } else {
        x = DEFAULT_X;  
        move(++y, x);  
    }
}

void Display::moveUp() {
    if (y == 0) {
        return;
    }

    if (NodeString::current->line.size() > NodeString::current->previous->line.size()){
        x = NodeString::current->previous->line.size();
        move(--y, x);
    } else {
        move(--y, x);
    }
}

void Display::moveDown() {
    if (y == NodeString::size) {
        return;
    }

    if (NodeString::current->line.size() > NodeString::current->next->line.size()){
        x = NodeString::current->next->line.size();
        move(++y, x);
    } else {
        move(++y, x);
    }
}

void Display::moveLeft() {
    if (y == 0 && x == DEFAULT_X){
        return;
    } else if (x == DEFAULT_X){
        x = NodeString::current->previous->line.size();
        move(--y, x);
    } else {
        move(y, --x);
    }
}

void Display::moveRight() {
    if (x == getmaxx(stdscr) && y == NodeString::size) {
        return;
    } else if (x == getmaxx(stdscr)) {
        x = DEFAULT_X;
        move(++y, x);
    } else {
        move(y, ++x);
    }
}


void Display::putFileInScreen(std::vector<std::string> fileContent) {
    defaultPosition();
    clear();
    for (const auto &line : fileContent) {
        mvaddstr(y, x, line.c_str());
        y++;
    }
    refresh();
    defaultPosition();
} 