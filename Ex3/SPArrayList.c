#define SPARRAYLIST_H_
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/**
 * SPArrayList summary:
 *
 * A container that represents a fixed size linked list. The capcity of the list
 * is specified at the creation. The container supports typical list
 * functionalities with the addition of random access as in arrays.
 * Upon insertion, if the maximum capacity is reached then an error message is
 * returned and the list is not affected. A summary of the supported functions
 * is given below:
 *
 * spArrayListCreate       - Creates an empty array list with a specified
 *                           max capacity.
 * spArrayListCopy         - Creates an exact copy of a specified array list.
 * spArrayListDestroy      - Frees all memory resources associated with an array
 *                           list.
 * spArrayListClear        - Clears all elements from a specified array list.
 * spArrayListAddAt        - Inserts an element at a specified index, elements
 *                           will be shifted to make place.
 * spArrayListAddFirst     - Inserts an element at the beginning of the array
 *                           list, elements will be shifted to make place.
 * spArrayListAddLast      - Inserts an element at the end of the array list.
 * spArrayListRemoveAt     - Removes an element at the specified index, elements
 *                           elements will be shifted as a result.
 * spArrayListRemoveFirst  - Removes an element from the beginning of the array
 *                           list, elements will be shifted as a result.
 * spArrayListRemoveLast   - Removes an element from the end of the array list
 * spArrayListGetAt        - Accesses the element at the specified index.
 * spArrayListGetFirst     - Accesses the first element of the array list.
 * spArrayListGetLast      - Accesses the last element of the array list.
 * spArrayListMaxCapcity   - Returns the maximum capcity of the array list.
 * spArrayListSize         - Returns the number of elements in that array list.
 * spArrayListIsFull       - Returns if the array list reached its max capacity.
 * spArrayListIsEmpty      - Returns true if the array list contains no elements.
 */
typedef struct sp_array_list_t {
    int* elements;
    int actualSize;
    int maxSize;
} SPArrayList;

/**
 * A type used for errors
 */
typedef enum sp_array_list_message_t {
    SP_ARRAY_LIST_SUCCESS,
    SP_ARRAY_LIST_INVALID_ARGUMENT,
    SP_ARRAY_LIST_FULL,
    SP_ARRAY_LIST_EMPTY
} SP_ARRAY_LIST_MESSAGE;

/**
 *  Creates an empty array list with the specified maximum capacity.
 *  @param maxSize - the maximum capacity of the target array list.
 *  @return
 *  NULL, if an allocation error occurred or maxSize  <= 0.
 *  An instant of an array list otherwise.
 */
SPArrayList* spArrayListCreate(int maxSize){

    SPArrayList *listMovesPointer = (SPArrayList*)malloc(sizeof(SPArrayList));
    if (listMovesPointer==NULL){
        printf("Error: malloc has failed\n");
        free(listMovesPointer);
        return NULL;
    }
    int* arrMoves =(int*) calloc(maxSize,sizeof(int));    //initializing to array with 0's (will later turn to -1)
    if(maxSize<=0 || arrMoves==NULL){
        printf("Error: malloc has failed\n");
        free(arrMoves);
        free(listMovesPointer);
        return NULL;
    }
    for(int i=0;i<maxSize;i++){                             //init with -1
        arrMoves[i]=-1;
    }
    listMovesPointer->elements = arrMoves;
    listMovesPointer->actualSize = 0;
    listMovesPointer->maxSize = maxSize;
    return listMovesPointer;
}

/**
 * Creates an exact copy of the src array list. Elements in the new copy will
 * be in the same order as they appeared in the source list.
 * @param src - the source array list.
 * @return
 * NULL if either an allocation error occurs or src == NULL.
 * A new copy of the source array list, otherwise.
 */
