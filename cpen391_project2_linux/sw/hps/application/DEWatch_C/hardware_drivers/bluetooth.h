/*
 * bluetooth.h
 *
 *  Created on: Jan 26, 2018
 *      Author: roy
 */
#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_
#include "../gui.h"

extern int send_data;
extern int end_cmd_bt;
extern int bt_locked;

void Init_bluetooth(void);
int putchar_bluetooth(int c);
void send_string_bluetooth(char *s);
void handle_data_bluetooth(Screen *switch_to_screen, Screen cur_screen);
int lock_bt (void);
int unlock_bt (void);

#endif
