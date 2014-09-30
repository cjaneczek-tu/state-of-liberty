/*
    Name of file	:	state-centric.c
	Author			:	Christian Janeczek <cjaneczek@tgm.ac.at>
	Version			:	2014-09-29
	Description		:	The state centric solution of the traffic light system
 */
  
#include <stdio.h>
#include <stdlib.h>

 /* defining the required enums */
typedef enum {GREEN, BLINKING_GREEN, YELLOW, BLINKING_YELLOW, RED, RED_AND_YELLOW} State;
typedef enum {WAIT, STANDBY, GO, PREPARE_TO_STOP, REPEAT, STOP, RESET, IDLE} Command;
/*  method-prototypes */
State switchState(Command, State);
Command switchCommand(int); 

int main(int argsc, char* argv[])
{
	State state = GREEN;
	Command command = PREPARE_TO_STOP;
	
	while(1){
		switch(state){
		case (GREEN): 
			if(command==PREPARE_TO_STOP){
			printf("STATE: GREEN");
			state = BLINKING_GREEN;
			command = REPEAT;
			/* start timer ... */
			break;
			}
		case (BLINKING_GREEN):
			if(c<=4){
				if(command==REPEAT){
				printf("STATE: BLINKING GREEN");
				c = c+1;
				if(c==4){
				command = STOP;
				}
				break;
				}
			}
			if(command==STOP){
			state = YELLOW;
			c = 0;
			command = WAIT;
			break;
			}
		case (YELLOW):
			if(command==WAIT){
			printf("STATE: YELLOW");
			state = RED;
			command = STANDBY;
			break;
			}
		case (RED):
			if(command==STANDBY){
			printf("STATE: RED");
			state = RED_AND_YELLOW;
			command = GO;
			break;
			}
			if(command==IDLE){
			printf("STATE: BLINKING_YELLOW");
			state = BLINKING_YELLOW;
			command = RESET;
			break;
			}
		case (RED_AND_YELLOW):
			if(command==GO){
			printf("STATE: RED_AND_YELLOW");
			state = GREEN;
			break;
			}
		case (BLINKING_YELLOW):
			if(command==RESET){
			printf("STATE: BLINKING_YELLOW");
			state = RED;
			command = STANDBY;
			break;
			}	
	}
	EXIT_SUCCESS;
}