SPArrayList* spArrayListCopy(SPArrayList* src){
	if(src==NULL)return NULL;
    SPArrayList* copy = spArrayListCreate(src->maxSize);
    if(copy==NULL){             //in case the allocation was failed
        return NULL;
    }
    for(int i=0;i<src->actualSize;i++){
        (copy->elements)[i]= (src->elements)[i];
    }
    copy->actualSize = src->actualSize;
    copy->maxSize = src->maxSize;
    return copy;
}

/**
 * Frees all memory resources associated with the source array list. If the
 * source array is NULL, then the function does nothing.
 * @param src - the source array list
 */
void spArrayListDestroy(SPArrayList* src){
    if (src==NULL){
        return;
    }
    else{
        if(src->elements != NULL){
            free(src->elements);
        }
        free(src);
    }
    return;
}

/**
 * Clears all elements from the source array list. After invoking this function,
 * the size of the source list will be reduced to zero and maximum capacity is
 * not affected.
 * @param src - the source array list
 * @return
 * SP_ARRAY_LIST_INVALID_ARGUMENT if src == NULL
 * SP_ARRAY_LIST_SUCCESS otherwise
 */
SP_ARRAY_LIST_MESSAGE spArrayListClear(SPArrayList* src){
    if (src==NULL){
        return SP_ARRAY_LIST_INVALID_ARGUMENT;
    }
    for(int i=0; i<src->maxSize;i++){
        src->elements[i]=-1;
    }
    src->actualSize = 0;
    return SP_ARRAY_LIST_SUCCESS;
}

/**
 * Inserts element at a specified index. The elements residing at and after the
 * specified index will be shifted to make place for the new element. If the
 * array list reached its maximum capacity and error message is returned and
 * the source list is not affected
 * @param src   - the source array list
 * @param elem  - the new element to be inserted
 * @param index - the index where the new element will be placed. The index is
 *                0-based.
 * @return
 * SP_ARRAY_LIST_INVALID_ARGUMENT - if src == NULL or the index is out of bound
 * SP_ARRAY_LIST_FULL - if the source array list reached its maximum capacity
 * SP_ARRAY_LIST_SUCCESS - otherwise
 */
SP_ARRAY_LIST_MESSAGE spArrayListAddAt(SPArrayList* src, int elem, int index){
    if (src==NULL || index>src->actualSize || index<0){//elem?
        return SP_ARRAY_LIST_INVALID_ARGUMENT;
    }
    if (src->actualSize==src->maxSize){
        return SP_ARRAY_LIST_FULL;
    }
    int* arr = src->elements;
    if(src->actualSize==0){
        arr[0]=elem;
    }
    else{
        for(int i=src->actualSize ;i>index;i--){
            arr[i] = arr[i-1];
        }
        arr[index]=elem;
    }
    src->actualSize +=1;      //setting +1 to the arraySize
    return SP_ARRAY_LIST_SUCCESS;
}

/**
 * Inserts element at a the beginning of the source element. The elements
 * will be shifted to make place for the new element. If the
 * array list reached its maximum capacity and error message is returned and
 * the source list is not affected
 * @param src   - the source array list
 * @param elem  - the new element to be inserted
 * @return
 * SP_ARRAY_LIST_INVALID_ARGUMENT - if src == NULL or the index is out of bound
 * SP_ARRAY_LIST_FULL - if the source array list reached its maximum capacity
 * SP_ARRAY_LIST_SUCCESS - otherwise
 */
SP_ARRAY_LIST_MESSAGE spArrayListAddFirst(SPArrayList* src, int elem){
    if (src==NULL ||elem<0){//elem?
        return SP_ARRAY_LIST_INVALID_ARGUMENT;
    }
    if (src->actualSize==src->maxSize){
        return SP_ARRAY_LIST_FULL;
    }
    int* arr = src->elements;
    if(src->actualSize==0){
        arr[0]=elem;
    }
    else{
        for(int i=src->actualSize;i>0;i--){
            arr[i] = arr[i-1];
        }
        arr[0]=elem;
    }
    src->actualSize+=1;
    return SP_ARRAY_LIST_SUCCESS;
}

