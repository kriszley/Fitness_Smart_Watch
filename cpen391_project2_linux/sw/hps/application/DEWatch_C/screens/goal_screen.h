/*
 * goal_screen.h
 *
 *  Created on: Feb 11, 2018
 *      Author: Roy
 */

#ifndef GOAL_SCREEN_H_
#define GOAL_SCREEN_H_

#include "../gui.h"

extern int dist_goal;
extern int time_goal;

void draw_goal_screen(void);
void update_goal_screen(void);
void handle_touch_goal_screen (Screen *switch_to_screen);

#endif /* GOAL_SCREEN_H_ */
