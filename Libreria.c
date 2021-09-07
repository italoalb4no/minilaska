/**
* @file Libreria.c
* @brief Implementazione delle funzioni di cui Libreria.h
*/
#include "Libreria.h"

/***************************************************************************************************************************************************************************************************************/
/* Funzioni per la grafica */
/***************************************************************************************************************************************************************************************************************/
void gotoxy(int x, int y)
{
	COORD coord;
 	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void set_Color(short Color)
{
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon, Color);
}

void stmpString(int x, int y, int c, char* car)
{
	gotoxy(x,y);
	set_Color(c);
	printf("%s",car);
	set_Color(7);
}

void stmpChar(int x, int y, int c, char car)
{
	gotoxy(x,y);
	set_Color(c);
	printf("%c",car);
	set_Color(7);
}
void stmpRet(int x, int y, int sizeX,int sizeY, char* car,  int c)
{
	int i=0;
	int j=0;

	while(i<sizeX)
	{
		while(j<sizeY)
		{
			stmpString(x+i,y+j, c, car);
			j++;
		}
		j=0;
		i++;
	}
	set_Color(7);
}
void stmpCornice (int x, int y, int distx, int disty, char* car, int color, int xUgY)
{
	int i=0;

	while (i<distx)/*muro orizzontale*/
	{
		stmpString(x+i,y, 		   color, car);
		stmpString(x+i,y+disty-1, color, car);

		i++;
	}

	i=0;
	while (i<disty) /*muro verticale*/
	{
		stmpString(x,i+y, 		   color, xUgY ? "  " : car);
		stmpString(x+distx-1,i+y, color, xUgY ? "  " : car);

		i++;
	}
}
void stmpScacchiera(int x, int y, int size, int nCol, int nRig, pedina sch[ ][DROW])
{
	int i = 0;
	int j = 0;
	int xc=0, yc=0;
	int col=0;

	stmpCornice(x,y, nCol*(size*2)+3,nRig*size+2, " ", COLCORNI, 1);

	/*
		nCol 	 ==> numero colonne
		(size*2) ==> per due perchè un carattere di y = 2 x
		+3 	 	 ==> ridimensionamento della cornice

		nRif 	 ==> numero righe
		size 	 ==> size di y
		+2 	 	 ==> ridimensionamento della cornice
	*/

	while(j<nRig) /*stampo i colori delle celle e la matrice che rappresenta le pedine*/
	{
		while(i<nCol)
		{
			stmpRet(getCord(x+1,size*2,i),getCord(y,size,j), size*2,size, " ",getColor(i,j));
			if(sch[i][j].colorTop!=VUOTO)
			{	
				col = sch[i][j].colorTop==PBIANCHE ? 9 : 6 ; 
			
				setPCentRet(x,y, i,j, size, sch[i][j].color, &xc,&yc);
				stmpChar(xc,yc, col, sch[i][j].color[0]);
				if(sch[i][j].color[1]!=VUOTO)
				{ 
					stmpChar(xc+1,yc, col, '/');
					stmpChar(xc+2,yc, col, sch[i][j].color[1]);
				}
				if(sch[i][j].color[2]!=VUOTO)
				{
					stmpChar(xc+3,yc, col, '/');
					stmpChar(xc+4,yc, col, sch[i][j].color[2]);
				}
			}
			i++;
		}
		i=0;
		j++;
	}
}
void stmpMenu(int y, menu a, int p)
{
	int i=0;

	while(i<a.n_Opz)
	{
		if(i!=p-1)centro(a.opzioni[i],y+i);
		else 	  stmpSel(a.opzioni[p-1],y+i);
		i++;
	}
	cls_Buffer();
}
void stmpSel(char* a, int y)
{
	set_Color(112);
	centro(a,y);
	set_Color(7);
}

int menuCntr (int ymin, menu a)
{
	int p 	 = 1;
	int y 	 = ymin;
	int ymax = ymin-1+a.n_Opz;
	int let  = 0;

	stmpMenu(ymin,a, p);
	cls_Buffer();


	while(let!=13)
	{
		if (kbhit())
		{
			let=getIntCar();

			if(su(let)) /*freccia su e w e W*/
			{
				p=y>ymin ? p-1 : a.n_Opz;
				y=y>ymin ? y-1 : ymax;
			}
			else if(giu(let)) /*freccia giu e s e S*/
			{
				p=y<ymax ? p+1 : 1;
				y=y<ymax ? y+1 : ymin;
			}
			else if(let>=49 && let<=57) /*numeri dal 1 al 9 */
			{
				p=switch_P(let);
				y=ymin+p-1;
				if(y>ymax)
				{
					p=ymax-ymin+1;
					y=ymax;
				}
			}
			else if(let==92) /*numeri premendo \ dal 10 al 19 */
			{
				while(let==92) if (kbhit()) let=getch();

				p=switch_P(let)+10;
				y=ymin+p-1;

				if(y>ymax)
				{
					p=ymax-ymin+1;
					y=ymax;
				}
			}
			stmpMenu(ymin,a, p);
		}
	}

	gotoxy(0, ymax+2);

	return p-1;
}

