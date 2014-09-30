#include <stdio.h>
#include <stdlib.h>

typedef enum
{
  GREEN,
  GREEN_BLINKING,
  YELLOW,
  YELLOW_BLINKING,
  RED,
  RED_AND_YELLOW
}TrafficLightState;

typedef enum
{
	STANDBY,
	GO,
	PREPARETOSTOP,
	STOP,
	WAIT,
	IDLE,
	REPEAT
}Command;

TrafficLightState streetLamp(Command, TrafficLightState);
Command commandswitch(int);



/*
  Name of file	: main.c
  Author	: Wolfgang Mair
  Version	: 2014-09-23
  Description	: A Programm which imitates the states of an traffic lamp
*/



int main(int argc, char* argv[])
{
	TrafficLightState t = RED_AND_YELLOW;
	Command c = GO;
	int z = NULL;

	printf("\nThe red and yellow lights are shining!\n\n");
	while (1){
		printf("Geben sie eine Zahl ein:\n");
		printf("1 ... Gruen!\n");
		printf("2 ... Gruen blinkend!\n");
		printf("3 ... Gelb!\n");
		printf("4 ... Rot!\n");
		printf("5 ... Rot und Gelb!\n");
		printf("6 ... Gelb blinkend!\n");
		printf("7 ... Blinken!\n\n");
		scanf("%d",&z);
		c = commandswitch(z);
		t = streetLamp(c,t);

	}

	EXIT_SUCCESS;
}

TrafficLightState streetLamp(Command c, TrafficLightState t)
{
	switch(t)
		{
			case GREEN:
				if(c == PREPARETOSTOP){
					t = GREEN_BLINKING;
					printf("\nThe green light starts blinking!\n\n");
					break;
				}
				if(c == REPEAT){
					t = GREEN_BLINKING;
					printf("\nThe green light blinks!");
				}
				printf("\nThe green light still shines brightly!\n\n");
				break;

			case GREEN_BLINKING:
				if(c == STOP){
					t = YELLOW;
					printf("\nThe green light turns off and the yellow light starts to shine!\n\n");
					break;
				}
				if(c == REPEAT){
					t = GREEN_BLINKING;
					printf("\nThe green light blinks!\n\n");
					break;
				}
				printf("\nThe green light is still blinking brightly!\n\n");
				break;

			case YELLOW:
				if(c == WAIT){
					t = RED;
					printf("\nThe yellow light turns off and the red light starts to shine!\n\n");
					break;
				}
				printf("\nThe yellow light still shines brightly!\n\n");
				break;

			case YELLOW_BLINKING:
				if(c == WAIT){
					t = RED;
					printf("\nThe yellow light turns off and the red light starts to shine!\n\n");
					break;
				}
				if(c == REPEAT){
					t = YELLOW_BLINKING;
					printf("\nThe yellow light blinks!");
				}
				printf("\nThe yellow light is still blinking brightly!\n\n");
				break;

			case RED:
				if(c == STANDBY)
				{
					t = RED_AND_YELLOW;
					printf("\nThe red and yellow light starts shining!\n\n");
					break;
				}

				if(c == IDLE)
				{
					t = YELLOW_BLINKING;
					printf("\nThe yellow light starts blinking!\n\n");
					break;
				}

				printf("\nThe red light still shines brightly!\n\n");
				break;

			case RED_AND_YELLOW:
				if(c == GO){
					t = GREEN;
					printf("\nThe red and yellow light turns off and the green light starts to shine!\n\n");
					break;
				}
				printf("\nThe red and yellow light still shines brightly!\n\n");
				break;

			default:
				t = YELLOW_BLINKING;
				printf("\nThe yellow light starts blinking!\n\n");
				break;
				
	}

	return t;
}

Command commandswitch (int z)
{
	Command c;

	switch(z)
	{
			case 1:
				c = GO;
				break;

			case 2:
				c = PREPARETOSTOP;
				break;

			case 3:
				c = STOP;
				break;

			case 4:
				c = WAIT;
				break;

			case 5:
				c = STANDBY;
				break;

			case 6:
				c = IDLE;
				break;

			case 7: 
				c = REPEAT;
				break;

			default:
				c = IDLE;
				break;
	}
}