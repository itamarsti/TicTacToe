#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "SPFIARParser.h"
#include <stdio.h>


bool spParserIsInt(const char* str){
    int index = 0;
    int validNum;
    while(str[index]!='\0'){
        if(str[index]=='\n'){
            index++;
            continue;
        }
        validNum = str[index]-'0';
        if(str[0]=='-' && strlen(str)>1 &&index==0){
            index++;
            continue;
        }
        else if(validNum<0 || validNum>9)return false;
        index++;
    }
    return true;
}

SPCommand spParserPraseLine(const char* str){
    setvbuf (stdout, NULL, _IONBF, 0);
    SPCommand spc;
    spc.validArg = false;
    char stringDup[SP_MAX_LINE_LENGTH];
    strcpy(stringDup,str);
    char *token = strtok(stringDup, "\t\r\n ");
    if(token==NULL){
        spc.cmd= SP_INVALID_LINE;
        return spc;
    }
    if(strcmp(token, "suggest_move")==0){
        spc.cmd = SP_SUGGEST_MOVE;}
    else if(strcmp(token, "undo_move")==0){
        spc.cmd = SP_UNDO_MOVE;}
    else if(strcmp(token,"quit")==0){
        spc.cmd = SP_QUIT;}
    else if(strcmp(token, "restart_game")==0){
        spc.cmd = SP_RESTART;}
    else if(strcmp(token,"add_disc")==0){
        token = strtok(NULL, "\t\r\n ");
        if(token==NULL || !spParserIsInt(token)){
            spc.cmd= SP_INVALID_LINE;
            return spc;
        }
        else if(spParserIsInt(token))
            spc.cmd= SP_ADD_DISC;
        spc.arg = atoi(token);
        spc.validArg = true;
    }
    else{
        spc.cmd= SP_INVALID_LINE;
        return spc;}
    token = strtok(NULL, "\t\r\n ");
    if(token!=NULL){
        spc.cmd= SP_INVALID_LINE;
        spc.validArg = false;
    }
    return spc;
}
