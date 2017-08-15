#include <stdio.h>
#include <stdlib.h>
#include "SPFIARGame.h"
#include "SPFIARParser.h"
#include "SPMainAux.h"
#include "SPMiniMax.h"

int main(void) {
    setvbuf (stdout, NULL, _IONBF, 0);
    while(true){               //in order to restart the game! #1 loop
        int difficulty = 0; //init
        int col = 0;
        char winner = SP_FIAR_GAME_NULL_CHAR;
        char input[BUFFER];
        char* errorDet;
        SPCommand CMD;
        SP_COMMAND command;
        SP_FIAR_GAME_MESSAGE message;
        bool boolRegUndo = true;
        bool boolRestart = false;
        bool boolDiskAdd = true;
        bool boolSugMove = true;
        difficulty = gameInit();
        SPFiarGame* game = spFiarGameCreate(HISTORY);
        if ((difficulty == -1) ||(game == NULL)){             //Error was handeled in the func spFiarGameCreate
            spFiarGameDestroy(game);
            fflush(stdout);
            printf("Exiting...\n");
            exit(0);}
        while (true){ 							//main game loop	#2 loop
            setvbuf (stdout, NULL, _IONBF, 0);
            spFiarGamePrintBoard(game);
            fflush(stdout);
            printf("Please make the next move:\n"); //get user action and follow through
            while (true){ //wait for valid command
                errorDet = fgets(input,BUFFER,stdin);
                if(errorDet==NULL){//when somthing happens to input
                    printf("Error: fgets has failed\n");
                    printf("Exiting...\n");
                    spFiarGameDestroy(game);
                    exit(0);}
                CMD = spParserPraseLine(input);
                command = CMD.cmd;
                if(command == SP_QUIT){
                    spFiarGameDestroy(game);
                    printf("Exiting...\n");
                    exit(0);}
                else if(command == SP_RESTART){
                    boolRestart = true;
                    spFiarGameDestroy(game);
                    printf("Game restarted!\n");
                    break;}
                else if(command == SP_UNDO_MOVE){
                    bool undid = undoMove(game);
                    if(!undid) continue;
                    if(boolRegUndo==true ) undoMove(game);
                    boolDiskAdd = true;
                    boolSugMove = true;
                    boolRegUndo=true;
                    break;}
                else if (boolDiskAdd==false && boolSugMove==false && (command == SP_ADD_DISC|| command == SP_SUGGEST_MOVE)){
                    printf("Error: the game is over\n");
                    continue;}
                else if (boolDiskAdd==true && command == SP_ADD_DISC){
                    message = spFiarGameSetMove(game, CMD.arg-1); //disc to col in 0 base
                    if (message == SP_FIAR_GAME_INVALID_ARGUMENT){
                        printf("Error: column number must be in range 1-7\n");
                        continue;}
                    else if (message == SP_FIAR_GAME_INVALID_MOVE){
                        printf("Error: column %d is full\n",CMD.arg);
                        continue;}
                    winner = spFiarCheckWinner(game);
                    boolRegUndo=false;
                    if (winner==SP_FIAR_GAME_NULL_CHAR){
                        game->undoCnt = 0;
                        spFiarGameSetMove(game, spMinimaxSuggestMove(game, difficulty)); //computer's turn
                        winner = spFiarCheckWinner(game);
                        boolRegUndo=true;}
                    if (winner != SP_FIAR_GAME_NULL_CHAR){
                        spFiarGamePrintBoard(game);
                        winnerPrintFunc(winner);		//printing winning or tie
                        boolDiskAdd = false;
                        boolSugMove = false;
                        continue; }
                    else if (winner==SP_FIAR_GAME_NULL_CHAR) break;}				//~~~end of add_disk~~~
                else if (boolSugMove==true && command == SP_SUGGEST_MOVE){
                    col = spMinimaxSuggestMove(game,difficulty) +1; //+1 because funcs are 0-based and input is 1-based
                    printf("Suggested move: drop a disc to column %d\n",col);//1 based number
                }
                else if(command == SP_INVALID_LINE){
                    fflush(stdout);
                    printf("Error: invalid command\n"); }
                else printf("Error: invalid command\n");}				 //end of 3th while loop
            if (boolRestart==true) break;}				//end of 2nd while loop
    }					//end of 1st while loop
}
