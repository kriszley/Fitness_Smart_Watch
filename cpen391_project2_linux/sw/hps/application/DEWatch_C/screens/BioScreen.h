/*
 * BioScreen.h
 *
 *  Created on: Feb 11, 2018
 *      Author: krisley3094
 */

#ifndef BIOSCREEN_H_
#define BIOSCREEN_H_

#include "../gui.h"

#define DoneButton 77
#define GPS_SCREEN_BACKGROUND WHITE
#define GPS_SCREEN_FOREGROUND WHITE
#define BIO_Y_HR 180
#define BIO_Y_O2 230
#define LABEL1_X 20
#define LABEL2_X 270
#define INFO1_X 130
#define INFO2_X 400

void draw_bio_screen(void);
void update_bio_screen(Screen *switch_to_screen);

#endif /* BIOSCREEN_H_ */
