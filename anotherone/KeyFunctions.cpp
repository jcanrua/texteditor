#include "KeyFunctions.h"

void KeyFunctions::addChar(int y, int x, const char ch){
    mvaddch(y,x,ch);
    refresh();
}

void KeyFunctions::deleteChar(int y, int x){
    mvdelch(y,x);
    refresh();
}

void KeyFunctions::deleteEmptyLine(int y){
    if(y==0){
        return;
    }
    mvdelch(y,0);
    deleteln();
    int x = 6;
    for(int i = 0;;){
        
    }
    move(--y,);


}
