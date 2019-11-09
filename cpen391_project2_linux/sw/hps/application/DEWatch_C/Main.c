/*
 * Group 3 project -- DE1-SMW
 */

//screens
#include "./screens/ClockScreen.h"
#include "./screens/goal_screen.h"
#include "./screens/history_screen.h"
#include "./screens/summary_screen.h"
#include "./screens/Startup.h"
#include "./screens/BioScreen.h"
#include <time.h>

//HW
#include "./hardware_drivers/Bio.h"
#include "./hardware_drivers/gps.h"
#include "./hardware_drivers/Touch.h"
#include "./hardware_drivers/bluetooth.h"
#include "./sdcard/sdcard.h"

//Other
#include "distance.h"
#include "gui.h"
#include "./time/time24h.h"
#include <stdio.h>

//Nightmares
#include <pthread.h>



int main(){
	//variables
	struct timespec t;
	t.tv_sec = 0;
	t.tv_nsec = 1000 * 1000;
	//pthread_t audio_thread;
	Screen switch_to_screen = CLOCK_s;
	Screen current_screen = NONE;
//	int last_button1 = 0;
	printf("Starting up!\n");
	// Initializations -- internal register settings
	Init_gps();
	Init_bluetooth();
	Init_touch();
	Init_bio();
	Init_Graphics();
	Init_Audio();

	//av_config_setup();

	//default time
	set_time(0, 0, 20, 2, 2018);
	printf("config done!\n");

	// Branching off a thread for audio
//	if(pthread_create(&audio_thread, NULL, echo_audio_continuous, NULL)) {
//		fprintf(stderr, "Error creating audio thread\n");
//		return 1;
//	}
	// Main Thread
	while(1){
		nanosleep(&t,NULL);
//		putchar_bluetooth('a');
  		// Note: ANYTHING HERE SHOULD NEVER BLOCK
  		//Process buffered data
  		handle_data_touch();
  		handle_data_bio();
  		handle_data_gps();
  		handle_data_bluetooth(&switch_to_screen, current_screen);
  		updateDistance();
  		update_time();
  		log_exercise_data_sdcard();

//  		if ((Button1) & (!last_button1)){
//  			printf("button 1 was pressed\n");
//  			currDistance += 0.001;
//  		}
//  		last_button1 = Button1;

  		// update a screen
  		switch (current_screen){
  			case STARTUP_s:
  				update_startup_screen(&switch_to_screen);
  			break;

  			case CLOCK_s:
  				handle_touch_clock_screen (&switch_to_screen);
  				update_clock_screen();
  			break;

  			case GOAL_s:
  				handle_touch_goal_screen(&switch_to_screen);
  				update_goal_screen();
  			break;

  			case SUMMARY_s:
  				handle_touch_summary_screen(&switch_to_screen);
  				update_summary_screen();
  			break;

  			case HISTORY_s:
  				handle_touch_history_screen(&switch_to_screen);
  				update_history_screen();
  			break;

  			case BIO_s:
  				update_bio_screen(&switch_to_screen);
  			break;

  			default:
  				if (switch_to_screen == NONE)
  					printf("Screen Error!");
  			break;
  		}

  		//switch to a different screen -- if set
  		switch (switch_to_screen){
  			case STARTUP_s:
  				draw_startup_screen();
  				current_screen = STARTUP_s;
  			break;

  			case HISTORY_s:
  				draw_history_screen();
				current_screen = HISTORY_s;
  			break;

  			case SUMMARY_s:
  				draw_summary_screen();
  				current_screen = SUMMARY_s;
  			break;

  			case CLOCK_s:
  				draw_clock_screen();
  				current_screen = CLOCK_s;
  			break;

  			case GOAL_s:
  				draw_goal_screen();
  				current_screen = GOAL_s;
  			break;

  			case BIO_s:
  			  	draw_bio_screen();
  			  	current_screen = BIO_s;
  			break;
  			default:
  			// it's fine not to have a new screen
  			break;
  		}
  		switch_to_screen = NONE;
  		pressed = 0;
  	}
  	return 0;
}
