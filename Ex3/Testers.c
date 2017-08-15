/*
/////////////////////////////////////GAME TESTER///////////////////////////////
SPFiarGame* game= spFiarGameCreate(20);
SP_FIAR_GAME_MESSAGE msg;
printf("first undo:\n");
msg = spFiarGameUndoPrevMove(game);
printf("%d",msg);
for (int i = -1 ; i<=30 ; i++) {
spFiarGamePrintBoard(game);
char c = spFiarGameGetCurrentPlayer(game);
printf("player= %c\n",c);
printf("col= %d, valid and set move codes= \n",i%8);
msg = spFiarGameIsValidMove(game, i % 8);
printf("%d",msg);
msg = spFiarGameSetMove(game, i%8);
printf("%d",msg);
printf("\n");
}

char check = game->gameBoard[0][1];
printf("CHECK = %c\n",check);
spFiarGamePrintBoard(game);
for (int i =0 ; i<=21 ; i++){
printf("Undo num %d \n", i+1);
msg = spFiarGameUndoPrevMove(game);
printf("\nmessage code = %d",msg);
}




spFiarCheckWinner(game);


SPFiarGame* copy = spFiarGameCopy(game);


spFiarGameDestroy(copy);
////////////////////////////////////END OF GAME TESTER
/////////////////////////////////// ARRAY TESTER
  SP_ARRAY_LIST_MESSAGE msg;

    SPArrayList* lst = spArrayListCreate(5);
    printf("size = %d \n",spArrayListSize(lst));
    printf("maxsize = %d\n",spArrayListMaxCapacity(lst));
    printf("is list check full?(expect 0) %d\n",spArrayListIsFull(lst));
    for(int i = 0 ; i<= 6;i++){
        printf("adding first\n");
        printf("i=%d ",i);
        msg = spArrayListAddFirst(lst, i);
        printf("add code=%d\n",msg);
    }
    int elem = spArrayListGetFirst(lst);
    printf("first elem=(4)%d\n",elem);
    elem = spArrayListGetLast(lst);
    printf("last elem=(0)%d\n",elem);

    printf("is list check full?(expect 1\n) %d",spArrayListIsFull(lst));
    printf("size = %d \n",spArrayListSize(lst));
    SPArrayList* copy = spArrayListCopy(lst);
    spArrayListDestroy(lst);
    for(int i = 0 ; i<= 6;i++){
        printf("checking copy\n");
        printf("i=%d",i);
        int elem = spArrayListGetAt(copy, i);
        printf("elem=%d\n",elem);
    }
    lst = copy; /////////////////////////////////SUPPOSED TO CAUSE MALLOC ERROR
    printf("list check empty?(expect 0\n) %d",spArrayListIsEmpty(copy));
    spArrayListClear(copy);
    for(int i = 0 ; i<= 6;i++){
        printf("checking copy after clear\n");
        printf("i=%d",i);
        int elem = spArrayListGetAt(copy, i);
        printf("elem=%d\n",elem);
    }
    printf("list check empty?(expect 1\n) %d",spArrayListIsEmpty(copy));


    for (int j = 0; j <2 ; ++j) {
        printf("checking copy after clear\n");
        printf("i=%d",j);
        msg= spArrayListAddLast(copy, j);
        printf("add code=%d\n",msg);
    }
    msg= spArrayListAddAt(copy, 42, 1);
    printf("add at 1=%d\n",msg);
    msg= spArrayListAddAt(copy, 42, 8);
    printf("add at 8=%d\n",msg);
    msg= spArrayListAddAt(copy, 42, 3);
    printf("add at 3=%d\n",msg);

    for(int i = 0 ; i<= 6;i++){
        printf("checking copy after adds\n");
        printf("i=%d",i);
        int elem = spArrayListGetAt(copy, i);
        printf("elem=%d\n",elem);
    }
    msg = spArrayListRemoveAt(copy, 8);
    printf("remove at 8=%d\n",msg);
    msg = spArrayListRemoveAt(copy, 1);
    printf("remove at 1=%d\n",msg);
    msg = spArrayListRemoveFirst(copy);
    printf("remove first=%d\n",msg);
    msg = spArrayListRemoveLast(copy);
    printf("remove last=%d\n",msg);
////////////////////////////////////////////END OF PARSER TESTER
///////////////////////////////////////////////////////////////////BIG ARIEL TESTER
 #include "SPFIARGame.h"
#include "SPMiniMax.h"
#include "SPMiniMaxNode.h"
//#include "SPBufferset.h"
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

#define HISTORY_SIZE 20
//******assumption - all the indexes given and returned from the function are 0-based (0-6)!!!!******
 int index = 0;
void ASSERT_TRUE(bool b){
    if(!b){
        printf("problem %d",index);
    }
}
static bool karin() {
    index = 0;
    SPFiarGame* res = spFiarGameCreate(HISTORY_SIZE);
    index++;
    ASSERT_TRUE(res!=NULL);
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS); //add_disc 5
    index++;
    printf("SUGGEST MOVE");
    spFiarGamePrintBoard(res);
    ASSERT_TRUE(spMinimaxSuggestMove(res, 2) == 1);
    index++;

    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS); //add disc to column 4
    index++;
    spFiarGamePrintBoard(res);
    ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS); //add_disc 4
    spFiarGamePrintBoard(res);
    index++;
    ASSERT_TRUE(spMinimaxSuggestMove(res, 2) == 1);
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS); //add disc to column 4
    spFiarGamePrintBoard(res);
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS); //add_disc 6
    spFiarGamePrintBoard(res);
    index++;
    ASSERT_TRUE(spMinimaxSuggestMove(res, 2) == 2);
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS); //add disc to column 4
    spFiarGamePrintBoard(res);
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 3) == SP_FIAR_GAME_SUCCESS); //add_disc 5
    spFiarGamePrintBoard(res);
    // ASSERT_TRUE(spFiarGameSetMove(res, 0) == SP_FIAR_GAME_SUCCESS);
    //spFiarGamePrintBoard(res);
    printf("\n\n score: %d\n",score(res));
    printf("\n\n suggest: %d\n",spMinimaxSuggestMove(res, 2));
    spFiarGameDestroy(res);
    return true;
}
static bool spFiarGameTest1() {
    index = 0;
    SPFiarGame* res = spFiarGameCreate(HISTORY_SIZE);
    index++;
    ASSERT_TRUE(res!=NULL);
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS); //add_disc 3
    index++;
    printf("SUGGEST 2");
    ASSERT_TRUE(spMinimaxSuggestMove(res, 7) == 3);
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 3) == SP_FIAR_GAME_SUCCESS); //add disc to column 4
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS);//add_disc 2
    index++;
    ASSERT_TRUE(spMinimaxSuggestMove(res, 7) == 3);
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 3) == SP_FIAR_GAME_SUCCESS);//add disc to column 4
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 0) == SP_FIAR_GAME_SUCCESS);//add_disc 1
    index++;
    ASSERT_TRUE(spMinimaxSuggestMove(res, 7) == 2);
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS); //add disc to column 3
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS);//add_disc 2
    printf("%d", score(res));
    index++;
    ASSERT_TRUE(spMinimaxSuggestMove(res, 7) == 2);
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS); //add disc to column 3
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 3) == SP_FIAR_GAME_SUCCESS);//add_disc 4
    index++;
    ASSERT_TRUE(spMinimaxSuggestMove(res, 7) == 1);
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS); //add disc to column 2
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 6) == SP_FIAR_GAME_SUCCESS);//add_disc 7
    index++;
    ASSERT_TRUE(spMinimaxSuggestMove(res, 7) == 1);
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS); //add disc to column 2
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 4) == SP_FIAR_GAME_SUCCESS);//add_disc 5
    index++;
    ASSERT_TRUE(spMinimaxSuggestMove(res, 7) == 0);
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 0) == SP_FIAR_GAME_SUCCESS); //add disc to column 1
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS);//add_disc 3
    index++;
    ASSERT_TRUE(spMinimaxSuggestMove(res, 7) == 0);
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 0) == SP_FIAR_GAME_SUCCESS); //add disc to column 1
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 0) == SP_FIAR_GAME_SUCCESS);//add_disc 1
    index++;
    ASSERT_TRUE(spMinimaxSuggestMove(res, 7) == 0);
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 0) == SP_FIAR_GAME_SUCCESS); //add disc to column 1
    index++;
    ASSERT_TRUE(spFiarCheckWinner(res) == SP_FIAR_GAME_PLAYER_2_SYMBOL);
    index++;
    spFiarGamePrintBoard(res);
    return true;
}

static bool spFiarGameTest2() {
    index = 0;
    SPFiarGame* res = spFiarGameCreate(HISTORY_SIZE);
    index++;
    ASSERT_TRUE(res!=NULL);
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 0) == SP_FIAR_GAME_SUCCESS); //add_disc 1
    index++;
    ASSERT_TRUE(spMinimaxSuggestMove(res, 2) == 0);
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 0) == SP_FIAR_GAME_SUCCESS); //add disc to column 4
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS); //add_disc 2
    index++;
    ASSERT_TRUE(spMinimaxSuggestMove(res, 2) == 1);
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS); //add disc to column 2
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS); //add_disc 3
    index++;
    ASSERT_TRUE(spMinimaxSuggestMove(res, 2) == 3);
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 3) == SP_FIAR_GAME_SUCCESS); //add disc to column 4
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS); //add_disc 3
    index++;
    ASSERT_TRUE(spMinimaxSuggestMove(res, 2) == 2);
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS); //add disc to column 3
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 4) == SP_FIAR_GAME_SUCCESS); //add_disc 5
    index++;
    ASSERT_TRUE(spMinimaxSuggestMove(res, 2) == 2);
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS); //add disc to column 3
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS); //add_disc 2
    index++;
    ASSERT_TRUE(spMinimaxSuggestMove(res, 2) == 2);
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS); //add disc to column 3
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS); //add_disc 3
    index++;
    ASSERT_TRUE(spMinimaxSuggestMove(res, 2) == 1);
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS); //add disc to column 2
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 3) == SP_FIAR_GAME_SUCCESS); //add_disc 4
    index++;
    ASSERT_TRUE(spMinimaxSuggestMove(res, 2) == 3);
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 3) == SP_FIAR_GAME_SUCCESS); //add disc to column 4
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS); //add_disc 2
    index++;
    ASSERT_TRUE(spMinimaxSuggestMove(res, 2) == 3);
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 3) == SP_FIAR_GAME_SUCCESS); //add disc to column 4
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 0) == SP_FIAR_GAME_SUCCESS); //add_disc 1
    index++;
    ASSERT_TRUE(spMinimaxSuggestMove(res, 2) == 0);
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 0) == SP_FIAR_GAME_SUCCESS); //add disc to column 1
    index++;
    ASSERT_TRUE(spFiarCheckWinner(res) == SP_FIAR_GAME_PLAYER_2_SYMBOL);
    spFiarGamePrintBoard(res);
    return true;
}

static void spFiarGameTest3() {
    index = 0;
    SPFiarGame* res = spFiarGameCreate(HISTORY_SIZE);
    index++;
    ASSERT_TRUE(res!=NULL);
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 4) == SP_FIAR_GAME_SUCCESS); //add_disc 5
    index++;
    ASSERT_TRUE(spMinimaxSuggestMove(res, 4) == 4);
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 4) == SP_FIAR_GAME_SUCCESS); //add disc to column 5
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS); //add_disc 2
    index++;
    ASSERT_TRUE(spMinimaxSuggestMove(res, 4) == 4);
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 4) == SP_FIAR_GAME_SUCCESS); //add disc to column 5
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 3) == SP_FIAR_GAME_SUCCESS); //add_disc 4
    index++;
    ASSERT_TRUE(spMinimaxSuggestMove(res, 4) == 2);
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS); //add disc to column 3
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 4) == SP_FIAR_GAME_SUCCESS); //add_disc 5
    index++;
    ASSERT_TRUE(spMinimaxSuggestMove(res, 4) == 4);
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 4) == SP_FIAR_GAME_SUCCESS); //add disc to column 5
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 3) == SP_FIAR_GAME_SUCCESS); //add_disc 4
    index++;
    ASSERT_TRUE(spMinimaxSuggestMove(res, 4) == 3);
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 3) == SP_FIAR_GAME_SUCCESS); //add disc to column 4
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 5) == SP_FIAR_GAME_SUCCESS); //add_disc 6
    index++;
    ASSERT_TRUE(spMinimaxSuggestMove(res, 4) == 6);
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 6) == SP_FIAR_GAME_SUCCESS); //add disc to column 7
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS); //add_disc 3
    index++;
    ASSERT_TRUE(spMinimaxSuggestMove(res, 4) == 3);
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 3) == SP_FIAR_GAME_SUCCESS); //add disc to column 4
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 6) == SP_FIAR_GAME_SUCCESS); //add_disc 7
    index++;
    ASSERT_TRUE(spMinimaxSuggestMove(res, 4) == 1);
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS); //add disc to column 2
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 4) == SP_FIAR_GAME_SUCCESS); //add_disc 5
    index++;
    ASSERT_TRUE(spMinimaxSuggestMove(res, 4) == 0);
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 0) == SP_FIAR_GAME_SUCCESS); //add disc to column 1
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 5) == SP_FIAR_GAME_SUCCESS); //add_disc 6
    index++;
    ASSERT_TRUE(spMinimaxSuggestMove(res, 4) == 2);
    index++;
    ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS); //add disc to column 3
    index++;
    ASSERT_TRUE(spFiarCheckWinner(res) == SP_FIAR_GAME_PLAYER_2_SYMBOL);
    spFiarGamePrintBoard(res);
    return ;
}

int main() {
    karin();
    //SP_BUFF_SET();
    //karin();
    //RUN_TEST(spFiarGameTest1);
    //RUN_TEST(spFiarGameTest2);
    //RUN_TEST(spFiarGameTest3);
}
 ///////////////////////////////////////////////////////////////////////////END OF BIG TESTER1
/////////////////////////////////////////////////////MINIMAXTESTER
#include "unit_test_util.h"
#include "SPFIARGame.h"
#include "SPMiniMax.h"
#include "SPMiniMaxNode.h"
#include <stdbool.h>
#include <limits.h>

#define HISTORY_SIZE 20


static bool spFiarGame2() {
    SPFiarGame* res = spFiarGameCreate(HISTORY_SIZE);
    ASSERT_TRUE(res!=NULL);
    ASSERT_TRUE(spFiarGameSetMove(res, 4) == SP_FIAR_GAME_SUCCESS); //add_disc 5
    ASSERT_TRUE(spMinimaxSuggestMove(res, 5) == 3);
    ASSERT_TRUE(spFiarGameSetMove(res, 3) == SP_FIAR_GAME_SUCCESS); //add disc to column 4
    ASSERT_TRUE(spFiarGameSetMove(res, 3) == SP_FIAR_GAME_SUCCESS); //add_disc 4
    ASSERT_TRUE(spMinimaxSuggestMove(res, 5) == 3);
    ASSERT_TRUE(spFiarGameSetMove(res, 3) == SP_FIAR_GAME_SUCCESS); //add disc to column 4
    ASSERT_TRUE(spFiarGameSetMove(res, 5) == SP_FIAR_GAME_SUCCESS); //add_disc 6
    ASSERT_TRUE(spMinimaxSuggestMove(res, 5) == 3);
    ASSERT_TRUE(spFiarGameSetMove(res, 3) == SP_FIAR_GAME_SUCCESS); //add disc to column 4
    ASSERT_TRUE(spFiarGameSetMove(res, 4) == SP_FIAR_GAME_SUCCESS); //add_disc 5
    ASSERT_TRUE(spMinimaxSuggestMove(res, 5) == 4);
    ASSERT_TRUE(spFiarGameSetMove(res, 4) == SP_FIAR_GAME_SUCCESS); //add disc to column 5
    ASSERT_TRUE(spFiarGameSetMove(res, 5) == SP_FIAR_GAME_SUCCESS); //add_disc 6
    ASSERT_TRUE(spMinimaxSuggestMove(res, 5) == 3);
    ASSERT_TRUE(spFiarGameSetMove(res, 3) == SP_FIAR_GAME_SUCCESS); //add disc to column 4
    ASSERT_TRUE(spFiarGameSetMove(res, 3) == SP_FIAR_GAME_SUCCESS); //add_disc 4
    ASSERT_TRUE(spMinimaxSuggestMove(res, 5) == 4);
    ASSERT_TRUE(spFiarGameSetMove(res, 4) == SP_FIAR_GAME_SUCCESS); //add disc to column 5
    ASSERT_TRUE(spFiarGameSetMove(res, 5) == SP_FIAR_GAME_SUCCESS); //add_disc 6
    ASSERT_TRUE(spMinimaxSuggestMove(res, 5) == 5);
    ASSERT_TRUE(spFiarGameSetMove(res, 5) == SP_FIAR_GAME_SUCCESS); //add disc to column 6
    ASSERT_TRUE(spFiarGameSetMove(res, 0) == SP_FIAR_GAME_SUCCESS); //add_disc 1
    ASSERT_TRUE(spMinimaxSuggestMove(res, 5) == 4);
    ASSERT_TRUE(spFiarGameSetMove(res, 4) == SP_FIAR_GAME_SUCCESS); //add disc to column 5
    ASSERT_TRUE(spFiarGameSetMove(res, 4) == SP_FIAR_GAME_SUCCESS); //add_disc 5
    ASSERT_TRUE(spMinimaxSuggestMove(res, 5) == 5);
    ASSERT_TRUE(spFiarGameSetMove(res, 5) == SP_FIAR_GAME_SUCCESS); //add disc to column 6
    ASSERT_TRUE(spFiarGameSetMove(res, 6) == SP_FIAR_GAME_SUCCESS); //add_disc 7
    ASSERT_TRUE(spMinimaxSuggestMove(res, 5) == 6);
    ASSERT_TRUE(spFiarGameSetMove(res, 6) == SP_FIAR_GAME_SUCCESS); //add disc to column 7
    ASSERT_TRUE(spFiarGameSetMove(res, 6) == SP_FIAR_GAME_SUCCESS); //add_disc 7
    ASSERT_TRUE(spMinimaxSuggestMove(res, 5) == 0);
    ASSERT_TRUE(spFiarGameSetMove(res, 0) == SP_FIAR_GAME_SUCCESS); //add disc to column 1
    ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS); //add_disc 3
    ASSERT_TRUE(spMinimaxSuggestMove(res, 5) == 2);
    ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS); //add disc to column 3
    spFiarGamePrintBoard(res);
    spFiarGameDestroy(res);
    return true;
}


static bool karin() {
    SPFiarGame* res = spFiarGameCreate(HISTORY_SIZE);
    ASSERT_TRUE(res!=NULL);
    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS); //add_disc 5
    spFiarGamePrintBoard(res);
    ASSERT_TRUE(spMinimaxSuggestMove(res, 2) == 1);
    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS); //add disc to column 4
    spFiarGamePrintBoard(res);
    ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS); //add_disc 4
    spFiarGamePrintBoard(res);
    ASSERT_TRUE(spMinimaxSuggestMove(res, 2) == 1);
    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS); //add disc to column 4
    spFiarGamePrintBoard(res);
    ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS); //add_disc 6
    spFiarGamePrintBoard(res);
    ASSERT_TRUE(spMinimaxSuggestMove(res, 2) == 2);
    ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS); //add disc to column 4
    spFiarGamePrintBoard(res);
    ASSERT_TRUE(spFiarGameSetMove(res, 3) == SP_FIAR_GAME_SUCCESS); //add_disc 5
    printf("\n%d",getSpanVal(res));
    printf("\n%d",spMinimaxSuggestMove(res, 2));
    spFiarGamePrintBoard(res);
    spFiarGameDestroy(res);
    return true;
}


int main() {
    //SP_BUFF_SET();
    RUN_TEST(karin);
}
///////////////////////////////////////////////////////////END MINIMAX TESTER
 ////////////////////////////////////MINIMAX TESTER2

#include "unit_test_util.h"
#include "SPFIARGame.h"
#include "SPMiniMax.h"
#include "SPMiniMaxNode.h"
//#include "SPBufferset.h"
#include <stdbool.h>
#include <limits.h>

#define HISTORY_SIZE 20
    //******assumption - all the indexes given and returned from the function are 0-based (0-6)!!!!******

    static bool spFiarGameTest1() {
    SPFiarGame* res = spFiarGameCreate(HISTORY_SIZE);
    ASSERT_TRUE(res!=NULL);
    ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS); //add_disc 3
    ASSERT_TRUE(spMinimaxSuggestMove(res, 7) == 3);
    ASSERT_TRUE(spFiarGameSetMove(res, 3) == SP_FIAR_GAME_SUCCESS); //add disc to column 4
    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS);//add_disc 2
    ASSERT_TRUE(spMinimaxSuggestMove(res, 7) == 3);
    ASSERT_TRUE(spFiarGameSetMove(res, 3) == SP_FIAR_GAME_SUCCESS);//add disc to column 4
    ASSERT_TRUE(spFiarGameSetMove(res, 0) == SP_FIAR_GAME_SUCCESS);//add_disc 1
    ASSERT_TRUE(spMinimaxSuggestMove(res, 7) == 2);
    ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS); //add disc to column 3
    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS);//add_disc 2
    ASSERT_TRUE(spMinimaxSuggestMove(res, 7) == 2);
    ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS); //add disc to column 3
    ASSERT_TRUE(spFiarGameSetMove(res, 3) == SP_FIAR_GAME_SUCCESS);//add_disc 4
    ASSERT_TRUE(spMinimaxSuggestMove(res, 7) == 1);
    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS); //add disc to column 2
    ASSERT_TRUE(spFiarGameSetMove(res, 6) == SP_FIAR_GAME_SUCCESS);//add_disc 7
    ASSERT_TRUE(spMinimaxSuggestMove(res, 7) == 1);
    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS); //add disc to column 2
    ASSERT_TRUE(spFiarGameSetMove(res, 4) == SP_FIAR_GAME_SUCCESS);//add_disc 5
    ASSERT_TRUE(spMinimaxSuggestMove(res, 7) == 0);
    ASSERT_TRUE(spFiarGameSetMove(res, 0) == SP_FIAR_GAME_SUCCESS); //add disc to column 1
    ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS);//add_disc 3
    ASSERT_TRUE(spMinimaxSuggestMove(res, 7) == 0);
    ASSERT_TRUE(spFiarGameSetMove(res, 0) == SP_FIAR_GAME_SUCCESS); //add disc to column 1
    ASSERT_TRUE(spFiarGameSetMove(res, 0) == SP_FIAR_GAME_SUCCESS);//add_disc 1
    ASSERT_TRUE(spMinimaxSuggestMove(res, 7) == 0);
    ASSERT_TRUE(spFiarGameSetMove(res, 0) == SP_FIAR_GAME_SUCCESS); //add disc to column 1
    ASSERT_TRUE(spFiarCheckWinner(res) == SP_FIAR_GAME_PLAYER_2_SYMBOL);
    spFiarGamePrintBoard(res);
    return true;
}

static bool spFiarGameTest2() {
    SPFiarGame* res = spFiarGameCreate(HISTORY_SIZE);
    ASSERT_TRUE(res!=NULL);
    ASSERT_TRUE(spFiarGameSetMove(res, 0) == SP_FIAR_GAME_SUCCESS); //add_disc 1
    ASSERT_TRUE(spMinimaxSuggestMove(res, 2) == 0);
    ASSERT_TRUE(spFiarGameSetMove(res, 0) == SP_FIAR_GAME_SUCCESS); //add disc to column 4
    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS); //add_disc 2
    ASSERT_TRUE(spMinimaxSuggestMove(res, 2) == 1);
    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS); //add disc to column 2
    ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS); //add_disc 3
    ASSERT_TRUE(spMinimaxSuggestMove(res, 2) == 3);
    ASSERT_TRUE(spFiarGameSetMove(res, 3) == SP_FIAR_GAME_SUCCESS); //add disc to column 4
    ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS); //add_disc 3
    ASSERT_TRUE(spMinimaxSuggestMove(res, 2) == 2);
    ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS); //add disc to column 3
    ASSERT_TRUE(spFiarGameSetMove(res, 4) == SP_FIAR_GAME_SUCCESS); //add_disc 5
    ASSERT_TRUE(spMinimaxSuggestMove(res, 2) == 2);
    ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS); //add disc to column 3
    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS); //add_disc 2
    ASSERT_TRUE(spMinimaxSuggestMove(res, 2) == 2);
    ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS); //add disc to column 3
    ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS); //add_disc 3
    ASSERT_TRUE(spMinimaxSuggestMove(res, 2) == 1);
    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS); //add disc to column 2
    ASSERT_TRUE(spFiarGameSetMove(res, 3) == SP_FIAR_GAME_SUCCESS); //add_disc 4
    ASSERT_TRUE(spMinimaxSuggestMove(res, 2) == 3);
    ASSERT_TRUE(spFiarGameSetMove(res, 3) == SP_FIAR_GAME_SUCCESS); //add disc to column 4
    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS); //add_disc 2
    ASSERT_TRUE(spMinimaxSuggestMove(res, 2) == 3);
    ASSERT_TRUE(spFiarGameSetMove(res, 3) == SP_FIAR_GAME_SUCCESS); //add disc to column 4
    ASSERT_TRUE(spFiarGameSetMove(res, 0) == SP_FIAR_GAME_SUCCESS); //add_disc 1
    ASSERT_TRUE(spMinimaxSuggestMove(res, 2) == 0);
    ASSERT_TRUE(spFiarGameSetMove(res, 0) == SP_FIAR_GAME_SUCCESS); //add disc to column 1
    ASSERT_TRUE(spFiarCheckWinner(res) == SP_FIAR_GAME_PLAYER_2_SYMBOL);
    spFiarGamePrintBoard(res);
    return true;
}

static bool spFiarGameTest3() {
    SPFiarGame* res = spFiarGameCreate(HISTORY_SIZE);
    ASSERT_TRUE(res!=NULL);
    ASSERT_TRUE(spFiarGameSetMove(res, 4) == SP_FIAR_GAME_SUCCESS); //add_disc 5
    ASSERT_TRUE(spMinimaxSuggestMove(res, 4) == 4);
    ASSERT_TRUE(spFiarGameSetMove(res, 4) == SP_FIAR_GAME_SUCCESS); //add disc to column 5
    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS); //add_disc 2
    ASSERT_TRUE(spMinimaxSuggestMove(res, 4) == 4);
    ASSERT_TRUE(spFiarGameSetMove(res, 4) == SP_FIAR_GAME_SUCCESS); //add disc to column 5
    ASSERT_TRUE(spFiarGameSetMove(res, 3) == SP_FIAR_GAME_SUCCESS); //add_disc 4
    ASSERT_TRUE(spMinimaxSuggestMove(res, 4) == 2);
    ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS); //add disc to column 3
    ASSERT_TRUE(spFiarGameSetMove(res, 4) == SP_FIAR_GAME_SUCCESS); //add_disc 5
    ASSERT_TRUE(spMinimaxSuggestMove(res, 4) == 4);
    ASSERT_TRUE(spFiarGameSetMove(res, 4) == SP_FIAR_GAME_SUCCESS); //add disc to column 5
    ASSERT_TRUE(spFiarGameSetMove(res, 3) == SP_FIAR_GAME_SUCCESS); //add_disc 4
    ASSERT_TRUE(spMinimaxSuggestMove(res, 4) == 3);
    ASSERT_TRUE(spFiarGameSetMove(res, 3) == SP_FIAR_GAME_SUCCESS); //add disc to column 4
    ASSERT_TRUE(spFiarGameSetMove(res, 5) == SP_FIAR_GAME_SUCCESS); //add_disc 6
    ASSERT_TRUE(spMinimaxSuggestMove(res, 4) == 6);
    ASSERT_TRUE(spFiarGameSetMove(res, 6) == SP_FIAR_GAME_SUCCESS); //add disc to column 7
    ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS); //add_disc 3
    ASSERT_TRUE(spMinimaxSuggestMove(res, 4) == 3);
    ASSERT_TRUE(spFiarGameSetMove(res, 3) == SP_FIAR_GAME_SUCCESS); //add disc to column 4
    ASSERT_TRUE(spFiarGameSetMove(res, 6) == SP_FIAR_GAME_SUCCESS); //add_disc 7
    ASSERT_TRUE(spMinimaxSuggestMove(res, 4) == 1);
    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS); //add disc to column 2
    ASSERT_TRUE(spFiarGameSetMove(res, 4) == SP_FIAR_GAME_SUCCESS); //add_disc 5
    ASSERT_TRUE(spMinimaxSuggestMove(res, 4) == 0);
    ASSERT_TRUE(spFiarGameSetMove(res, 0) == SP_FIAR_GAME_SUCCESS); //add disc to column 1
    ASSERT_TRUE(spFiarGameSetMove(res, 5) == SP_FIAR_GAME_SUCCESS); //add_disc 6
    ASSERT_TRUE(spMinimaxSuggestMove(res, 4) == 2);
    ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS); //add disc to column 3
    ASSERT_TRUE(spFiarCheckWinner(res) == SP_FIAR_GAME_PLAYER_2_SYMBOL);
    spFiarGamePrintBoard(res);
    return true;
}

int main() {
    //SP_BUFF_SET();
    RUN_TEST(spFiarGameTest1);
    RUN_TEST(spFiarGameTest2);
    RUN_TEST(spFiarGameTest3);
}
///////////////////////////////////////////////////////////////END MINIMAX TESTER2
///////////////////////////////////////////////////////////// MINIMAX TESTER 3
 #include "unit_test_util.h"
#include "SPFIARGame.h"
#include "SPMiniMax.h"
#include "SPMiniMaxNode.h"
#include <stdbool.h>
#include <limits.h>

#define HISTORY_SIZE 20


static bool spFiarGameSetMoveTest1() {
    printf("\n\n***spFiarGameSetMoveTest1***\n\n");
    SPFiarGame* res = spFiarGameCreate(HISTORY_SIZE);
    ASSERT_TRUE(res!=NULL);
    int repeat = 2;
    while (repeat-- > 0) {
        for (int i = 0; i < SP_FIAR_GAME_N_COLUMNS; i++) {
            ASSERT_TRUE(spFiarGameSetMove(res, i) == SP_FIAR_GAME_SUCCESS);
        }
    }

        for (int i = 0; i < 3; i++) {
            ASSERT_TRUE(spFiarGameSetMove(res, i) == SP_FIAR_GAME_SUCCESS);
        }

    spFiarGamePrintBoard(res);
    printf("\n\nwinner: %c\n\n",spFiarCheckWinner(res));


    ASSERT_TRUE(spFiarGameSetMove(res, 6) == SP_FIAR_GAME_SUCCESS);
    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS);

    spFiarGamePrintBoard(res);
    printf("\n\nwinner %c\n\n",spFiarCheckWinner(res));
    spFiarGameDestroy(res);

    return true;
}

static bool spFiarGameSetMoveTest2() {
    printf("\n\n***spFiarGameSetMoveTest2***\n\n");
    SPFiarGame* res = spFiarGameCreate(HISTORY_SIZE);
    ASSERT_TRUE(res!=NULL);

    ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS);
    ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS);
    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS);
    ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS);
    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS);
    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS);
    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS);
    ASSERT_TRUE(spFiarGameSetMove(res, 3) == SP_FIAR_GAME_SUCCESS);
    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS);
    ASSERT_TRUE(spFiarGameSetMove(res, 3) == SP_FIAR_GAME_SUCCESS);
    ASSERT_TRUE(spFiarGameSetMove(res, 3) == SP_FIAR_GAME_SUCCESS);
    ASSERT_TRUE(spFiarGameSetMove(res, 6) == SP_FIAR_GAME_SUCCESS);
    ASSERT_TRUE(spFiarGameSetMove(res, 4) == SP_FIAR_GAME_SUCCESS);
    ASSERT_TRUE(spFiarGameSetMove(res, 5) == SP_FIAR_GAME_SUCCESS);

    spFiarGamePrintBoard(res);
    printf("\n\nwinner: %c",spFiarCheckWinner(res));
    printf("\n\nscoreFunction result:%d\n\n",scoreFunction(res));
    spFiarGameDestroy(res);

    return true;
}


static bool spFiarSuggestMoveTest1() {
    printf("\n\n***spFiarSuggestMoveTest1***\n\n");
    SPFiarGame* res = spFiarGameCreate(HISTORY_SIZE);
    ASSERT_TRUE(res!=NULL);
    int repeat = 2;
    while (repeat-- > 0) {
        for (int i = 0; i < SP_FIAR_GAME_N_COLUMNS; i++) {
            ASSERT_TRUE(spFiarGameSetMove(res, i) == SP_FIAR_GAME_SUCCESS);
        }
    }

    for (int i = 0; i < 4; i++) {
        ASSERT_TRUE(spFiarGameSetMove(res, i) == SP_FIAR_GAME_SUCCESS);
    }

    spFiarGamePrintBoard(res);
    printf("\nsuggest col: %d\n",spMinimaxSuggestMove(res,7));
    spFiarGameDestroy(res);

    return true;
}

static bool spFiarSuggestMoveTest2() {
    printf("\n\n***spFiarSuggestMoveTest2***\n\n");
    SPFiarGame* res = spFiarGameCreate(HISTORY_SIZE);
    ASSERT_TRUE(res!=NULL);
    int repeat = 2;
    while (repeat-- > 0) {
        for (int i = 0; i < SP_FIAR_GAME_N_COLUMNS; i++) {
            ASSERT_TRUE(spFiarGameSetMove(res, i) == SP_FIAR_GAME_SUCCESS);
        }
    }

    spFiarGamePrintBoard(res);
    printf("\nsuggest col: %d\n",spMinimaxSuggestMove(res,7));
    spFiarGameDestroy(res);

    return true;
}

static bool spFiarSuggestMoveTest3() {
    printf("\n\n***spFiarSuggestMoveTest3***\n\n");
    SPFiarGame* res = spFiarGameCreate(HISTORY_SIZE);
    ASSERT_TRUE(res!=NULL);
    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS);
    ASSERT_TRUE(spFiarGameSetMove(res, 6) == SP_FIAR_GAME_SUCCESS);
    ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS);
    ASSERT_TRUE(spFiarGameSetMove(res, 5) == SP_FIAR_GAME_SUCCESS);
    ASSERT_TRUE(spFiarGameSetMove(res, 4) == SP_FIAR_GAME_SUCCESS);
    ASSERT_TRUE(spFiarGameSetMove(res, 3) == SP_FIAR_GAME_SUCCESS);
    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS);
    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS);
    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS);
    ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS);
    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS);
    ASSERT_TRUE(spFiarGameSetMove(res, 3) == SP_FIAR_GAME_SUCCESS);
    ASSERT_TRUE(spFiarGameSetMove(res, 1) == SP_FIAR_GAME_SUCCESS);
    ASSERT_TRUE(spFiarGameSetMove(res, 4) == SP_FIAR_GAME_SUCCESS);
    ASSERT_TRUE(spFiarGameSetMove(res, 3) == SP_FIAR_GAME_SUCCESS);
    ASSERT_TRUE(spFiarGameSetMove(res, 2) == SP_FIAR_GAME_SUCCESS);
    ASSERT_TRUE(spFiarGameSetMove(res, 0) == SP_FIAR_GAME_SUCCESS);


    spFiarGamePrintBoard(res);
    printf("\nsuggest col: %d\n",spMinimaxSuggestMove(res,7));
    spFiarGameDestroy(res);

    return true;
}

static bool spFiarSuggestMoveTest4() {
    printf("\n\n***spFiarSuggestMoveTest4***\n\n");
    SPFiarGame* res = spFiarGameCreate(HISTORY_SIZE);
    ASSERT_TRUE(res!=NULL);
    ASSERT_TRUE(spFiarGameSetMove(res, 0) == SP_FIAR_GAME_SUCCESS);
    spFiarGamePrintBoard(res);
    printf("\n suggest column: %d **%c**\n",spMinimaxSuggestMove(res,2),res->currentPlayer);
    return true;
}



int main() {
    RUN_TEST(spFiarGameSetMoveTest1);
    RUN_TEST(spFiarGameSetMoveTest2);
    RUN_TEST(spFiarSuggestMoveTest1);
    RUN_TEST(spFiarSuggestMoveTest2);
    RUN_TEST(spFiarSuggestMoveTest3);
    RUN_TEST(spFiarSuggestMoveTest4);

}

/////////////////////////////////////////////END MINIMAX TESTER 3



#include "SPMiniMax.h"

int spMinimaxSuggestMove(SPFiarGame* currentGame,
                         unsigned int maxDepth) {
    int result = -1;
    if (maxDepth <= 0 || !currentGame ||
        currentGame->currentPlayer==SP_FIAR_GAME_EMPTY_ENTRY)
        return result;

    //max or min player
    bool isMax = (currentGame->currentPlayer == SP_FIAR_GAME_PLAYER_1_SYMBOL);
    int val = initFirstValue(isMax);
    int currVal;

    for (int col = 0; col < SP_FIAR_GAME_N_COLUMNS; ++col) {
        //check if it is a valid move
        if (spFiarGameIsValidMove(currentGame, col)) {
            //copy game
            SPFiarGame *copy = spFiarGameCopy(currentGame);
            if (!copy) {
                spFiarGameDestroy(currentGame);
                return -1;
            }

            //checking if it is a winning move
            if(winningMove(copy,col)) return col;

            // MinMaxVal algorithm
            currVal = recursiveMinMaxVal(copy, maxDepth - 1, !isMax);
            spFiarGameDestroy(copy);

            //update best col and best score
            if (isMax ) {
                if(currVal==INT_MAX) return col;
                if (currVal > val) {
                    val = currVal;
                    result = col;
                }
            } else {
                if(currVal==INT_MIN) return col;
                if (currVal < val) {
                    val = currVal;
                    result = col;
                }
            }
        }
    }
    return result;
}

#include "SPMiniMaxNode.h"

int recursiveMinMaxVal(SPFiarGame* currentGame,
                       unsigned int level,bool isMax){

    if (level == 0) return scoreFunction(currentGame);

    //init variables
    int res = initFirstValue(isMax);
    int winVal = initWinnerScore(isMax);
    bool isLeaf = true;

    for (int col = 0; col < SP_FIAR_GAME_N_COLUMNS; ++col) {
        if (spFiarGameIsValidMove(currentGame, col)) {
            isLeaf = false;

            //create copy
            SPFiarGame* copy = spFiarGameCopy(currentGame);
            if (!copy) {
                spFiarGameDestroy(currentGame);
                return -1;
            }

            //checking if it is a winning move
            if(winningMove(copy,col)) return winVal;

            //recursive call
            if (isMax) {
                res = MAX(res, recursiveMinMaxVal(copy,level-1,!isMax));
            } else {
                res = MIN(res, recursiveMinMaxVal(copy,level-1,!isMax));
            }

            //destroy copy
            spFiarGameDestroy(copy);
        }
    }

    if (isLeaf) return scoreFunction(currentGame);

    return res;
}


int initFirstValue(bool isMax){
    if (isMax) {
        return INT_MIN;
    } else {
        return INT_MAX;
    }
}


int initWinnerScore(bool isMax){
    if (isMax) {
        return INT_MAX;
    } else {
        return INT_MIN;
    }
}






/////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <time.h>
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
        SPCommand CMD;
        SP_COMMAND command;
        SP_FIAR_GAME_MESSAGE message;
        bool boolRestart = false;
        bool boolDiskAdd = true;
        bool boolSugMove = true;
        difficulty = gameInit();
        SPFiarGame* game = spFiarGameCreate(HISTORY);
        if ((difficulty == -1) ||(game == NULL)){             //Error was handeled in the func spFiarGameCreate
            spFiarGameDestroy(game);
            fflush(stdout);
            printf("Exiting…\n");
            exit(0);
        }
        while (true){ 							//main game loop	#2 loop
            setvbuf (stdout, NULL, _IONBF, 0);
            spFiarGamePrintBoard(game);
            fflush(stdout);
            printf("Please make the next move:\n"); //get user action and follow through
            while (true){ //wait for valid command
                int errorNum = scanf(" %[^\t\n]s",&input);
                if(errorNum<0){//when somthing happens to input
                    fflush(stdout);
                    printf("Error: scanf has failed\n");
                    spFiarGameDestroy(game);
                    fflush(stdout);
                    printf("Exiting…\n");
                    exit(0);
                }
                CMD = spParserPraseLine(input);
                command = CMD.cmd;
                if(command == SP_QUIT){
                    spFiarGameDestroy(game);
                    printf("Exiting…\n");
                    exit(0);
                }
                else if(command == SP_RESTART){
                    boolRestart = true;
                    break;
                }
                else if(command == SP_UNDO_MOVE){
                    if (spArrayListIsEmpty(game->moves)){

                    }
                    undoMove(game);
                    boolDiskAdd = true;
                    boolSugMove = true;
                    break;
                }
                else if (boolDiskAdd==false && boolSugMove==false && (command == SP_ADD_DISC|| command == SP_SUGGEST_MOVE)){
                    printf("Error: the game is over\n");
                    continue;
                }
                else if (boolDiskAdd==true && command == SP_ADD_DISC){
                    message = spFiarGameSetMove(game, CMD.arg-1); //disc to col in 0 base
                    if (message == SP_FIAR_GAME_INVALID_ARGUMENT){
                        printf("Error: column number must be in range 1-7\n");
                        continue;
                    }
                    else if (message == SP_FIAR_GAME_INVALID_MOVE){
                        printf("Error: column %d is full\n",CMD.arg);
                        continue;
                    }
                    winner = spFiarCheckWinner(game);
                    if (winner==SP_FIAR_GAME_NULL_CHAR){
                        game->undoCnt = 0;
                        spFiarGameSetMove(game, spMinimaxSuggestMove(game, difficulty)); //computer's turn
                        winner = spFiarCheckWinner(game);
                    }
                    if (winner != SP_FIAR_GAME_NULL_CHAR){
                        winnerPrintFunc(winner);		//printing winning or tie
                        boolDiskAdd = false;
                        boolSugMove = false;
                        continue;
                    }
                    else if (winner==SP_FIAR_GAME_NULL_CHAR) break;
                }				//~~~end of add_disk~~~

                else if (boolSugMove==true && command == SP_SUGGEST_MOVE){
                    col = spMinimaxSuggestMove(game,difficulty) +1; //+1 because funcs are 0-based and input is 1-based
                    printf("Suggested move: drop a disc to column %d\n",col);//1 based number
                }
                else if(command == SP_INVALID_LINE){
                    fflush(stdout);
                    printf("Error: invalid command\n");
                }
                else printf("Error: invalid command\n");
            }				 //end of 3th while loop
            if (boolRestart==true) break;
        }				//end of 2nd while loop
    }					//end of 1st while loop


}
*/
