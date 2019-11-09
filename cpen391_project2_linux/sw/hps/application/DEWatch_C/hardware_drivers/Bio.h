/*
 * Bio.h
 *
 *  Created on: Feb 1, 2018
 *      Author: Roy
 */

#ifndef BIO_H_
#define BIO_H_

extern int heartRate;
extern int bloodOxygen;

extern char bio_HR[3];
extern char bio_O2[3];

void Init_bio (void);
int handle_data_bio (void);

#endif /* BIO_H_ */