void selezione (int x, int y, int size, int col, int rig, int* xFin, int* yFin, int dis)
{
	int l=0;   /*variabile per tasto premuto*/
	int xR=(*xFin), yR=(*yFin);/*variabili per ritornare la casella iniziale se viene premuto esc*/

	/*stampo la prima cornice*/
	stmpCornice(getCord(x+1,size*2,*xFin),getCord(y,size,*yFin), size*2,size,"*", getColor(*xFin,*yFin),0);
	/*pulisco il buffer dove vengono salvati i tasti premuti*/
	cls_Buffer();

	while(l!=13)
	{/*controllo se vine premuto un tasto*/
		if (kbhit())
		{/*prendo il primo tasto premuto*/
			l=getIntCar();
			/*cancello il precedete rettangolo*/
			stmpCornice(getCord(x+1,size*2,*xFin),getCord(y,size,*yFin), size*2,size," ", getColor(*xFin,*yFin),0);
			
			/*if a catena per decidere di quanto variare x e y*/
			if(su(l) && (*yFin)>1) 			 (*yFin)-=2;  /*freccia su*/
			else if(giu(l) && (*yFin)<rig-2) (*yFin)+=2; /*freccia giu*/
			else if(destra(l) && (*xFin)<col-1)			/*freccia destra*/
			{
				if(dis) (*xFin)+=2;
				else if((*yFin)==col-1)(*xFin)+=2;
				else
				{
					(*xFin)+=1;
					if((*xFin)%2==0)(*yFin)-=1;
					else 			(*yFin)+=1;
				}
			}
			else if(sinistra(l) && (*xFin)>0)/*freccia sinistra*/
			{
				if(dis) (*xFin)-=2;
				else if((*yFin)==col-1)(*xFin)-=2;
				else 
				{
					(*xFin)-=1;
					if((*xFin)%2==0)(*yFin)-=1;
					else 			(*yFin)+=1;
				}
			}
			else if(esc(l))
			{
				(*yFin)=dis ? -1 :yR;
				(*xFin)=dis ? -1 :xR;
				l=13;
			}
			/*stampo la nuova cornice*/
			if(l!=13)stmpCornice(getCord(x+1,size*2,(*xFin)),getCord(y,size,(*yFin)), size*2,size, "*",getColor(*xFin,*yFin),0);
		}
	}
}
int spostamento(int x, int y, int size, int* xFin, int* yFin)
{
	int c=0;
	int r=0;
	int xR=x, yR=y;
	int caso = 11; 
	/* 
		0 ==> prima cella 
		1 ==> ultima cella 
		2 ==> prima cella ultima riga
		3 ==> prima cella ultima colonna
		4 ==> prima colonna 
		5 ==> prima riga  
		6 ==> ultima colonna 
		7 ==> ultima riga 
		default ==> lontano dai bordi 
	*/
	/*(*xFin) = xR;*/
	/*(*yFin) = yR;*/
	
	

	if(x==0 && y==0)/*prima cella*/
	{
		x++;
		y++;
		/*unica possibile mossa in avanti*/
		c = 1; 
		r = 1;
		caso =0;
	}
	else if(x==6 && y==6)/*ultima cella*/
	{
		x--;
		y--;
		/*unica possibile mossa indietro*/
		c = 1; 
		r = 1;
		caso =1;
	}
	else if(x==6 && y==0)/*prima cella ultima riga*/
	{
		x--;
		y++;
		/*unica possibile mossa in avanti*/
		c = 1; 
		r = 1;
		caso =2;
	}
	else if(x==0 && y==6)/*prima cella ultima colonna*/
	{
		x++;
		y--;
		/*unica possibile mossa indietro*/
		c = 1; 
		r = 1;
		caso =3;
	}
	/********************************************/
	else if(x==0 && y!=0) /*prima colonna*/
	{
		x++;
		y--;
		/*due mosse possibili*/
		c = 1;
		r = 3;   
		caso =4;
	}
	else if(x!=0 && y==0) /*prima riga*/
	{
		x--;
		y++;
		/*due mosse possibili*/
		c = 3;
		r = 1;
		caso =5;
	}
	else if(x==6 && y!=0) /*ultima colonna*/
	{
		x--;
		y--;
		/*due mosse possibili*/
		c = 1;
		r = 3;
		caso =6;   
	}
	else if(x!=0 && y==6) /*ultima riga*/
	{
		x--;
		y--;
		/*due mosse possibili*/
		c = 3;
		r = 1;
		caso =7;
	}
	/********************************************/
	else/*caso lontano dai bordi*/
	{
		x--;
		y--;
		/*quattro mosse possibili*/
		c = 3;
		r = 3;
		caso =9;/*default*/
	}
	
	/*mostro un riquadro che si muove che mostra le possibili mosse*/
	selezione(getCord(X,size*2,x)-1,getCord(Y,size,y)-1,size, c,r, xFin, yFin, 1);
	
	/* 
		0 ==> prima cella ==> 1 mossa
		1 ==> ultima cella  ==> 1 mossa
		2 ==> prima cella ultima riga ==> 1 mossa
		3 ==> prima cella ultima colonna ==> 1 mossa
		
		4 ==> prima colonna  ==> 2 mosse
		5 ==> prima riga  ==> 2 mosse
		6 ==> ultima colonna ==> 2 mosse
		7 ==> ultima riga ==> 2 mosse
		
		default ==> lontano dai bordi ==> 4 mosse
	*/	
	if((*xFin)!=-1 && (*yFin)!=-1)/*non e stato premuto esc*/
	{	
		switch(caso)
		{
			case 0: /*0 ==> prima cella */
				(*xFin) = 1;
				(*yFin) = 1;
			break; 
			case 1: /*1 ==> ultima cella */
				(*xFin) = 5;
				(*yFin) = 5;
			break; 
			case 2: /*2 ==> prima cella ultima riga  x==6 && y==0*/
				(*xFin) = 5;
				(*yFin) = 1;
			break; 
			case 3: /*3 ==> prima cella ultima colonna x==0 && y==6*/
				(*xFin) = 1;
				(*yFin) = 5;
			break; 
			case 4: /*4 ==> prima colonna*/
				(*xFin) = 1;
				(*yFin) += yR-1;	
			break; 
			case 5: /*5 ==> prima riga */
				(*xFin) += xR-1;
				(*yFin) = 1;
			break; 
			case 6: /*6 ==> ultima colonna*/
				(*xFin) = 5;
				(*yFin) += yR-1;	
			break; 
			case 7: /*7 ==> ultima riga */
				(*xFin) += xR-1;
				(*yFin) = 5;
			break; 
			default: 
				(*xFin) += xR-1;
				(*yFin) += yR-1;
			break;
		}
	
		return 1;
	}
	else return 0;
}


