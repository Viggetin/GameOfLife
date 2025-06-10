/*!
 * \file functions.c
 * \brief Tämä tiedosto sisältää ohjelman tarvittavat funktiot.
 */

//Includes
#include "header.h"

/* Functions */

/**
 * Lyhyt selitys ohjelman toiminnasta
 * 
 * Alustaa pelilaudan lataamalla tiedon game.txt-tiedostosta.
 * 
 * Funktion idea on aloittaa itse peli. Ensimmäisenä avaamalla game.txt tiedostossa sisältävän pelilaudan johon on "piirretty" Pelin kartta
 * Aluksi ongelmien välttämiseksi structin current ja future laudat nollataan.
 * Seuraavaksi avataan game.txt jossa käydään jokainen laudan solu läpi lukien, että onko solu 0 (tyhjä solu), 1 (Ihmisten solu), 2(Örkkien solu)
 * (W) vesistö solu tai (^) vuori solu.
 * 
 * Lopulta funktio lopettaa sulkemalla avatun tiedoston ja täten pelilaudat on asetettu oikein tulevia funktioita varten
 * @param board Pelilauta, johon tiedot ladataan.
 */

void game_init(struct cell board[ROWS][COLUMNS]) {
    // Alustetaan muuttujat tiedoston lukemista varten
    FILE *fp;
    char state;

    // Nollataan kaikki pelilaudan solut ja asetetaan tyyppi 'N' (normaali)
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            board[i][j].current = 0; // Nykyinen tila nollataan
            board[i][j].future = 0; // Tuleva tila nollataan
            board[i][j].type = 'N'; // Solun tyyppi asetetaan normaaliksi
        }
    }

    // Avataan tiedosto game.txt lukuja varten
    fp = fopen("game.txt", "r");
    if (!fp) {
        // Tiedoston avaaminen epäonnistui, tulostetaan virheilmoitus ja poistutaan
        printf("Failed to open game.txt");
        return;
    }

    // Alustetaan rivin ja sarakkeen muuttujat
    int r = 1; 
    int c = 1; 
    // Luetaan tiedostosta solujen tilat ja asetetaan ne pelilaudalle
    while ((r < ROWS - 1) && (fscanf(fp, "%c", &state) == 1)) {
        if (state == '\n') {
            // Rivinvaihto, siirrytään seuraavalle riville
            r++; 
            c = 1; 
            continue;
        }

        if (c < COLUMNS - 1) 
        {
            // Käsitellään tiedostosta luettu tila
            switch (state) 
            {
                case '0':
                    // Tyhjä solu, asetetaan nykyinen tila ja tyyppi
                    board[r][c].current = 0;
                    board[r][c].type = 'N';
                    break;
                case '1':
                    // Ihmisten solu, asetetaan nykyinen tila ja tyyppi
                    board[r][c].current = 1;
                    board[r][c].type = 'N';
                    break;
                case '2':
                    // Örkkien solu, asetetaan nykyinen tila ja tyyppi
                    board[r][c].current = 2; 
                    board[r][c].type = 'N';
                    break;
                case 'W':
                    // Vesistö solu, asetetaan tyyppi
                    board[r][c].type = 'W'; 
                    break;
                case '^':
                    // Vuori solu, asetetaan tyyppi
                    board[r][c].type = '^'; 
                    break;
                case '@':
                    // Vuoriston sisällä oleva solu, asetetaan tyyppi
                    board[r][c].type = '@'; 
                    break;
                default:
                    // Tuntematon tila, ei tehdä mitään
                    break;
            }
            c++;
        }
    }

    // Suljetaan tiedosto
    fclose(fp);
}





