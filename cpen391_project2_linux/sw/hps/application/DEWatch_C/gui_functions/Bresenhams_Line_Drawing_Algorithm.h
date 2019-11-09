/*
 * Bresenhams_Line_Drawing_Algorithm.h
 *
 *  Created on: Jan 30, 2018
 *      Author: Roy
 */

#ifndef BRESENHAMS_LINE_DRAWING_ALGORITHM_H_
#define BRESENHAMS_LINE_DRAWING_ALGORITHM_H_

#include <stdint.h>

#define HPS2FPGA_AXI_BASE ( 0xc0000000 )
#define HPS2FPGA_AXI_SPAN ( 0x0400ffff )

extern int cur_screen;

void Init_Graphics(void);
void draw_new_screen(void);
uint16_t get_pixel(const char *pic_data, int x, int y, int pic_x_max);
uint64_t get_4pixels (const char *pic_data, int x, int y, int pic_x_max);
void WriteAPixel(int x, int y, uint16_t Colour);
void Write4APixels(int x, int y, uint64_t Colour);

void Init_Audio(void);
int audio_available (void);
void echo_audio(void);
void echo_audio_continuous (void);

#endif /* BRESENHAMS_LINE_DRAWING_ALGORITHM_H_ */
