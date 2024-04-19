#include "header.h"
#include <stdio.h>

/* Functions */
/**
 * Lyhyt selitys ohjelman toiminnasta
 *
 * Funktion idea on aloittaa itse peli. Ensimmäisenä nollaamalla 8x8 taulukon nolliksi molemmat current ja futuren
 * Current taulukon idea on olla se joka printataan esille ja joka päivitetään aina pelin tapahtumien jälkeen
 * Future toimii siis ns Temp muuttujana jonne tallennetaan pelin muutokset ennen kun korvataan current taulukko uudella.
 * 
 * Funktiossa asetetaan myös elävät solut jota voi muokata tarvittaessa
 */
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
/**
 * Lyhyt selitys ohjelman toiminnasta
 *
 * Funktion idea on aloittaa pelin "toteuttamisen" annettujen sääntöjen mukaisesti
 * funktio aloittaa käymällä läpi taulukon joka ikisen solun läpi josta tarkistetaan countNeighbors funktion avulla solun naapureiden lukumäärän
 * Naapureiden lukumäärän perusteella voidaan ehtolauseilla päätellä tuleeko tämän hetkinen solu elämään tai menehtymään
 * Funktion lopussa taulukko siiretään updateBoard funktioon
 * 
 */
void calculateSim(struct cell board[ROWS][COLUMNS])
{
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
        int count = countNeighbors(board, i, j);
        if (board[i][j].current == 1) // Cell is currently alive
            {
                //Elävällä solulla on vain yksi naapuri tai 4 naapuria josta solu menehtyy joko yksinäisyyteen tai ylikansoittumiseen
                if(count < 2 || count > 3)
                {
                    board[i][j].future = 0;
                }
                // Muuten jos solulla on 3 naapuria niin se jatkaa elämistä
                else
                {
                    board[i][j].future = 1;
                }
            }
                else
            {
                // Jos solu on tyhjä mutta sillä on kolme naapuria tulee solusta elävä
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
/**
 * Lyhyt selitys ohjelman toiminnasta
 *
 * Funktion idea on laskea nykyisen tarkkailun alla olevan solun ympärillä olevien naapureiden lukumäärän
 * Funktiossa tämä tarkastellaan for looppeja käyttäen vasemmalta oikealle ja ylhäältä alas
 * Funktio erikseen tarkistaa, että se ei ota huomioon itse tarkasteltavaa solua
 * 
 * Funktio palautta count muuttujan, jota käytetään hyväksi calculateSim funktiossa
 */
int countNeighbors(struct cell board[ROWS][COLUMNS], int r, int c)
{
    int count = 0;
    
    for (int i = r - 1; i <= r + 1; i++) 
    {
        for (int j = c - 1; j <= c + 1; j++) 
        {
            // Jatka jos kyseessä on tarkasteltava solu
            if (i == r && j == c)
                continue;
            // plussataan naapuri jos on
            if (board[i][j].current == 1)
            {
                count++;
            }
        }
    }
    return count;
}
/**
 * Lyhyt selitys ohjelman toiminnasta
 *
 * Funktiossa printataan nykyinen voimassa oleva taulu esille terminaaliin
 */
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
 * Lyhyt selitys ohjelman toiminnasta
 *
 * Funktio korvaa vanhemman taulukon future taululla 
 * joka on päivitetty alkuperäisestä calculateSim funktion laskujen mukaisesti
 */
void updateBoard(struct cell board[ROWS][COLUMNS])
{
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLUMNS; c++) {
            board[r][c].current = board[r][c].future;
        }
    }
}