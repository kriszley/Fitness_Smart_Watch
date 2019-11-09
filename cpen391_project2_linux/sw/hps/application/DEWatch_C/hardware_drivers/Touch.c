/*
 * touch.c
 *
 *  Created on: Jan 29, 2018
 *      Author: Eric/Roy
 */
#include "Touch.h"
#include <stdio.h>


typedef enum {SYNC_S, DATAX1_S, DATAX2_S, DATAY1_S, DATAY2_S} touch_state_t;
typedef enum {PRESS_S, RELEASE_S} touch_state_mode_t;

volatile unsigned char after_touch;

touch_state_t touch_s = SYNC_S;
touch_state_mode_t touch_s_mode = PRESS_S;

int newX;
int newY;

volatile int touchX;
volatile int touchY;
volatile int pressed;
volatile int touch_filter_on;

FILE *touch_fd;


/*****************************************************************************
** Initialise touch screen controller
*****************************************************************************/
/*The host should be configured for 9600 BAUD, 8 data bits and 1 Stop bit.*/
void Init_touch (void){
	  touch_fd = fopen("/proc/touch", "r");
	  if (touch_fd== NULL)
		  printf("ERROR: could not open \"/dev/touch\"...\n");
	  return;
}


// reads the buffer and interprets the data
int handle_data_touch (void){
	char data;

	while (1){
		int read = fread(&data, sizeof(char), 1, touch_fd);
		if( read == 0)
			return 0;
		switch (touch_s){
			case SYNC_S:
				if (data == RELEASE_SYNC){ //press
					touch_s_mode = RELEASE_S;
					touch_s = DATAX1_S;
				}
				else if (data == PRESS_SYNC){
					touch_s_mode = PRESS_S;
					touch_s = DATAX1_S;
				}
				else {
					touch_s = SYNC_S;
				}
			break;

			case DATAX1_S:
				newX = data&0x7F;
				touch_s = DATAX2_S;
			break;

			case DATAX2_S:
				newX += ((int)data&0x1F)<<7;
				touch_s = DATAY1_S;
			break;

			case DATAY1_S:
				newY = data&0x7F;
				touch_s = DATAY2_S;
			break;

			case DATAY2_S:
				newY += ((int)data&0x1F)<<7;
				if (touch_s_mode == PRESS_S){
					if (pressed != 1 && touch_filter_on == 0){
						touchX = newX>>9;
						touchY = newY>>9;
					}
				}
				else if (touch_s_mode == RELEASE_S){
//					if (touch_filter_on == 0){
						pressed = 1;
//						set_touch_filter();
//					}
				}
				touch_s = SYNC_S;
			break;

			default:
				touch_s = SYNC_S;
			break;
		}
	}
	return 0;
}