/**
* Tämä funktio on osa simulointia, joka käsittelee pelilaudan solujen tilojen päivitystä pelin jokaisella askeleella. 
* Jokaiselle solulle lasketaan ympäröivien solujen määrä, jotka ovat joko ihmisiä tai örkkejä, ja tarkistetaan myös, onko vieressä vihollissoluja.
*
* Ensin käydään läpi jokainen solu pelilaudalla.
* Lasketaan ympäröivien ihmisten ja örkkien määrä kullekin solulle käyttämällä countNeighbors-funktiota.
* Tarkistetaan, että solu ei ole este (vuori, vesi tai seinä).
* Tarkistetaan solun nykyinen tila ja sovelletaan sääntöjä sen perusteella:
*
* Jos solu on ihminen:
* Jos naapurien määrä on alle 2 tai yli 3, ihminen kuolee alikuolleisuuden tai ylikuolleisuuden vuoksi.
* Muutoin yritetään liikkua oikealle, ja jos se on mahdollista, siirrytään sinne. Jos oikealla on örkki ja ei ole vierekkäisiä vihollissoluja, taistelu tapahtuu ja molemmat kuolevat.
*
* Jos solu on örkki, sitä koskevat vastaavat säännöt ihmisten sijasta.
* Jos solu on tyhjä ja naapureiden joukossa on 3 ihmistä ja 0 örkkiä, syntyy uusi ihminen. Jos taas naapureiden joukossa on 3 örkkiä ja 0 ihmistä, syntyy uusi örkki.
*
* Lopuksi päivitetään pelilauta tulevaisuuden tilan mukaiseksi.
* @param board Pelilauta, jonka solujen tiloja päivitetään.
*/
void calculateSim(struct cell board[ROWS][COLUMNS]) {
    // Käydään läpi jokainen pelilaudan solu
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            int humanCount = 0, orcCount = 0;
            bool adjacentEnemy = false;
            
            // Lasketaan ympäröivien ihmisten ja örkkien määrä sekä tarkistetaan vihollisten läheisyys
            if (board[i][j].type != '^' && board[i][j].type != 'W' && board[i][j].type != '@') {
                countNeighbors(board, i, j, &humanCount, &orcCount, &adjacentEnemy);
            }

            // Päivitetään solun tuleva tila nykyisen tilan perusteella
            if (board[i][j].current == 1) {
                if (humanCount < 2 || humanCount > 3) {
                    // Jos ihmisen ympärillä on liian vähän tai liikaa ihmisiä, ihminen kuolee
                    board[i][j].future = 0;
                } else {
                    if (j + 1 < COLUMNS && board[i][j + 1].current == 0 && board[i][j + 1].type == 'N') {
                        // Yritetään liikkua oikealle, jos se on mahdollista
                        board[i][j + 1].future = 1;
                    } else if (j + 1 < COLUMNS && board[i][j + 1].current == 2 && !adjacentEnemy) {
                        // Jos oikealla on örkki ja ei ole vierekkäisiä vihollissoluja, tapahtuu taistelu
                        board[i][j].future = 0;
                        board[i][j + 1].future = 0;
                    } else {
                        board[i][j].future = 1;
                    }
                }
            } else if (board[i][j].current == 2) {
                if (orcCount < 2 || orcCount > 3) {
                    // Jos örkin ympärillä on liian vähän tai liikaa örkkejä, örkki kuolee
                    board[i][j].future = 0;
                } else {
                    if (j - 1 >= 0 && board[i][j - 1].current == 0 && board[i][j - 1].type == 'N') {
                        // Yritetään liikkua vasemmalle, jos se on mahdollista
                        board[i][j - 1].future = 2;
                    } else if (j - 1 >= 0 && board[i][j - 1].current == 1 && !adjacentEnemy) {
                        // Jos vasemmalla on ihminen ja ei ole vierekkäisiä vihollissoluja, tapahtuu taistelu
                        board[i][j].future = 0;
                        board[i][j - 1].future = 0;
                    } else {
                        board[i][j].future = 2;
                    }
                }
            } else {
                // Tyhjä solu
                if (board[i][j].type == 'N' && board[i][j].current == 0) {
                    if (humanCount == 3 && orcCount == 0) {
                        // Jos ympärillä on 3 ihmistä ja ei örkkejä, syntyy uusi ihminen
                        board[i][j].future = 1; 
                    } else if (orcCount == 3 && humanCount == 0) {
                        // Jos ympärillä on 3 örkkiä ja ei ihmisiä, syntyy uusi örkki
                        board[i][j].future = 2;
                    }
                }
            }
        }
    }
    // Päivitetään pelilauta tulevaisuuden tilan mukaiseksi
    updateBoard(board);
}






