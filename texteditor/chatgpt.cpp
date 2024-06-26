#include "NodeString.h"
#include <ncurses.h> // Assuming ncurses is being used

int NodeString::size = 0;

NodeString::NodeString(const std::string &line, NodeString *nextprev, int type) {
    this->line = line;
    if (type > 0) {
        this->next = nextprev;
        this->previous = nullptr;
        if (nextprev != nullptr) nextprev->previous = this;
    } else {
        this->next = nullptr;
        this->previous = nextprev;
        if (nextprev != nullptr) nextprev->next = this;
    }
    size++;
}

NodeString::NodeString(const std::string &line, NodeString *next, NodeString *previous) {
    this->line = line;
    this->next = next;
    this->previous = previous;
    if (next != nullptr) next->previous = this;
    if (previous != nullptr) previous->next = this;
    size++;
}

void NodeString::goToLine(NodeString *&aux, int y) {
    aux = this;
    for (int i = 0; i < y; i++) {
        if (aux->next != nullptr) {
            aux = aux->next;
        } else {
            break;
        }
    }
}

void NodeString::deleteLine(NodeString *&aux) {
    if (aux == nullptr || aux->previous == nullptr) return;

    NodeString *prev = aux->previous;
    NodeString *nex = aux->next;

    if (prev != nullptr) prev->next = nex;
    if (nex != nullptr) nex->previous = prev;

    delete aux;
    aux = prev;
    size--;
}

void NodeString::deleteChar(NodeString *&aux, int y, int &x) {
    if (x == 0 && y != 0) {
        NodeString *prev = aux->previous;
        if (prev != nullptr) {
            deleteln();
            x = prev->line.size();
            prev->line += aux->line;
            mvaddstr(y-1, x, aux->line.c_str());
            deleteLine(aux);
            y--;
        }
    } else {
        if (x > 0) {
            aux->line.erase(aux->line.begin() + x - 1);
            mvdelch(y, x - 1);
            x--;
        }
    }
    refresh();
}

void NodeString::addChar(NodeString *aux, int y, int x, const char ch) {
    // On screen
    mvaddch(y, x, ch);
    refresh();

    // In the buffer
    if (x <= aux->line.size()) {
        aux->line.insert(aux->line.begin() + x, ch);
    } else {
        aux->line.push_back(ch);
    }
}

void NodeString::enter(NodeString *&aux, int &y, int &x) {
    std::string newLine;
    if (x < aux->line.size()) {
        newLine = aux->line.substr(x);
        aux->line.erase(x);
    }

    NodeString *newNode = new NodeString(newLine, aux->next, aux);
    aux->next = newNode;
    if (newNode->next != nullptr) {
        newNode->next->previous = newNode;
    }

    // On screen
    insertln();
    x = 0;
    move(++y, x);
    addstr(newLine.c_str());
    refresh();
    aux = newNode;
    size++;
}

void NodeString::moveUp(NodeString *&aux, int &y, int &x) {
    if (y == 0 || aux->previous == nullptr) return;
    aux = aux->previous;
    y--;
    if (x > aux->line.size()) x = aux->line.size();
    move(y, x);
}

void NodeString::moveDown(NodeString *&aux, int &y, int &x) {
    if (y == size - 1 || aux->next == nullptr) return;
    aux = aux->next;
    y++;
    if (x > aux->line.size()) x = aux->line.size();
    move(y, x);
}

void NodeString::moveLeft(NodeString *&aux, int &y, int &x) {
    if (x == 0) {
        if (y == 0 || aux->previous == nullptr) return;
        aux = aux->previous;
        y--;
        x = aux->line.size();
    } else {
        x--;
    }
    move(y, x);
}

void NodeString::moveRight(NodeString *&aux, int &y, int &x) {
    if (x == aux->line.size()) {
        if (aux->next == nullptr) return;
        aux = aux->next;
        y++;
        x = 0;
    } else {
        x++;
    }
    move(y, x);
}
