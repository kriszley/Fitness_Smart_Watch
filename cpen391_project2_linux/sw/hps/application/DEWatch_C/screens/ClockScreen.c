/*
 * FirstScreen.c
 *
 *  Created on: Jan 31, 2018
 *      Author: Rouyeen
 */

#include "ClockScreen.h"

#include <string.h>
#include "../time/time24h.h"
#include "../gui.h"
#include "../hardware_drivers/Touch.h"

#define CLOCK_SCREEN_BACKGROUND WHITE
#define CLOCK_SCREEN_FORGROUND WHITE
#define CLOCK_Y 215


time_t prev_time;
int tick = 1;// flag for ticking the middle colon every second

void draw_clock_screen_base(void){
	initBackground(); // Initialize background
	draw_button_settings(X0,Y0);
	draw_button_running(X7,Y7);
	draw_button_history(X6,Y7);
}

//cleanup and show the clock screen for the first time
void draw_clock_screen(void){

	draw_clock_screen_base();

	// draw time and date for the first time
	char time_str[26];
	get_time_str(time_str);
	OutGraphicsCharFont5(270,CLOCK_Y, CLOCK_SCREEN_FORGROUND, CLOCK_SCREEN_BACKGROUND, time_str[11], 0);
	OutGraphicsCharFont5(270+38,CLOCK_Y, CLOCK_SCREEN_FORGROUND, CLOCK_SCREEN_BACKGROUND, time_str[12], 0);
	OutGraphicsCharFont5(270+38*2,CLOCK_Y, CLOCK_SCREEN_FORGROUND, CLOCK_SCREEN_BACKGROUND, ':', 0);
	OutGraphicsCharFont5(270+38*3,CLOCK_Y, CLOCK_SCREEN_FORGROUND, CLOCK_SCREEN_BACKGROUND, time_str[14], 0);
	OutGraphicsCharFont5(270+38*4,CLOCK_Y, CLOCK_SCREEN_FORGROUND, CLOCK_SCREEN_BACKGROUND, time_str[15], 0);
	print_string_lcd(295, 280, CLOCK_SCREEN_FORGROUND, CLOCK_SCREEN_BACKGROUND, time_str, 10, 0, 2, 2);

	prev_time = cur_time;
	draw_new_screen();
	return;
}

// update the screen if it is already showing the clock
void update_clock_screen (void){
	// flashing seconds
	if (prev_time != cur_time){
		draw_clock_screen_base();
		if (tick == 1){
//			redrawBackground(270+38*2, (310+38*2)+38, CLOCK_Y, CLOCK_Y + 59);
			OutGraphicsCharFont5(270+38*2,CLOCK_Y, CLOCK_SCREEN_FORGROUND, CLOCK_SCREEN_BACKGROUND, ' ', 0);
			tick = 0;
		}
		else {
//			redrawBackground(270+38*2, (310+38*2)+38, CLOCK_Y, CLOCK_Y + 59);
			OutGraphicsCharFont5(270+38*2,CLOCK_Y, CLOCK_SCREEN_FORGROUND, CLOCK_SCREEN_BACKGROUND, ':', 0);
			tick = 1;
		}

		//rest of the clock
		char time_str[26];
		get_time_str(time_str);
		OutGraphicsCharFont5(270,CLOCK_Y, CLOCK_SCREEN_FORGROUND, CLOCK_SCREEN_BACKGROUND, time_str[11], 0);
		OutGraphicsCharFont5(270+38,CLOCK_Y, CLOCK_SCREEN_FORGROUND, CLOCK_SCREEN_BACKGROUND, time_str[12], 0);
		OutGraphicsCharFont5(270+38*3,CLOCK_Y, CLOCK_SCREEN_FORGROUND, CLOCK_SCREEN_BACKGROUND, time_str[14], 0);
		OutGraphicsCharFont5(270+38*4,CLOCK_Y, CLOCK_SCREEN_FORGROUND, CLOCK_SCREEN_BACKGROUND, time_str[15], 0);
		print_string_lcd(295, 280, CLOCK_SCREEN_FORGROUND, CLOCK_SCREEN_BACKGROUND, time_str, 10, 0, 2, 2);

		prev_time = cur_time;
		draw_new_screen();
	}
	return;
}

void handle_touch_clock_screen (Screen *switch_to_screen){
	if (pressed == 1){
		if (touchX == 7 && touchY == 7){
			*switch_to_screen = GOAL_s;
		}
		else if (touchX == 0 && touchY == 0){
			*switch_to_screen = STARTUP_s;//TODO: maybe add more settings
		}
		else if (touchX == 6 && touchY == 7){
			*switch_to_screen = HISTORY_s;
		}
	}
}
