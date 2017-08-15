

/*


	SPFiarGame* game= spFiarGameCreate(20);
	SP_FIAR_GAME_MESSAGE msg;
	SP_FIAR_GAME_MESSAGE winnerMsg;

	//printf("first undo:\n");
	//msg = spFiarGameUndoPrevMove(game);
	//printf("%d\n",msg);
	int randCol;
	srand (time(NULL));

	for (int i = 0 ; i<=70 ; i++) {
		fflush(stdout);
		printf("round number %d\n",i);
		winnerMsg = spFiarCheckWinner(game);
		if(winnerMsg==SP_FIAR_GAME_NULL_CHAR)printf("The Winner is: no winner yet\n");
		else if(winnerMsg==SP_FIAR_GAME_PLAYER_1_SYMBOL)printf("The Winner is: X\n");
		else if(winnerMsg==SP_FIAR_GAME_PLAYER_2_SYMBOL)printf("The Winner is: O\n");
		else if(winnerMsg==SP_FIAR_GAME_TIE_SYMBOL)printf("The Winner is: Tie\n");
		if(winnerMsg==SP_FIAR_GAME_PLAYER_1_SYMBOL) break;
		if(winnerMsg==SP_FIAR_GAME_PLAYER_2_SYMBOL) break;
		if(winnerMsg==SP_FIAR_GAME_TIE_SYMBOL) break;

		spFiarGamePrintBoard(game);

		randCol = rand()%9;
		fflush(stdout);
		printf("rand number is: %d\n",randCol);
	    char c = spFiarGameGetCurrentPlayer(game);
	    printf("player= %c\n",c);
	    printf("col= %d, valid and set move codes= ",randCol+1);
	    msg = spFiarGameIsValidMove(game, randCol);
	    if(msg==true){
	    	fflush(stdout);
	    	printf("true\n");
	    }else{
	    	fflush(stdout);
	    	printf("false\n");
	    }
	    msg = spFiarGameSetMove(game, randCol);
	    printf("%d",msg);
	    printf("\n");
	}
*/
