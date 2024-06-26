#include "texteditor.h"

int main(int argc, char* argv[]) {
    try {
        if (argc > 1) {
            TextEditor editor(argv[1]);
            editor.run();
        } else {
            TextEditor editor;
            editor.run();
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}