/***************************************************************************************************************************************************************************************************************/
/*Funzioni  di controllo*/
/***************************************************************************************************************************************************************************************************************/
int su(int a)	    {return a==72 || a==119 || a==87;}
int giu(int a)	    {return a==80 || a==115 || a==83;}
int destra(int a)   {return a==77 || a==100 || a==68;}
int sinistra(int a) {return a==75 || a==97  || a==65;}
int esc(int a)		{return a==27;}


/***************************************************************************************************************************************************************************************************************/
/*Funzioni  di get*/
/***************************************************************************************************************************************************************************************************************/
int getCord(int coord, int size, int i){return (coord+1)+i*(size);}
int getColor(int i, int j)			  {return (i%2==0 && j%2!=0) || (i%2!=0 && j%2==0)? WHITE : BLACK;}
int getCentrRetX(int x, int i, int size, char* a)
{
	int app=0;

	switch(countH(a))
	{
		case 1: /*torre di 1 carattere*/
			app=size-1;
		break;
		case 2: /*torre di 2 caratteri*/
			app= size-2;
		break;
		case 3: /*torre di 3 caratteri*/
			app= size-3;
		break;
	}

	return getCord(x+1,size*2,i)+app;
}
int countH(char* a)
{
	if(a[0]==VUOTO) 	 return 0;
	else if(a[1]==VUOTO) return 1;
	else if(a[2]==VUOTO) return 2;
	else 				 return 3;
}
int getCentrRetY(int y, int j, int size){return getCord(y,size,j)+size/2;}
int getIntCar()
{
	int l=0;

	l=getch();
	if(l==224)l=getch();

	return l;
}

int switch_P (int c)
{
	int p=0;

	switch (c)
	{
		case 49:
			p=1;
		break;
		case 50:
			p=2;
		break;
		case 51:
			p=3;
		break;
		case 52:
			p=4;
		break;
		case 53:
			p=5;
		break;
		case 54:
			p=6;
		break;
		case 55:
			p=7;
		break;
		case 56:
			p=8;
		break;
		case 57:
			p=9;
		break;
	}
	return p;
}