/**
* Laskee tietyn solun ympärillä olevien naapurisolujen määrän ja tarkistaa, onko vieressä vihollissoluja.
* Tämä funktio laskee tietyn solun ympärillä olevien naapurisolujen määrän ja samalla tarkistaa, onko vieressä vihollissoluja.
* 
* Aluksi alustetaan muuttujat humanCount, orcCount ja adjacentEnemy. Käydään läpi solun ympärillä olevat solut käyttämällä kaksiulotteista silmukkaa.
* Tarkistetaan, että käsiteltävä solu ei ole itse solu, jota tarkastellaan, ja että se ei ole laudan reunalla tai este (vuori, vesi tai seinä).
* Jos naapuri on ihminen, lisätään humanCount-muuttujan arvoa yhdellä tai jos naapuri on örkki, lisätään orcCount-muuttujan arvoa yhdellä.
*
* Tarkistetaan myös, onko naapurisolussa vihollissolu. Jos solun vieressä on vihollissolu, asetetaan adjacentEnemy-Booleani arvoksi true.
* Tämän toiminnan jälkeen humanCount ja orcCount sisältävät ihmis- ja örkkinäkyvien solujen määrän, ja adjacentEnemy kertoo, onko tarkasteltavan solun vieressä vihollissoluja.
* Näitä tietoja käytetään edelleen pelin simulaatiossa, kun päätetään solun tuleva tila.
*
* @param board Pelilauta, jossa solut sijaitsevat.
* @param r Solun rivi-indeksi.
* @param c Solun sarakkeen indeksi.
* @param humanCount Ihmisten määrä solun ympärillä (tulos).
* @param orcCount Örkkien määrä solun ympärillä (tulos).
* @param adjacentEnemy Onko solun vieressä vihollissoluja (tulos).
*/

void countNeighbors(struct cell board[ROWS][COLUMNS], int r, int c, int* humanCount, int* orcCount, bool* adjacentEnemy) {
    // Alustetaan laskurit ja adjacentEnemy
    *humanCount = 0;
    *orcCount = 0;
    *adjacentEnemy = false; 
    
    // Käydään läpi solun ympärillä olevat solut
    for (int i = r - 1; i <= r + 1; i++) {
        for (int j = c - 1; j <= c + 1; j++) {
            // Tarkistetaan, että solu ei ole itse solu ja että se ei ole laudan reunalla tai este
            if ((i == r && j == c) || i < 0 || j < 0 || i >= ROWS || j >= COLUMNS ||
                board[i][j].type == 'W' || board[i][j].type == '^' || board[i][j].type == '@') {
                continue;
            }
            // Lisätään ihmisten ja örkkien määrää
            if (board[i][j].current == 1) {
                (*humanCount)++;
            } else if (board[i][j].current == 2) {
                (*orcCount)++;
            }
            // Tarkistetaan vihollisten läheisyys
            if ((board[r][c].current == 1 && board[i][j].current == 2) || (board[r][c].current == 2 && board[i][j].current == 1)) {
                *adjacentEnemy = true;
            }
        }
    }
}



