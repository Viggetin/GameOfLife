//Includes

#include "header.h"

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

void game_init(struct cell board[ROWS][COLUMNS]) {
    FILE *fp;
    int c, r;
    char state;

    c = 0;
    r = 0;

    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLUMNS; j++)  
        {
            board[i][j].current = 0;  // Nollataan koko taulukko
            board[i][j].future = 0;
        }
    }

    fp = fopen("game.txt", "r");
    if (fp == NULL) {
        perror("Failed to open game.txt");
        return;  // Exit the function if file cannot be opened
    }

    while (r < ROWS && fscanf(fp, "%c", &state) == 1) {
        if (state == '\n') {
            r++;
            c = 0;
            continue;  // Skip to the next row on encountering a newline
        }
        if (state == '0' || state == '1') {
            board[r][c].current = state - '0';  // Convert character '0' or '1' to integer 0 or 1
            c++;
        }

        if (c >= COLUMNS && state != '\n') {
            r++;
            c = 0;
        }
    }

    fclose(fp);

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

void printBoard(WINDOW * w,struct cell board[ROWS][COLUMNS]) {
    clear();  // Clear the screen
    wmove(w,1,1);
    
    for (int i = 1; i < ROWS-1; i++) {
        for (int j = 1; j < COLUMNS-1; j++) {
            attron(COLOR_PAIR(1));
            
            mvwprintw(w,i, j * 2, "%d", board[i][j].current);
        }
    }
    wrefresh(w);
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