int getAltTorre(pedina a)
{
	int i=0;
	
	if(a.color[i]==VUOTO) return 0;

	while (i<=2)
	{
		if(a.color[i+1]==VUOTO)return i+1;
		i++;
	}

	return 3;
}

char getColorTop(pedina a)
{
	int i = getAltTorre(a);
	
	return i==0 ? a.color[i] : a.color[i-1]>='a' && a.color[i-1]<='z' ? a.color[i-1] : a.color[i-1] + 'a'-'A';
}


/***************************************************************************************************************************************************************************************************************/
/*Funzioni  di set*/
/***************************************************************************************************************************************************************************************************************/
void setPCentRet(int x, int y, int i, int j, int size, char* a, int* xr,int* yr)
{
	*xr=getCentrRetX(x,i, size, a);
	*yr=getCentrRetY(y,j, size);
}


/***************************************************************************************************************************************************************************************************************/
/*Funzioni generiche*/
/***************************************************************************************************************************************************************************************************************/
void cls_Buffer(){while (kbhit()) getch();}

void centro(char* a, int rig)
{
	gotoxy((80-strlen(a))/2,rig);
	printf ("%s",a);
}

/***************************************************************************************************************************************************************************************************************/
/*Costruttori*/
/***************************************************************************************************************************************************************************************************************/
pedina Pedina(int x_, int y_, char color_,int promo_)
{
	pedina a;

	a.x=x_;
	a.y=y_;

	a.color[0]=color_;
	a.color[1]=VUOTO;
	a.color[2]=VUOTO;
	a.colorTop=	color_;

	a.promozione=promo_;

	return a;
}


/***************************************************************************************************************************************************************************************************************/
/*Funzioni d'inizializzazzione */
/***************************************************************************************************************************************************************************************************************/
void inizScacchiera(pedina s[][DROW], int opz)
{
	int i=0;
	int j=0;
	int c=0;
	char app;

	for(i=0;i<DROW;i++)/*righe*/
	{
		for(j=0;j<DCOL;j++)/*colonne*/
		{
			if(i!=3 && c%2==0)
			{
				if(i<3) app=opz ? PNERE    : PBIANCHE; /*deciso da opz per avare le bianca verso il destra o verso il sinistra*/
				else 	app=opz ? PBIANCHE : PNERE;	  /*deciso da opz per avare le bianca verso il sinistra o verso il destra*/
			}
			else app=VUOTO;/*vuoto*/

			s[j][i]= Pedina(j,i, app, 0);
			c++;
		}
	}
}

/***************************************************************************************************************************************************************************************************************/
/*Funzioni di controllo*/
/***************************************************************************************************************************************************************************************************************/
int isPNull(pedina a){return a.colorTop==VUOTO;}


/***************************************************************************************************************************************************************************************************************/
/*Funzioni di gioco */
/***************************************************************************************************************************************************************************************************************/
void cntrFine(short int e)
{
/*end = 0 nessuno ha vinto
* end = 1 ha vinto il bianco
* end = 2 ha vinto il nero
* end = 3 stallo
*/	
int x = 90;
int y = 21;

	stmpCornice(x-(e==3 ? 16 : 6),y-1,(e==3 ? 43 : 30),4, " ", COLCORNI+300, 1);
	switch(e)
	{
		case 1: 
			stmpString(x,y,7,"Ha vinto il bianco");
		break;
		case 2: 
			stmpString(x,y,7,"Ha vinto il nero");
		break;
		case 3: 
			stmpString(x-14,y,7,"La partita si e' conclusa con uno stallo");
		break;
	}
	
	stmpString(x-5,y+1,7,"Premere invio per continuare");
	getch();
	
	cls;
}

void Menu ()
{
	menu a;
	int e = 0;
	
	/*OPZIONI DA MOSTRARE AL GIOCATORE PER POTER SCEGLIERE COSA FARE*/
	a.opzioni[0]="1 - Gioca";
	a.opzioni[1]="2 - Esci ";
	a.n_Opz=2;

	while(!e)
	{
		switch(menuCntr(10,a))/*funzione per mostrare il menu*/
		{
			case 0:/*parte il gioco*/
				cntrFine(game_start());
			break;
			case 1:/*esco*/
				e=1;
			break;
		}
	}
}

void actionPromote(pedina sch[][DROW], int x, int y)
{
	int val = getAltTorre(sch[x][y])-1;
	
	sch[x][y].promozione = 1;
	if(sch[x][y].color[val]>='a' && sch[x][y].color[val]<='z')sch[x][y].color[val] -='a'-'A';
}

