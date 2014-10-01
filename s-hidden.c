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
#include "functions.h"

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