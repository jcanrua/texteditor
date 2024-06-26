void Display::moveUp() {
    if (y == 0) {
        return;
    }

    if (NodeString::current->line.size() > NodeString::current->previous->line.size()){
        x = NodeString::current->previous->line.size();
        move(--y, x);
    } else {
        move(--y, x);
    }
}

void Display::moveDown() {
    if (y == NodeString::size) {
        return;
    }

    if (NodeString::current->line.size() > NodeString::current->next->line.size()){
        x = NodeString::current->next->line.size();
        move(++y, x);
    } else {
        move(++y, x);
    }
}

void Display::moveLeft() {
    if (y == 0 && x == 5){
        return;
    } else if (x == 5){
        x = NodeString::current->previous->line.size();
        move(--y, x);
    } else {
        move(y, --x);
    }
}

void Display::moveRight() {
    if (x == getmaxx(stdscr) && y == NodeString::size) {
        return;
    } else if (x == getmaxx(stdscr)) {
        x = 5;
        move(++y, x);
    } else {
        move(y, ++x);
    }
}
