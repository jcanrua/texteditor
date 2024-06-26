#include "nodeString.h"

NodeString *NodeString::first = nullptr;
NodeString *NodeString::last = nullptr;
NodeString *NodeString::current = nullptr;
int NodeString::size = 0;

NodeString::NodeString(const std::string &line, NodeString *next, NodeString *previous) {    
    this->line = line;
    this->previous = previous;
    this->next = next;
    size++;
}

void NodeString::putFileInBuffer(std::vector<std::string> fileContent) {
    NodeString *aux = nullptr;
    for (const auto &line : fileContent) {
        if (!aux) {
            first = new NodeString(line, nullptr, nullptr);
            aux = first;
        } else {
            aux->next = new NodeString(line, nullptr, aux);
            aux = aux->next;
        }
    }
    last = current = aux;
    size = fileContent.size();
}

void NodeString::goToLine(int y, int numberLine) {
    // Desde current
    int dist1 = numberLine - y;           
    // Desde el final
    int dist2 = size - numberLine;
    
    NodeString *aux;
    if (abs(dist1) <= dist2 && abs(dist1) <= numberLine) {
        
        if (dist1 < 0) {
            for (int i = 0; i < dist1; i++) {
                current = current->previous;
            }
        } else {
            for (int i = 0; i < dist1; i++) {
                current = current->next;
            }
        }
    } else if (dist2 <= abs(dist1) && dist2 <= numberLine) {
        aux = last;

        for (int i = 0; i < dist2; i++) {
            aux = aux->previous;
        }

        current = aux;
    } else {
        aux = first;

        for (int i = 0; i < numberLine; i++) {
            aux = aux->next;
        }

        current = aux;
    } 
}

void NodeString::deleteLine(int type) {
    if (!current || !current->previous) return;

    NodeString *toDelete = current;
    if (type >= 0) {
        current = current->previous;
        current->next = toDelete->next;
    } else {
        current = toDelete->next;
        if (current) current->previous = toDelete->previous;
    }

    if (toDelete->next) toDelete->next->previous = current;
    if (toDelete == first) first = current;
    if (toDelete == last) last = current->previous;

    delete toDelete;
    size--;
}

void NodeString::deleteChar(int y, int x) {
    if (x == 5 && y == 0){  
        return;
    } else if (x == 5) {
        NodeString *aux = current->previous;
        if (aux) {
            aux->line += current->line;
            deleteLine(1);
        }
    } else {
        current->line.erase(current->line.begin() + x - 5);
    }
}

void NodeString::addChar(int x, const char ch) {
    int adjustedX = x - 5;
    if (adjustedX <= current->line.size()) {
        current->line.insert(adjustedX, 1, ch);
    } else {
        current->line.push_back(ch);
    }
}

void NodeString::newLine(int x) {
    std::string newLine = "";
    newLine = current->line.substr(x);
    current->line.erase(x);

    NodeString* newNode = new NodeString(newLine, current->next, current);

    current->next = newNode;

    if (newNode->next != nullptr) {
        newNode->next->previous = newNode;
    } else {
        last = newNode;
    }
}

void NodeString::newLine() {
    NodeString* newNode = new NodeString("", current->next, current);

    current->next = newNode;

    if (newNode->next != nullptr) {
        newNode->next->previous = newNode;
    } else {
        last = newNode;
    }
}

void NodeString::moveUp() {
    if (current->previous != nullptr) {
        current = current->previous;
    }
}

void NodeString::moveDown() {
    if (current->next != nullptr) {
        current = current->next;
    }
}

void NodeString::moveLeft(int x) {
    if (x == 0 && current->previous != nullptr) {
        current = current->previous;
    }
}

void NodeString::moveRight(int x) {
    if (x > current->line.size() && current->next != nullptr) {
        current = current->next;
    }
}
