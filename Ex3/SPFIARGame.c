#include<stdio.h>
#include <stdlib.h>
#include "SPFIARGame.h"
#include "SPArrayList.h"

SPFiarGame* spFiarGameCreate(int historySize){  //create new game
    setvbuf (stdout, NULL, _IONBF, 0);
    if(historySize<=0) return NULL;

    SPFiarGame* game = (SPFiarGame*)malloc(sizeof(SPFiarGame)); //malloc and check
    if (game==NULL){
        printf("Error: malloc has failed");
        return NULL;
    }
    game->currentPlayer = SP_FIAR_GAME_PLAYER_1_SYMBOL;     //fill values
    for(int i = 0; i <SP_FIAR_GAME_N_COLUMNS ; i++ ){
        game->tops[i] = 0;
    }
    for (int i = 0; i <SP_FIAR_GAME_N_ROWS ; i++ ){
        for (int j = 0; j <SP_FIAR_GAME_N_COLUMNS ; j++ ){
            game->gameBoard[i][j] = SP_FIAR_GAME_EMPTY_ENTRY;
        }
    }

    game->moves = spArrayListCreate(historySize); //doubled because each move player undoes = his&computer
    if (game->moves == NULL) return NULL;

    game->histSize = historySize;
    game->undoCnt = 0;
    game->simulate = false;

    return game;
}

SPFiarGame* spFiarGameCopy(SPFiarGame* src){  //return copy of src game
    if (src == NULL) return NULL;

    SPFiarGame* copy = (SPFiarGame*)malloc(sizeof(SPFiarGame)); //malloc and check
    if (copy==NULL){
        printf("Error: malloc has failed");
        return NULL;
    }

    copy->currentPlayer = src->currentPlayer;     //fill values
    for(int i = 0; i <SP_FIAR_GAME_N_COLUMNS ; i++ ){
        copy->tops[i] = src->tops[i];
    }
    for (int i = 0; i <SP_FIAR_GAME_N_ROWS ; i++ ){
        for (int j = 0; j <SP_FIAR_GAME_N_COLUMNS ; j++ ){
            copy->gameBoard[i][j] = src->gameBoard[i][j];
        }
    }

    copy->moves = spArrayListCopy(src->moves);
    if (copy->moves == NULL) return NULL;

    copy->histSize = src->histSize;
    copy->undoCnt = src->undoCnt;

    return copy;
}

void spFiarGameDestroy(SPFiarGame* src){    //free res from src game
    if (src == NULL) return;
    spArrayListDestroy(src->moves);
    free(src);
    return;
}

SP_FIAR_GAME_MESSAGE spFiarGameSetMove(SPFiarGame* src, int col){   //move - add correct disk in game src to col
    if(src == NULL || col <0 || col>=SP_FIAR_GAME_N_COLUMNS) return SP_FIAR_GAME_INVALID_ARGUMENT; //illegal move
    else if (src->tops[col] >= SP_FIAR_GAME_N_ROWS) return SP_FIAR_GAME_INVALID_MOVE;   //col is full

    char player = src->currentPlayer;
    if (player == SP_FIAR_GAME_PLAYER_1_SYMBOL) {
        src->gameBoard[src->tops[col]][col] = SP_FIAR_GAME_PLAYER_1_SYMBOL;   //add correct symbol to game board
        src->currentPlayer = SP_FIAR_GAME_PLAYER_2_SYMBOL;
    }
    else if (player == SP_FIAR_GAME_PLAYER_2_SYMBOL) {
        src->gameBoard[src->tops[col]][col] = SP_FIAR_GAME_PLAYER_2_SYMBOL;
        if (src->simulate==false) printf("Computer move: add disc to column %d\n",col +1);
        src->currentPlayer = SP_FIAR_GAME_PLAYER_1_SYMBOL;
    }
    if(spArrayListIsFull(src->moves)) spArrayListRemoveFirst(src->moves); //make room
    spArrayListAddLast(src->moves,col); //update stats
    src->tops[col]++;
    return SP_FIAR_GAME_SUCCESS;
}

bool spFiarGameIsValidMove(SPFiarGame* src, int col){ //Checks if a disk can be put in the specified column.
    if(src == NULL || col <0 || col>=SP_FIAR_GAME_N_COLUMNS ||src->tops[col] >= SP_FIAR_GAME_N_ROWS) return false;
    return true;
}

SP_FIAR_GAME_MESSAGE spFiarGameUndoPrevMove(SPFiarGame* src){
    if (src == NULL) return SP_FIAR_GAME_INVALID_ARGUMENT;
    if (src->undoCnt >= src->histSize) return SP_FIAR_GAME_NO_HISTORY;

    if (spArrayListIsEmpty(src->moves)) return SP_FIAR_GAME_NO_HISTORY;

    int col = spArrayListGetLast(src->moves);       //edit game state
    spArrayListRemoveLast(src->moves);
    src->gameBoard[src->tops[col]-1][col] = SP_FIAR_GAME_EMPTY_ENTRY;
    (src->tops[col])--;
    changeTurn(src);

    if ((src->currentPlayer == SP_FIAR_GAME_PLAYER_2_SYMBOL)&& (src->simulate==false)){
        printf("Remove disc: remove computer\'s disc at column %d\n", col +1);

    }
    else if ((src->currentPlayer == SP_FIAR_GAME_PLAYER_1_SYMBOL)&& (src->simulate==false)){
        printf("Remove disc: remove user\'s disc at column %d\n",  col +1);
        src->undoCnt++;
    }
    return SP_FIAR_GAME_SUCCESS;
}

