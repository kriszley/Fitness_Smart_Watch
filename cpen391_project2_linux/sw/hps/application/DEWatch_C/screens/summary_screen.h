/*
 * summary_screen.h
 *
 *  Created on: Feb 13, 2018
 *      Author: Roy
 */

#ifndef SUMMARY_SCREEN_H_
#define SUMMARY_SCREEN_H_

#include "../gui.h"

extern char summary_file_name[8+4];

void draw_summary_screen(void);
void update_summary_screen(void);
void handle_touch_summary_screen (Screen *switch_to_screen);

extern double s_total_dist;
extern int s_avg_hr;
extern int s_avg_o2;
extern int s_duration;


#endif /* SUMMARY_SCREEN_H_ */
