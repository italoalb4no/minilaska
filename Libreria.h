/**
* @file Libreria.h
* @brief Libreria MiniLaska
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

/** @brief Numero di righe della scacchiera */
#define DROW 7
/** @brief Numero di colonne della scacchiera */
#define DCOL 7
/** @brief Clearing the Screen */
#define cls system("cls") 


/***************************************************************************************************************************************************************************************************************/
/*COSTANTI*/
/***************************************************************************************************************************************************************************************************************/

/** @brief Carattere che identifica una pedina nera*/
const char PNERE	= 'n';	  	    
/** @brief Carattere che identifica una cella vuota*/
const char VUOTO	= '0';	 	   
/** @brief Carattere che identifica una pedina bianca*/
const char PBIANCHE = 'b'; 	      
/** @brief Carattere che identifica una pedina NULL*/
const char PNULL	= '2'; 	  	 
/** @brief Colore della cornice della scacchiera*/
const int  COLCORNI = 700;      
/** @brief Colore con sfondo bianco con scritte nere*/
const int  WHITE	= 240;     
/** @brief Colore nero con lettere biache*/
const int  BLACK	= 7;   	  
/** @brief Dimensione*/
const int  SIZE_	= 5;   	 
/** @brief Coordinata X iniziale per posizionare la schacchiera*/
const int  X 		= 0;  	
/** @brief Coordinata Y iniziale per posizionare la schacchiera*/
const int  Y 		= 0;   


/***************************************************************************************************************************************************************************************************************/
/*STRUTTURE*/
/***************************************************************************************************************************************************************************************************************/

/**
 * @struct pedina
 * @brief Questa struct descrive una pedina
*/
typedef struct pedina {
    /** @brief Colonna in cui si trova la pedina*/
    short x;
    /** @brief Riga in cui si trova la pedina*/
    short y;

    /** @brief Rappresenta la torre*/
    char  color[3];	 
    /** @brief Carattere che identifica il colore della pedina più in alto. Può assumere i valori PNERE o PBIANCHE.*/
    char  colorTop;
    /** @brief Indica se la pedina è stata promossa.
     *  Se la pedina è promossa, essa può muoversi anche all'indietro.
     *  Assume i valori: 0 (non promossa), 1 (promossa)
    */
    short promozione;
} pedina;

/**
 * @struct menu
 * @brief Questa struct descrive il menù di gioco
*/
typedef struct menu {
    /** @brief Vettore di stringhe; rappresenta le opzioni possibili*/
	char* opzioni[20];
    /** @brief Indica il numero di opzioni possibili*/
	int n_Opz;
} menu;

/***************************************************************************************************************************************************************************************************************/
/* Funzioni per la grafica */
/***************************************************************************************************************************************************************************************************************/
/**
 * @brief Permette di colorare i caratteri nella command line interface dalla funzione in poi.
 * @details Questa funzione è stata trovata online.
 * @param Color Il codice del colore da utilizzare
*/
void set_Color(short Color);

/**
 * @brief Permette di spostarsi da una coordinata a un'altra nella command line interface.
 * @details Questa funzione è stata trovata online.
 * @param x La coordinata X
 * @param y La coordinata Y
*/
void gotoxy(int x, int y);

/**
 * @brief Stampa una stringa specifica in un punto specificato e in un colore determinato
 * 
 * @param x La coordinata X
 * @param y La coordinata Y
 * @param c Colore
 * @param car Stringa
 */
void stmpString(int x, int y, int c, char *car);

/**
 * @brief Stampa un carattere specifico in un punto specificato e in un colore determinato
 * 
 * @param x La coordinata X
 * @param y La coordinata Y
 * @param c Colore
 * @param car Carattere
 */
void stmpChar(int x, int y, int c, char car);

/**
 * @brief Stampa un rettangolo di spazi in uno specifico colore a delle determinate cordinate
 * 
 * @param x La coordinata X
 * @param y La coordinata Y
 * @param sizeX Lunghezza
 * @param sizeY Altezza
 * @param c Colore
 * @param car Carattere
 */
void stmpRet(int x, int y, int sizeX,int sizeY, char* car, int c);

