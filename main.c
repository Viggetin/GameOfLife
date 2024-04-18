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
#include <stdio.h>

/* Definitions and Constants */
#define ROWS 9+1
#define COLUMNS 9+1
#define Generations

struct cell
{ 
    int current;
    int future; 
}; 

/* Function Prototypes */
void game_init(struct cell board[ROWS][COLUMNS]);
int countNeighbors(struct cell board[ROWS][COLUMNS], int r, int c);
void printBoard(struct cell board[ROWS][COLUMNS]);
void updateBoard(struct cell board[ROWS][COLUMNS]);
void calculateSim(struct cell board[ROWS][COLUMNS]);



/* Main Function */
int main(void)
{
    struct cell board[ROWS][COLUMNS];  // Julistetaan Board Array
    int x = 0;

    game_init(board);
    printBoard(board);
    while(x < 10)
    {
        calculateSim(board);
        printBoard(board);
        x++;
    }
    return 0;
}

/* Functions */

void game_init(struct cell board[ROWS][COLUMNS])
{
    //Nollataan board.Current
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLUMNS; j++)  
        {
            board[i][j].current = 0;  // Nollataan koko taulukko
            board[i][j].future = 0;
        }
    }
    
    // Esimerkki elävät solut
    board[2][2].current = 1;
    board[2][3].current = 1;
    board[1][4].current = 1;
    board[2][5].current = 1;
    board[2][6].current = 1;
    board[3][3].current = 1;
    board[3][5].current = 1;
    board[4][4].current = 1;

}

void calculateSim(struct cell board[ROWS][COLUMNS])
{
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
        int count = countNeighbors(board, i, j);
        if (board[i][j].current == 1) // Cell is currently alive
            {  
                if(count < 2 || count > 3)
                {
                    board[i][j].future = 0;
                }
                else
                {
                    board[i][j].future = 1;
                }
            }
                else
            {
                if(count == 3)
                {
                    board[i][j].future = 1;
                }
                else
                {
                    board[i][j].future = 0;
                }
            }
        }
    }
    updateBoard(board);
}
int countNeighbors(struct cell board[ROWS][COLUMNS], int r, int c)
{
    int count = 0;
    
    for (int i = r - 1; i <= r + 1; i++) 
    {
        for (int j = c - 1; j <= c + 1; j++) 
        {
            // Continue if it's the cell itself
            if (i == r && j == c)
                continue;
            // Count if the neighboring cell is 1
            if (board[i][j].current == 1)
            {
                count++;
            }
        }
    }
    return count;
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

void updateBoard(struct cell board[ROWS][COLUMNS])
{
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLUMNS; c++) {
            board[r][c].current = board[r][c].future;
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