void promote(pedina sch[][DROW])
{
	int i = 0;
	
	for(i=0; i<DCOL ; i+=2)
	{
		if(sch[i][0].colorTop==PNERE &&  !sch[i][0].promozione)   actionPromote(sch, i, 0);
		if(sch[i][6].colorTop==PBIANCHE && !sch[i][6].promozione) actionPromote(sch, i, 6);
	}
}

short int game_start()
{
	int sX=0, sY=0, cX = 0, cY = 0;/*s ==> spostamento | c ==> conquista*/
	int aX, aY=0;/*variabili di controllo per x e y*/
	short int exit=0;
	char turno=PBIANCHE;
	int opz = 0;
	pedina sch[DCOL][DROW];
    inizScacchiera(sch,opz);
   	stmpString(87, 3, 7, "Turno: ");
	stmpChar(87+7, 3, 7, turno);

	while(exit==0)/*da inserire end(sch)*/
	{
		stmpScacchiera(X,Y, SIZE_, DCOL,DROW, sch);/*stampo la schaccheira*/
		
		do{
			aX=sX;/*salvo il valore precedente delle x*/
			aY=sY;/*salvo il valore precedente delle y*/
			selezione(X,Y, SIZE_, DCOL,DROW, &sX,&sY,0);/*faccio scegliere al giocatore la pedina da spostare*/
		}while((sX==aX && sY==aY) || sch[sX][sY].colorTop != turno);/*controllo se e stato premuto esc ==> vedi selezione()*/
		
		/*avvio la funzione di sposta che mi mostra le possibili mosse*/
		cX = 0;
		cY = 0;
		if(spostamento(sX,sY, SIZE_, &cX,&cY))
		{
			stmpString(80, 5, 7, "\t\t\t\t");/*cancello il testo precedente*/
			stmpString(80, 6, 7, "\t\t\t\t");/*cancello il testo precedente*/
			if(sposta(sch, sX, sY, cX, cY))
			{
				/*stmpString(80, 5, 7, "Spostamento avvenuto");*/
				promote(sch);
				turno = switchTurno(turno);
				exit  = end(sch, turno);
				
				stmpString(87, 3, 7, "\t\t\t\t");/*cancello il testo precedente*/
				stmpString(87, 3, 7, "Turno: ");
				stmpChar(87+7, 3, 7, turno);
			}
			else stmpString(80, 5, 7, "Impossibile spostare la pedina");
		}
	}
	stmpScacchiera(X,Y, SIZE_, DCOL,DROW, sch);
	
	return exit;
}

int sposta(pedina a[][DROW], int xS, int yS, int xTo, int yTo) {
	
	pedina dest = a[xTo][yTo]; /* cella di destinazione*/
	pedina origin = a[xS][yS]; /* cella di origine*/
	
	if((origin.colorTop==PNERE && yTo>yS && origin.promozione == 0) || (origin.colorTop==PBIANCHE && yTo<yS && origin.promozione == 0)){
		/*La cella sta compiendo un movimento all'indietro per il quale deve essere promossa*/
		stmpString(89, 6, 7, "Non promossa");
		return 0;
	}else if(dest.colorTop==VUOTO) {
		/*La cella di destinazione e' vuota: sposto la pedine in quella posizione scambiandola con altra (swap)*/
		a[xTo][yTo] = origin;
		a[xS][yS] = dest;
		return 1;
	}else if(dest.colorTop != origin.colorTop){
			/*La cella di destinazione non e' vuota e il top color NON e' lo stesso della pedina da spostare: chiamo conquista*/
			return conquista(a, xS, yS, xTo, yTo);
	}else if (dest.colorTop == origin.colorTop){
			/*La cella di destinazione non e' vuota e il top color e' lo stesso della pedina da spostare: impossibile spostare*/
			return 0;
	}
	
	return 0;
}