/**
 * @brief Stampa una cornice di una sequenza di char in uno specifico colore a delle determinate coordinate
 * 
 * @param x La coordinata X
 * @param y La coordinata Y
 * @param distx Lunghezza per il segmento costruito sull'asse X
 * @param disty Lunghezza per il segmento costruito sull'asse Y
 * @param car Carattere
 * @param color Colore
 * @param xUgY Specifica se la larghezza della linea della cornice delle X sia uguale alla linea della cornice delle Y; assume valori 0 e 1
 */
void stmpCornice (int x, int y, int distx, int disty, char* car, int color, int xUgY);	  		

/**
 * @brief Stampa della scacchiera
 * 
 * @param x La coordinata X
 * @param y La coordinata Y
 * @param size Dimensione della riga costruita sull'asse Y
 * @param nCol Il numero di colonne
 * @param nRig Il numero di righe
 * @param sch La matrice contenente le pedine
 */
void stmpScacchiera(int x, int y, int size, int nCol, int nRig, pedina sch[ ][DROW]);

/**
 * @brief Stampa del menù specificato
 * 
 * @param y Cordinata y da cui partire
 * @param a Menù da stampare
 * @param p Valore che identifica l'opzione del menù che è stata selezionata 
 */
void stmpMenu(int y, menu a, int p);

/**
 * @brief Stampa della opzione selezionata per il menù
 * 
 * @param a Stringa da stampare 
 * @param y Riga a cui stampare la stringa passata
 */
void stmpSel(char* a, int y);

/**
 * @brief Stampa del menù al centro
 * 
 * @param ymin Coordinata Y da cui inzia a stampare il menù
 * @param a Menù da stampare
 * @return Valore che identifica la posione dell'opzione del menù che è stata scelta
 */
int  menuCntr (int ymin, menu a);

/**
 * @brief Selezionare una pedina da muovere o muovere una pedina in una cella selezionata cambiando opz a 1
 * 
 * @param x Cordinata X della cella da cui partire
 * @param y Cordinata Y della cella da cui partire
 * @param size Dimensione della cornice che identifica la pedina selezionata
 * @param col Numero di colonne
 * @param rig Numero di righe
 * @param xFin Coordinata X della cella selezionata attraverso invio
 * @param yFin Coordinata Y della cella selezionata attraverso invio
 * @param dis Identifica il comportamento con il tasto di esc ('0' ritorna le coordinate iniziali, '1' ritorna le coordinate settate a (-1;-1))
 */
void selezione (int x, int y, int size, int col, int rig, int* xFin, int* yFin, int dis);

/**
 * @brief Decidere in quale casella spostare la pedina
 * 
 * @param x Cordinata x della cella da cui partire
 * @param y Cordinata y della cella da cui partire
 * @param size Dimensione della cornice che identifica la pedina selezionata
 * @param xFin Coordinata X della cella selezionata attraverso il tasto 'invio'
 * @param yFin Coordinata Y della cella selezionata attraverso il tasto 'invio'
 * @return Specifica se l'azione di spostamento grafico ha avuto come risultato true(1) o false (0)
 */
int  spostamento(int x, int y, int size, int* xFin, int* yFin);

/***************************************************************************************************************************************************************************************************************/
/*Funzioni  di controllo*/
/***************************************************************************************************************************************************************************************************************/
/**
 * @brief Controllo per il movimento verso l'alto (su)
 * 
 * @param a Valore di una lettera associato ad un intero
 * @return Specifica se l'azione ha avuto come risultato true(1) o false (0)
 */
int su(int a);

/**
 * @brief Controllo per il movimento verso il basso (giù)
 * 
 * @param a Valore di una lettera associato ad un intero
 * @return Specifica se l'azione ha avuto come risultato true(1) o false (0)
 */
int giu(int a);

/**
 * @brief Controllo per il movimento verso destra
 * 
 * @param a Valore di una lettera associato ad un intero
 * @return Specifica se l'azione ha avuto come risultato true(1) o false (0)
 */
int destra(int a);

/**
 * @brief Controllo per il movimento verso sinistra
 * 
 * @param a Valore di una lettera associato ad un intero
 * @return Specifica se l'azione ha avuto come risultato true(1) o false (0)
 */
int sinistra(int a);

/**
 * @brief Controllo se è stato premuto il tasto 'esc'
 * 
 * @param a Valore di una lettera associato ad un intero
 * @return Specifica se l'azione ha avuto come risultato true(1) o false (0)
 */
