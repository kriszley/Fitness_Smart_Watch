/*
 * Bio.c
 *
 *  Created on: Feb 1, 2018
 *      Author: Roy
 */

#include "Bio.h"
#include <stdio.h>
#include <stdint.h>
#include "../time/time24h.h"

typedef enum {SYNC, STAT, PLETH, DATA, CHK} bio_state_t;
typedef enum {HR_MSB, HR_LSB, SPO2} bio_state_mode_t;

// last verified value, global
int bloodOxygen = 0;
int heartRate = 0;
char bio_HR[3]  = "000";
char bio_O2[3]  = "000";


time_t last_update = 0;
FILE *bio_fd;


void Init_bio(void){
  bio_fd = fopen("/proc/bio", "r");
  if (bio_fd== NULL)
	  printf("ERROR: could not open \"/dev/bio\"...\n");
  return;
}


// Reads the buffer data and updates the HR value
// Implemented using a FSM
int handle_data_bio (void){
	static bio_state_t bio_s = SYNC;
	static bio_state_mode_t bio_s_mode = HR_MSB;
	static int newHeartRate = 0;
	static int newBloodOxygen = 0;
	static int checksum = 0;
	char data;

	// reset if data is old
	if (last_update + 5 < cur_time){
		bloodOxygen = 0;
		sprintf(bio_O2,"000");
		heartRate = 0;
		sprintf(bio_HR,"000");
	}

	while (1){
		if( fread(&data, sizeof(char), 1, bio_fd) == 0)
			return 0;
		// change state based on position in data pattern
		// Refer to Specs
		switch (bio_s){
			case SYNC:
				// wait for sync symbol
				if (data == 0x01){
					checksum = data;
					bio_s = STAT;
				}
			break;

			case STAT:
				checksum += data;
				if ((data & 0x81) == 0x81){
					bio_s_mode = HR_MSB;
					bio_s = PLETH;
				}
				else if ((data & 0x81) == 0x80){
					bio_s_mode++;//goes to the next measurment
					bio_s = PLETH;
				}
				else {
					bio_s = SYNC;
				}
			break;

			case PLETH:
				checksum += data;
				bio_s = DATA;
			break;

			case DATA:
				checksum += data;
				if (bio_s_mode == HR_MSB){
					newHeartRate = (((int)data)<<7) & 0x180;
				}
				else if (bio_s_mode == HR_LSB){
					newHeartRate |= data & 0x7F;
				}
				else if (bio_s_mode == SPO2){
					newBloodOxygen = data;
				}
				bio_s = CHK;
			break;

			case CHK:
				if ((data&0xFF) == (checksum&0xFF)) {
					if (bio_s_mode == SPO2)
					{
						if ((newBloodOxygen < 100) && (newBloodOxygen > 80)){
							bloodOxygen = newBloodOxygen;
							sprintf(bio_O2,"%03d", newBloodOxygen);
							last_update = cur_time;
						}

					}
					else if (bio_s_mode == HR_LSB){
						if ((newHeartRate != 511) && (newHeartRate != 127) &&
								(newHeartRate != 128) && (newHeartRate < 200) && (newHeartRate > 50)){
							heartRate = newHeartRate;
							sprintf(bio_HR,"%03d", newHeartRate);
							last_update = cur_time;
						}
					}
				}
				bio_s = SYNC;
			break;
			default:
				bio_s = SYNC;
			break;
		}
	}
	return 0;
}
