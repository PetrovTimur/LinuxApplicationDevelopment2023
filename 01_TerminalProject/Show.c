#include <ncurses.h>
#include <stdlib.h>
#include <sys/stat.h>

#define DX 3

int main(int argc, char* argv[]) {
        if (argc < 2) {
                printf("Too few arguments\n");
                return 1;
        }

        FILE *f = fopen(argv[1], "r");
        int fd = fileno(f);

        struct stat buf;
        fstat(fd, &buf);
        off_t size = buf.st_size;

        printf("%ld\n", size);
        char *data = (char*) malloc(size + 1);
        size_t result = fread(data, 1, size, f);
        printf("%ld\n", result);
        // printf("%c, %d\n", data[size-3], data[size-1]);
        data[size] = EOF;

        fseek(f, 0, SEEK_SET);

        int count = 0, i = 0;
        char ch;
        while (data[i] != EOF) {
                if (data[i] == '\n')
                        count++;
                i++;
                // printf("%d\n", i);
        }

        count++;
        printf("lines: %d\n", count);

        fseek(f, 0, SEEK_SET);

        // count
        char *lines[count];

        char *buffer;
        size_t bufsize = 100;
        size_t characters;

        i = 0;
        // return 0;
        lines[0] = (char*) malloc(bufsize * sizeof(char));
        buffer = (char *)malloc(bufsize * sizeof(char));

        int zz;
        while ((zz = getline(&(lines[i]),&bufsize,f)) != -1) {
                // fputs(lines[i], stdout);
                i++;
                lines[i] = (char*) malloc(100);
        }

        // i = 0;
        // for (i = 0; i < count; i++) {
        //         fputs(lines[i], stdout);
        // }

        WINDOW *win;
        int c = 0;

        initscr();
        noecho();
        cbreak();
        printw("Window:");
        refresh();

        win = newwin(LINES-2*DX, COLS-2*DX, DX, DX);
        keypad(win, TRUE);
        scrollok (win, TRUE);
        box(win, 0, 0); 
        wmove(win, 1, 0);

        char line[COLS];
        printf("%d\n", COLS);

        i = 0;
        int j = 0;
        while((c = wgetch(win)) != 27) {
                if (c == KEY_DOWN) {
                        i++;
                        // printf("%d\n", i);
                } else if (c == KEY_RIGHT) {
                        j++;
                } else if (c == KEY_LEFT) {
                        j--;
                } else if (c == KEY_UP) {
                        i--;
                }
                // wprintw(win, "  Key: %d, Name: %s\n", c, keyname(c));
                for (int k = i; k < LINES - 2 * DX + i; k++) {
                        result = snprintf(line, COLS, " %d: %s", k, lines[k] + j);
                        // printf("%d\n", result);
                        wprintw(win, line);
                }
                box(win, 0, 0); 
                wrefresh(win);
        }
        endwin();

        free(data);

        return 0;
}