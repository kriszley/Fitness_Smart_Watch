/*
 * summary_screen.c
 *
 *  Created on: Feb 13, 2018
 *      Author: Roy
 */

#include "summary_screen.h"

#include "../hardware_drivers/Touch.h"
#include "../gui.h"
#include <string.h>
#include <stdio.h>

double s_total_dist;
int s_avg_hr;
int s_avg_o2;
int s_duration;


void draw_summary_screen(void){
	printf("reached\n");
	initBackground();
	draw_button_back(X0,Y7); //back
	print_string_lcd(10, 10, WHITE, BLACK, "Exercise Summary", 16, 0, 4,0); //title

	// get the distance
	print_string_lcd(70, 70, WHITE, BLACK, "Distance Finished",17, 0,3, 0);
	char Current_dis[6];

	snprintf(Current_dis,6,"%f",s_total_dist);
	print_string_lcd(400, 70, WHITE, BLACK,Current_dis,6, 0,3, 0);
	print_string_lcd(480, 70, WHITE, BLACK, "KM", 3, 0, 3, 0);

	// get the heartrate
	print_string_lcd(70, 130, WHITE, BLACK, "Average Heart Rate",18, 0,3, 0);
	char avg_hr[3];
	int num = sprintf(avg_hr,"%d",s_avg_hr);
	print_string_lcd(400, 130, WHITE, BLACK, avg_hr,num, 0,3, 0);
	print_string_lcd(460, 130, WHITE, BLACK, "Beats/Sec",9, 0,3, 0);

	// get the blood oxygen

	print_string_lcd(70, 190, WHITE, BLACK, "Average Blood O",15, 0,3, 0);
	print_string_lcd(312, 205, WHITE, BLACK, "2",1, 0,2, 0);
	char avg_o2[3];
	num = sprintf(avg_o2,"%d",s_avg_o2);
	print_string_lcd(400, 190, WHITE, BLACK, avg_o2,num, 0,3, 0);
	print_string_lcd(460, 190, WHITE, BLACK, "%",1, 0,3, 0);

	// get the duration
	int hours = s_duration/3600;
	int mins =  (s_duration - hours*3600)/60;
	int sec = (s_duration- mins*60 - hours*3600);
	char buff[3];

	print_string_lcd(70, 250, WHITE, BLACK, "Duration",8, 0,3, 0);

	sprintf(buff,"%02d",hours);
	print_string_lcd(400, 250, WHITE, BLACK, buff,2, 0,3, 0);
	print_string_lcd(430, 250, WHITE, BLACK,":",2, 0,3, 0);
	sprintf(buff,"%02d",mins);
	print_string_lcd(440, 250, WHITE, BLACK, buff, 2, 0, 3, 0);
	print_string_lcd(470, 250, WHITE, BLACK,":",2, 0,3, 0);
	sprintf(buff,"%02d",sec);
	print_string_lcd(480, 250, WHITE, BLACK, buff, 2, 0, 3, 0);

	if (s_duration != 0){
		print_string_lcd(70, 310, WHITE, BLACK, "Average Speed",13, 0,3, 0);
		double avg_speed = s_total_dist / s_duration *3600;
		snprintf(Current_dis,6,"%f",avg_speed);

		print_string_lcd(400, 310, WHITE, BLACK, Current_dis,6, 0,3, 0);
		print_string_lcd(490, 310, WHITE, BLACK, "KM/h",4, 0,3, 0);
	}
	draw_new_screen();
}
void update_summary_screen(void){
	//probably nothing to do here!
	return;
}
void handle_touch_summary_screen (Screen *switch_to_screen){
	if (pressed == 1){
		if (touchX == 0 && touchY == 7){
			*switch_to_screen = HISTORY_s;//back button
		}
	}
	return;
}