SP_FIAR_GAME_MESSAGE spFiarGamePrintBoard(SPFiarGame* src){ //print src board
    if (src == NULL) return SP_FIAR_GAME_INVALID_ARGUMENT;

    for (int i =SP_FIAR_GAME_N_ROWS -1 ; i>=0 ; i-- ){
        printf("%c ",SP_FIAR_GAME_STRAIGHT_SYMBOL);
        for (int j = 0 ; j < SP_FIAR_GAME_N_COLUMNS ; j++){
            printf("%c ", src->gameBoard[i][j]);
        }
        printf("%c\n",SP_FIAR_GAME_STRAIGHT_SYMBOL);
    }
    printf("-----------------\n");
    printf("  1 2 3 4 5 6 7  \n");
    return SP_FIAR_GAME_SUCCESS;
}

char spFiarGameGetCurrentPlayer(SPFiarGame* src){// Returns the current player of the specified game.
    if (src==NULL) return SP_FIAR_GAME_EMPTY_ENTRY;
    else if (src->currentPlayer == SP_FIAR_GAME_PLAYER_1_SYMBOL) return SP_FIAR_GAME_PLAYER_1_SYMBOL;
    else if (src->currentPlayer == SP_FIAR_GAME_PLAYER_2_SYMBOL) return SP_FIAR_GAME_PLAYER_2_SYMBOL;
    return SP_FIAR_GAME_EMPTY_ENTRY;
}

#define OFFSET 3
char spFiarCheckWinner(SPFiarGame* src){//report winner/tie/none
    if (src == NULL) return SP_FIAR_GAME_NULL_CHAR;

    char (*board)[SP_FIAR_GAME_N_COLUMNS] = src->gameBoard;
    for(int i =0 ; i < SP_FIAR_GAME_N_ROWS ; i++){//horizontal win lookup
        for (int j = 0 ; j < SP_FIAR_GAME_N_COLUMNS - OFFSET ; j++){
            if ((board[i][j] == board[i][j+1]) && (board[i][j] == board[i][j+2]) && (board[i][j] == board[i][j+3])){
                if (board[i][j] == SP_FIAR_GAME_PLAYER_1_SYMBOL ) return SP_FIAR_GAME_PLAYER_1_SYMBOL;
                if (board[i][j] == SP_FIAR_GAME_PLAYER_2_SYMBOL ) return SP_FIAR_GAME_PLAYER_2_SYMBOL;
            }
        }
    }

    for(int i =0 ; i < SP_FIAR_GAME_N_ROWS - OFFSET ; i++){//vertical win lookup
        for (int j = 0 ; j < SP_FIAR_GAME_N_COLUMNS; j++){
            if ((board[i][j] == board[i+1][j]) && (board[i][j] == board[i+2][j]) && (board[i][j] == board[i+3][j])){
                if (board[i][j] == SP_FIAR_GAME_PLAYER_1_SYMBOL ) return SP_FIAR_GAME_PLAYER_1_SYMBOL;
                if (board[i][j] == SP_FIAR_GAME_PLAYER_2_SYMBOL ) return SP_FIAR_GAME_PLAYER_2_SYMBOL;
            }
        }
    }

    for(int i =0 ; i < SP_FIAR_GAME_N_ROWS - OFFSET ; i++){//diagonal (/) lookup
        for (int j = 0 ; j < SP_FIAR_GAME_N_COLUMNS - OFFSET; j++){
            if ((board[i][j] == board[i+1][j+1]) && (board[i][j] == board[i+2][j+2]) && (board[i][j] == board[i+3][j+3])){
                if (board[i][j] == SP_FIAR_GAME_PLAYER_1_SYMBOL ) return SP_FIAR_GAME_PLAYER_1_SYMBOL;
                if (board[i][j] == SP_FIAR_GAME_PLAYER_2_SYMBOL ) return SP_FIAR_GAME_PLAYER_2_SYMBOL;
            }
        }
    }

    for(int i = 0 ; i < SP_FIAR_GAME_N_ROWS - OFFSET ; i++){//diagonal (\) lookup
        for (int j = 3 ; j < SP_FIAR_GAME_N_COLUMNS ; j++){
            if ((board[i][j] == board[i+1][j-1]) && (board[i][j] == board[i+2][j-2]) && (board[i][j] == board[i+3][j-3])){
                if (board[i][j] == SP_FIAR_GAME_PLAYER_1_SYMBOL ) return SP_FIAR_GAME_PLAYER_1_SYMBOL;
                if (board[i][j] == SP_FIAR_GAME_PLAYER_2_SYMBOL ) return SP_FIAR_GAME_PLAYER_2_SYMBOL;
            }
        }
    }

    for (int k = 0; k <SP_FIAR_GAME_N_COLUMNS ; k++) {//if there is room for a disc: no tie
        if (src->tops[k] < SP_FIAR_GAME_N_ROWS) return SP_FIAR_GAME_NULL_CHAR;
    }
    return SP_FIAR_GAME_TIE_SYMBOL; //if we got here board is full and no-one won
}

char changeTurn(SPFiarGame* src) { //switch turn and return current
    if (src->currentPlayer == SP_FIAR_GAME_PLAYER_1_SYMBOL) {
        src->currentPlayer = SP_FIAR_GAME_PLAYER_2_SYMBOL;
        return SP_FIAR_GAME_PLAYER_2_SYMBOL;
    } else {
        src->currentPlayer = SP_FIAR_GAME_PLAYER_1_SYMBOL;
        return SP_FIAR_GAME_PLAYER_1_SYMBOL;
    }
}
