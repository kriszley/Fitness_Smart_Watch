/*
 * goal_screen.c
 *
 *  Created on: Feb 11, 2018
 *      Author: Roy
 */

#include "goal_screen.h"

#include "../gui.h"
#include "../hardware_drivers/Touch.h"
#include <limits.h>
#include <stdio.h>

//global
int time_goal = 0;
int dist_goal = 0;

//internal
unsigned int cur_goal_10x = 10; // X.Y
unsigned int cur_goal_time = 10; // mins
enum {TIME, DISTANCE} goal_type = TIME;
int update_screen = 0;

void draw_goal_screen_base(void){
	initBackground();
	//title top
	print_string_lcd(10, 10, WHITE, BLACK, "Exercise Tracking", 17, 0, 4,0);
	draw_button_back(X0,Y7);
	draw_button_start(X7,Y7);
	//row 2
	print_string_lcd(10, Y2+20, WHITE, BLACK, "Goal type:", 10, 0, 2,0);
	draw_button_left(X2,Y2);
	draw_button_right(X5,Y2);
	//row 4
	if (goal_type == TIME){
		print_string_lcd(10, Y4+20, WHITE, BLACK, "Duration:", 9,0,2,0);
	}
	else if (goal_type == DISTANCE) {
		print_string_lcd(10, Y4+20, WHITE, BLACK, "Distance:", 9,0,2,0);
	}
	draw_button_left(X2,Y4);
	draw_button_right(X5,Y4);
}

void draw_goal_screen(void){
	draw_goal_screen_base();
	draw_new_screen();
	update_screen = 1;
	return;
}
void update_goal_screen(void){
	if (goal_type == TIME){
		if (update_screen){
			draw_goal_screen_base();
			// goal type
			print_string_lcd((X2+X5)/2+20, Y2+20, WHITE, BLACK, "Time", 4,0,2,0);
			//value
			char buf[13];
			sprintf(buf, "%d Minutes", cur_goal_time);
			print_string_lcd(X3+20, Y4+20, WHITE, BLACK, buf, 12,0,2,0);
			draw_new_screen();
		}
	}
	else if (goal_type == DISTANCE) {
		if (update_screen){
			draw_goal_screen_base();
			//goal type
			print_string_lcd((X2+X5)/2, Y2+20, WHITE, BLACK, "Distance", 9,0,2,0);
			//value
			char buf[10];
			int end = sprintf(buf, "%d", cur_goal_10x/10);
			sprintf(&buf[end], ".%d Km", cur_goal_10x%10);
			print_string_lcd((X2+X5)/2, Y4+20, WHITE, BLACK, buf, 8,0,2,0);
			draw_new_screen();
		}
	}
	update_screen = 0;
	return;
}
void handle_touch_goal_screen (Screen *switch_to_screen){
	if (pressed == 1){
		if ((touchY == 2) && (touchX == 2 || touchX == 5)){
			goal_type = !goal_type;
			update_screen = 1;
		}
		else if (touchX == 2 && touchY == 4){
			if (cur_goal_10x > 5 && goal_type == DISTANCE){
				cur_goal_10x -= 5;
			}
			else if (cur_goal_time > 10 && goal_type == TIME){
				cur_goal_time -= 10;
			}
			update_screen = 1;
		}
		else if (touchX == 5 && touchY == 4){
			if (goal_type == DISTANCE){
				cur_goal_10x += 5;
			}
			else if(goal_type == TIME){
				cur_goal_time += 10;
			}
			update_screen = 1;
		}
		else if (touchX == 0 && touchY == 7){
			*switch_to_screen = CLOCK_s;
		}
		else if (touchX == 7 && touchY == 7){
			if (goal_type == DISTANCE){
				time_goal = 0;
				dist_goal = cur_goal_10x;
			}
			else if(goal_type == TIME){
				time_goal = cur_goal_time;
				dist_goal = 0;
			}
			*switch_to_screen = BIO_s;
		}
	}
	return;
}