int conquista(pedina a[][DROW], int xS, int yS, int xTo, int yTo){
	pedina r;
	int hTo=getAltTorre(a[xTo][yTo])-1, hS=getAltTorre(a[xS][yS]);
	
	/*
	numeri valori dove b deve arrivare 
	
	| 4 |   |   |   | 1 | 
	------------------------
	|   | n |   | n |   |
	------------------------
	|   |   | b |   |   |
	------------------------
	|   | n |   | n |   |
	------------------------
	| 3 |   |   |   | 2 | 
	*/
	
	/*creo la nuova pedina da mettere nelle posizoni dopo la pedina conquistata*/
	if(xS+1==xTo && yS-1==yTo)		r = Pedina(xTo+1, yTo-1, (a[xTo][yTo].promozione ? a[xTo][yTo].colorTop - ('a' - 'A') : a[xTo][yTo].colorTop), a[xS][yS].promozione);/*1*/ 
	else if(xS+1==xTo && yS+1==yTo) r = Pedina(xTo+1, yTo+1, (a[xTo][yTo].promozione ? a[xTo][yTo].colorTop - ('a' - 'A') : a[xTo][yTo].colorTop), a[xS][yS].promozione);/*2*/
	else if(xS-1==xTo && yS+1==yTo) r = Pedina(xTo-1, yTo+1, (a[xTo][yTo].promozione ? a[xTo][yTo].colorTop - ('a' - 'A') : a[xTo][yTo].colorTop), a[xS][yS].promozione);/*3*/
	else if(xS-1==xTo && yS-1==yTo) r = Pedina(xTo-1, yTo-1, (a[xTo][yTo].promozione ? a[xTo][yTo].colorTop - ('a' - 'A') : a[xTo][yTo].colorTop), a[xS][yS].promozione);/*4*/
	
	if(r.x>=0 && r.x<=6 && r.y>=0 && r.y<=6 && a[r.x][r.y].colorTop==VUOTO)
	{
		if(hS==3)a[r.x][r.y] = a[xS][yS];
		else 
		{
			r.color[1]= a[xS][yS].color[0];/*copio la torre che c'e' al interno della pedina spostata sopra la pedina conquistata*/
			r.color[2]= a[xS][yS].color[1];
			r.colorTop = a[xS][yS].colorTop;/*modifico il top della nuova pedina a il valore della pedina spostata*/
		
			a[r.x][r.y] = r;/*carico dentro la posizione designata la pedina appena creata*/	 
		}
		
		
		a[xTo][yTo].color[hTo] = VUOTO;						/*accedo alla pedina dalla quale prendo la pedina piu in alto e la cancello*/
		a[xTo][yTo].colorTop   = getColorTop(a[xTo][yTo]); /*modifico il color top della pedina da dove e stato sottratto il top*/
		if(hTo == 0) a[xTo][yTo].promozione = 0;
		else 	     a[xTo][yTo].promozione = a[xTo][yTo].color[hTo-1]>='A' && a[xTo][yTo].color[hTo-1]<='Z';/*? 1 : 0;*/
		
		
		a[xS][yS].color[0] = a[xS][yS].color[1] = a[xS][yS].color[2]= a[xS][yS].colorTop = VUOTO; /*cancello la pedina che ho spostato*/
		a[xS][yS].promozione = 0;														  		 /*cella che contiene la pedina spostata diventa vuota*/
		
		
		return 1;/*ritorno 1 per dire che l'operazione ha avuto buon fine*/
	}
	else return 0;
}


/*end = 0 nessuno ha vinto
* end = 1 ha vinto il bianco
* end = 2 ha vinto il nero
* end = 3 stallo
*/

short int end(pedina sch[][DROW], char turno){
    
    int black_coordinates[45];
    
    int white_coordinates[45];
    
    short int i, j, black_counter, white_counter, bc, wc, black_moves_found, white_moves_found;
    
    black_moves_found = 0;
    white_moves_found = 0;
    white_counter = 0;
    black_counter = 0;
    bc = 0;
    wc = 0;
    
    for(i = 0; i < 7; i++){
    
        for(j = 0; j < 7; j++){
    
                if(!isPNull(sch[j][i])) {
                    
                    if(sch[j][i].colorTop == PNERE){
                        black_counter++;
                        black_coordinates[bc] = j;
                        bc++;
                        black_coordinates[bc] = i;
                        bc++;
                    }
                    
                    else if(sch[j][i].colorTop == PBIANCHE){
                        white_counter++;
                        white_coordinates[wc] = j;
                        wc++;
                        white_coordinates[wc] = i;
                        wc++;
                    }
                }
            
        }
    }
    /*If no pawn has been eaten return 0*/
    if (white_counter == 11 && black_counter == 11)return 0;
    
    else if (white_counter == 0 && black_counter == 0) return 3;
    
    else if (white_counter == 0)return 2;
    
    else if (black_counter == 0)return 1;
    
		else {

			i = 0;

			while (i < bc && !black_moves_found){
			/*Reference is: matrix[black_coordinates[i]][black_coordinates[i+1]]*/

				if(
					there_are_moves_available(
						sch,
						black_coordinates[i], /*x*/
						black_coordinates[i + 1], /*y*/
						PBIANCHE
					) == 1
				) black_moves_found = 1;

				i = i + 2;

			}

			i = 0;
			while (i < wc && !white_moves_found){
			/*Reference is: matrix[white_coordinates[i]][white_coordinates[i+1]]*/

				if(
					there_are_moves_available(
						sch,
						white_coordinates[i],
						white_coordinates[i + 1],
						PNERE
					) == 1
				) white_moves_found = 1;

				i = i + 2;
			}	
		}
    
    if(!white_moves_found && !black_moves_found) return 3;
    
	else if(!black_moves_found && turno == PNERE) return 3;

	else if(!white_moves_found && turno == PBIANCHE) return 3;

	else if (!white_moves_found) return 2;

	else if(!black_moves_found) return 1;
		
		/*else*/
		return 0;
        

}

