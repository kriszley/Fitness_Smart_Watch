/*
 * gps.c
 *
 *  Created on: Jan 27, 2018
 *      Author: roy
 */

#include "gps.h"
#include <string.h>
#include <stdio.h>

//Internal state
typedef enum {SYNC_S, DATA_S, CHECK_S} gps_state_t;
static const char cmd_string[6] = "$GPGGA";//no \0


//global variables
char gps_time[11] = "000000.000"; //HHMMSS.sss
char gps_lat[11]  = "0000.0000N";
char gps_lon[12]  = "00000.0000W";
int   gps_fix  = 0;

char new_gps_time[12] = "000000.000";
char new_gps_lat[12]  = "0000.0000N";
char new_gps_lon[13]  = "00000.0000W";

FILE *gps_fd;


void Init_gps (void){
	  gps_fd = fopen("/proc/gps", "r");
	  if (gps_fd== NULL)
		  printf("ERROR: could not open \"/dev/gps\"...\n");
	  return;
}

void handle_data_gps(void){
	static gps_state_t gps_s = SYNC_S;
	static unsigned int data_pos = 0;
	static unsigned int data_sec = 0;
	static int checksum = 0;
	char data;

	while (1){
		if( fread(&data, sizeof(char), 1, gps_fd) == 0)
			return;
//		printf("%c", data);
		switch(gps_s){
		//Wait for the first '$GP'
		case SYNC_S:
			if (data == cmd_string[data_pos]){
				checksum ^= data;
				data_pos++;
				if (data_pos == 6){
					gps_s = DATA_S;
					data_pos = 0;
				}
			}
			else {
				gps_s = SYNC_S;
				data_pos = 0;
				checksum = 0;
			}
		break;

		case DATA_S:
			checksum ^= data;
			if(data == ','){
				//data section end
				data_pos = 0;
				if (data_sec == 2) strncpy(gps_lat, new_gps_lat,9);
				else if (data_sec == 4) strncpy(gps_lon, new_gps_lon,10);
				data_sec++;
			} else if (data == '*') {
				//command string end
				data_sec = 0;
				data_pos = 0;
				gps_s = CHECK_S;
			} else {
				if (data_pos > 11){
					gps_s = SYNC_S;
					data_pos = 0;
					data_sec = 0;
					printf("corrupt GPS data");
				}
				//or an actual data
				if      (data_sec == 1) gps_time[data_pos] = data;
				else if (data_sec == 2) new_gps_lat[data_pos]  = data;
				else if (data_sec == 3) gps_lat[9]         = data;
				else if (data_sec == 4)	new_gps_lon[data_pos]  = data;
				else if (data_sec == 5)	gps_lon[10]        = data;
				else if (data_sec == 6)	gps_fix = (data == '1');
				data_pos++;
			}
		break;

		case CHECK_S:
			gps_s = SYNC_S;
		break;

		default:
			gps_s = SYNC_S;
		break;
		}
	}
 }
