#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define DX 3

int main(int argc, char* argv[]) {
        if (argc < 2) {
                printf("Too few arguments. Specify path to file you wan to display\n");
                return 1;
        }

        setlocale(LC_ALL, "");

        FILE *f = fopen(argv[1], "rt");

        int line_count = 0, i = 0;

        size_t bufsize = 100;
        char *buffer = (char *)malloc(bufsize * sizeof(char));

        int len;
        while ((len = getline(&buffer, &bufsize, f)) != -1) {
                i++;
        }


        line_count = i;

        fseek(f, 0, SEEK_SET);

        char *lines[line_count];

        for (i = 0; i < line_count; i++) {
                lines[i] = (char *) malloc(bufsize * sizeof(char));
                len = getline(&(lines[i]), &bufsize, f);
                lines[i][strcspn(lines[i], "\n")] = '\0';

        }

        WINDOW *win;
        int c = 0;

        initscr();
        noecho();
        cbreak();
        mvprintw(0, 0, "File: %s, lines: %d", argv[1], line_count);
        refresh();

        int width = COLS - 2 * DX, height = LINES - 2 * DX - 2;
        win = newwin(LINES-2*DX, COLS-2*DX, DX, DX);
        keypad(win, TRUE);
        scrollok (win, TRUE);
        box(win, 0, 0); 
        wmove(win, 1, 0);

        int line = 0, offset = 0;

        while (1) {
                werase(win);
                box(win, 0, 0);
                wrefresh(win);

                for (i = 1; i <= height; i++) {
                        mvwprintw(win, i, 1, "%5d: %.*s", line + i, width - 10, lines[line + i] + offset);
                }

                c = wgetch(win);
                if (c == 27)
                        break;

                switch(c) {
                case KEY_DOWN: line = ((line + height + 2) > line_count) ? line : line + 1; break;
                case KEY_UP: line = ((line < 1) ? line : line - 1); break;
                case KEY_RIGHT: offset++; break;
                case KEY_LEFT: offset = ((offset < 1) ? offset: offset - 1); break;
                case KEY_NPAGE: line = ((line + 2 * height + 1) > line_count) ? line_count - height - 1 : line + height;; break;
                case KEY_PPAGE: line = ((line < height) ? 0 : line - height); break;
                default: continue;
                }
        }

        endwin();

        for (i = 0; i < line_count; i++) {
                free(lines[i]);
        }
        free(buffer);
        fclose(f);

        return 0;
}