/**
* Lyhyt selitys ohjelman toiminnasta
* Näyttää pelilaudan nykyisen tilan näytöllä ja päivittää sen.
* Funktio vastaa pelilaudan nykyisen tilan näyttämisestä näytöllä. Se tyhjentää ensin ncurses-näytön, jonka jälkeen piirtää pelitapahtumat.
* Samalla se asettaa boolean-arvon "insideMountain" kertomaan, onko kohdattu vuoristoalue, jota varten vuoristosolut väritetään harmaaksi.
* Käy sitten läpi jokaisen pelilaudan solun seuraavasti:
*
* --> Jos solu on jokisolu (W), piirretään joki-symboli näytölle.
* --> Jos solu on vuorisolu (^), vaihdetaan "insideMountain" -booleanin arvoa ja piirretään vuorisymboli näytölle.
* --> Jos "insideMountain" on tosi, solu väritetään harmaaksi.
* --> Jos solu on elävä ihmissolu (current == 1), piirretään ihmis-symboli näytölle.
* --> Jos solu on elävä örkkisolu (current == 2), piirretään örkki-symboli näytölle.
* --> Muussa tapauksessa solu piirretään tyhjänä näytölle.
*
* Lopuksi funktio piirtää laatikon (box) ikkunan ympärille ja päivittää näytön (wrefresh).
* 
* @param w NCurses-ikkuna, johon pelilauta piirretään.
* @param board Pelilauta, jossa solujen tilat sijaitsevat.
*/

void printBoard(WINDOW *w, struct cell board[ROWS][COLUMNS]) 
{
    // Tyhjentää ikkunan sisällön
    werase(w);
    
    // Käy läpi pelilaudan solut
    for (int i = 0; i < ROWS; i++) 
    {
        for (int j = 0; j < COLUMNS; j++) 
        {
            int x_pos = j * 2; // X-koordinaatti
            
            // Tarkistetaan solun tyyppi ja tila, ja piirretään vastaava symboli tai väri
            if (board[i][j].type == 'W') 
            {
                // Joki-symboli
                wattron(w, COLOR_PAIR(River));
                mvwprintw(w, i, x_pos, "~~");
                wattroff(w, COLOR_PAIR(River));
            } else if (board[i][j].type == '^') 
            {
                // Vuorisymboli, väri riippuu "insideMountain" -booleanista
                wattron(w, COLOR_PAIR(Mountain));
                mvwprintw(w, i, x_pos, "^^");
                wattroff(w, COLOR_PAIR(Mountain));
            } else if (board[i][j].current == 1) 
            {
                // Ihmis-symboli
                wattron(w, COLOR_PAIR(Human_pair));
                mvwprintw(w, i, x_pos, "HH");
                wattroff(w, COLOR_PAIR(Human_pair));
            } else if (board[i][j].current == 2) 
            {
                // Örkki-symboli
                wattron(w, COLOR_PAIR(Orc_pair));
                mvwprintw(w, i, x_pos, "OO");
                wattroff(w, COLOR_PAIR(Orc_pair));
            } else if (board[i][j].type == '@') 
            {
                // Harmaa väri
                wattron(w, COLOR_PAIR(Gray));
                mvwprintw(w, i, x_pos, "##");
                wattroff(w, COLOR_PAIR(Gray));
            } else 
            {
                // Tyhjä solu
                wattron(w, COLOR_PAIR(ground));
                mvwprintw(w, i, x_pos, "  ");
                wattroff(w, COLOR_PAIR(ground));
            }
        }
    }
    
    // Piirtää laatikon (box) ikkunan ympärille ja päivittää näytön
    box(w, 0, 0);
    wrefresh(w);
}






/**
* Lyhyt selitys ohjelman toiminnasta
* 
* Päivittää pelilaudan nykyisen tilan tulevaisuuden tilaan.
* Funktio korvaa vanhemman taulukon future taululla 
* joka on päivitetty alkuperäisestä calculateSim funktion laskujen mukaisesti
* 
* @param board Pelilauta, joka päivitetään.
*/
void updateBoard(struct cell board[ROWS][COLUMNS])
{
    // Käy läpi kaikki solut pelilaudalla
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLUMNS; c++) {
            // Korvaa nykyinen tila tulevaisuuden tilalla
            board[r][c].current = board[r][c].future; 
        }
    }
}