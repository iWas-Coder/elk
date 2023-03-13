#include <ncurses.h>
#include <stdlib.h>
#include <string.h>


#define NUM_OPTIONS 4
#define OPTION_LENGTH 20
#define COMMAND_LENGTH 100


int main(void) {
  int choice = 0;
  char options[NUM_OPTIONS][OPTION_LENGTH] = {
    "Option 1",
    "Option 2",
    "Option 3",
    "Option 4"
  };

  // Initialize ncurses
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);

  // Get current window size
  int max_x, max_y;
  getmaxyx(stdscr, max_y, max_x);

  // Colours
  start_color();
  init_pair(1, COLOR_WHITE, COLOR_BLUE);
  init_pair(2, COLOR_BLACK, COLOR_WHITE);
  init_pair(3, COLOR_WHITE, COLOR_BLACK);

  // Main loop
  while (1) {
    clear();
    printw("Welcome to ELK!\n\n");

    // Show the available options
    for (int i = 0; i < NUM_OPTIONS; i++) {
      attron(COLOR_PAIR(1));
      if (i == choice) attron(COLOR_PAIR(3));

      mvprintw(max_y / 2 - NUM_OPTIONS / 2 + i, max_x / 2 - strlen(options[i]) / 2 - 2, " ");
      mvprintw(max_y / 2 - NUM_OPTIONS / 2 + i, max_x / 2 - strlen(options[i]) / 2 - 1, "%s", options[i]);
      mvprintw(max_y / 2 - NUM_OPTIONS / 2 + i, max_x / 2 + strlen(options[i]) / 2 + 1, " ");
      attroff(COLOR_PAIR(1));
      if (i == choice) attroff(COLOR_PAIR(3));
    }

    // Wait for user's selection
    int c = getch();
    switch (c) {
      case KEY_UP:
        if (choice > 0) choice--;
        break;
      case KEY_DOWN:
        if (choice < NUM_OPTIONS - 1) choice++;
        break;
      case '\n':
        if (choice == NUM_OPTIONS - 1) {
          endwin();
          return 0;
        }
        else {
          char command[COMMAND_LENGTH];
          snprintf(command, sizeof(command), "echo 'Selected Option %d'", choice + 1);
          endwin();
          system(command);
          return 0;
        }
        break;
    }
  }
  
  endwin();
  return 0;
}