int esc(int a);

/***************************************************************************************************************************************************************************************************************/
/*Funzioni  di get*/
/***************************************************************************************************************************************************************************************************************/

/**
 * @brief Restituisce le coordinate di un punto piu in alto a sinistra di ogni cella della scacchiera
 * 
 * @param coord Coordinata X o coordinata Y
 * @param size Dimensione della scacchiera contenente le pedine
 * @param i Identifica la colonna o la riga su cui vado a calcolare la coordinata
 * 
 * @return Le coordinate di un punto
 */ 
int  getCord(int coord, int size, int i);

/**
 * @brief Ottengo il colore della cella
 * 
 * @param i Colonna della cella
 * @param j Riga della cella
 * @return Il colore della cella 
 */
int  getColor(int i, int j);

/**
 * @brief Ottengo la Coordinata X da cui poi iniziare a costruire il rettangolo
 * 
 * @param x La coordinata X di partenza
 * @param i Colonna in cui mi trovo
 * @param size Dimensione della scacchiera
 * @param a Stringa che mi identifica la torre da stampare
 * @return La Coordinata X 
 */
int  getCentrRetX(int x, int i, int size, char* a);

/**
 * @brief Ottengo la Coordinata Y da cui poi iniziare a costruire il rettangolo
 * 
 * @param y La coordinata Y di partenza
 * @param j Riga in cui mi trovo
 * @param size Dimensione della scacchiera
 * @return La Coordinata Y 
 */
int  getCentrRetY(int y, int j, int size);

/**
 * @brief Ottengo un carattere rappresentante un intero
 * @details Non interrompe l'esecuzione del programma
 * 
 * @return Carattere rappresentante un intero
 */
int  getIntCar();

/**
 * @brief Ottengo il valore del numero premuto da 1 a 9
 * 
 * @param c Valore di una lettera associato a un intero
 * @return Il numero associato ad un intero che è rappresentato dal parametro della funzione
 */
int  switch_P (int c);

/**
 * @brief Ottengo la lettera della posizione più alta della torre che rappresenta la pedina che domina sulla torre
 * 
 * @param a Pedina sulla quale cerco la lettera nella posizione più alta
 * @return La lettera della posizione più alta della torre 
 */
char getColorTop(pedina a);

/**
 * @brief Conta l'altezza della pedina
 * 
 * @param a  Pedina
 * @return Altezza della torre
 */
int getAltTorre(pedina a);

/**
 * @brief Conta l'altezza della stringa (che identifica una torre di pedine)
 * 
 * @param a Torre di pedine 
 * @return Altezza della stringa
 */
int  countH(char* a);

/***************************************************************************************************************************************************************************************************************/
/*Funzioni  di set*/
/***************************************************************************************************************************************************************************************************************/

/**
 * @brief Stabilisco il punto del centro del rettangolo
 * 
 * @param x Coordinata X di partenza
 * @param y Coordinata Y di partenza
 * @param i Colonna
 * @param j Riga
 * @param size Dimensione della scacchiera contenente le pedine
 * @param a Identifica la torre di pedine
 * @param xr Valore di ritorno della coordinata X
 * @param yr Valore di ritorno della coordinata Y
 */
void setPCentRet(int x, int y, int i, int j, int size, char* a, int* xr,int* yr);

/***************************************************************************************************************************************************************************************************************/
/*Funzioni generiche*/
/***************************************************************************************************************************************************************************************************************/

/**
 * @brief Pulisco il buffer di input
 */
void cls_Buffer();

/**
 * @brief Inserisco al centro delle ascisse (asse X) una stringa specificata
 * 
 * @param a Stringa da inserire
 * @param rig Riga a cui stampare
 */
void centro(char* a, int rig);

/***************************************************************************************************************************************************************************************************************/
/*Costruttori*/
/***************************************************************************************************************************************************************************************************************/

/**
 * @brief Costruttore di un elemento avente come tipo la struttura 'Pedina'
 * 
 * @param x_ Coordinata X della pedina
 * @param y_ Coordinata Y della pedina
 * @param color_ Colore della pedina
 * @param promo_ Valore della promozione della pedina (0 o 1)
 * @return La pedina 
 */
pedina Pedina(int x_, int y_, char color_,int promo_);

