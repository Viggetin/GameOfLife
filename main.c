/**
 * file:    GameOfLife.c
 * author:  John Doe
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
#include <stdio.h>

/* Definitions and Constants */
#define ROWS 9
#define COLUMNS 9

struct cell
{ 
    int current;
    int future; 
}; 

/* Function Prototypes */
void game_init(struct cell board[ROWS][COLUMNS]);
int countNeighbors(struct cell board[ROWS][COLUMNS], int i, int j);
void printBoard(struct cell board[ROWS][COLUMNS]);



/* Main Function */
int main(void)
{
    struct cell board[ROWS][COLUMNS];  // Julistetaan Board Array
    game_init(board);  

    // Esimerkki elävät solut
    board[1][1].current = 1;
    board[1][2].current = 1;
    board[1][3].current = 1;
    board[5][1].current = 1;
    board[6][2].current = 1;
    board[6][3].current = 1;

    printBoard(board);
}

/* Functions */

void game_init(struct cell board[ROWS][COLUMNS])
{
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLUMNS; j++)  
        {
            board[i][j].current = 0;  // Nollataan koko taulukko
        }
    }

}

int countNeighbors(struct cell board[ROWS][COLUMNS], int i, int j)
{

}
// Funktiossa käydään kaikki board arrayn solut läpi jotka printataan näkyville
void printBoard(struct cell board[ROWS][COLUMNS]) {
    printf("Current state of the board:\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            printf("%d ", board[i][j].current);  // printataan jokaisen solun arvo
        }
        printf("\n");
    }
    printf("\n");
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
