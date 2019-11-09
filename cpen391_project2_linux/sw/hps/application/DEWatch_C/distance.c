/*
 * distance.c
 *
 *  Created on: Feb 13, 2018
 *      Author: krisley3094
 */

#include "distance.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./hardware_drivers/gps.h"
#include "./time/time24h.h"
#include <math.h>
double currDistance = 0;

//private
int currently_tracking = 0;
time_t last_update_time = 0;
char prev_gps_lat[9] = "";
char prev_gps_lon[10] = "";


//private prototypes
double convertDistance(double lat2, double lat1, double lon2, double lon1);
double convertLon2Dec(char* lon);
double convertLat2Dec(char* lat);


void start_distance_tracking (void){
	currDistance = 0;
	last_update_time = 0;
	currently_tracking = 1;
	return;
}

void stop_distance_tracking (void){
	last_update_time = 0;
	currently_tracking = 0;
	return;
}

void updateDistance(){
	//once per second max, need to be fixed and currently tracking
	if ( (cur_time > last_update_time) && (currently_tracking == 1)){// && (gps_fix == 1)){
		last_update_time = cur_time;
		if ((strncmp(prev_gps_lat, "", 1) == 0) || (strncmp(prev_gps_lon, "", 1) == 0)){
			goto copy_coord;
		}

		if(strncmp(gps_lat, prev_gps_lat,9) != 0 || strncmp(gps_lon, prev_gps_lon,10) != 0){
			double lat_dest = convertLat2Dec(gps_lat);
			double lat_src = convertLat2Dec(prev_gps_lat);
			double lon_dest = convertLon2Dec(gps_lon);
			double lon_src = convertLon2Dec(prev_gps_lon);
			double instDist = convertDistance(lat_dest, lat_src, lon_dest, lon_src);
			if ( instDist > 0.001 && instDist < 1.0){
				currDistance += instDist;
			}
//			printf("%lf\n", instDist);
		}
copy_coord:
		strncpy(prev_gps_lat, gps_lat,9);
		strncpy(prev_gps_lon, gps_lon,10);
	}
	return;
}

//GPS distance -- math formula from an online source
double convertDistance(double lat2, double lat1, double lon2, double lon1){

	double dLat = .01745329 * (lat2 - lat1);
	double dLon = .01745329 * (lon2 - lon1);

	lat1 = .01745329 * lat1;
	lat2 = .01745329 * lat2;

	double a = sin(dLat/2.0) * sin(dLat/2.0) + sin(dLon/2.0) * sin(dLon/2.0) * cos(lat1) * cos(lat2);
	double c = 2.0 * atan2(sqrt(a), sqrt(1-a));
	double d = 3975.0 * c;

	return d * 1.609344; //Convert to metric system

}

//math formula from an online source
double convertLat2Dec(char* lat){

	char lat_dd[3];
	char lat_mm[8];
	lat_dd[2] = '\0';
	lat_mm[7] = '\0';
	strncpy(lat_dd, lat, 2);
	strncpy(lat_mm, lat+2, 7);

	double lat_dd_dec = atof(lat_dd);
	double lat_mm_dec = atof(lat_mm);
	return lat_dd_dec + (lat_mm_dec / 60);
}

//math formula from an online source
double convertLon2Dec(char* lon){
	char lon_dd[4];
	char lon_mm[8];
	lon_dd[3] = '\0';
	lon_mm[7] = '\0';
	strncpy(lon_dd, lon, 3);
	strncpy(lon_mm, lon+3, 7);

	int lon_dd_dec = atoi(lon_dd);
	double lon_mm_dec = atof(lon_mm);
	return lon_dd_dec + (lon_mm_dec / 60);
}
