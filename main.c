/*!
 * \file GameOfLife.c
 * \author Victor Sten
 * \date 2024-04-17
 * \version 1.0
 *
 * \brief Ohjelma simuloi kaksintaistelua ihmisten ja örkkien välillä kartalla, jossa on vuoria, jokia ja seinämäalueita.
 * 
 * Ohjelmassa käytetään hyväksi Ncurses kirjastoa jolla luodaan pelin visuaalinen puoli.
 *
 * \note This software is released under the GPL License.
 */

/* Includes */
#include "header.h"

/*!
 * \brief Main function.
 *
 * \return Return 0 on success.
 */
int main(void) {
    // Luodaan pelilauta ja alustetaan se tyhjillä soluilla
    struct cell board[ROWS][COLUMNS] = {{0}};
    int ch;
    int i = 0;
    // Luodaan valikkovaihtoehdot
    char list[3][50] = { "Start the Game (E)", "Pause the Game (P)", "Exit the Program (Z)" };

    // Alustetaan peli avaamalla pelilaudan tiedosto ja asettamalla pelilaudan alkutila
    game_init(board);

    // Alustetaan ncurses-kirjasto
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);

    // Alustetaan värejä
    start_color();
    init_pair(Human_pair,COLOR_BLUE,COLOR_BLUE);
    init_pair(ground, COLOR_GREEN, COLOR_GREEN);
    init_pair(River, COLOR_WHITE, COLOR_BLUE);
    init_pair(Mountain, COLOR_WHITE, COLOR_BLACK);
    init_pair(Gray, COLOR_WHITE, COLOR_WHITE);
    init_pair(Orc_pair, COLOR_RED, COLOR_RED);

    // Luodaan peli-ikkuna ja valikko-ikkuna
    WINDOW *win = newwin(50, 100, 10, 60);
    WINDOW *menu = newwin(10, 55, 2, 15);
    keypad(menu, TRUE);
    
    bool running = false;

    // Pääsilmukka
    while (1) {
        // Päivitetään valikko
        wclear(menu);
        mvwprintw(menu, 1, 2, "Welcome to the Game Of Life!");
        box(menu, 0, 0);
        refresh();
        wrefresh(menu);

        // Tulostetaan valikkovaihtoehdot
        for (int j = 0; j < 3; j++)
        {
            if (j == i)
                wattron(menu, A_STANDOUT);
            else
                wattroff(menu, A_STANDOUT);
            mvwprintw(menu, j + 2, 2, "%s", list[j]);
        }

        // Näytetään pelaajien värit
        mvwprintw(menu, 6, 2, "Blue army is Humans");
        mvwprintw(menu, 7, 2, "Red army is Orcs");

        wrefresh(menu);

        // Odottaa pelaajan valintaa
        ch = wgetch(menu);
        move(0,20);
        printw("<%03d>", ch);
        // Käsitellään pelaajan valinta
        switch (ch) {
            case 'e':  // Aloita peli
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
            case 'p':  // Keskeytä peli
                nodelay(win, FALSE);
                break;
            case 'z':  // Poistu ohjelmasta
                delwin(menu);
                delwin(win);
                endwin();
                return 0;
        }
    }
}

/*!
 * \brief License Information.
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