/**********************************************************************************/
/* The function receives the matrix, the coordinates and the enemy's color as input
*  and returns 1 if a move is available, 0 otherwise
*/

short int there_are_moves_available(pedina sch[][DROW], int x, int y, char enemy_s_color){
	

	if(x == 0 && y == 0){
		if(
			!move_bottom_right(sch, x, y, enemy_s_color) &&
			!eat_bottom_right(sch, x, y, enemy_s_color)
		) return 0;
		return 1;
	}
	else if(x == 0 && y == 6){
		if(
			!move_top_right(sch, x, y, enemy_s_color) && 
			!eat_top_right(sch, x, y, enemy_s_color)
		) return 0;
		return 1;
	}
	else if(x == 6 && y == 0){
		if(
			!move_bottom_left(sch, x, y, enemy_s_color) &&
			!eat_bottom_left(sch, x, y, enemy_s_color)
		) return 0;
		return 1;
	}
	else if(x == 6 && y == 6){
		if(
			!move_top_left(sch, x, y, enemy_s_color) &&
			!eat_top_left(sch, x, y, enemy_s_color)
		) return 0;
		return 1;
	}
	else if(x == 0){
		if(
			!eat_top_right(sch, x, y, enemy_s_color) &&
			!eat_bottom_right(sch, x, y, enemy_s_color) &&
			!move_bottom_right(sch, x, y, enemy_s_color) &&
			!move_top_right(sch, x, y, enemy_s_color)
		) return 0;
		return 1;
	}
	else if(x == 6){
		if(
			!eat_top_left(sch, x, y, enemy_s_color) &&
			!eat_bottom_left(sch, x, y, enemy_s_color) &&
			!move_bottom_left(sch, x, y, enemy_s_color) &&
			!move_top_left(sch, x, y, enemy_s_color)
		) return 0;
		return 1;
	}
	else if(y == 0){
		if(
			!eat_bottom_left(sch, x, y, enemy_s_color) &&
			!eat_bottom_right(sch, x, y, enemy_s_color) &&
			!move_bottom_left(sch, x, y, enemy_s_color) &&
			!move_bottom_right(sch, x, y, enemy_s_color)
		) return 0;
		return 1;
	}
	else if(y == 6){
		if(
			!eat_top_left(sch, x, y, enemy_s_color) &&
			!eat_top_right(sch, x, y, enemy_s_color) &&
			!move_top_left(sch, x, y, enemy_s_color) &&
			!move_top_right(sch, x, y, enemy_s_color)
		) return 0;
		return 1;
	}
	else if(x == 1 && y == 1){
		if(
			!eat_bottom_right(sch, x, y, enemy_s_color) &&
			!move_in_all_directions(sch, x, y, enemy_s_color)
		) return 0;
		return 1;
	}
	else if(x == 1 && y == 5){
		if(
			!eat_top_right(sch, x, y, enemy_s_color) &&
			!move_in_all_directions(sch, x, y, enemy_s_color)
		) return 0;
		return 1;
	}
	else if(x == 5 && y == 5){
		if(
			!eat_top_left(sch, x, y, enemy_s_color) && 
			!move_in_all_directions(sch, x, y, enemy_s_color)
		) return 0;
		return 1;
	}
	else if(x == 5 && y == 1){
		if(
			!eat_bottom_left(sch, x, y, enemy_s_color) &&
			!move_in_all_directions(sch, x, y, enemy_s_color)
		) return 0;
		return 1;
	}
	else if(x == 1){
		if(
			!eat_bottom_right(sch, x, y, enemy_s_color) &&
			!eat_top_right(sch, x, y, enemy_s_color) &&
			!move_in_all_directions(sch, x, y, enemy_s_color)
		) return 0;
		return 1;
	}
	else if(x == 5){
		if(
			!eat_bottom_left(sch, x, y, enemy_s_color) &&
			!eat_top_left(sch, x, y, enemy_s_color) &&
			!move_in_all_directions(sch, x, y, enemy_s_color)
		) return 0;
		return 1;
	}
	else if(y == 1){
		if(
			!eat_bottom_right(sch, x, y, enemy_s_color) &&
			!eat_bottom_left(sch, x, y, enemy_s_color) &&
			!move_in_all_directions(sch, x, y, enemy_s_color)
		) return 0;
		return 1;
	}
	else if(y == 5){
		if(
			!eat_top_left(sch, x, y, enemy_s_color) &&
			!eat_top_right(sch, x, y, enemy_s_color) &&
			!move_in_all_directions(sch, x, y, enemy_s_color)
		) return 0;
		return 1;
	}
	else{
		if(
			!eat_bottom_right(sch, x, y, enemy_s_color) &&
			!eat_bottom_left(sch, x, y, enemy_s_color) &&
			!eat_top_left(sch, x, y, enemy_s_color) &&
			!eat_top_right(sch, x, y, enemy_s_color) &&
			!move_in_all_directions(sch, x, y, enemy_s_color)
		) return 0;
		return 1;
	}

}


