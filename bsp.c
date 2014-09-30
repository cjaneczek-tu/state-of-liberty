/*
    Name of file	:	state-centric.c
	Author			:	Christian Janeczek <cjaneczek@tgm.ac.at>
	Version			:	2014-09-29
	Description		:	The state centric solution of the traffic light system
 */
  
#include <stdio.h>
#include <stdlib.h>

 /* prototypes */
static int c = 0;
typedef enum {GREEN, BLINKING_GREEN, YELLOW, BLINKING_YELLOW, RED, RED_AND_YELLOW} state;
typedef enum {WAIT, STANDBY, GO, PREPARE_TO_STOP, REPEAT, STOP, RESET, IDLE} command;
int main(int argsc, char* argv[])
{
	printf("Hello world");
	EXIT_SUCCESS;
}