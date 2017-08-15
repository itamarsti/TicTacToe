#include <limits.h>
#include "SPMiniMax.h"
#include <stdlib.h>
#include <stdio.h>
#include "SPMiniMaxNode.h"

/*
 */
int spMinimaxSuggestMove(SPFiarGame* currentGame,unsigned int maxDepth){
    if ((currentGame==NULL)|| maxDepth<=0) return -1;
    else{
        int maxCompare = INT_MIN;
        int minCompare = INT_MAX;
        int WinnerIndex = -1;
        int winnerScore;
        SPFiarGame* gameCopy = spFiarGameCopy(currentGame);
        gameCopy->simulate = true;
        bool maxPlayer = true;
        if(currentGame->currentPlayer==SP_FIAR_GAME_PLAYER_2_SYMBOL) maxPlayer=false;
        if(gameCopy==NULL)return -1;
        for(int i=0;i<SP_FIAR_GAME_N_COLUMNS;i++){
            if (spFiarGameIsValidMove(gameCopy,i)){
                spFiarGameSetMove(gameCopy,i);
                char win = spFiarCheckWinner(gameCopy);
                if (win == SP_FIAR_GAME_PLAYER_1_SYMBOL || win == SP_FIAR_GAME_PLAYER_2_SYMBOL){
                    spFiarGameUndoPrevMove(gameCopy);
                    spFiarGameDestroy(gameCopy);
                    return i;
                }
                if(maxPlayer){
                    winnerScore = recursiveFunc(gameCopy,!maxPlayer, maxDepth -1);
                    if(winnerScore==INT_MAX) return i;
                    if(winnerScore>maxCompare){
                        maxCompare=winnerScore;
                        WinnerIndex = i;
                    }
                }
                else if (!maxPlayer){
                    winnerScore = recursiveFunc(gameCopy,!maxPlayer, maxDepth -1);
                    if(winnerScore==INT_MIN) return i;
                    if(winnerScore<minCompare){
                        minCompare=winnerScore;
                        WinnerIndex = i;

                    }
                }
                spFiarGameUndoPrevMove(gameCopy);
            }
        }
        spFiarGameDestroy(gameCopy);
        return WinnerIndex;				//do not forget to return in 1-base
    }
}
