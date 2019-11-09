/* Time selection screen
 * Called on every start-up
 */
#include "Startup.h"
#include "../hardware_drivers/Touch.h"
#include "../time/time24h.h"
#include "../gui.h"
#include <stdio.h>

int timeSet = 0;
int cancel = 0;
static char *months[12] = {"JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};
static int max_day_month[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

int cur_min = 0;
int cur_hour = 0;

int cur_year = 2018;
int cur_day = 1;
int cur_month = 0;

//private prototypes
void drawClock(void);
void drawMonthDay(void);
void drawYear(void);
int getButton(int x, int y);
void startupbuttonPress(int buttonID);

void draw_startup_screen_base(){
	initBackground();
    drawClock();
    drawYear();
    drawMonthDay();

    draw_button_up(X1, Y1); // HourU
    draw_button_down(X1, Y4); // HourD
    draw_button_up(X2, Y1); // MinU
    draw_button_down(X2, Y4); // MinD

    draw_button_up(X4, Y1); // MonU
    draw_button_down(X4, Y4); // MonD
    draw_button_up(X5, Y1); // DayU
    draw_button_down(X5, Y4); // DayD
    draw_button_up(X6, Y1); // YearU
    draw_button_down(X6, Y4); // YearD

    draw_button_right(X7,Y7);
    print_string_lcd(10,10, WHITE,WHITE, "Settings", 8, 0, 4,0);

    draw_button_left(X2,Y6);
    print_string_lcd(X3+10,Y6+15, WHITE,WHITE, "Background", 10, 0, 3,0);
    draw_button_right(X5,Y6);

    draw_button_back(X0, Y7);
}

void draw_startup_screen(){
	get_time(&cur_hour, &cur_min, &cur_day, &cur_month, &cur_year);
	draw_startup_screen_base();
    draw_new_screen();
}


void update_startup_screen(Screen *switch_to_screen){
    int buttonID;

	if(pressed) {
		buttonID = getButton(touchX, touchY);
		startupbuttonPress(buttonID);
		draw_startup_screen_base();
		draw_new_screen();
	}

	if (cancel){
		cancel = 0;
		*switch_to_screen = CLOCK_s;
	}

	// Set time
	if (timeSet){
		timeSet = 0;
		int set_success = set_time(cur_hour, cur_min, cur_day, cur_month, cur_year);
		if (set_success){
			*switch_to_screen = CLOCK_s;
		}
	}
	return;
}


int getButton(int x, int y)
{
    return x*10 + y;
}

void startupbuttonPress(int buttonID)
{
    switch(buttonID)
    {
        case HourU:
        	if (cur_hour < 23)
        		cur_hour++;
        	else if (cur_hour >= 23)
        		cur_hour = 0;
        break;
            
        case HourD:
        	if (cur_hour > 0)
        		cur_hour--;
        	else if (cur_hour <= 0)
        		cur_hour = 23;
        break;
            
        case MinU:
        	if (cur_min < 59)
        		cur_min++;
        	else if (cur_min >= 59)
        		cur_min = 0;
        break;
            
        case MinD:
            if (cur_min > 0)
            	cur_min--;
            else if (cur_min <= 0)
            	cur_min = 59;
		break;
            
        case MonU:
            if(cur_month < 11)
                cur_month++;
            else if (cur_month >= 11)
            	cur_month = 0;
            if (cur_day > max_day_month[cur_month])
            	cur_day = max_day_month[cur_month];
        break;
            
        case MonD:
        	if(cur_month > 0)
        		cur_month--;
        	else if (cur_month <= 0)
        		cur_month = 11;
        	if (cur_day > max_day_month[cur_month])
				cur_day = max_day_month[cur_month];
        break;
            
        case DayU:
        	if (cur_day < max_day_month[cur_month])
        		cur_day++;
        	else if (cur_day >= max_day_month[cur_month])
        		cur_day = 1;
        break;
        
        case DayD:
        	if (cur_day > 1)
        		cur_day--;
        	else if (cur_day <= 1)
        		cur_day = max_day_month[cur_month];

        break;

        case YearU:
        	cur_year++;
        break;
            
        case YearD:
        	if (cur_year > 1900)
        		cur_year--;
        break;

        case BGU:
        	if (bg < 2) bg++;
        break;

        case BGD:
        	if (bg > 0) bg--;
        break;

        case BACK:
        	cancel = 1;
        break;

        case SET:
            timeSet = 1; // Set global screen variable to clock screen
        break;
    }
}
    
void drawClock(){
	char buf[5] = "00:00";
	sprintf(buf,"%02d:%02d",cur_hour,cur_min);
//	redrawBackground(CLOCK_X, CLOCK_X+5*FONT5_XPIXELS, CLOCK_Y, CLOCK_Y+FONT5_YPIXELS);
	print_string_lcd(CLOCK_X,CLOCK_Y, CLOCK_COL, STARTUP_BACKGROUND,buf,5,0,5,0);
}

void drawMonthDay(){
	char buf[6];
	sprintf(buf,"%c%c%c/%02d/",months[cur_month][0],months[cur_month][1],months[cur_month][2],cur_day);
//	redrawBackground(DATE_X, DATE_X+6*FONT5_XPIXELS, DATE_Y, DATE_Y+FONT5_YPIXELS);
	print_string_lcd(DATE_X,DATE_Y, CLOCK_COL, STARTUP_BACKGROUND,buf,7,0,5,-4);
}

void drawYear(){
	char buf[6];
	sprintf(buf,"%d",cur_year);
//	redrawBackground(YEAR_X, YEAR_X+4*FONT5_XPIXELS, YEAR_Y, YEAR_Y+FONT5_YPIXELS);
	print_string_lcd(YEAR_X,YEAR_Y, CLOCK_COL, STARTUP_BACKGROUND,buf,4,0,5,-4);
}
