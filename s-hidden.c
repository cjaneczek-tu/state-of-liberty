/*
    Name of file	:	s-hidden.c
	Author			:	Christian Janeczek <cjaneczek@tgm.ac.at>
	Version			:	2014-09-30
	Description		:	The state centric solution of the traffic light system, with hidden transitions
 */
  
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

 /* defining the required enums */
typedef enum {GREEN, BLINKING_GREEN, YELLOW, BLINKING_YELLOW, RED, RED_AND_YELLOW} State;
typedef enum {WAIT, STANDBY, GO, PREPARE_TO_STOP, REPEAT, STOP, RESET, IDLE} Command;
/*  method-prototypes */
State outStating(Command, State, bool, bool, bool);
State switchState(Command, State);
Command switchCommand(int);
State nextState(State);
bool greenOn(bool);
bool yellowOn(bool);
bool redOn(bool);
bool greenOff(bool);
bool yellowOff(bool);
bool redOff(bool);
bool blinkingGreen(bool);
bool blinkingYellow(bool);  

/*
* the main-method
*/		
int main(int argc, char* argv[])
{
	State state = GREEN;
	Command command = PREPARE_TO_STOP;
	bool greenLight = true;
	bool redLight = false;
	bool yellowLight = false;

	while (1){

		state = outStating(command,state,greenLight,yellowLight,redLight);

	}

	EXIT_SUCCESS;
}

/*
* This very method switches between the states of the traffic and manages the various lights
* As seen under the 'Hidden Transactions' section of 'Embedded Systems'
* 
*/
State outStating(Command c, State state, bool greenLight, bool yellowLight, bool redLight)
{
	switch(state)
		{
			case GREEN:
				printf("\n---GREEN---\n");
				sleep(1);
				greenLight = greenOn(greenLight);
				state = nextState(state);
				greenLight = greenOff(greenLight);
				break;

			case BLINKING_GREEN:
				printf("\n---BLINKING_GREEN---\n");
				sleep(1);
				greenLight = blinkingGreen(greenLight);
				state = nextState(state);
				// greenLight = greenOff(greenLight);
				break;

			case YELLOW:
				printf("\n---YELLOW---\n");
				sleep(1);
				yellowLight = yellowOn(yellowLight);
				state = nextState(state);
				yellowLight = yellowOff(yellowLight);
				break;

			// case BLINKING_YELLOW:
			// 	// yellowLight = blinkingYellow(yellowLight);
			// 	// state = nextState(state);
			// 	// yellowLight = yellowOff(yellowLight);
			// 	break;

			case RED:
				printf("\n---RED---\n");
				sleep(1);
				redLight = redOn(redLight);
				state = nextState(state);
				redLight = redOff(redLight);
				break;

			case RED_AND_YELLOW:
				printf("\n---RED_AND_YELLOW---\n");
				sleep(1);
				redLight = redOn(redLight);
				yellowLight = yellowOn(yellowLight);
				state = nextState(state);
				redLight = redOff(redLight);
				yellowLight = yellowOff(yellowLight);
				break;

			default:
				printf("\n---BLINKING_YELLOW---\n");
				sleep(1);
				redLight = redOff(redLight);
				greenLight = greenOff(greenLight);
				yellowLight = blinkingYellow(yellowLight);
				state = BLINKING_YELLOW;
				break;
	}
	return state;
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