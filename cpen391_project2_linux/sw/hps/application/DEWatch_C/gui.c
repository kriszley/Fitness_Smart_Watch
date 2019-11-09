/*
 * Background.c
 *
 *  Created on: Feb 8, 2018
 *      Author: krisley3094
 */
#include "gui.h"

#include "./gui_assets/background_city.h"
#include "./gui_assets/background_river.h"
#include "./gui_assets/background_park.h"
#include "./gui_assets/button_up.h"
#include "./gui_assets/button_down.h"
#include "./gui_assets/button_right.h"
#include "./gui_assets/button_left.h"
#include "./gui_assets/button_settings.h"
#include "./gui_assets/button_running.h"
#include "./gui_assets/button_stop.h"
#include "./gui_assets/button_start.h"
#include "./gui_assets/button_back.h"
#include "./gui_assets/button_history.h"

#include "./gui_functions/Bresenhams_Line_Drawing_Algorithm.h"

BACKGROUND bg = CITY;

void initBackground(){
	int y,x;

	for (y = 0; y < 480; y++){
		for (x = 0; x < 720; x += 4){
			switch(bg){
			case RIVER:
				Write4Pixels(x, y, get_4pixels(river_data, x, y, 720));
			break;
			case CITY:
				Write4Pixels(x, y, get_4pixels(city_data, x, y, 720));
			break;
			case PARK:
				Write4Pixels(x, y, get_4pixels(park_data, x, y, 720));
			break;
			}

		}
	}
}

//void redrawBackground(int x1, int x2, int y1, int y2){
//	int i,j;
//    for(i = y1; i < y2; i++) {
//        for(j = x1; j < x2; j++){
//        switch(bg){
//			case RIVER:
//        	Write4Pixels(j, i, get_4pixels(river_data, j, i, 720));
//			break;
//			case CITY:
//				Write4Pixels(j, i, get_4pixels(city_data, j, i, 720));
//			break;
//			case PARK:
//				Write4Pixels(j, i, get_4pixels(park_data, j, i, 720));
//			break;
//			}
//        }
//    }
//}

void draw_button_up (int x, int y){
	int i,j;
    for(i = 0; i < 60; i++) {
        for(j = 0; j < 90; j++){
        	WriteAPixel(x+j, y+i,  get_4pixels(up_data, j, i, 90));
        }
    }
}

void draw_button_down (int x, int y){
	int i,j;
    for(i = 0; i < 60; i++) {
        for(j = 0; j < 90; j++){
        	WriteAPixel(x+j, y+i, get_4pixels(down_data, j, i, 90));
        }
    }
}

void draw_button_left (int x, int y){
	int i,j;
    for(i = 0; i < 60; i++) {
        for(j = 0; j < 90; j++){
        	WriteAPixel(x+j, y+i,  get_4pixels(left_data, j, i, 90));
        }
    }
}

void draw_button_right (int x, int y){
	int i,j;
    for(i = 0; i < 60; i++) {
        for(j = 0; j < 90; j++){
        	WriteAPixel(x+j, y+i,  get_4pixels(right_data, j, i, 90));
        }
    }
}

void draw_button_settings (int x, int y){
	int i,j;
    for(i = 0; i < 60; i++) {
        for(j = 0; j < 90; j++){
        	WriteAPixel(x+j, y+i,  get_4pixels(settings_data, j, i, 90));
        }
    }
}

void draw_button_running(int x, int y){
	int i,j;
    for(i = 0; i < 60; i++) {
        for(j = 0; j < 90; j++){
        	WriteAPixel(x+j, y+i,  get_4pixels(running_data, j, i, 90));
        }
    }
}


void draw_button_start (int x, int y){
	int i,j;
    for(i = 0; i < 60; i++) {
        for(j = 0; j < 90; j++){
        	WriteAPixel(x+j, y+i,  get_4pixels(start_data, j, i, 90));
        }
    }
}

//TODO: Change the picture
void draw_button_back (int x, int y){
	int i,j;
    for(i = 0; i < 60; i++) {
        for(j = 0; j < 90; j++){
        	WriteAPixel(x+j, y+i,  get_4pixels(back_data, j, i, 90));
        }
    }
}


void draw_button_history(int x, int y){
	int i,j;
    for(i = 0; i < 60; i++) {
        for(j = 0; j < 90; j++){
        	WriteAPixel(x+j, y+i,  get_4pixels(back_data, j, i, 90));
        }
    }
}

void draw_button_stop(int x, int y){
	int i,j;
    for(i = 0; i < 60; i++) {
        for(j = 0; j < 90; j++){
        	WriteAPixel(x+j, y+i,  get_4pixels(stop_data, j, i, 90));
        }
    }
}