/**
 * Inserts element at a the end of the source element. If the array list
 * reached its maximum capacity and error message is returned and the source
 * list is not affected.
 * @param src   - the source array list
 * @param elem  - the new element to be inserted
 * @return
 * SP_ARRAY_LIST_INVALID_ARGUMENT - if src == NULL or the index is out of bound
 * SP_ARRAY_LIST_FULL - if the source array list reached its maximum capacity
 * SP_ARRAY_LIST_SUCCESS - otherwise
 */
SP_ARRAY_LIST_MESSAGE spArrayListAddLast(SPArrayList* src, int elem){
    if (src==NULL ||elem<0){//elem?
        return SP_ARRAY_LIST_INVALID_ARGUMENT;
    }
    if (src->actualSize==src->maxSize){
        return SP_ARRAY_LIST_FULL;
    }
    int* arr = src->elements;
    arr[src->actualSize]= elem;
    src->actualSize+=1;
    return SP_ARRAY_LIST_SUCCESS;
}

/**
 * Removes an element from a specified index. The elements residing after the
 * specified index will be shifted to make to keep the list continuous. If the
 * array list is empty then an error message is returned and the source list
 * is not affected
 * @param src   - The source array list
 * @param index - The index from where the new element will be removed.
 *                The index is 0-based.
 * @return
 * SP_ARRAY_LIST_INVALID_ARGUMENT - if src == NULL or the index is out of bound
 * SP_ARRAY_LIST_EMPTY - if the source array list is empty
 * SP_ARRAY_LIST_SUCCESS - otherwise
 */
SP_ARRAY_LIST_MESSAGE spArrayListRemoveAt(SPArrayList* src, int index){
	 if (src==NULL || index<0 || index>=src->actualSize){//elem?
	        return SP_ARRAY_LIST_INVALID_ARGUMENT;
	    }
	if (src->actualSize==0){
        return SP_ARRAY_LIST_EMPTY;
    }
    int* arr = src->elements;
    if (src->actualSize==1){
        arr[0]=-1;
    }
    else{
        for(int i=index;i<src->actualSize;i++){
            arr[i]=arr[i+1];
        }
        arr[src->actualSize-1]=-1;
    }
    src->actualSize-=1;
    return SP_ARRAY_LIST_SUCCESS;
}


/**
 * Removes an element from a the beginning of the list.
 * The elements will be shifted to make to keep the list continuous. If the
 * array list is empty then an error message is returned and the source list
 * is not affected
 * @param src   - The source array list
 * @param elem  - The new element to be inserted
 * @return
 * SP_ARRAY_LIST_INVALID_ARGUMENT - if src == NULL
 * SP_ARRAY_LIST_EMPTY - if the source array list is empty
 * SP_ARRAY_LIST_SUCCESS - otherwise
 */
SP_ARRAY_LIST_MESSAGE spArrayListRemoveFirst(SPArrayList* src){
	if (src==NULL){//elem?
	        return SP_ARRAY_LIST_INVALID_ARGUMENT;
	    }
	if (src->actualSize==0){
        return SP_ARRAY_LIST_EMPTY;
    }
    int* arr = src->elements;
    if (src->actualSize==1){
        arr[0]=-1;
    }
    else{
        for(int i=0;i<src->actualSize-1;i++){
            arr[i]=arr[i+1];
        }
        arr[src->actualSize-1]=-1;
    }
    src->actualSize-=1;
    return SP_ARRAY_LIST_SUCCESS;
}

/**
 * Removes an element from a the end of the list.
 * The elements will be shifted to make to keep the list continuous. If the
 * array list is empty then an error message is returned and the source list
 * is not affected
 * @param src   - The source array list
 * @param elem  - The new element to be inserted
 * @return
 * SP_ARRAY_LIST_INVALID_ARGUMENT - if src == NULL
 * SP_ARRAY_LIST_EMPTY - if the source array list is empty
 * SP_ARRAY_LIST_SUCCESS - otherwise.
 */
