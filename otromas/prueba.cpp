#include "texteditor.h"

TextEditor::TextEditor() {
    initscr();
    if (stdscr == NULL) {
        std::cerr << "Error initializing ncurses." << std::endl;
        exit(1);
    }
    keypad(stdscr, TRUE);
    raw();
    noecho();
    refresh();
    openFile("untitled");
}

TextEditor::TextEditor(const std::string& fileName) : fileName(fileName) {
    initscr();
    if (stdscr == NULL) {
        std::cerr << "Error initializing ncurses." << std::endl;
        exit(1);
    }
    keypad(stdscr, TRUE);
    raw();
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
        this->fileName = "untitled";
        std::ofstream file(this->fileName);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file");
        }
        file.close();
    } 
    else {
        lines.clear();
        std::string line;
        while (std::getline(file, line)) {
            lines.push_back(line);
        }
        file.close();
        displayFile();
    }
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
        mvprintw(i, 0, lines[i].c_str());
    }
    refresh();
}

std::string TextEditor::borrarUno(const std::string& s) {
    return (s.empty()) ? "" : s.substr(0, s.length() - 1);
}


void TextEditor::run() {
    int ch;
    int x = 0, y = 0;
    std::string currentLine;

    while ((ch = getch()) != 17) {  
        switch (ch) {
            default: //Teclas sin asignar
                currentLine.insert(x,1,ch);
                mvaddch(y, x++, ch);
                break;
            //MOVIMIENTO
            case KEY_UP:
                if(y > 0){
                    move(--y, x);
                }
                break;
            case KEY_DOWN:
                if(y < 200){
                    move(++y, x);
                }
                break;
            case KEY_RIGHT:
                if (x < 200) {
                    move(y, ++x);
                }
                break;
            case KEY_LEFT:
                if (x > 0) {
                    move(y, --x);
                } else if (y > 0) {
                    currentLine = lines[y];
                    x = currentLine.size();
                    move(y, x);
                }
                break;

            case 10: //Enter
                lines.insert(lines.begin() + y + 1, currentLine);
                y++;
                x = 0;
                move(y, x);
                break;
            

            case 127: // Borrar
            case 8:   // Borrar (en otros sistemas)
            case KEY_BACKSPACE: // Borrar (en otros sistemas)
                if (x > 0) {
                    currentLine.erase(x - 1, 1);
                    mvaddch(y, --x, ' ');
                    move(y, x);
                } else if (y > 0) {
                    x = lines[y - 1].length();
                    currentLine = lines[y - 1];
                    lines.erase(lines.begin() + --y);
                    move(y, x);
                }
                break;
            
            case 19: // Guardar (Ctrl+S)
                saveFileAs(fileName);
                break;
            
            case 15: // Abrir archivo (Ctrl+O)
                if (!currentLine.empty()) {
                    lines.insert(lines.begin() + y, currentLine);
                    y++;
                    x = 0;
                    currentLine.clear();
                    move(y, x);
                }
                clear();
                refresh();
                printw("Enter file name: ");
                echo();
                char filename[256];
                getstr(filename);
                noecho();
                openFile(filename);
                break;
            }
            refresh();
        }
}
