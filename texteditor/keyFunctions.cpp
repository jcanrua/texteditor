#include "keyFunctions.h"


void KeyFunctions::deleteCharW(int y, int x){
    mvdelch(y,x);
    refresh();
}

void KeyFunctions::deleteLineW(int y){
    if(y==0){
        return;
    }
     
    
}
