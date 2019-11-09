#ifndef STARTUP_H_
#define STARTUP_H_ 

#include "../gui.h"

#define STARTUP_BACKGROUND BLACK
#define CLOCK_COL WHITE
#define DATE_COL WHITE
#define ARROW_COL WHITE 
#define CLOCK_X 90
#define CLOCK_Y 215-60
#define DATE_X  345
#define DATE_Y  215-60
#define YEAR_X  575
#define YEAR_Y  215-60

// Button IDs XY
#define HourU 11
#define HourD 14
#define MinU  21
#define MinD  24
#define MonU  41
#define MonD  44
#define DayU  51
#define DayD  54
#define YearU 61
#define YearD 64

#define BGU 26
#define BGD 56

#define BACK 07
#define SET  77

void draw_startup_screen(void);
void update_startup_screen(Screen *switch_to_screen);

#endif
