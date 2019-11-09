/*
 * Shapes.h
 *
 *  Created on: Jan 30, 2018
 *      Author: Roy
 */

#ifndef SHAPES_H_
#define SHAPES_H_

void arc(int x, int y, int radius, int angle1,int angle2);
void circle(int x0, int y0, int radius, int colour);
void filledRectangleBorder(int x1, int y1, int x2, int y2, int fillCol, int borderCol);
void filledRectangle(int x1, int y1, int x2, int y2, int colour);
void rectangle(int x1, int y1, int x2, int y2, int colour);
void square(int x, int y, int length, int colour);
void triangle(int x1, int y1, int x2, int y2, int x3, int y3, int colour);

#endif /* SHAPES_H_ */
