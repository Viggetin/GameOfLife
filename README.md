Game of Life

Tämä ohjelma toteuttaa Conwayn Game of Life -pelin kaltaisen taistelu pelin kahden eri armeijan välillä (LOTR).

Game of Life on soluautomaatti, joka toimii kaksiulotteisella ruudukolla. Peli etenee askel askeleelta sääntöjen mukaisesti, jotka määräävät, mitkä solut pysyvät elossa, syntyvät uudestaan tai kuolevat. Ohjelma käyttää tekstipohjaista käyttöliittymää näyttääkseen pelin tilan ja päivittääkseen sitä jokaisen askeleen jälkeen. Tätä on logiikkaa on muutettu, että se toimisi kahden eri osapuolen välisessä kamppailussa. Taistelu on otettu Lord of the rings sarjasta inspiraationa.

Ohjelma käyttää seuraavia kirjastoja:

stdio.h: Perustoimintoja varten.

ncurses.h: Visuaalinen käyttöliittymä.

unistd.h: usleep-funktio, joka mahdollistaa millisekuntien viivästykset.
