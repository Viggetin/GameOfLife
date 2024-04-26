/**
 * file:    GameOfLife.c
 * author:  Victor Sten
 * date:    2024-04-17
 * version: 1.0
 *
 * brief: A brief description of what the program does.
 *
 * Detailed description of the program. This program is designed to 
 * demonstrate modern C programming practices, including structured 
 * documentation, use of constants, function prototypes, and 
 * basic program structure.
 *
 * This software is released under the GPL License.
 */

/* Includes */
#include "header.h"

int main(void) {
    struct cell board[ROWS][COLUMNS] = {{0}};
    int ch;
    int i = 0;
    char list[3][50] = { "Start the Game (E)", "Pause the Game (P)", "Exit the Program (Z)" };

    game_init(board);

    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);

    start_color();
    init_pair(Creature_pair,COLOR_BLUE,COLOR_BLUE);
    init_pair(ground, COLOR_GREEN, COLOR_GREEN);
    init_pair(River, COLOR_WHITE, COLOR_BLUE);
    init_pair(Mountain, COLOR_WHITE, COLOR_GREEN);

    WINDOW *win = newwin(50, 100, 10, 60);
    WINDOW *menu = newwin(7, 55, 2, 15);
    keypad(menu, TRUE);
    
    bool running = false;

    while (1) {
        wclear(menu);
        mvwprintw(menu, 1, 2, "Welcome to the Game Of Life!");
        box(menu, 0, 0);
        refresh();
        wrefresh(menu);

        for (int j = 0; j < 3; j++)
        {
            if (j == i)
                wattron(menu, A_STANDOUT);
            else
                wattroff(menu, A_STANDOUT);
            mvwprintw(menu, j + 2, 2, "%s", list[j]);
        }
        wrefresh(menu);

        ch = wgetch(menu);
        move(0,20);
        printw("<%03d>", ch);
        switch (ch) {
            case 'e':  // Start the game
                wclear(win);
                nodelay(win, TRUE);
                running = true;
                while (running)
                {
                    ch = wgetch(win);
                    if (ch == 'z' || ch == 'p') {
                        running = false;
                    }
                    calculateSim(board);
                    printBoard(win, board);
                    wrefresh(win);
                    sleep(1);
                }
                break;
            case 'p':  // Pause the game
                nodelay(win, FALSE);
                break;
            case 'z':  // Exit the program
                delwin(menu);
                delwin(win);
                endwin();
                return 0;
        }
    }
}


/**
 * brief: License Information
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
