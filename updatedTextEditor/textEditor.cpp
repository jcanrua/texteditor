#include "textEditor.h"

std::string TextEditor::fileName = "";

void TextEditor::initialize(){
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    
    NodeString::current = new NodeString("", nullptr, nullptr);
    NodeString::first = NodeString::last = NodeString::current;
    
    Display::defaultPosition();
} 

void TextEditor::openFile(const std::string &fileName){
    std::ifstream file(fileName);
    if (!file.is_open()) {
        mvaddstr(Display::y, Display::x, "Error: Cannot open file.");
        refresh();
        return;
    }

    std::string line;
    std::vector<std::string> fileContent;

    while (getline(file, line)) {
        fileContent.push_back(line);
    }

    NodeString::putFileInBuffer(fileContent);
    Display::putFileInScreen(fileContent);

    file.close();
}

void TextEditor::saveFile(const std::string &filename) {
    std::ofstream file(filename);
    NodeString *aux = NodeString::first;

    while (aux != nullptr) {
        file << aux->line << std::endl;
        aux = aux->next;
    }

    file.close();
}


void TextEditor::closeFile() {
    endwin();
    NodeString *aux = NodeString::first;
    
    while (aux != nullptr) {
        NodeString *next = aux->next;
        delete aux;
        aux = next;
    }
}

void TextEditor::saveCloseFile(const std::string &filename){
    endwin();
    std::ofstream file(filename);
    NodeString *aux = NodeString::first;

    while (aux != nullptr) {
        file << aux->line << std::endl;
        NodeString *next = aux->next;
        delete aux;
        aux = next;
    }

    file.close();
}


void TextEditor::run() {
    int ch;
    while ((ch = getch()) != KEY_F(1)) {
        switch (ch) {
            case KEY_UP:
                Display::moveUp();
                NodeString::moveUp();
                break;
            case KEY_DOWN:
                Display::moveDown();
                NodeString::moveDown();
                break;
            case KEY_LEFT:
                Display::moveLeft();
                NodeString::moveLeft(Display::x);
                break;
            case KEY_RIGHT:
                Display::moveRight();
                NodeString::moveRight(Display::x);
                break;
            case KEY_BACKSPACE:
                Display::deleteChar();
                NodeString::deleteChar(Display::y, Display::x);
                break;
            case '\n':
                NodeString::newLine(Display::x);
                Display::newLine();
                break;
            case Ctrl_S:
                saveFile(fileName);
                break;
            case Ctrl_X:
                closeFile();
                break;
            default:
                Display::addChar(ch);
                NodeString::addChar(Display::x, ch);
                break;
        }
        refresh();
    }
}

