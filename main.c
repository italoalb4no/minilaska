/**
* @file main.c
* @mainpage IaP - CT0441-1 (CT3) 2020-21 - MiniLaska
* @section intro_sec Introduzione
*
* Gli studenti sono stati chiamati a sviluppare, in linguaggio ANSI C, miniLaska, una variante del gioco originale http://www.lasca.org/.
* <br> Rispetto al gioco originale, miniLaska prevede le seguenti limitazioni:
* \li si può mangiare/conquistare una sola volta per mossa;
* \li le torri possono essere alte al massimo 3 pedine, superato questo limite, la pedina più in basso viene rimossa dalla scacchiera.
*
* @section group Gruppo
* **Group ID 16** <br/>
* \li Jacopo Cini 885258
* \li Italo Albano 884034
* \li Matteo Grazioso 884055
*
* @section exe Esecuzione del programma
* Durante la fase di sviluppo, il gruppo ha usufruito di funzioni appartenenti alla libreria windows.h; 
    di conseguenza la fase di compilazione può essere effettuata solo ed esclusivamente su sistema operativo Windows; 
    si precisa pertanto che non può dunque essere generato alcun eseguibile per Linux e MacOS.
*/

#include "Libreria.c"

/**
 * @brief Main del progetto
 */
int main(){
	Menu();
    return 0;
}
