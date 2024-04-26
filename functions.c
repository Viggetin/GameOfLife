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
    char state;

    // Initialize all cells to zero
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            board[i][j].current = 0;
            board[i][j].future = 0;
            board[i][j].type = 'N'; // Default type
        }
    }

    // Open the game file
    fp = fopen("game.txt", "r");
    if (!fp) {
        refresh();
        perror("Failed to open game.txt");
        return;
    }

            // Inside game_init function
        for (int r = 1; r < ROWS - 1; r++) {
        for (int c = 1; c < COLUMNS - 1; ) {
            if (fscanf(fp, "%c", &state) != 1) {
                // EOF reached unexpectedly, you might want to handle this
                break;  // Handle EOF or read error
            }
            if (state == '\n') {
                break;  // Done with the current line, move to the next row
            }
            if (state == '0') {
                board[r][c].current = 0;
                board[r][c].type = 'N'; // Normal cell
            } else if (state == '1') {
                board[r][c].current = 1;
                board[r][c].type = 'N'; // Normal cell
            } else if (state == 'W') {
                board[r][c].type = 'W'; // River cell
            } else if (state == '^') {
                board[r][c].type = '^'; // Mountain cell
            }
            c++; // Move to the next column
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
int countNeighbors(struct cell board[ROWS][COLUMNS], int r, int c) {
    int count = 0;
    for (int i = r - 1; i <= r + 1; i++) {
        for (int j = c - 1; j <= c + 1; j++) {
            if ((i == r && j == c) || i < 0 || j < 0 || i >= ROWS || j >= COLUMNS) {
                continue;  // Skip the cell itself and out of bounds indices
            }
            if (board[i][j].current == 1) {
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

void printBoard(WINDOW *w, struct cell board[ROWS][COLUMNS]) {
    werase(w);
    for (int i = 1; i < ROWS - 1; i++) {
        for (int j = 1; j < COLUMNS - 1; j++) {
            int x_pos = j * 2; // Positioning for each cell

            if (board[i][j].type == '^') {
                wattron(w, COLOR_PAIR(Mountain)); // Mountain color
                mvwprintw(w, i, x_pos, "^ ");    // Mountain symbol with a space after
                wattroff(w, COLOR_PAIR(Mountain));
            } else if (board[i][j].type == 'W') {
                wattron(w, COLOR_PAIR(River));   // River color
                mvwprintw(w, i, x_pos, "~ ");    // River symbol with a space after
                wattroff(w, COLOR_PAIR(River));
            } else if (board[i][j].current == 1) {
                wattron(w, COLOR_PAIR(Creature_pair)); // Living cell color
                mvwprintw(w, i, x_pos, "1 ");         // Living cell symbol with a space after
                wattroff(w, COLOR_PAIR(Creature_pair));
            } else {
                wattron(w, COLOR_PAIR(ground)); // Dead cell color
                mvwprintw(w, i, x_pos, "  ");   // Empty space for dead cells
                wattroff(w, COLOR_PAIR(ground));
            }
        }
    }
    box(w, 0, 0);
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