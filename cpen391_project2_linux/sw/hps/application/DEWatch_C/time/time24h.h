/*
 * time24h.h
 *
 *  Created on: Feb 7, 2018
 *      Author: Roy
 */

#ifndef TIME24H_H_
#define TIME24H_H_

#include <time.h>
extern time_t cur_time;

//Simple clock
void update_time(void);
int set_time(int hour, int min, int day, int month, int year);
void get_time(int *hour, int *min, int *day, int *month, int *year);
void get_time_str (char *buffer);


#endif /* TIME24H_H_ */
