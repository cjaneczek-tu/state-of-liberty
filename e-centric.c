/*
    Name of file	:	s-hidden.c
	Author			:	Christian Janeczek <cjaneczek@tgm.ac.at>
	Version			:	2014-10-01
	Description		:	The event centric solution of the traffic light system
 */
  
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

 /* defining the required enums */
typedef enum {GREEN, BLINKING_GREEN, YELLOW, BLINKING_YELLOW, RED, RED_AND_YELLOW} State;
typedef enum {WAIT, STANDBY, GO, PREPARE_TO_STOP, REPEAT, STOP, RESET, IDLE} Command;

/* method prototypes*/
State nextState(State);
bool greenOn(bool);
bool yellowOn(bool);
bool redOn(bool);
bool greenOff(bool);
bool yellowOff(bool);
bool redOff(bool);
bool blinkingGreen(bool);
bool blinkingYellow(bool);  

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

/*
* Taking the following state 
*/
State nextState(State s){
	switch(s){
		case GREEN:
			s = BLINKING_GREEN;
			break;

		case BLINKING_GREEN:
			s = YELLOW;
			break;

		case YELLOW:
			s = RED;
			break;

		case RED:
			s = RED_AND_YELLOW;
			break;

		case RED_AND_YELLOW:
			s = GREEN;
			break;

		default:
			s = RED;
			break;
	}
	return s;
}

/*
* Turns ON the green light
*/
bool greenOn(bool greenLight){
	if(greenLight == false){
		greenLight = true;
		printf("\nGREEN ON!\n");
		sleep(1);
	}
	return greenLight;	
}

/*
* Turns OFF the green light
*/
bool greenOff(bool greenLight){
	if(greenLight == true){
		greenLight = false;
		printf("\nGREEN OFF!\n");
		sleep(1);
	}
	return greenLight;
}

/*
* Turns ON the yellow light
*/
bool yellowOn(bool yellowLight){
	if(yellowLight == false){
		yellowLight = true;
		printf("\nYELLOW ON!\n");
		sleep(1);
	}
	return yellowLight;
}

/*
* Turns OFF the yellow light
*/
bool yellowOff(bool yellowLight){
	if(yellowLight == true){
		yellowLight = false;
		printf("\nYELLOW OFF!\n");
		sleep(1);
	}
	return yellowLight;
}

/*
* Turns ON the red light
*/
bool redOn(bool redLight){
	if(redLight == false){
		redLight = true;
		printf("\nRED ON!\n");
		sleep(1);
	}
	return redLight;
}

/*
* Turns OFF the red light
*/
bool redOff(bool redLight){
	if(redLight == true){
		redLight = false;
		printf("\nRED OFF!\n");
		sleep(1);
	}
	return redLight;
}

/*
* Frequently turning the green light ON and OFF again!
*/
bool blinkingGreen(bool greenLight){
	printf("\nGREEN ON!\n");
	sleep(1);
	printf("\nGREEN OFF!\n");
	sleep(1);
	printf("\nGREEN ON!\n");
	sleep(1);
	printf("\nGREEN OFF!\n");
	sleep(1);
	greenLight = true;
	return greenLight;
}

/*
* Frequently turning the yellow light ON and OFF again!
*/
bool blinkingYellow(bool yellowLight){
	printf("\nYELLOW ON!\n");
	sleep(1);
	printf("\nYELLOW OFF!\n");
	sleep(1);
	printf("\nYELLOW OFF!\n");	
	sleep(1);
	printf("\nYELLOW ON!\n");
	yellowLight = true;
	return yellowLight;
}