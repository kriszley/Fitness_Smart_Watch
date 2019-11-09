/*************************************************************************************************
** This function draws a single ASCII character at the coord and colour specified
** it optionally ERASES the background colour pixels to the background colour
** This means you can use this to erase characters
**
** e.g. writing a space character with Erase set to true will set all pixels in the
** character to the background colour
**
*************************************************************************************************/
#include "OutGraphicsCharFont.h"

void OutGraphicsCharFont1(int x, int y, int fontcolour, int backgroundcolour, int c, int Erase)
{
// using register variables (as opposed to stack based ones) may make execution faster
// depends on compiler and CPU

	register int row, column, theX = x, theY = y ;
	register int pixels ;
	register char theColour = fontcolour  ;
	register int BitMask, theC = c ;

// if x,y coord off edge of screen don't bother

    if(((short)(x) > (short)(XRES-1)) || ((short)(y) > (short)(YRES-1)))
        return ;


// if printable character subtract hex 20
	if(((short)(theC) >= (short)(' ')) && ((short)(theC) <= (short)('~'))) {
		theC = theC - 0x20 ;
		for(row = 0; (char)(row) < (char)(7); row ++)	{

// get the bit pattern for row 0 of the character from the software font
			pixels = Font5x7[theC][row] ;
			BitMask = 16 ;

			for(column = 0; (char)(column) < (char)(5); column ++)	{

// if a pixel in the character display it
				if((pixels & BitMask))
					WriteAPixel(theX+column, theY+row, theColour) ;

				else {
					if(Erase == 1)

// if pixel is part of background (not part of character)
// erase the background to value of variable BackGroundColour

						WriteAPixel(theX+column, theY+row, backgroundcolour) ;
				}
				BitMask = BitMask >> 1 ;
			}
		}
	}
}

void print_char_lcd (int x, int y, int fontcolour, int backgroundcolour, int c, int Erase, int size){
	switch(size){
		case 1:
			OutGraphicsCharFont1(x, y, fontcolour, backgroundcolour, c, Erase);
		break;
		case 2:
			OutGraphicsCharFont2(x, y, fontcolour, backgroundcolour, c, Erase);
		break;
		case 3:
			OutGraphicsCharFont3(x, y, fontcolour, backgroundcolour, c, Erase);
		break;
		case 4:
			OutGraphicsCharFont4(x, y, fontcolour, backgroundcolour, c, Erase);
		break;
		case 5:
			OutGraphicsCharFont5(x, y, fontcolour, backgroundcolour, c, Erase);
		break;
		default:
		break;
	}
	return;
}
// draws a string on display
// size is font number 1-5
void print_string_lcd(int x, int y, int fontcolour, int backgroundcolour, const char *str,int str_len, int Erase, int size, int extra_space){
	int dist = 5;
	if (size == 2) dist = FONT2_XPIXELS;
	else if (size == 3) dist = FONT3_XPIXELS;
	else if (size == 4) dist = FONT4_XPIXELS;
	else if (size == 5) dist = FONT5_XPIXELS;
	int i;
	for (i = 0; (i < str_len) && (str[i] != '/0'); i++){
		print_char_lcd( x+i*(dist+extra_space), y, fontcolour, backgroundcolour, str[i], Erase, size);
	}
}


