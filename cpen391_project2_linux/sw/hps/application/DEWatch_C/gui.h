/*
 * gui.h
 *
 *  Created on: Feb 8, 2018
 *      Author: krisley3094
 */

#ifndef GUI_H_
#define GUI_H_

#define X0 0
#define X1 90
#define X2 90*2
#define X3 90*3
#define X4 90*4
#define X5 90*5
#define X6 90*6
#define X7 90*7
#define Y0 0
#define Y1 60
#define Y2 120
#define Y3 180
#define Y4 240
#define Y5 300
#define Y6 360
#define Y7 420

#define RES_Y 480
#define RES_X 720

// TODO: DELETE ME
#include "./gui_functions/Colours.h"


#include "./gui_functions/Bresenhams_Line_Drawing_Algorithm.h"
#include "./gui_functions/Shapes.h"
#include "./gui_functions/OutGraphicsCharFont.h"

void draw_button_down(int x, int y);
void draw_button_left(int x, int y);
void draw_button_right(int x, int y);
void draw_button_settings(int x, int y);
void draw_button_up(int x, int y);
void draw_button_running(int x, int y);
void draw_button_start(int x, int y);
void draw_button_back(int x, int y);
void draw_button_history(int x, int y);
void draw_button_stop(int x, int y);
void Init_colors();
void initBackground();
void redrawBackground(int x1, int x2, int y1, int y2);

typedef enum {
	NONE,CLOCK_s,HR_s,GPS_s,GOAL_s,STARTUP_s,SUMMARY_s,HISTORY_s,BIO_s
} Screen;

typedef enum {RIVER, CITY, PARK} BACKGROUND;
extern BACKGROUND bg;

#endif
