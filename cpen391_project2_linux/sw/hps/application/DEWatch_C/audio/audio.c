/*
 * audio.c
 *
 *  Created on: Feb 9, 2018
 *      Author: Roy
 */

//#include "altera_up_avalon_audio.h"
//#include "altera_up_avalon_audio_and_video_config.h"
//
//void av_config_setup() {
//	alt_up_av_config_dev *av_config = alt_up_av_config_open_dev("/dev/audio_and_video_config_0");
//	if (av_config == NULL){
//		printf("error");
//		return;
//	}
//	while (!alt_up_av_config_read_ready(av_config)) {
//	}
//}
//
//void play_tone(){
//	unsigned int buf[4];
//	buf[0] = 0x00007FFF;
//	buf[1] = 0x00007FFF;
//	buf[2] = 0x00008000;
//	buf[3] = 0x00008000;
//	int count = 0;
//	alt_up_audio_dev * audio = alt_up_audio_open_dev("/dev/audio_0");
//	if (audio != NULL ) printf("connnnnnnnected!");
//	while (1){
//		while ( alt_up_audio_write_fifo_space(audio, ALT_UP_AUDIO_LEFT) == 0 ){
//			printf("left : %d\n", alt_up_audio_write_fifo_space(audio, ALT_UP_AUDIO_LEFT));
//			printf("right: %d\n",alt_up_audio_write_fifo_space(audio, ALT_UP_AUDIO_RIGHT));
//		}
//			alt_up_audio_write_fifo(audio, buf, 4, ALT_UP_AUDIO_LEFT);
//			alt_up_audio_write_fifo(audio, buf, 4, ALT_UP_AUDIO_RIGHT);
//			count++;
//			printf("%d\n", count);
//	}
//}
