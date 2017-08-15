/*
 * TesterParser.c
 *
 *  Created on: 13 αιεπι 2017
 *      Author: Itamar
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "SPFIARParser.h"


void someFunc(){
	SPCommand CMD;
	SP_COMMAND command;
	//char* message;
	setvbuf (stdout, NULL, _IONBF, 0);
	fflush(stdout);
	char buf[1024];
	printf("please write the command:\n");
	scanf("%s",buf);
	CMD = spParserPraseLine(buf);
	command = CMD.cmd;
	fflush(stdout);
	if (command==SP_SUGGEST_MOVE)printf("suggest move");

	//char* message;
	setvbuf (stdout, NULL, _IONBF, 0);
	fflush(stdout);

	printf("please write the command:\n");
	scanf("%s",buf);
	printf("buf is: %s\n",buf);
	CMD = spParserPraseLine(buf);
	command = CMD.cmd;
	fflush(stdout);
	if (command==SP_QUIT)printf("la la land");
	else if (command==SP_SUGGEST_MOVE)printf("sa sa land");
	else (printf("notnot land"));
}