/***************************************************************************************************************************************************************************************************************/
/*Funzioni d'inizializzazione */
/***************************************************************************************************************************************************************************************************************/

/**
 * @brief Inizializzazione della scacchiera con i valori di default
 * 
 * @param s La matrice che rappresenta la scacchiera contenente le pedine
 * @param opz Definisce se si vuole giocare con le pedine Bianche (1) o con le pedine nere (0)
 */
void inizScacchiera(pedina s[][DROW], int opz);

/***************************************************************************************************************************************************************************************************************/
/*Funzioni di controllo*/
/***************************************************************************************************************************************************************************************************************/

/**
 * @brief Controllo se la pedina in input è una cella vuota
 * 
 * @param a La cella(pedina) presa in considerazione
 * @return 1 se la cella è vuota, 0 altrimenti 
 */
int isPNull(pedina a);

/***************************************************************************************************************************************************************************************************************/
/*Funzioni di gioco */
/***************************************************************************************************************************************************************************************************************/

/**
 * @brief Avvio del menù di gioco
 */
void Menu();

/**
 * @brief Restituisce nel prompt le informazioni su come si è conclusa la partita (vedere end per i valori)
 * 
 * @param e Valore specificato dalla funzione 'end'
 */
void cntrFine(short int e);

/**
 * @brief Avvio del gioco
 * 
 * @return Valore di conclusione della partita (vedere end per i valori)
 */
short int game_start();

/**
 * @brief Promuove una pedina
 * 
 * @param sch La matrice che rappresenta la scacchiera contenente le pedine
 * @param x Colonna 
 * @param y Riga
 */
void actionPromote(pedina sch[][DROW], int x, int y);

/**
 * @brief Controlla se ci sono pedine da promuovere 
 * 
 * @param sch La matrice che rappresenta la scacchiera contenente le pedine
 */
void promote(pedina sch[][DROW]);

/**
 * @brief Operazione di spostamento della pedina
 * @param a La matrice che rappresenta la scacchiera contenente le pedine
 * @param xS La coordinata X della cella di origine (Pedina selezionata)
 * @param xS La coordinata Y della cella di origine (Pedina selezionata)
 * @param xTo La coordinata X della cella di destinazione
 * @param yTo La coordinata Y della cella di destinazione
 * 
 * @return Un valore di controllo 
 */
int sposta(pedina a[][DROW], int xS, int yS, int xTo, int yTo);
int conquista(pedina[][DROW], int, int, int, int);

/**
 * @brief Controlla e restituisce lo stato della partita, se ancora in corso o 
 * conclusa con uno stallo o con la vittoria di una delle due parti, e in caso quale
 * @param sch La matrice che rappresenta la scacchiera contenente le pedine
 * @param turno Il carattere che rappresenta il turno al momento in cui la funzione viene invocata
 * 
 * @return Uno di 4 possibili numeri interi, che rappresentano lo stato della partita al momento dell' invocazione (0: nessuno ha vinto; 1: ha vinto il bianco; 2: ha vinto il nero; 3: stallo)
 */
short int end(pedina sch [][DROW], char turno);

/**
 * @brief Determina se la pedina selezionata ha mosse disponibili
 * @param sch La matrice contenente le pedine
 * @param x La coordinata X della pedina presa in considerazione
 * @param y La coordinata Y della pedina presa in considerazione
 * @param enemy_s_color Il carattere rappresentante il colore dell'avversario
 * 
 * @return Un valore che indica se la pedina considerata ha o meno mosse disponibili a disposizione
 */
short int there_are_moves_available(pedina sch[][DROW], int x, int y, char enemy_s_color);

/**
 * @brief La possibilità o meno per una pedina di effettuare una conquista in basso a sinistra
 * @param sch La matrice contenente le pedine
 * @param x La coordinata X della pedina presa in considerazione
 * @param y La coordinata Y della pedina presa in considerazione
 * @param enemy_s_color Il carattere rappresentante il colore dell'avversario
 * 
 * @return Un valore che indica la possibilità di effettuare la conquista
 */
short int eat_bottom_left(pedina sch[][DROW], int x, int y, char enemy_s_color);

