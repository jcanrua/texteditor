#include "nodeString.h"

int NodeString::size = 0;

NodeString::NodeString(const std::string &line, NodeString *next, NodeString *previous) {    
    this->line = line;
    this->previous = previous;
    this->next = next;
    size++;
}

void NodeString::putFileInBuffer(std::vector<std::string> fileContent) {
    NodeString *aux;
    aux = first;
    size = fileContent.size();

    for(int i = 0; i < size; i+=2) {
        aux->line = fileContent[i];
        aux->next = new NodeString(fileContent[i+1], nullptr, aux);
        // Dos veces porque avanzo de dos en dos 
        aux = aux->next;
        aux = aux->next;
    }

    last = aux;
    delete aux;
}

void NodeString::goToLine(NodeString *&current, int y, int numberLine) {
    // Desde current
    int dist1 = numberLine - y;           
    // Desde el final
    int dist2 = size - numberLine;
    
    NodeString *aux;
    if (abs(dist1) <= dist2 && abs(dist1) <= numberLine) {
        
        if (dist1 < 0) {
            for (int i = 0; i < dist1; i++){
                current = current->previous;
            }
        } else {
            for (int i = 0; i < dist1; i++){
                current = current->next;
            }
        }
    } else if (dist2 <= abs(dist1) && dist2 <= numberLine) {
        aux = last;

        for (int i = 0; i < dist2; i++){
            aux = aux->previous;
        }

        current = aux;
        delete aux;
    } else {
        aux = first;

        for (int i = 0; i < numberLine; i++){
            aux = aux->next;
        }

        current = aux;
        delete aux;
    } 
}

void NodeString::deleteLine(NodeString *&current, int type) {
    if ((current->previous == nullptr) || (current = nullptr))
        return;

    NodeString *auxPrev = current->previous;
    NodeString *auxNext = current->next;

    auxPrev->next = auxNext;
    auxNext->previous = auxPrev;

    if (type >= 0){
        current = auxPrev;
    } else {
        current = auxNext;
    }

    if (current->next == nullptr)
        last = current;
    
    delete auxNext;
    delete auxPrev;
    size--;
}

void NodeString::deleteChar(NodeString *&current, int y, int x) {
    if (current->previous == nullptr)
        return;

    if (x == 0){
        NodeString *aux = current->previous;
        aux->line += current->line;
        deleteLine(current, 1);
        delete aux;
    } else {
        current->line.erase(current->line.begin() + x - 1);
    }
}

void NodeString::addChar(NodeString *&current, int x, const char ch) {
    if (x <= current->line.size()) {
        current->line.insert(current->line.begin() + x, ch);
    } else {
        current->line.push_back(ch);
    }
}

void NodeString::enter(NodeString *&current, int x){
    std::string newLine;
    if (x < current->line.size()){
        newLine = current->line.substr(x);
        current->line.erase(x);
    }

    NodeString *newNode = new NodeString(newLine, current->next, current);
    current->next = newNode;

    if (newNode->next != nullptr) {
        newNode->next->previous = newNode;
    }
}

void NodeString::moveUp(NodeString *&current){
    if (current->previous != nullptr){
        current = current->previous;
    }
}

void NodeString::moveDown(NodeString *&current){
    if (current->next != nullptr){
        current = current->next;
    }
}

void NodeString::moveLeft(NodeString *&current, int x){
    if (x == 0 && current->previous != nullptr){
        current = current->previous;
    }
}

void NodeString::moveRight(NodeString *&current, int x){
    if (x > current->line.size() && current->next != nullptr){
        current = current->next;
    }
}

