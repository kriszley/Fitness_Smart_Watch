/*
 * bluetooth.c
 *
 *  Created on: Jan 26, 2018
 *      Author: roy
 */

#include "bluetooth.h"
#include <string.h>
#include <stdio.h>
#include <sys/file.h>

FILE *bt_fd;
int send_data = 0;
int end_cmd_bt = 0;
int bt_locked = 0;

int lock_bt (void){
	int result = flock(fileno(bt_fd), LOCK_EX | LOCK_NB);
	bt_locked =  (result == 0)? 1 : 0;
	return bt_locked;
}


int unlock_bt (void){
	if (bt_locked == 1){
		flock(fileno(bt_fd), LOCK_UN);
		bt_locked = 0;
	}
	return 0;
}



int putchar_bluetooth(int c){
	char to_send = (char) c;
	fwrite(&to_send, sizeof(char), 1, bt_fd);
	return 1;
}

void send_string_bluetooth(char *s){
	int idx;
	int len = strlen(s);
	for (idx = 0; idx < len; idx++)
	{
		putchar_bluetooth(s[idx]);
	}
}


#define NUM_COMMANDS 5
//static char CMDS_STR[NUM_COMMANDS][4] = { "","LIST", "SEND", "BEGN", "ENDD"};

// gets commands for sending data
void handle_data_bluetooth(Screen *switch_to_screen, Screen cur_screen){
	char data;
	//static int cmd_pos = 0;
	//static int cmd_num = 0;
	//static char filename[13];//just in case we need it
	//static int new_line = 1;
	while (1){
		if( fread(&data, sizeof(char), 1, bt_fd) == 0){
			return;
		}
		printf("%c", data);

		if (data=='B'){
			printf("Starting\n");
			send_data = 1;
			if (cur_screen != BIO_s){
				*switch_to_screen = BIO_s;
			}
		}
		else if (data == 'E'){
			printf("Ending\n");
			send_data = 0;
			end_cmd_bt = 1;
		}

//		if (data == '\n' || data == '\r') {
//			new_line = 1;
//			continue;
//		}
//		//process the command and see what it is
//		if (cmd_pos == 0){
//			int i;
//			for (i = 1; i < NUM_COMMANDS; i++){
//				if (data == CMDS_STR[i][0]){
//					cmd_pos++;
//					cmd_num = i;
//					printf("command found %d", cmd_num);
//				}
//			}
//			if (cmd_num  == 0){
//				cmd_pos = 0;
//				if(new_line == 1){
//					send_string_bluetooth("command not found\n");
//					new_line = 0;
//				}
//			}
//		}
//		else {
//			//check rest of command name
//			if (cmd_pos < 4 && data == CMDS_STR[cmd_num][cmd_pos]){
//				cmd_pos++;
//				if (cmd_pos == 4 && cmd_num != 2){
//					if (cmd_num == 1){
////						send_file_list_bluetooth();
//					}
//					else if (cmd_num == 3){
//						printf("Starting\n");
//						send_data = 1;
//						if (cur_screen != BIO_s){
//							*switch_to_screen = BIO_s;
//						}
//					}
//					else if (cmd_num == 4){
//						printf("Ending\n");
//						send_data = 0;
//						end_cmd_bt = 1;
//					}
//					cmd_num = 0;
//					cmd_pos = 0;
//				}
//			}
//			//save arguments
//			else if (cmd_pos >= 4 && cmd_num == 2){
//				filename[cmd_pos-4] = data;
//				cmd_pos++;
//				if (cmd_pos >= 4+12){
////					send_file_bluetooth(filename);
//					cmd_num = 0;
//					cmd_pos = 0;
//				}
//			}
//			//not found - reset
//			else {
//				cmd_num = 0;
//				cmd_pos = 0;
//			}
//		}
	}
}

//int wait_for_ack_bluetooth(const char *expected_ack){
//	int retry;
//	int ack_pos = 0;
//	int ack_len = strlen(expected_ack);
//	for (retry = 0; retry < TIMEOUT_COUNT; retry++){
//		if((BLUETOOTH_STAT & 0x01) == 0x01 ){
//			char reply = BLUETOOTH_RX;
//			if (reply == expected_ack[ack_pos]){
//				ack_pos++;
//				if(ack_pos == ack_len)
//					return 0; // response ok
//			}
//		}
//	}
//	return 1; //did not get all acknowledgment characters on time
//}


void Init_bluetooth(void){
	  bt_fd = fopen("/proc/bluetooth", "r+");
	  if (bt_fd== NULL)
		  printf("ERROR: could not open \"/dev/bt\"...\n");
	  return;
}

//int config_bluetooth (void){
//	// Start command mode
//	send_string_bluetooth("$$$");
//	// wait for answer
//	if (wait_for_ack_bluetooth("CMD") != 0)
//		return 1;
//
//    // Send auth mode 4
//	send_string_bluetooth("SA,4\r\n");
//	if (wait_for_ack_bluetooth("AOK") != 0)
//		return 1;
//
//	// Set a new name
//	send_string_bluetooth("SN,GROUP_3_2018\r\n");
//	if (wait_for_ack_bluetooth("AOK") != 0)
//		return 1;
//
//	// Set password
//	send_string_bluetooth("SP,1235\r\n");
//	if (wait_for_ack_bluetooth("AOK") != 0)
//		return 1;
//
//	// End command mode
//	send_string_bluetooth("---\r\n");
//	if (wait_for_ack_bluetooth("END") != 0)
//		return 1;
//
//	FIFO_Init(&bluetooth_buffer, bluetooth_data_store, BLUETOOTH_BUFFER_SIZE);
//	return 0;
//}

