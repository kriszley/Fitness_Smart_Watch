/*
 * OutGraphicsCharFont4.c
 *
 *  Created on: Jan 30, 2018
 *      Author: Roy
 */

#include "OutGraphicsCharFont.h"
#include "Bresenhams_Line_Drawing_Algorithm.h"
/******************************************************************************************************************************
** This function draws a single ASCII character at the coord specified using the colour specified
** OutGraphicsCharFont2(100,100, RED, 'A', TRUE, FALSE, 1, 1) ;	// display upper case 'A' in RED at coords 100,100, erase background
** no scroll, scale x,y= 1,1
**
******************************************************************************************************************************/
void OutGraphicsCharFont4(int x, int y, int colour, int backgroundcolour, int c, int Erase)
{
	register int 	row,
					column,
					theX = x,
					theY = y ;
	register int 	pixels ;
	register char 	theColour = colour  ;
	register int 	BitMask,
					theCharacter = c,
					j,
					theRow, theColumn;


    if(((short)(x) > (short)(XRES-1)) || ((short)(y) > (short)(YRES-1)))  // if start off edge of screen don't bother
        return ;
    int hit = 0;
	if(((short)(theCharacter) >= (short)(' ')) && ((short)(theCharacter) <= (short)('~'))) {			// if printable character
		theCharacter -= 0x20 ;																			// subtract hex 20 to get index of first printable character (the space character)
		theRow = FONT4_YPIXELS * 3;
		theColumn = FONT4_XPIXELS;

		for(row = 0; row < theRow ; row = row + 3)	{
			pixels = Font22x40[theCharacter][row+2] + (((unsigned int)Font22x40[theCharacter][row+1]) << 8) + (((unsigned int)Font22x40[theCharacter][row]) << 16) ;		  	// get the pixels for row 0 of the character to be displayed
			BitMask = 1<<23;							   											// set of hex 200 i.e. bit 7-0 = 0010 0000 0000
			for(column = 0; column < theColumn;   )  	{
				if((pixels & BitMask)){														// if valid pixel, then write it
					WriteAPixel(theX+column, theY+row/3, theColour);
					hit++;
				}
				else {
					// if not a valid pixel, do we erase or leave it along (no erase)
					if(Erase == 1)
						WriteAPixel(theX+column, theY+row/3, backgroundcolour) ;
					// else leave it alone
				}
					column ++ ;
				BitMask = BitMask >> 1 ;
			}
		}
	}
}



