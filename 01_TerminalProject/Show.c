#include <locale.h>
#include <ncurses.h>
#include <stdlib.h>

#define DX 2
#define DY 1

int min(int a, int b) { return a > b ? b : a; }
int max(int a, int b) { return a > b ? a : b; }

void show(WINDOW *win, int start, int end, char **lines) {
  wclear(win);
  for (int i = start; i < end; ++i) {
    wattron(win, COLOR_PAIR(1));
    wprintw(win, "%d", i);
    wattroff(win, COLOR_PAIR(1));
    wprintw(win, ": %s", lines[i]);
  }
  wmove(win, 0, 0);
  wrefresh(win);
}

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("no files specified\n");
    return 0;
  }
  char *fname = argv[1];
  FILE *fd = fopen(fname, "r");
  if (fd == NULL) {
    printf("can't read file %s", fname);
    return 0;
  }
  int len_lines = 0;
  char c;
  while (!feof(fd)) {
    c = fgetc(fd);
    if (c == '\n') {
      len_lines++;
    }
  }
  fseek(fd, 0, SEEK_SET);
  char **lines = calloc(len_lines, sizeof(char *));
  size_t len = 0;
  for (int i = 0; i < len_lines; ++i) {
    getline(lines + i, &len, fd);
  }

  WINDOW *win, *frame;
  setlocale(LC_ALL, "");

  initscr();
  start_color();
  init_pair(1, COLOR_CYAN, COLOR_BLACK);
  init_pair(2, COLOR_MAGENTA, COLOR_BLACK);

  noecho();
  cbreak();
  printw("Show: %s, %d lines", fname, len_lines);
  refresh();

  int height = LINES - 2 * DY - 2;

  win = newwin(height, COLS - 2 * DX - 2, DY + 1, DX + 1);
  frame = newwin(height + 2, COLS - 2 * DX, DY, DX);
  wattron(frame, COLOR_PAIR(2));
  box(frame, 0, 0);
  wrefresh(frame);
  keypad(win, TRUE);
  int start = 0, end = min(start + height, len_lines);
  int ch;
  show(win, start, end, lines);
  while ((ch = wgetch(win)) != 27) { // ESC
    switch (ch) {
    case KEY_UP:
      start = max(0, start - 1);
      break;
    case KEY_DOWN:
      start = min(start + 1, len_lines);
      break;
    case ' ':
      start = min(start + 1, len_lines);
      break;
    case KEY_PPAGE:
      start = max(0, start - height);
      break;
    case KEY_NPAGE:
      start = min(height + start, len_lines);
      break;
    }
    end = min(start + height, len_lines);
    show(win, start, end, lines);
  }
  delwin(win);
  endwin();
  return 0;
}
