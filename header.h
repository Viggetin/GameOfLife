#ifndef HEADER_H
#define HEADER_H

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

#endif