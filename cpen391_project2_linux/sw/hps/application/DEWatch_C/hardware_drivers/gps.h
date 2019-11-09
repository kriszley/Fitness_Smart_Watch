/*
 * gps.h
 *
 *  Created on: Jan 27, 2018
 *      Author: roy
 */

#ifndef GPS_H_
#define GPS_H_

extern char gps_time[];
extern char gps_lat[];
extern char gps_lon[];
extern int gps_fix;


void Init_gps (void);
void handle_data_gps (void);

#endif /* GPS_H_ */
