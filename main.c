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

/* Main Function */
int main(void)
{
    struct cell board[ROWS][COLUMNS];  // Julistetaan Board
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
