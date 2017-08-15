#ifndef SPMAINAUX_H_
#define SPMAINAUX_H_
#include "SPFIARGame.h"
#define HISTORY 20
#define BUFFER 1024
//put auxiliary functions and constants used by the main function here.

/**
 * sets difficulty or quit

 * @return
 * difficulty or -1 for quit
 */
int gameInit();

/**
 * undo last move of game or return error
 * @game - the game which we want to undo move in
 * @return
 * void
 */
bool undoMove(SPFiarGame* game);

/**
 * destroy game and change it to a new game. Also init game and return difficulty.
 * @game - the game which we want to restart
 * @return
 * difficulty level
 */
int restartGame(SPFiarGame* game);

/**
 * prints the winning line.
 * @game - the game which we want to restart
 * @return
 * void
 */
void winnerPrintFunc(char winner);


#endif
