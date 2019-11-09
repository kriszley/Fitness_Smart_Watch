/*
 * Touch.h
 *
 *  Created on: Jan 29, 2018
 *      Author: Eric
 */

#ifndef TOUCH_H_
#define TOUCH_H_

#define PRESS_SYNC        0x81
#define RELEASE_SYNC      0x80

extern volatile int touchX;
extern volatile int touchY;
extern volatile int pressed;
extern volatile int touch_filter_on;

void Init_touch (void);
int handle_data_touch (void);

#endif /* TOUCH_H_ */
