
/* 
 * File:   main.c
 * Author: Lukas Fischer
 * GitHub: https://github.com/Jinthebandit/TicTacToe-C.git
 * 
 * REQUIREMENTS HW-01:
 * Erstellen eines Tic Tac Toe Spiels
 * Mit einem Spielfeld von 3x3 Zellen
 * Das Spielfeld wird mit printf() auf stdout ausgegeben
 * OPTIONAL: Gewinner wird ausgegeben
 * OPTIONAL: Nur zulässige Züge werden erlaubt
 * 
 * REQUIREMENTS HW-02
 * Variablen für Spielfeld global definieren.
 * Ausgabe des Spielfelds in seperate Funktion einbetten.
 * Zulaessigkeit der Spielzuege ueberpruefen.
 * 
 * 
 * Created on 18. September 2019, 11:21
 */

// Benötigte Bibliotheken importieren
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <string.h>

// Makro Definition (Konstanten) für die Spieler erstellen
#define Player_01 1
#define Player_02 2

// forward declaration of functions
void recursivePlays(int r);
bool checkWinner(int p);
void executeMove(int p);
void showBoard(void);
int randomizePlayer(void);
bool checkBoardFull(void);
int checkMoveValid(int a, int b);


/*
 *  Spielfeld in ein 3x3 Array einteilen und auf 0 setzen.
 *  Spielfeld Layout:
 *  [0][0] [0][1] [0][2]
 *  [1][0] [1][1] [1][2]
 *  [2][0] [2][1] [2][2]
 */
int board[3][3] = { 0 };

/*
 * Hier wird das Spiel initiiert.
 */
int main() {    
    /* Die Werte fuer Spieler 1 & 2 anzeigen. */
    printf("Player 1: %d",Player_01);
    printf("\nPlayer 2: %d\n\n",Player_02);
    
    /* Leeres Board einmal anzeigen. */
    showBoard();
    
    /* Rekursive Funktion solange ausfuehren, bis Spiel beendet. */
    recursivePlays(randomizePlayer());
    
    return 0;
}

/*
 * Anzeige des aktuellen Spielbretts.
 * Die Werte werden aus dem Array ausgelesen.
 */
void showBoard(void) {    
    printf("Spielfeld:\n");
    printf("\n             %d | %d | %d  ", board[0][0], board[0][1], board[0][2]);
    printf("\n            ---+---+---");
    printf("\n             %d | %d | %d  ", board[1][0], board[1][1], board[1][2]);
    printf("\n            ---+---+---");
    printf("\n             %d | %d | %d  ", board[2][0], board[2][1], board[2][2]);
    printf("\n\n");
}

/*
 * Pseudo-zufaellig einen Spieler fuer den ersten Zug waehlen.
 * Wenn die zufaellige Zahl gerade ist -> Spieler 1, sonst Spieler 2 
 */
int randomizePlayer(void) {
    /* Pseudo-Zufallszahl generieren */
    srand(time(NULL));
    int startPlayer = rand();
    
    /* Wenn Zufallszahl gerade -> Spieler 1, sonst Spieler 2 */    
    if (startPlayer % 2 == 0){
        startPlayer = Player_01;
    } else {
        startPlayer = Player_02;
    }
    
    return startPlayer;
}

/*
 * Es wird ueberprueft ob noch Zuege gemacht werden koennen oder ob es einen Sieger gibt.
 * Funktion ruft sich selbst so oft neu auf, bis das Spielbrett voll ist, oder ein Sieger feststeht.
 */
void recursivePlays(int previousPlayer) {  
    /* Spieler abwechseln */
    int activePlayer;
    switch(previousPlayer) {
        case 1: activePlayer = Player_02; break;
        case 2: activePlayer = Player_01; break;
    }
    
    /* Auf Wincondition und verbliebene Zuege ueberpruefen */
    if (checkWinner(previousPlayer)) {
        printf("Der Gewinner ist: Spieler %i", previousPlayer);
    } else if (checkBoardFull()){
        showBoard();
        printf("\nSpiel beendet.\n\n"
                "Es gibt keinen Sieger.");
    } else {
        executeMove(activePlayer);
        showBoard();
        recursivePlays(activePlayer);
    }
}

