#include "NodeString.h"
#include "textEditor.h"

int NodeString::size = -1;

NodeString::NodeString(const std::string &line, NodeString *nextprev, int type){
    this->line = line;
    int tmp_x = getmaxx(stdscr) - 4;
    //Se crea la ventana aqui
    if (size == -1){
        size++;
    } else {
        wresize(TextEditor::text, ++size, tmp_x);
    }

    if (type > 0) {
        this->next = nextprev;
        this->previous = nullptr;
        if (nextprev != nullptr)
            nextprev->previous = this;
    } else {
        previous = nextprev;
        next = nullptr;
        if (nextprev != nullptr)
            nextprev->next = this;
    }
}

NodeString::NodeString(const std::string &line, NodeString *next, NodeString *previous){
    this->line = line;
    this->next = next;
    this->previous = previous;
    if (next != nullptr)
        next->previous = this;
    if (previous != nullptr) 
        previous->next = this;

    int tmp_x = getmaxx(stdscr) - 4;
    wresize(TextEditor::text, ++size, tmp_x);
}

//Se puede hacer sin el first (puedes ir para atras con aux tambien)
void NodeString::goToLine(NodeString *first, NodeString *&aux, int y, int &x){
    aux = first;
    for(int i = 0; i<y;i++) {
        if(aux->next != nullptr) { 
            aux = aux->next;    
            x = aux->line.size();
            wmove(TextEditor::text,y,x);
        } else
            break;
    }
}

void NodeString::deleteLine(NodeString *aux, int y){
    if((y == 0) || (aux->previous == nullptr) || (aux = nullptr))
        return;

    NodeString *prev = aux->previous, *nex = aux->next;

    if (prev != nullptr)
        prev->next = nex;
    if (nex != nullptr)
        nex->previous = prev;
    
    delete aux;
    aux = prev;
    int tmp_x = getmaxx(stdscr) - 4;
    wresize(TextEditor::text, --size, tmp_x);
}
 
void NodeString::deleteChar(NodeString *aux, int &y, int &x){
    if (x == 0 && y != 0) {
        NodeString *prev = aux->previous;
        //Mezcla de en pantalla y en el buffer
        deleteln();
        x = prev->line.size();
        prev->line += aux->line;
        mvwaddstr(TextEditor::text, y-1, x, aux->line.c_str());  
        deleteLine(aux, y);
        y--;
    } else {
        if (x > 0) {
            aux->line.erase(aux->line.begin() + x - 1);
            //En pantalla
            mvwdelch(TextEditor::text, y, --x);
        }
    }
    wrefresh(TextEditor::text);
}

 
//REVISAR ESTO
void NodeString::addChar(NodeString *&aux, int &y, int &x, const char ch){
    int tmp_x = getmaxx(stdscr) - 4;
    if (x >= tmp_x){
        x = 0;
        wresize(TextEditor::text, size+1, tmp_x);
        mvwaddch(TextEditor::text, y++, x, ch);
        aux = aux->next;
        
    }
    //En pantalla
    mvwaddch(TextEditor::text, y, ++x, ch);
    wrefresh(TextEditor::text);
    
    //En el buffer
    if (x <= aux->line.size()) {
        aux->line.insert(aux->line.begin() + x, ch);
    } else {
        aux->line.push_back(ch);
    }

    int tmp_x = getmaxx(stdscr) - 4;
    wresize(TextEditor::text, size-1, tmp_x);
}


void NodeString::enter(NodeString *&aux, int &y, int &x) {
    int tmp_x = getmaxx(stdscr) - 4;
    wresize(TextEditor::text, size+1, tmp_x);
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
    wmove(TextEditor::text, ++y, x);
    waddstr(TextEditor::text, newLine.c_str());
    wrefresh(TextEditor::text);
    aux = newNode;
    size++;
}





void NodeString::moveUp(NodeString *aux, int y, int x){
    if( y == 0) {
        return;
    }

    if (x > aux->previous->line.size()) {
        x = aux->previous->line.size();
    }

    wmove(TextEditor::text, --y, x);
    wrefresh(TextEditor::text);
    NodeString *help = aux->previous;
    aux = help;
}

void NodeString::moveDown(NodeString *aux, int y, int x){
    if(y == size){
        return;
    }
    if(x>aux->next->line.size()){
        x = aux->next->line.size();
    }
    wmove(TextEditor::text, ++y,x);
    wrefresh(TextEditor::text);
    NodeString *help = aux->next;
    aux = help;
}

//NO HECHO CON VENTANAS

void NodeString::moveLeft(NodeString *aux, int y, int x){
    if(x == 0){
        x = aux->previous->line.size();
        move(--y,x);
    }
    else{
        move(y,--x);
    }
}

void NodeString::moveRight(NodeString *aux, int y, int x){
    if(x == aux->line.size() + 1){
        return;
    }   
    else{
        move(y,++x);
    }
}
