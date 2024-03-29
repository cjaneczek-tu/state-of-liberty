/*
    Name of file	:	e-centric.c
	Author			:	Christian Janeczek <cjaneczek@tgm.ac.at>
	Version			:	2014-10-01
	Description		:	The event centric solution of the traffic light system
 */
  
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "functions.h" 

int main(int argsc, char* argv[])
{
	State state = GREEN;
	Command command = PREPARE_TO_STOP;
	int c = 0;
	int error_got_a_problem = 0;
	bool error = true;
	bool greenLight = false;
	bool redLight = false;
	bool yellowLight = false;
	
	while(1){
		switch(command){
		case PREPARE_TO_STOP: 
			if(state==GREEN){
	    	printf("\nSTATE: GREEN \n");
	    	/*For a more efficient display of the output,
	    	 I put the system to sleep for 2000 milliseconds,
	    	  right after each printf*/
	    	sleep(1);
	    	greenLight = greenOn(greenLight);
	    	state = nextState(state);
			command = REPEAT;
			}
			break;
		case REPEAT:
			if(c<=4){
				if(state==BLINKING_GREEN){
				greenLight = greenOn(greenLight);
				printf("\nSTATE: BLINKING GREEN \n");
				sleep(1);
				greenLight = greenOff(greenLight);
				c = c+1;
				if(c==4){
					/*LEFT OFF HERE, NOT KNOWING WHAT TO DO*/
					command = STOP;
				}
				if(command==STOP){
				state = nextState(state);
				c = 0;
				command = WAIT;
				}
				}
			}
			break;
		case STOP:
			state = nextState(state);
			c=0;
			command = WAIT;
			break;
		case WAIT:
		    if(state==YELLOW){
			printf("\nSTATE: YELLOW \n");
			sleep(1);
			yellowLight = yellowOn(yellowLight);
			state = nextState(state);
			command = STANDBY;
			yellowLight = yellowOff(yellowLight);
			}
			break;
		case STANDBY:
			if(state==RED){
				printf("\nSTATE: RED \n");
				sleep(1);
				redLight = redOn(redLight);
				state = nextState(state);
				command = GO;
				redLight = redOff(redLight);
				error_got_a_problem=0;
				error=false;
			}
			if(error_got_a_problem==7){
				command = IDLE;

			}
			if(state==RED){
			printf("\nSTATE: RED \n");
			sleep(1);
			state = nextState(state);
			command = GO;
			}
			break;
		case IDLE:
			if(error_got_a_problem==7){
				state = BLINKING_YELLOW;
			}
			break;
		case GO:
			if(state==RED_AND_YELLOW){
			printf("\nSTATE: RED_AND_YELLOW \n");
			sleep(1);
			redLight = redOn(redLight);
			yellowLight = yellowOn(yellowLight);
			state = nextState(state);
			command = PREPARE_TO_STOP;
			redLight = redOff(redLight);
			yellowLight = yellowOff(yellowLight);
			/* An error occurs one time, showing that the state will have the following order:
			   RED - BLINKING YELLOW - RED */
			if(error==true){
				error_got_a_problem=7;
			}
			}
			break;
		case RESET:
			if(state==BLINKING_YELLOW){
			printf("\nSTATE: BLINKING_YELLOW \n");
			sleep(1);
			yellowLight = blinkingYellow(yellowLight);
			state = nextState(state);
			command = STANDBY;
			}
			break;	
		}
	}
	EXIT_SUCCESS;
}