/*
 * Ueberpruefen, ob der Zug des Spielers zum Sieg gefuehrt hat.
 * Zuerst werden die Reihen nacheinander ueberprueft.
 * Danach die Spalten.
 * Danach die Diagonalen.
 * Gibt true oder false zurueck.
 */
bool checkWinner(int activePlayer) {
    bool isWinner = false;
    
    int i;
    for (i=0; i<3; i++) {
        if (board[i][0] == activePlayer && board[i][1] == activePlayer && board[i][2] == activePlayer) {          // Reihen ueberpruefen
            isWinner = true;
            break;
        } else if (board[0][i] == activePlayer && board[1][i] == activePlayer && board[2][i] == activePlayer) {   // Spalten ueberpruefen
            isWinner = true;
            break;
        } else if (board[0][0] == activePlayer && board[1][1] == activePlayer && board[2][2] == activePlayer) {   // Diagonale1 ueberpruefen
            isWinner = true;
            break;
        } else if (board[0][3] == activePlayer && board[1][1] == activePlayer && board[2][0] == activePlayer) {   // Diagonale2 ueberpruefen
            isWinner = true;
            break;
        }
    }    
    
    return isWinner;
}

/*
 * Ueberpruefen, ob noch Zuege gemacht werden koennen oder ob das Spielbrett voll ist.
 * Gibt true oder false zurueck.
 */
bool checkBoardFull(void) {
    bool boardFull;
    
    if(board[0][0] && board[0][1] && board[0][2] 
        && board[1][0] && board[1][1] && board[1][2]
        && board[2][0] && board[2][1] && board[2][2] != 0) {
        boardFull = true;
    } else {
        boardFull = false;
    }
    
    return boardFull;
}

/*
 * Es wird ueberprueft ob der Zug zulaessig ist -> ob das Feld noch frei ist.
 * Gibt 0,1 oder 2 zurueck.
 */
int checkMoveValid(int row, int col) {
    int validCode = 2;
    
    /* 
     * validCode = 0 -> Eingabe fehlerhaft
     * validCode = 1 -> Feld bereits besetzt
     * validCode = 2 -> Alles in Ordnung
     */
    if ((col != 0 && col != Player_01 && col != Player_02) || (row != 0 && row != Player_01 && row != Player_02)){
        validCode = 0;
    } else if (board[row][col] != 0) {
        validCode = 1;
    }
    
    return validCode;
}

/*
 * Der jeweilige Spieler p wird aufgerufen seinen Zug zu machen.
 * Es wird ueberprueft ob der Zug zulaessig ist.
 * Wenn der Zug zulaessig ist, wird der Zug ausgeführt.
 * Der Wert des jeweiligen Spielers wird im Array auf der gesetzten Position geaendert.
 */
void executeMove(int activePlayer) {
    /* Eingabe durch Spieler anfordern. "Reihe,Spalte" */
    int col, row;
    char input[4];
    
    printf("Spieler %i Machen Sie ihren Zug (Reihe,Spalte): ", activePlayer);
    if (fgets(input, 40, stdin)) {
        input[strcspn(input, "\n")+1] = 0;
        sscanf(input, "%i, %i", &row, &col);
    }
    
    col -= 1;
    row -= 1;
    
    /* Gueltigkeit des Zugs ueberpruefen und wenn gueltig, ausfuehren. */
    if (checkMoveValid(row, col) == 0){
        printf("Ungueltiger Zug.\n");
        executeMove(activePlayer);
    } else {
        if (checkMoveValid(row, col) == 1) {
            printf("Position %i x %i ist bereits voll.\n"
                    "Bitte machen sie einen anderen Zug.\n", row, col);
            executeMove(activePlayer);
        } else {
            board[row][col] = activePlayer;
        }
    }
}
