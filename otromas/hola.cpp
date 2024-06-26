while ((ch = getch()) != 17) { // Ctrl+Q 
    switch (ch) {
        default: // Unassigned keys
            if (currentLine.size() >= x) {
                currentLine.insert(x, 1, ch);
                mvaddch(y, x++, ch);
            } else {
                currentLine += ch; // Append character if x is at the end
                mvaddch(y, x++, ch);
            }
            break;
        // Movement
        case KEY_UP:
            if (y > 0) {
                lines[y] = currentLine;
                currentLine = lines[--y];
                if (x > currentLine.size()) {
                    x = currentLine.size();
                }
                move(y, x);
            }
            break;
        case KEY_DOWN:
            if (y < lines.size() - 1) {
                lines[y] = currentLine;
                currentLine = lines[++y];
                if (x > currentLine.size()) {
                    x = currentLine.size();
                }
                move(y, x);
            }
            break;
        case KEY_RIGHT:
            if (x < currentLine.size()) {
                move(y, ++x);
            }
            break;
        case KEY_LEFT:
            if (x > 1) {
                move(y, --x);
            } else if (y > 0) {
                lines[y] = currentLine;
                currentLine = lines[--y];
                x = currentLine.size();
                move(y, x);
            }
            break;

        case 10: // Enter
            lines[y] = currentLine;
            lines.insert(lines.begin() + y + 1, "");
            currentLine.clear();
            displayFile(); // Update display after modifying lines
            y++;
            x = 2;
            move(y, x);
            break;

        case 127: // Delete (Backspace)
        case 8:   // Backspace
        case KEY_BACKSPACE:
            if (x > 0) {
                currentLine.erase(--x, 1);
                mvaddch(y, x, ' ');
                move(y, x);
            } else if (y > 0) {
                x = lines[y - 1].length();
                currentLine = lines[y - 1] + currentLine;
                lines.erase(lines.begin() + y);
                y--;
                move(y, x);
            }
            break;

        case 19: // Save (Ctrl+S)
            lines[y] = currentLine;
            saveFileAs(fileName);
            break;

        case 15: // Open file (Ctrl+O)
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