/**
 * @brief La possibilità o meno per una pedina di effettuare una conquista in alto a sinistra
 * @param sch La matrice contenente le pedine
 * @param x La coordinata X della pedina presa in considerazione
 * @param y La coordinata Y della pedina presa in considerazione
 * @param enemy_s_color Il carattere rappresentante il colore dell'avversario
 * 
 * @return Un valore che indica la possibilità di effettuare la conquista
 */
short int eat_top_left(pedina sch[][DROW], int x, int y, char enemy_s_color);

/**
 * @brief La possibilità o meno per una pedina di effettuare una conquista in alto a destra
 * @param sch La matrice contenente le pedine
 * @param x La coordinata X della pedina presa in considerazione
 * @param y La coordinata Y della pedina presa in considerazione
 * @param enemy_s_color Il carattere rappresentante il colore dell'avversario
 * 
 * @return Un valore che indica la possibilità di effettuare la conquista
 */
short int eat_top_right(pedina sch[][DROW], int x, int y, char enemy_s_color);

/**
 * @brief La possibilità o meno per una pedina di effettuare una conquista in basso a destra
 * @param sch La matrice contenente le pedine
 * @param x La coordinata X della pedina presa in considerazione
 * @param y La coordinata Y della pedina presa in considerazione
 * @param enemy_s_color Il carattere rappresentante il colore dell'avversario
 * 
 * @return Un valore che indica la possibilità di effettuare la conquista
 */
short int eat_bottom_right(pedina sch[][DROW], int x, int y, char enemy_s_color);

/**
 * @brief La possibilità o meno per una pedina di effettuare uno spostamento in una qualsiasi
 * direzione senza effettuare una conquista
 * @param sch La matrice contenente le pedine
 * @param x La coordinata X della pedina presa in considerazione
 * @param y La coordinata Y della pedina presa in considerazione
 * @param enemy_s_color Il carattere rappresentante il colore dell'avversario
 * 
 * @return La possibilità della pedina di muoversi in una qualunque direzione 
 */
short int move_in_all_directions(pedina sch[][DROW], int x, int y, char enemy_s_color);

/**
 * @brief La possibilità o meno per una pedina di effettuare uno spostamento in basso a sinistra
 * @param sch La matrice contenente le pedine
 * @param x La coordinata X della pedina presa in considerazione
 * @param y La coordinata Y della pedina presa in considerazione
 * @param enemy_s_color Il carattere rappresentante il colore dell'avversario
 * 
 * @return La possibilità della pedina di essere posizionata o meno nella data direzione
 */
short int move_bottom_left(pedina sch[][DROW], int x, int y, char enemy_s_color);

/**
 * @brief La possibilità o meno per una pedina di effettuare uno spostamento in alto a sinistra
 * @param sch La matrice contenente le pedine
 * @param x La coordinata X della pedina presa in considerazione
 * @param y La coordinata Y della pedina presa in considerazione
 * @param enemy_s_color Il carattere rappresentante il colore dell'avversario
 * 
 * @return La possibilità della pedina di essere posizionata o meno nella data direzione
 */
short int move_top_left(pedina sch[][DROW], int x, int y, char enemy_s_color);

/**
 * @brief La possibilità o meno per una pedina di effettuare uno spostamento in alto a destra
 * @param sch La matrice contenente le pedine
 * @param x La coordinata X della pedina presa in considerazione
 * @param y La coordinata Y della pedina presa in considerazione
 * @param enemy_s_color Il carattere rappresentante il colore dell'avversario
 * 
 * @return La possibilità della pedina di essere posizionata o meno nella data direzione
 */
short int move_top_right(pedina sch[][DROW], int x, int y, char enemy_s_color);

/**
 * @brief La possibilità o meno per una pedina di effettuare uno spostamento in basso a destra
 * @param sch La matrice contenente le pedine
 * @param x La coordinata X della pedina presa in considerazione
 * @param y La coordinata Y della pedina presa in considerazione
 * @param enemy_s_color Il carattere rappresentante il colore dell'avversario
 * 
 * @return La possibilità della pedina di essere posizionata o meno nella data direzione
 */
short int move_bottom_right(pedina sch[][DROW], int x, int y, char enemy_s_color);

/**
 * @brief Cambia il turno del giocatore
 * @param turno Il turno attuale
 * 
 * @return Il turno aggiornato 
 */
char switchTurno(char turno);

