/*
 * time24h.c
 *
 *  Created on: Feb 7, 2018
 *      Author: Roy
 */

#include "time24h.h"
#include <time.h>
#include <stdio.h>
time_t cur_time = 0;

void update_time(void){
	cur_time = time(NULL);
}

/* Sets the system time
* 	Note: month range is 0 to 11
* 	returns 1 on success
*/
int set_time(int hour, int min, int day, int month, int year){

	struct tm new_time;
	new_time.tm_sec   = 0;
	new_time.tm_min   = min;
	new_time.tm_hour  = hour;
	new_time.tm_mday  = day;
	new_time.tm_mon   = month;
	new_time.tm_year  = year-1900;
	new_time.tm_wday  = 0;
	new_time.tm_yday  = 0;
	new_time.tm_isdst = -1;

	cur_time = mktime(&new_time);
	if (cur_time != (time_t)-1){
		stime(&cur_time);
	}
	return (cur_time != (time_t)-1);
}

void get_time(int *hour, int *min, int *day, int *month, int *year){
	update_time();
	struct tm cur_tm;
	gmtime_r(&cur_time, &cur_tm);
	*hour = cur_tm.tm_hour+1;
	*min = cur_tm.tm_min;
	*day = cur_tm.tm_mday;
	*month = cur_tm.tm_mon;
	*year = cur_tm.tm_year+1900;
}

void get_time_str (char *buffer){
	if ( NULL == ctime_r(&cur_time, buffer) ){
		printf("Error while getting time.\n");
	}
}
