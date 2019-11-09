/*
 * OutGraphicsCharFont1.h
 *
 *  Created on: Jan 30, 2018
 *      Author: Roy
 */

#ifndef OUTGRAPHICSCHARFONT1_H_
#define OUTGRAPHICSCHARFONT1_H_

// Constants ideally put this in a header file and #include it
#define XRES 800
#define YRES 480

#define FONT2_XPIXELS	10				// width of Font2 characters in pixels (no spacing)
#define FONT2_YPIXELS	14				// height of Font2 characters in pixels (no spacing)

#define FONT3_XPIXELS	16				// width of Font3 characters in pixels (no spacing)
#define FONT3_YPIXELS	27				// height of Font3 characters in pixels (no spacing)

#define FONT4_XPIXELS	22				// width of Font3 characters in pixels (no spacing)
#define FONT4_YPIXELS	40				// height of Font3 characters in pixels (no spacing)

#define FONT5_XPIXELS	38				// width of Font3 characters in pixels (no spacing)
#define FONT5_YPIXELS	59				// height of Font3 characters in pixels (no spacing)

extern const unsigned char Font5x7[][7];
extern const unsigned short int Font10x14[][14];
extern const unsigned char Font16x27[][27*2];
extern const unsigned char Font22x40[][40*3];
extern const unsigned char Font38x59[][59*4];

void OutGraphicsCharFont1(int x, int y, int fontcolour, int backgroundcolour, int c, int Erase);
void OutGraphicsCharFont2(int x, int y, int fontcolour, int backgroundcolour, int c, int Erase);
void OutGraphicsCharFont3(int x, int y, int fontcolour, int backgroundcolour, int c, int Erase);
void OutGraphicsCharFont4(int x, int y, int fontcolour, int backgroundcolour, int c, int Erase);
void OutGraphicsCharFont5(int x, int y, int fontcolour, int backgroundcolour, int c, int Erase);

void print_char_lcd  (int x, int y, int fontcolour, int backgroundcolour, int c, int Erase, int size);
void print_string_lcd(int x, int y, int fontcolour, int backgroundcolour, const char *str,int str_len, int Erase, int size, int extra_space);

#endif /* OUTGRAPHICSCHARFONT1_H_ */
