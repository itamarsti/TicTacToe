#include <stdio.h>
#include <stdlib.h>
#include "SPMainAux.h"
#include "SPFIARGame.h"
#include "SPFIARGame.h"
#include "SPFIARParser.h"
#include <stdbool.h>
#include <string.h>

int gameInit(){//set difficulty or quit code
    setvbuf (stdout, NULL, _IONBF, 0);
    int difficulty = 0;//init
    char cmd[BUFFER];
    bool isInt=false;
    while (true){ //get difficulty
    	fflush(stdout);
        printf("Please enter the difficulty level between [1-7]:\n");
        char* errorDet = fgets(cmd,BUFFER,stdin);
        if(errorDet==NULL){//when somthing happens to input
            printf("Error: fgets has failed\n");
            return -1;
        }
        if(strcmp(cmd,"quit\n")==0 || strcmp(cmd,"quit")==0){
            difficulty = -1;
            return difficulty;
        }
        isInt = spParserIsInt(cmd);
        if (isInt==false){
            fflush(stdout);
            printf("Error: invalid level (should be between 1 to 7)\n");
            continue;
        }
        else{
            difficulty = atoi(cmd);
            if(difficulty<=7&& difficulty>=1) break;
            else{
                fflush(stdout);
                printf("Error: invalid level (should be between 1 to 7)\n");
                continue;
            }
        }
    }
    return difficulty;
}

bool undoMove(SPFiarGame* game){//undo 2 moves (player and computer)
    SP_FIAR_GAME_MESSAGE message;
    message = spFiarGameUndoPrevMove(game);
    if (message == SP_FIAR_GAME_INVALID_ARGUMENT ||message == SP_FIAR_GAME_NO_HISTORY ){
        printf("Error: cannot undo previous move!\n");
        return false;
    }
    return true;
}

void winnerPrintFunc(char winner){
    fflush(stdout);
    if (winner == SP_FIAR_GAME_PLAYER_1_SYMBOL){
        printf("Game over: you win\nPlease enter \'quit\' to exit or \'restart\' to start a new game!\n");
    }
    else if (winner == SP_FIAR_GAME_PLAYER_2_SYMBOL){
        printf("Game over: computer wins\nPlease enter \'quit\' to exit or \'restart\' to start a new game!\n");
    }
    else if(winner == SP_FIAR_GAME_TIE_SYMBOL){
        printf("Game over: it’s a tie\nPlease enter \'quit\' to exit or \'restart\' to start a new game!\n");
    }
}
