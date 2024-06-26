#include "texteditor.h"


TextEditor::TextEditor() {
    initscr();
    if (stdscr == nullptr) {
        std::cerr << "Error initializing ncurses." << std::endl;
        exit(1);
    }
    keypad(stdscr, TRUE);
    cbreak();
    noecho();
    refresh();
    openFile("untitled");
}

TextEditor::TextEditor(const std::string& fileName) : fileName(fileName) {
    initscr();
    if (stdscr == nullptr) {
        std::cerr << "Error initializing ncurses." << std::endl;
        exit(1);
    }
    keypad(stdscr, TRUE);
    raw();
    cbreak();
    noecho();
    refresh();
    openFile(fileName);
}

TextEditor::~TextEditor() {
    endwin();
}

void TextEditor::openFile(const std::string& fileName) {
    this->fileName = fileName;
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::ofstream newFile(fileName);
        if (!newFile.is_open()) {
            throw std::runtime_error("Could not open file");
        }
        newFile.close();
    } else {
        lines.clear();
        std::string line;
        while (std::getline(file, line)) {
            lines.push_back(line);
        }
        file.close();
    }
    if (lines.empty()) {
        lines.push_back("");
    }
    displayFile();
    move(0,4);
    refresh();
}

void TextEditor::saveFileAs(const std::string& fileName) {
    this->fileName = fileName;
    std::ofstream file(fileName);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file for writing");
    }
    for (const std::string& line : lines) {
        file << line << std::endl;
    }
    file.close();
}

void TextEditor::closeFile() {
    lines.clear();
    clear();
    refresh();
}

void TextEditor::displayFile() {
    clear();
    for (size_t i = 0; i < lines.size(); i++) {
        mvprintw(i, 0, "%3zu %s", i + 1, lines[i].c_str());
    }
    refresh();
}


void TextEditor::run() {
    int ch;
    int x = 4, y = 0;
    std::string currentLine = lines[y];
    

    while ((ch = getch()) != 17) { // Ctrl+Q 
        switch (ch) {
            default: // Teclas sin asignar
                if (currentLine.size() >= x) {
                    currentLine.insert(x, 1, ch);
                    mvaddch(y, x++, ch);
                    refresh();
                } else {
                    currentLine += ch; // Append character if x is at the end
                    mvaddch(y, x++, ch);
                    refresh();
                }
                break;
            // Movimiento
            case KEY_UP:
                if (y > 0) {
                    lines[y] = currentLine;
                    currentLine = lines[--y];
                    if(currentLine.empty()){
                        move(y,4);
                        x = 4;
                        break;
                    }
                    else if(x > currentLine.size() + 4) {
                        x = currentLine.size() + 4;
                    }
                    move(y, x);
                    refresh();
                }
                break;

            case KEY_DOWN:
                if (y < lines.size()-1) {
                    lines[y] = currentLine;
                    currentLine = lines[++y];
                    if (x > currentLine.size() + 4) {
                        x = currentLine.size() +4;
                    }
                    move(y, x);
                    refresh();
                }
                break;

            case KEY_RIGHT:
                if (x < currentLine.size() + 4) {
                    move(y, ++x);
                    refresh();
                }
                else if(lines.size() - 1 > y){
                    lines[y] = currentLine;
                    currentLine = lines[++y];
                    move(y,4);
                    refresh();
                    x = 4;
                }
                break;

            case KEY_LEFT:
                if (x > 4) {
                    move(y, --x);
                    refresh();
                } 
                else if (y > 0) {
                    lines[y] = currentLine;
                    currentLine = lines[--y];
                    x = currentLine.size() + 4;
                    move(y, x);
                    refresh();
                }
                break;

            case 10: // Enter
                if(x == currentLine.size() + 4){
                    lines[y] = currentLine;<
                    currentLine.clear();
                    lines.insert(lines.begin() + ++y, "");
                    x = 4;
                    move(y, x);
                    displayFile();
                }
                else{
                    //En el buffer
                    std::string tmp = currentLine.substr(x-3);
                    lines[y] = currentLine.erase(x-3);
                    lines.insert(lines.begin()+1,tmp);
                    //En pantalla ALGO DE AQUI FALLLA
                    for(int i = 0; i<tmp.size(); i++){
                        mvdelch(y,x+i);
                    }
                    mvaddstr(++y,4,tmp.c_str());
                    move(y,tmp.size()+4);
                    refresh();
                }
                break;
        
            case 127: // Borrar
            case 8:   
            case KEY_BACKSPACE: 
                if(x>4){
                    //String
                    currentLine.erase(x-5,1);
                    lines[y] = currentLine;
                    //Muestra en pantalla
                    mvdelch(y,--x);
                    refresh();
                } else if(x == 4 && y != 0){
                    //unir con el string de arriba
                    std::string tmp = currentLine;
                    lines[y-1].append(tmp);
                    //Borrar la linea 
                    lines.erase(lines.begin() + y);
                    //Hacer current a la de arriba 
                    currentLine = lines[--y];
                    //En pantalla
                    deleteln();
                    x = currentLine.size() + 4 - tmp.size();
                    mvaddstr(y,x,tmp.c_str());
                    move(y,x);
                    refresh();
                    
                }
                break;

            case KEY_DC:
                //String
                currentLine.erase(x,1);
                lines[y] = currentLine;
                //Muestra en pantalla
                mvdelch(y,x);
                refresh();
                break;
            
            case 19: // Guardar Ctrl+S
                lines[y] = currentLine;
                saveFileAs(fileName);
                break;

            case 15: // Open file Ctrl+O
                if (!currentLine.empty()) {
                    lines[y] = currentLine;
                }
                clear();
                refresh();
                printw("Enter file name: ");
                echo();
                char filename[256];
                getstr(filename);
                noecho();
                openFile(filename);
                y = 0;
                x = 0;
                currentLine = lines[y];
                move(y, x);
                break;
        }
        refresh();
    }
}