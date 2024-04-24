#ifndef HEADER_H
#define HEADER_H

/* Includes */
#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>

/* Definitions and Constants */
#define ROWS 50+2
#define COLUMNS 50+2
#define Generations
#define Creature 1;
struct cell
{ 
    int current;
    int future; 
}; 

/* Function Prototypes */
void game_init(struct cell board[ROWS][COLUMNS]);
int countNeighbors(struct cell board[ROWS][COLUMNS], int r, int c);
void printBoard(WINDOW * w,struct cell board[ROWS][COLUMNS]);
void updateBoard(struct cell board[ROWS][COLUMNS]);
void calculateSim(struct cell board[ROWS][COLUMNS]);

#endif