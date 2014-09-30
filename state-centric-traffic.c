/*
    Name of file	:	state-centric-traffic.c
	Author			:	Christian Janeczek <cjaneczek@tgm.ac.at>
	Version			:	2014-09-29
	Description		:	The state centric solution of the traffic light system
 */
  
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

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
	int c = 0;
	int error_got_a_problem = 0;
	bool error = true;
	
	while(1){
		switch(state){
		case GREEN: 
			if(command==PREPARE_TO_STOP){
	    	printf("STATE: GREEN \n");
	    	/*For a more efficient display of the output,
	    	 I put the system to sleep for 2000 milliseconds,
	    	  right after each printf*/
	    	sleep(1);
			state = BLINKING_GREEN;
			command = REPEAT;
			}
			break;
		case BLINKING_GREEN:
			if(c<=4){
				if(command==REPEAT){
				printf("STATE: BLINKING GREEN \n");
				sleep(1);
				c = c+1;
				if(c==4){
					command = STOP;
				}
				if(command==STOP){
				state = YELLOW;
				c = 0;
				command = WAIT;
				}
				}
			}
			break;
		case YELLOW:
		    if(command==WAIT){
			printf("STATE: YELLOW \n");
			sleep(1);
			state = RED;
			command = STANDBY;
			}
			break;
		case RED:
			if(command==IDLE){
				printf("STATE: RED \n");
				sleep(1);
				state = BLINKING_YELLOW;
				command = RESET;
				error_got_a_problem=0;
				error=false;
			}
			if(error_got_a_problem==7){
				command = IDLE;

			}
			if(command==STANDBY){
			printf("STATE: RED \n");
			sleep(1);
			state = RED_AND_YELLOW;
			command = GO;
			}
			break;
		case RED_AND_YELLOW:
			if(command==GO){
			printf("STATE: RED_AND_YELLOW \n");
			sleep(1);
			state = GREEN;
			command = PREPARE_TO_STOP;
			/* An error occurs one time, showing that the state will have the following order:
			   RED - BLINKING YELLOW - RED */
			if(error==true){
				error_got_a_problem=7;
			}
			}
			break;
		case BLINKING_YELLOW:
			if(command==RESET){
			printf("STATE: BLINKING_YELLOW \n");
			sleep(1);
			state = RED;
			command = STANDBY;
			}
			break;	
		}
	}
	EXIT_SUCCESS;
}