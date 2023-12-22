#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <locale.h>

#define DX 3

int main(int argc, char* argv[]) {
        if (argc < 2) {
                printf("Too few arguments\n");
                return 1;
        }

        setlocale(LC_ALL, "");

        FILE *f = fopen(argv[1], "rt");
        int fd = fileno(f);

        struct stat buf;
        fstat(fd, &buf);
        off_t size = buf.st_size;

        // printf("%ld\n", size);
        // char *data = (char*) malloc(size + 1);
        // size_t result = fread(data, 1, size, f);
        // printf("%ld\n", result);
        // // printf("%c, %d\n", data[size-3], data[size-1]);
        // data[size] = EOF;

        // fseek(f, 0, SEEK_SET);

        int count = 0, i = 0, maxlen = 0;
        // char ch;
        // while (data[i] != EOF) {
        //         if (data[i] == '\n')
        //                 count++;
        //         i++;
        //         // printf("%d\n", i);
        // }

        // count++;
        // printf("lines: %d\n", count);

        // count
        // char *lines[count];

        char *buffer;
        size_t bufsize = 100;
        size_t characters;

        i = 0;
        // return 0;
        // lines[0] = (char*) malloc(bufsize * sizeof(char));
        buffer = (char *)malloc(bufsize * sizeof(char));

        int len;
        while ((len = getline(&buffer, &bufsize, f)) != -1) {
                // fputs(buffer, stdout);
                maxlen = len > maxlen ? len : maxlen;
                i++;
                // lines[i] = (char*) malloc(100);
        }

        // printf("lines: %d, maxlen: %d\n", i, maxlen);
        maxlen++;
        
        char *lines[i];
        int lens[i];
        fseek(f, 0, SEEK_SET);

        for (int p = 0; p < i; p++) {
                lines[p] = (char *) malloc(bufsize * sizeof(char));
        }


        i = 0;
        while ((len = getline(&(lines[i]), &bufsize, f)) != -1) {
                lens[i] = len;
                // strncpy(lines[i], buffer, maxlen);
                // fputs(buffer, stdout);
                // fputs(lines[i], stdout);
                // printf("%d, %d\n", len, lines[i][maxlen]);
                // int succ = strncpy
                i++;
                // lines[i] = (char*) malloc(100);
        }

        count = i;
        for (i = 0; i < count; i++) {
                // printf("%c: %d\n", lines[1][i], lines[1][i]);
                // printf("%d: %d\n", i, lens[i]);
                // fputs(lines[i], stdout);
                // printf("%c\n", lines[i][maxlen - 2]);
        }

        WINDOW *win;
        int c = 0;
        // printf("%s\n\n\n", "hi");

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

        printf("%s\n", argv[1]);

        int width = COLS - 2 * DX - 2;
        int height = LINES - 2 * DX;
        char line[width];

        // printf("count = %d\n", count);
        i = 0;
        int result;
        int j = 0;
        while((c = wgetch(win)) != 27) {
                // wclear(win);
                // box(win, 1, 1);
                if ((c == KEY_DOWN) && (i < count - height)) {
                        // printf("%d, %d, %d\n", i, count, height);
                        i++;
                        // printf("%d\n", i);
                } else if ((c == KEY_RIGHT) && (j < maxlen - width)) {
                        j++;
                } else if ((c == KEY_LEFT) && (j > 0)) {
                        j--;
                } else if ((c == KEY_UP) && (i > 0)) {
                        i--;
                }
                for (int k = i; k < height + i; k++) {
                        result = snprintf(line, width, "%d: %s", k, lines[k] + j);
                        // printf("%d\n", result);

                        // if (result == width) {
                        //         line[width - 1] = "\n";
                        // }

                        // int length = lens[k];
                        // if (length - j >= width) {
                        //         result = snprintf(line, width, " %d: %s", k, lines[k] + j);
                        //         printf("%d\n", result);
                        //         line[width - 1] = '\n';
                        // } else {
                        //         if (j >= length) {
                        //                 result = snprintf(line, width, " %d: %s", k, lines[k] + lens[k] - 1);
                        //         } else {
                        //                 result = snprintf(line, width, " %d: %s", k, lines[k] + j);
                        //         }
                        // }
                        mvwprintw(win, k - i + 1, 1, line);
                }
                box(win, 0, 0); 
                wrefresh(win);
        }
        endwin();

        // free(data);
        fclose(f);

        return 0;
}