/* you can eat top only if you're 'n'(enemy_s_color = 'b') or if you're promoted*/
short int eat_top_left(pedina sch[][DROW], int x, int y, char enemy_s_color){

	if(enemy_s_color == 'b' || sch[x][y].promozione == 1){
		if(
			isPNull(sch[x - 2][y - 2])
			&&
			sch[x - 1][y - 1].colorTop == enemy_s_color
		)
			return 1;
	}
	return 0;

}

/*you can eat top only if you're 'n' (enemy_s_color == 'b') or if you're promoted*/
short int eat_top_right(pedina sch[][DROW], int x, int y, char enemy_s_color){
	
	if(enemy_s_color == 'b' || sch[x][y].promozione == 1){
		if(
			isPNull(sch[x + 2][y - 2])
			&&
			sch[x + 1][y - 1].colorTop == enemy_s_color
		)
			return 1;
	}

	return 0;
}

/*you can eat bottom only if you're 'b' (enemy_s_color == 'n') or if you're promoted*/
short int eat_bottom_right(pedina sch[][DROW], int x, int y, char enemy_s_color){
	
	if(enemy_s_color == 'n' || sch[x][y].promozione == 1){
		if(
			isPNull(sch[x + 2][y + 2])
			&&
			sch[x + 1][y + 1].colorTop == enemy_s_color
		)
			return 1;
	}
	return 0;
}

/*you can only eat bottom if you're 'b' (enemy_s_color == 'n') or if you're promoted*/
short int eat_bottom_left(pedina sch[][DROW], int x, int y, char enemy_s_color){
	
	if(enemy_s_color == 'n' || sch[x][y].promozione == 1){
		if(
			isPNull(sch[x - 2][y + 2])
			&&
			sch[x - 1][y + 1].colorTop == enemy_s_color
		)
			return 1;
	}
	return 0;
}

short int move_bottom_left(pedina sch[][DROW], int x, int y, char enemy_s_color){
	
	if(enemy_s_color == 'n' || sch[x][y].promozione == 1){
		if(
			isPNull(sch[x - 1][y + 1])
		)
			return 1;
	}
	return 0;
}

short int move_bottom_right(pedina sch[][DROW], int x, int y, char enemy_s_color){
	
	if(enemy_s_color == 'n' || sch[x][y].promozione == 1){
		if(
			isPNull(sch[x + 1][y + 1])
		)
			return 1;
	}
	return 0;
}

short int move_top_right(pedina sch[][DROW], int x, int y, char enemy_s_color){
	
	if(enemy_s_color == 'b' || sch[x][y].promozione == 1){
		if(
			isPNull(sch[x + 1][y - 1])
		)
			return 1;
	}

	return 0;
}

short int move_top_left(pedina sch[][DROW], int x, int y, char enemy_s_color){

	if(enemy_s_color == 'b' || sch[x][y].promozione == 1){
		if(
			isPNull(sch[x - 1][y - 1])
		)
			return 1;
	}
	return 0;

}

short int move_in_all_directions(pedina sch[][DROW], int x, int y, char enemy_s_color){
	if(
		move_bottom_left(sch, x, y, enemy_s_color) ||
		move_bottom_right(sch, x, y, enemy_s_color) ||
		move_top_left(sch, x, y, enemy_s_color) ||
		move_top_right(sch, x, y, enemy_s_color)
	) return 1;
	return 0;
}

char switchTurno (char turno){
	if(turno == PNERE)
		return PBIANCHE;
	else if(turno == PBIANCHE)
		return PNERE;
	return turno;
	
}
