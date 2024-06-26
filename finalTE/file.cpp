#include "textEditor.h"
#include "nodeString.h"

std::string TextEditor::fileName = "untitled.txt";


void TextEditor::openFile(const std::string &fileName){
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::ofstream newFile(fileName);
        newFile.close();  
    } else {
        std::string line;
        std::vector<std::string> fileContent;

        while (getline(file, line)) {
            fileContent.push_back(line);
        }

        NodeString::putFileInBuffer(fileContent);
        TextEditor::putFileInScreen(fileContent);

        file.close();
    }
}

void TextEditor::saveFile(const std::string &fileName){
    std::ofstream file(fileName);
    NodeString *aux = NodeString::first;
    while (aux) {
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


void TextEditor::putFileInScreen(std::vector<std::string> fileContent) {
    defaultPosition();
    clear();
    TextEditor::x = DEFAULT_X;
    for (const auto &line : fileContent) {
        mvaddstr(TextEditor::y, TextEditor::x, line.c_str());
        TextEditor::y++;
    }
    refresh();
    defaultPosition();
} 

void NodeString::putFileInBuffer(std::vector<std::string> fileContent) {
    if (first != nullptr) {
        NodeString *aux = first;
        NodeString *nextNode = nullptr;

        while (aux != nullptr) {
            nextNode = aux->next;
            delete aux; 
            aux = nextNode; 
        }

        first = current = last = nullptr;
    }
    
    NodeString *aux = nullptr;

    for (const auto &line : fileContent) {
        NodeString *newNode  = new NodeString(line, nullptr, aux);
        if (!first) {
            first = newNode;
        } else {
            aux->next = newNode;
        }
        aux = newNode;  
    }

    last = aux;
    current = first;
    size = fileContent.size();
}


