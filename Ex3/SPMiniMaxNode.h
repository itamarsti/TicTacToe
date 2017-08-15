#ifndef SPMINIMAXNODE_H_
#define SPMINIMAXNODE_H_

#include "SPFIARGame.h"
//Notice: the second function calculates score of a specific board, while the first func
// checks score of a move (including future outcome) according to minimax algorithem
/**
 * helper func to help suggest_move function. recursively returns score of given play, according to minimax
 *
 * @param game - The current game state
 * @return
 * the calculated score of the given play
 */
int recursiveFunc(SPFiarGame* game,bool minmax,unsigned int depth);
/**
 * helper func to calculate the score of a given board
 *
 * @param game - The current game state
 * @return
 * the calculated score of the given game state
 */
int score(SPFiarGame* game);

#endif
