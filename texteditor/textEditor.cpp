#include "textEditor.h"

TextEditor::TextEditor(const std::string& fileName){
    //Ya esta iniciada la base
    if(stdscr == nullptr){
        std::cerr << "No se pudo iniciar ncurses" << std::endl;
    }
    //Se establece el fileName
    this->fileName = fileName;

    int tmp_x = getmaxx(stdscr) - 4;
    text = newwin(1, tmp_x, 0, 4);
    numbers = newwin(1,4,0,0);
}

TextEditor::~TextEditor(){
    endwin();
}

void TextEditor::openFile(const std::string& fileName){
    //Manera sencilla de ver si existe o no y abrir/crear
     std::ifstream file(fileName);
    if(!file.is_open()){
        //Si el ifstream no lo ha podido abrir, lo crea con el ofstream
        std::ofstream newFile(fileName);
        if(!newFile.is_open()){
            throw std::runtime_error("No se pudo abrir el archivo");
        }
        newFile.close();
    }
    else{
        //VACIAR EL BUFFER
        std::string line;
        while(getline(file,line)){

        }
        file.close();
    }
}
void saveFileAs(const std::string& fileName);
void closeFile();
void run(); 