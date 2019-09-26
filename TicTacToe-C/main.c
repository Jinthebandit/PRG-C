
/* 
 * File:   main.c
 * Author: Lukas Fischer
 * 
 * Requirements:
 * Erstellen eines Tic Tac Toe Spiels
 * Mit einem Spielfeld von 3x3 Zellen
 * Das Spielfeld wird mit printf() auf stdout ausgegeben
 * OPTIONAL: Gewinner wird ausgegeben
 * OPTIONAL: Nur zulässige Züge werden erlaubt
 * 
 * History:
 * V1 -> alles in main()
 * V2 -> Funktionen zug() und board() erstellt
 * V3 -> Rekursive Funktion erstellt
 * V4 -> Funktion winner() fuer winconditions implementiert
 * V5 -> forward declaration der Funktionen
 * V6 -> is_valid() Funktion implementiert
 * V7 -> refakturiert
 * V8 -> random_player() Funktion implementiert
 * 
 * Created on 18. September 2019, 11:21
 */

// Benötigte Bibliotheken importieren
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

// Makro Definition (Konstanten) für die Spieler erstellen
#define Player_01 1
#define Player_02 2

// forward declaration of functions
int recursive(int r);
int winner(int p);
int zug(int p);
int board(void);
int random_player(void);
int is_full(void);
int is_valid(int a, int b);


/*
 *  Spielfeld in ein 3x3 Array einteilen und auf 0 setzen.
 *  Spielfeld Layout:
 *  [0][0] [0][1] [0][2]
 *  [1][0] [1][1] [1][2]
 *  [2][0] [2][1] [2][2]
 */
int rows[3][3] = { 0 };

/*
 * Funktion main()
 * Hier wird das Spiel initiiert.
 */
int main() {    
    /* Die Werte fuer Spieler 1 & 2 anzeigen. */
    printf("Player 1: %d",Player_01);
    printf("\nPlayer 2: %d\n\n",Player_02);
    
    /* Leeres Board einmal anzeigen. */
    board();
    
    /* Rekursive Funktion solange ausfuehren, bis Spiel beendet. */
    recursive(random_player());
    
    return 0;
}

/*
 * Funktion board()
 * Anzeige des aktuellen Spielbretts.
 * Die Werte werden aus dem Array ausgelesen.
 */
int board(void) {     
    printf("Spielfeld:\n");
    printf("\n   %d | %d | %d  ", rows[0][0], rows[0][1], rows[0][2]);
    printf("\n  ---+---+---");
    printf("\n   %d | %d | %d  ", rows[1][0], rows[1][1], rows[1][2]);
    printf("\n  ---+---+---");
    printf("\n   %d | %d | %d  ", rows[2][0], rows[2][1], rows[2][2]);
    printf("\n\n");
}

/*
 * Funktion random_player()
 * Pseudo-zufaellig einen Spieler fuer den ersten Zug waehlen.
 * Wenn die zufaellige Zahl gerade ist -> Spieler 1, sonst Spieler 2 
 */
int random_player(void) {
    /* Pseudo-Zufallszahl generieren */
    srand(time(NULL));
    int player = rand();
    
    /* Wenn Zufallszahl gerade -> Spieler 1, sonst Spieler 2 */    
    if (player % 2 == 0){
        player = Player_01;
    } else {
        player = Player_02;
    }
    
    return player;
}

/*
 * Funktion recursive()
 * Es wird ueberprueft ob noch Zuege gemacht werden koennen oder ob es einen Sieger gibt.
 * Funktion ruft sich selbst so oft neu auf, bis das Spielbrett voll ist, oder ein Sieger feststeht.
 */
int recursive(int r) {  
    /* Spieler abwechseln */
    int p;
    switch(r) {
        case 1: p = Player_02; break;
        case 2: p = Player_01; break;
    }
    
    /* Auf Wincondition und verbliebene Zuege ueberpruefen */
    if (winner(r)) {
        printf("Der Gewinner ist: Spieler %i", r);
    } else if (is_full()){
        board();
        printf("\nSpiel beendet.\n\nEs gibt keinen Sieger.");
    } else {
        zug(p);
        board();
        recursive(p);
    }
}

/*
 * Funktion winner()
 * Ueberpruefen, ob der Zug des Spielers zum Sieg gefuehrt hat.
 * Zuerst werden die Reihen nacheinander ueberprueft.
 * Danach die Spalten.
 * Danach die Diagonalen.
 * Gibt true oder false zurueck.
 */
int winner(int p) {
    int i;
    bool w = false;
    for (i=0; i<3; i++) {
        if (rows[i][0] == p && rows[i][1] == p && rows[i][2] == p) {          // Reihen ueberpruefen
            w = true;
            break;
        } else if (rows[0][i] == p && rows[1][i] == p && rows[2][i] == p) {   // Spalten ueberpruefen
            w = true;
            break;
        } else if (rows[0][0] == p && rows[1][1] == p && rows[2][2] == p) {   // Diagonale1 ueberpruefen
            w = true;
            break;
        } else if (rows[0][3] == p && rows[1][1] == p && rows[2][0] == p) {   // Diagonale2 ueberpruefen
            w = true;
            break;
        }
    }    
    
    return w;
}

/*
 * Funktion is_full()
 * Ueberpruefen, ob noch Zuege gemacht werden koennen oder ob das Spielbrett voll ist.
 * Gibt true oder false zurueck.
 */
int is_full(void) {
    bool full;
    if(rows[0][0] && rows[0][1] && rows[0][2] 
        && rows[1][0] && rows[1][1] && rows[1][2]
        && rows[2][0] && rows[2][1] && rows[2][2] != 0) {
        full = true;
    } else {
        full = false;
    }
    
    return full;
}

/*
 * Funktion is_valid()
 * Es wird ueberprueft ob der Zug zulaessig ist -> ob das Feld noch frei ist.
 * Gibt 0,1 oder 2 zurueck.
 */
int is_valid(int a, int b) {
    int valid = 2;
    if ((a != 0 && a != Player_01 && a != Player_02) || (b != 0 && b != Player_01 && b != Player_02)){ // Wenn Eingabe fuer Reihe und Spalte weder 0,1 oder 2 ist
        valid = 0;
    } else if (rows[b][a] != 0) { // Wenn die Eingegebene Reihe und Spalte einen Wert enthaelt der nicht 0 ist -> voll
        valid = 1;
    }
    
    return valid;
}

/*
 * Funktion Zug()
 * Der jeweilige Spieler p wird aufgerufen seinen Zug zu machen.
 * Es wird ueberprueft ob der Zug zulaessig ist.
 * Wenn der Zug zulaessig ist, wird der Zug ausgeführt.
 * Der Wert des jeweiligen Spielers wird im Array auf der gesetzten Position geaendert.
 */
int zug(int p) {
    /* Eingabe durch Spieler anfordern. */
    int a, b;
    printf("Spieler %i Machen Sie ihren Zug (Reihe,Spalte): ", p);
    scanf("%i,%i", &b, &a);  // Eingabe von Reihe (b) und Spalte (a) durch Spieler
    a -= 1;
    b -= 1;
    
    /* Gueltigkeit des Zugs ueberpruefen und wenn gueltig, ausfuehren. */
    if (is_valid(a,b) == 0){
        printf("Ungueltiger Zug.\n");
        zug(p);
    } else {
        if (is_valid(a,b) == 1) {
            printf("Position %i x %i ist bereits voll.\nBitte machen sie einen anderen Zug.\n", b, a);
            zug(p);
        } else {
            rows[b][a] = p;
        }
    }
}