SP_ARRAY_LIST_MESSAGE spArrayListRemoveLast(SPArrayList* src){
	if (src==NULL){//elem?
	        return SP_ARRAY_LIST_INVALID_ARGUMENT;
	    }
	if (src->actualSize==0){
        return SP_ARRAY_LIST_EMPTY;
    }
    int* arr = src->elements;
    if (src->actualSize==1){
        arr[0]=-1;
    }
    else{
        arr[src->actualSize-1]=-1;
    }
    src->actualSize-=1;
    return SP_ARRAY_LIST_SUCCESS;
}

/**
 * Returns the element at the specified index. The function is called
 * with the assertion that all arguments are valid. If any of the arguments is
 * invalid then an undefined value is returned.
 * @param src - the source array list
 * @param index - the specified index, the index is 0-based.
 * @return
 * Undefined value if either src == NULL or index out of bound.
 * Otherwise, the element at the specified index is returned.
 */
int spArrayListGetAt(SPArrayList* src, int index){
    if(src==NULL||index<0||index>=src->actualSize){
        return -2;                                  //not to be confused with -1 == the empty cell
    }
    int* arr = src->elements;
    return arr[index];
}

/**
 * Returns the element at the beginning of the list. The function is called
 * with the assertion that all arguments are valid. If any of the arguments is
 * invalid then an undefined value is returned.
 * @param src - the source array list
 * @return
 * Undefined value if either src == NULL or the list is empty
 * Otherwise, the element at the beginning of the list is returned.
 */
int spArrayListGetFirst(SPArrayList* src){
    if(src==NULL||src->actualSize==0){
        return -2;
    }
    int* arr = src->elements;
    return arr[0];
}

/**
 * Returns the element at the end of the list. The function is called
 * with the assertion that all arguments are valid. If any of the arguments is
 * invalid then an undefined value is returned.
 * @param src - the source array list
 * @return
 * Undefined value if either src == NULL or the list is empty
 * Otherwise, the element at the end of the list is returned.
 */
int spArrayListGetLast(SPArrayList* src){
    if(src==NULL||src->actualSize==0){
        return -2;
    }
    int* arr = src->elements;
    return arr[src->actualSize-1];
}
/**
 * Returns the maximum capacity of the list. The function is called
 * with the assertion that all arguments are valid. If any of the arguments is
 * invalid then an undefined value is returned.
 * @param src - the source array list
 * @return
 * Undefined value if either src == NULL
 * Otherwise, the maximum capacity of the list is returned.
 */
int spArrayListMaxCapacity(SPArrayList* src){
    if(src==NULL){
        return -2;
    }
    return src->maxSize;
}

/**
 * Returns the number of elements in the list. The function is called
 * with the assertion that all arguments are valid. If any of the arguments is
 * invalid then an undefined value is returned.
 * @param src - the source array list
 * @return
 * Undefined value if either src == NULL
 * Otherwise, the number of the elements in the list is returned.
 */
int spArrayListSize(SPArrayList* src){
    if(src==NULL){
        return -2;
    }
    return src->actualSize;
}

/**
 * Returns true if the list is full, that is the number of elements in the list
 * equals its maximum capacity.
 * @param src - the source array list
 * @return
 * false if either src == NULL or the number of elements in the list is less
 * than its maximum capacity.
 * Otherwise, true is returned.
 */
bool spArrayListIsFull(SPArrayList* src){
    if(src==NULL||src->actualSize<src->maxSize){
        return false;
    }
    assert(src->actualSize==src->maxSize);    //to make sure it's the same size - not suppose to ever act
    return true;;
}

/**
 * Returns true if the list is empty, that is the number of elements in the list
 * equals to zero.
 * @param src - the source array list
 * @return
 * false if either src == NULL or the number of elements in the list is not zero.
 * Otherwise, true is returned.
 */
bool spArrayListIsEmpty(SPArrayList* src){
    if(src==NULL||src->actualSize>0){
        return false;
    }
    assert(src->actualSize==0);       //to make sure it's the same size - not suppose to ever act
    return true;
}
