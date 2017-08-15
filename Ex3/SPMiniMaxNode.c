#include <limits.h>
#include "SPMiniMaxNode.h"
#include "SPFIARGame.h"
#include <stdbool.h>
#define OFFSET 3


int recursiveFunc(SPFiarGame* game,bool minmax,unsigned int depth){
    if (depth==0)return score(game);
    else{
        int scoreWinner;
        int minWinner =INT_MAX;
        int maxWinner = INT_MIN;
        bool edge = true;
        for(int i=0; i<SP_FIAR_GAME_N_COLUMNS;i++){				//if you don't win in your move
            if (spFiarGameIsValidMove(game,i)){
                edge = false;
                spFiarGameSetMove(game,i);
                char win = spFiarCheckWinner(game);			//winning case
                if(win == SP_FIAR_GAME_PLAYER_1_SYMBOL || win == SP_FIAR_GAME_PLAYER_2_SYMBOL){
                    if(minmax==false){				//checking for winner
                        spFiarGameUndoPrevMove(game);
                        return INT_MIN;
                    }
                    else if (minmax==true){
                        spFiarGameUndoPrevMove(game);
                        return INT_MAX;
                    }
                }
                if(minmax==false){
                    scoreWinner = recursiveFunc(game,!minmax,depth-1);
                    if(scoreWinner<minWinner){
                        minWinner=scoreWinner;
                    }
                }
                else if (minmax==true){
                    scoreWinner = recursiveFunc(game,!minmax,depth-1);
                    if(scoreWinner>maxWinner){
                        maxWinner=scoreWinner;
                    }
                }
                spFiarGameUndoPrevMove(game);
            }
        }
        if (edge) return score(game);
        if(minmax==false){return minWinner;}
        else{return maxWinner;}
    }
}


int score(SPFiarGame* game){
    char (*board)[SP_FIAR_GAME_N_COLUMNS] = game->gameBoard;
    int scores[7] = {0}; //init to 0
    int cnt = 0;
    int weight[7] = {-5,-2,-1,0,1,2,5};
    int score = 0;
    for(int i =0 ; i < SP_FIAR_GAME_N_ROWS ; i++){//horizontal span lookup
        for (int j = 0 ; j < SP_FIAR_GAME_N_COLUMNS - OFFSET ; j++){
            for (int k = 0; k <=OFFSET ; k++) {          //inside the span
                if (board[i][j+k] == SP_FIAR_GAME_PLAYER_1_SYMBOL) cnt++;
                else if(board[i][j+k] == SP_FIAR_GAME_PLAYER_2_SYMBOL) cnt --;}//presume the board is made of X, O , *empty*
            if (cnt == 4) return INT_MAX;       //if someone is a winner
            else if (cnt == -4) return INT_MIN;
            scores[cnt+3]++;
            cnt = 0;}}
    for(int i =0 ; i < SP_FIAR_GAME_N_ROWS - OFFSET ; i++){//vertical span lookup
        for (int j = 0 ; j < SP_FIAR_GAME_N_COLUMNS; j++){
            for (int k = 0; k <=OFFSET ; k++) {          //inside the span
                if (board[i+k][j] == SP_FIAR_GAME_PLAYER_1_SYMBOL) cnt++;
                else if(board[i+k][j] == SP_FIAR_GAME_PLAYER_2_SYMBOL) cnt --;}//presume the board is made of X, O , *empty*
            if (cnt == 4) return INT_MAX;       //if someone is a winner
            else if (cnt == -4) return INT_MIN;
            scores[cnt+3]++;
            cnt = 0;}}
    for(int i =0 ; i < SP_FIAR_GAME_N_ROWS - OFFSET ; i++){//diagonal (/) lookup
        for (int j = 0 ; j < SP_FIAR_GAME_N_COLUMNS - OFFSET; j++){
            for (int k = 0; k <=OFFSET ; k++) {          //inside the span
                if (board[i+k][j+k] == SP_FIAR_GAME_PLAYER_1_SYMBOL) cnt++;
                else if(board[i+k][j+k] == SP_FIAR_GAME_PLAYER_2_SYMBOL) cnt --;}//presume the board is made of X, O , *empty*
            if (cnt == 4) return INT_MAX;       //if someone is a winner
            else if (cnt == -4) return INT_MIN;
            scores[cnt+3]++;
            cnt = 0;}}
    for(int i = 0 ; i < SP_FIAR_GAME_N_ROWS - OFFSET ; i++){//diagonal (\) lookup
        for (int j = 3 ; j < SP_FIAR_GAME_N_COLUMNS ; j++){
            for (int k = 0; k <=OFFSET ; k++) {          //inside the span
                if (board[i+k][j-k] == SP_FIAR_GAME_PLAYER_1_SYMBOL) cnt++;
                else if(board[i+k][j-k] == SP_FIAR_GAME_PLAYER_2_SYMBOL) cnt --;}//presume the board is made of X, O , *empty*
            if (cnt == 4) return INT_MAX;       //if someone is a winner
            else if (cnt == -4) return INT_MIN;
            scores[cnt+3]++;
            cnt = 0;}}
    for (int l = 0; l < 7; ++l) {       //multiply by weight vector
        score+= scores[l]*weight[l];}
    return score;}
