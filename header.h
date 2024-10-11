#ifndef HEADER_H
#define HEADER_H

/*!
* \file header.h
* \brief Tämä tiedosto sisältää ohjelman tarvittavat kirjastot, määrittelyt ja funktioiden prototyypit.
*/


/*!
 * \defgroup Sisällytetyt kirjastot
 * \brief Ohjelmassa tarvittavat kirjastot.
 * @{
 */
#include <stdio.h>    /**< Perustoimintoja varten. */
#include <ncurses.h>  /**< Visuaalinen käyttöliittymä. */
#include <unistd.h>   /**< usleep-funktio, joka mahdollistaa millisekuntien viivästykset. */

/*! @} */

/*!
 * \defgroup definitions Määrittelyt ja vakiot
 * \brief Ohjelmassa käytettävät määrittelyt ja vakiot.
 * @{
 */
#define ROWS 52 /**< Pelilaudan rivien määrä. */
#define COLUMNS 52 /**< Pelilaudan sarakkeiden määrä. */
#define Generations /**< Generaatioiden määrä. */
#define ground 1 /**< Maan väri. */
#define Human_pair 5 /**< Ihmisten väri. */
#define River 2 /**< Joen väri. */
#define Mountain 3 /**< Vuoren väri. */
#define Gray 4 /**< Harmaan väri. */
#define Orc_pair 6 /**< Örkkien väri. */
/*! @} */

/*!
 * \struct cell
 * \brief Pelilaudan solu, joka tallentaa nykyisen ja tulevan tilan sekä tyypin.
 */
struct cell
{
    int current; /**< Nykyinen tila. */
    int future; /**< Tuleva tila. */
    char type; /**< Solun tyyppi ('N' normaali, 'W' vesi/joki, '^' vuori). */
};

/*!
 * \defgroup prototypes Funktioiden prototyypit
 * \brief Ohjelmassa tarvittavat funktioiden prototyypit.
 * @{
 */
void game_init(struct cell board[ROWS][COLUMNS]);
void countNeighbors(struct cell board[ROWS][COLUMNS], int r, int c, int* humanCount, int* orcCount, bool* adjacentEnemy);
void printBoard(WINDOW *w, struct cell board[ROWS][COLUMNS]);
void updateBoard(struct cell board[ROWS][COLUMNS]);
void calculateSim(struct cell board[ROWS][COLUMNS]);
/*! @} */

#endif /* HEADER_H */