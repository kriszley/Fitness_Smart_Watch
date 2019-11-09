#include "BioScreen.h"

#include <stdio.h>
#include <string.h>
#include "../hardware_drivers/Bio.h"
#include "../hardware_drivers/Touch.h"
#include "../hardware_drivers/bluetooth.h"
#include "../gui.h"
#include "goal_screen.h"
#include "../time/time24h.h"
#include "../distance.h"
#include "../sdcard/sdcard.h"

char last_drawn_HR[3];
char last_drawn_O2[3];
double last_drawn_dist = 0;
int last_time_elapsed = 0;

time_t start_time;


void draw_bio_screen_base(void){
	char dist[10];
	char time[10];

	initBackground();
	// Title
	print_string_lcd(10, 10, GPS_SCREEN_FOREGROUND, GPS_SCREEN_BACKGROUND, "Current Exercise", 16, 0, 4, 0);
	// Labels
	print_string_lcd(LABEL1_X, BIO_Y_HR, GPS_SCREEN_FOREGROUND, GPS_SCREEN_BACKGROUND, "HR:", 3, 0, 3, 0);
	print_string_lcd(LABEL1_X, BIO_Y_O2, GPS_SCREEN_FOREGROUND, GPS_SCREEN_BACKGROUND, "O2:", 3, 0, 3, 0);
	print_string_lcd(LABEL2_X, BIO_Y_HR, GPS_SCREEN_FOREGROUND, GPS_SCREEN_BACKGROUND, "DIST:", 5, 0, 3, 0);
	print_string_lcd(LABEL2_X, BIO_Y_O2, GPS_SCREEN_FOREGROUND, GPS_SCREEN_BACKGROUND, "TIME:", 5, 0, 3, 0);

	// Distance/Time goal and units
	if (dist_goal != 0){
		sprintf(dist, "/%2d.%d KM", dist_goal/10, dist_goal%10);
		print_string_lcd(LABEL2_X + 12 * FONT3_XPIXELS, BIO_Y_HR, GPS_SCREEN_FOREGROUND, GPS_SCREEN_BACKGROUND, dist, 7, 0 , 3, 0);
		print_string_lcd(LABEL2_X + 12 * FONT3_XPIXELS, BIO_Y_O2, GPS_SCREEN_FOREGROUND, GPS_SCREEN_BACKGROUND, "MIN", 3, 0 , 3, 0);
	}
	else {
		print_string_lcd(LABEL2_X + 12 * FONT3_XPIXELS, BIO_Y_HR, GPS_SCREEN_FOREGROUND, GPS_SCREEN_BACKGROUND, "KM", 2, 0 , 3, 0);
		sprintf(time, "/%3d MIN", time_goal);
		print_string_lcd(LABEL2_X + 12 * FONT3_XPIXELS, BIO_Y_O2, GPS_SCREEN_FOREGROUND, GPS_SCREEN_BACKGROUND, time, 8, 0 , 3, 0);
	}

	draw_button_stop(X7, Y7); // Finished button
	return;
}

void draw_bio_screen(){

	start_time = cur_time;
	strncpy(last_drawn_HR, bio_HR, 3);
	strncpy(last_drawn_O2, bio_O2, 3);

	draw_bio_screen_base();

	// Initial values
	print_string_lcd(LABEL1_X + 4 * FONT3_XPIXELS, BIO_Y_HR, GPS_SCREEN_FOREGROUND, GPS_SCREEN_BACKGROUND, bio_HR, 3, 0, 3, 0);
	print_string_lcd(LABEL1_X + 4 * FONT3_XPIXELS, BIO_Y_O2, GPS_SCREEN_FOREGROUND, GPS_SCREEN_BACKGROUND, bio_O2, 3, 0, 3, 0);
	print_string_lcd(LABEL2_X + 6 * FONT3_XPIXELS, BIO_Y_HR, GPS_SCREEN_FOREGROUND, GPS_SCREEN_BACKGROUND, "00.00", 5, 0 , 3, 0);
	print_string_lcd(LABEL2_X + 6 * FONT3_XPIXELS, BIO_Y_O2, GPS_SCREEN_FOREGROUND, GPS_SCREEN_BACKGROUND, "00:00", 5, 0 , 3, 0);

	if (send_data == 0){
		send_string_bluetooth("START*");
		putchar_bluetooth((char)0);
		putchar_bluetooth((char)0);
		putchar_bluetooth((char)255);
		putchar_bluetooth((char)255);
		putchar_bluetooth((char)0);
		putchar_bluetooth((char)0);
		send_data = 1;
	}

	end_cmd_bt = 0;

	//start logging
	start_distance_tracking();
	start_exercise_log();

	draw_new_screen();
	return;
}

/* Update heartrate, O2, time, distance
 * Checks for finish button press
 */
void update_bio_screen(Screen *switch_to_screen) {
	int time_elapsed; // In seconds
	char print_time[5];
	char print_dist[5];

	if ( (pressed && (touchX == 7 && touchY == 7)) || end_cmd_bt == 1 ) {
		stop_distance_tracking();
		stop_exercise_log();

		end_cmd_bt = 0;
		send_data = 0;

		send_string_bluetooth("END*");
		putchar_bluetooth((char)0);
		putchar_bluetooth((char)0);
		putchar_bluetooth((char)255);
		putchar_bluetooth((char)255);
		putchar_bluetooth((char)0);
		putchar_bluetooth((char)0);
		printf("sending END");

		set_summery_form_file(open_file_name);
		*switch_to_screen = SUMMARY_s;
		return;
	}

	time_elapsed = difftime(cur_time, start_time);
	if (last_time_elapsed != time_elapsed){
		if ((strncmp(last_drawn_HR, bio_HR, 3) != 0) ||
			(strncmp(last_drawn_O2, bio_O2, 3) != 0) ||
			(last_drawn_dist != currDistance)        ||
			(last_time_elapsed != time_elapsed)){
			//draw all the values
			draw_bio_screen_base();
			print_string_lcd(LABEL1_X + 4*FONT3_XPIXELS, BIO_Y_HR, GPS_SCREEN_FOREGROUND, GPS_SCREEN_BACKGROUND, bio_HR, 3, 0, 3, 0);
			print_string_lcd(LABEL1_X + 4*FONT3_XPIXELS, BIO_Y_O2, GPS_SCREEN_FOREGROUND, GPS_SCREEN_BACKGROUND, bio_O2, 3, 0, 3, 0);
			sprintf(print_dist, "%2.3f", currDistance);
			print_string_lcd(LABEL2_X + 6*FONT3_XPIXELS, BIO_Y_HR, GPS_SCREEN_FOREGROUND, GPS_SCREEN_BACKGROUND, print_dist, 5, 0, 3, 0);
			int min = time_elapsed / 60;
			int sec = time_elapsed % 60;
			sprintf(print_time,"%02d:%02d", min, sec);
			print_string_lcd(LABEL2_X + 6*FONT3_XPIXELS, BIO_Y_O2, GPS_SCREEN_FOREGROUND, GPS_SCREEN_BACKGROUND, print_time, 5, 0, 3, 0);

			// update last values
			last_time_elapsed = time_elapsed;
			last_drawn_dist = currDistance;
			strncpy(last_drawn_HR, bio_HR, 3);
			strncpy(last_drawn_O2, bio_O2, 3);

			draw_new_screen();
		}
	}
}

