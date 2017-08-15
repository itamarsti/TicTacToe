/*
 * Tester2.c
 *
 *  Created on: 13 αιεπι 2017
 *      Author: Itamar
 */
/*
	SPFiarGame* game= spFiarGameCreate(20);
	SP_FIAR_GAME_MESSAGE msg;
	SP_FIAR_GAME_MESSAGE winnerMsg;

	//printf("first undo:\n");
	//msg = spFiarGameUndoPrevMove(game);
	//printf("%d\n",msg);
	for(int j=0;j<6;j++){
		for(int i =0;i<7;i++){
			fflush(stdout);
			printf("round number %d\n",j*6+i+1);
			winnerMsg = spFiarCheckWinner(game);
			if(winnerMsg==SP_FIAR_GAME_NULL_CHAR)printf("The Winner is: no winner yet\n");
			else if(winnerMsg==SP_FIAR_GAME_PLAYER_1_SYMBOL)printf("The Winner is: X\n");
			else if(winnerMsg==SP_FIAR_GAME_PLAYER_2_SYMBOL)printf("The Winner is: O\n");
			else if(winnerMsg==SP_FIAR_GAME_TIE_SYMBOL)printf("The Winner is: Tie\n");
			if(winnerMsg==SP_FIAR_GAME_PLAYER_1_SYMBOL) break;
			if(winnerMsg==SP_FIAR_GAME_PLAYER_2_SYMBOL) break;
			if(winnerMsg==SP_FIAR_GAME_TIE_SYMBOL) break;
			spFiarGamePrintBoard(game);
			char c = spFiarGameGetCurrentPlayer(game);
			fflush(stdout);
			printf("player= %c\n",c);
			fflush(stdout);
			printf("col= %d, valid and set move codes= ",i);
			if((i==3 && j==1)||(i==3 && j==2)){
				game->gameBoard[j][i]='O';
			}
			else if((i!=3 && j==2)||(i!=3 && j==3)){
				game->gameBoard[j][i]='O';
			}
			else if((i==3 && j==4)||(i==3 && j==5)){
				game->gameBoard[j][i]='O';
			}
			else{
				game->gameBoard[j][i]='X';
			}
		}
	}

	char check = game->gameBoard[0][1];
	printf("CHECK = %c\n",check);
	spFiarGamePrintBoard(game);
	for (int i =0 ; i<=21 ; i++){
	    printf("Undo num %d \n", i+1);
	    msg = spFiarGameUndoPrevMove(game);
	    printf("\nmessage code = %d\n",msg);
	}
	if(game!=NULL){
		fflush(stdout);
		printf("before destroying\n");
	}
	spFiarGameDestroy(game);
	if(game!=NULL){
		fflush(stdout);
		printf("memory was freed\n");
		}
*/
