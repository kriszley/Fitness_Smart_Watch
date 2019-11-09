/*
 * Colours.h
 *
 *  Created on: Mar 14, 2015
 *      Author: Paul
 */

// see --http://www.rapidtables.com/web/color/RGB_Color.htm for example colours

// This file creates symbolic names for the colours that you can specify in your program
// the actual RGB values are set up in the FPGA Rom, so the name BLACK for example, refer to colour
// palette number 0 whose 24 bit RGB value is 0x000000, WHITE is palette number 1 = RGB value 0xFFFFFF etc
//
// See the ColourPalette.c source file

#ifndef COLOURS_H_
#define COLOURS_H_

// create a set of symbolic constants representing colour name e.g. BLACK, WHITE, RED = {0, 1, 2...} etc and a new data type called Colour (see bottom)
#define WHITE 0xFFFF
#define BLACK 0xFFFF
#define MAEOON 0xFFFF

#endif /* COLOURS_H_ */
