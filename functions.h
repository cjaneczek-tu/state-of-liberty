/*
    Name of file	:	functions.h
	Author			:	Christian Janeczek <cjaneczek@tgm.ac.at>
	Version			:	2014-10-01
	Description		:	Headerfile, which contains the required function-header for the state machines
 */

#ifndef _functions_h_
#define _functions_h_

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

#endif