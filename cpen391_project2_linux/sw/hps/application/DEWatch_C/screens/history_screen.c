/*
 * history_screen.c
 *
 *  Created on: Feb 13, 2018
 *      Author: Roy
 */
#include "history_screen.h"
#include "summary_screen.h"
#include "../gui.h"
#include "../hardware_drivers/Touch.h"
#include "../sdcard/sdcard.h"
#include <dirent.h>
#include <string.h>
#include <stdio.h>

// buffer
#define TOTAL_SIZE 100
char screen_file_names[TOTAL_SIZE][14];
char real_file_name[TOTAL_SIZE][13];
int is_button_active[TOTAL_SIZE];

//private status
int tail_entry = 0;
int head_entry = 0;
int last_head = 0;
int last_tail= 0;
int up_is_active = 0;
int down_is_active = 0;
int total_files = 0;
DIR *d;


char file_to_open[19] = "/RUNS/";
static char dir_path[6] = "/RUNS";

void construct_full_path(int i){
	strncpy(&file_to_open[6], real_file_name[i],13);
	file_to_open[18] = '\0';
}

void format_file_name (int i){
	screen_file_names[i][0] = '2';
	screen_file_names[i][1] = '0';
	screen_file_names[i][2] = real_file_name[i][0];
	screen_file_names[i][3] = real_file_name[i][1];

	screen_file_names[i][4] = ' ';

	screen_file_names[i][5] = real_file_name[i][2];
	screen_file_names[i][6] = real_file_name[i][3];
	screen_file_names[i][7] = real_file_name[i][4];

	screen_file_names[i][8] = ' ';

	screen_file_names[i][9] = real_file_name[i][5];
	screen_file_names[i][10] = real_file_name[i][6];

	screen_file_names[i][11] = ' ';

	screen_file_names[i][12] = real_file_name[i][7];
	screen_file_names[i][13] = '\0';
}


void redraw_list (){
	initBackground();
	draw_button_back(X0,Y7);//back
	print_string_lcd(10, 10, WHITE, BLACK, "Exercise History", 16, 0, 4,0);//title

	int entry = head_entry;
	int pos_on_screen = 0;
	while (entry != tail_entry){
//		redrawBackground(20, X5, (pos_on_screen+1)*Y1, (pos_on_screen+2)*Y1);
		print_string_lcd( 20 , (pos_on_screen+1)*Y1+10, WHITE, BLACK, screen_file_names[entry], 13, 0, 4,0);
		draw_button_right(X4,(pos_on_screen+1)*Y1);
		entry = (entry+1)%(TOTAL_SIZE + 1);
		pos_on_screen++;
	}
	return;
}


void draw_history_screen(){
	total_files = 0;
	head_entry = 0;

	//get the list of most recent and show 6 of them
	struct dirent *dir;
	d = opendir(dir_path);
	if (d) {
		//read all file names
		while (((dir = readdir(d)) != NULL) && (total_files < TOTAL_SIZE)) {
			if (dir->d_type == DT_REG){
				strcpy(real_file_name[total_files], dir->d_name);
				format_file_name(total_files);
				printf("%s\n", dir->d_name);
				total_files++;
			}
		}
	closedir(d);
	}
	else{
		print_string_lcd(200, 200, WHITE, BLACK, "SD Card Error", 17, 0, 4,0); //title
	}

	tail_entry = (total_files > 6)?  6 : total_files;
	last_head = head_entry;
	last_tail = tail_entry;
	redraw_list();

	if (total_files > 6){
		draw_button_down(X7,Y7);
		down_is_active = 1;
	}
	draw_new_screen();
	return;
}

void update_history_screen(){
	if( (last_head != head_entry)  || (last_tail != tail_entry)){
		redraw_list();
		if ((tail_entry != total_files)){
			draw_button_down(X7,Y7);
			down_is_active = 1;
		}
		else {
			down_is_active = 0;
		}
		if (head_entry != 0){
			draw_button_up(X7,Y0);
			up_is_active = 1;
		}
		else {
			up_is_active = 0;
		}
		draw_new_screen();

		last_head = head_entry;
		last_tail = tail_entry;
	}
}

void handle_touch_history_screen (Screen *switch_to_screen){
	if (pressed == 1){
		if (touchX == 0 && touchY == 7){
			*switch_to_screen = CLOCK_s;//back button
		}

		else if (touchX == 4){
			if ((touchY > 0) && (touchY < 8)){
				int file_idx = (head_entry+touchY-1);
				if ( file_idx < tail_entry){
					construct_full_path(file_idx);
					set_summery_form_file(file_to_open);
					*switch_to_screen = SUMMARY_s;
				}
			}
		}

		// Scroll up
		if (touchX == 7 && touchY == 0){
			if (up_is_active == 0) return;
			if (head_entry == 0)
				head_entry = TOTAL_SIZE-1;
			else
				head_entry--;

			if (tail_entry - head_entry > 6){
				if (tail_entry == 0)
					tail_entry = TOTAL_SIZE-1;
				else
					tail_entry--;
			}
		}

		//Scroll down
		if (touchX == 7 && touchY == 7){
			if (down_is_active == 0) return;
			tail_entry = (tail_entry+1)%(TOTAL_SIZE + 1);
			if (tail_entry - head_entry > 6){
				head_entry = (head_entry+1)%(TOTAL_SIZE + 1);
			}
		}
	}
	return;
}

