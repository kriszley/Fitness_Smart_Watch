//#include "Bresenhams_Line_Drawing_Algorithm.h"
//#include <math.h>
//void rectangle(int x1, int y1, int x2, int y2, int colour)
//{
//
//    int hLen = (x2>x1) ? (x2 - x1) : (x1-x2);
//    int yLen = (y2>y1)? (y2 - y1) : (y1-y2);
//
//    HLine(x1, y1, hLen, colour); // Top
//    HLine(x1, y2, hLen, colour); // Bottom
//    VLine(x1, y1, yLen, colour); // Left
//    VLine(x2, y1, yLen, colour); // Right
//}
//
//void filledRectangle(int x1, int y1, int x2, int y2, int colour)
//{
//    int hLen =(x2 > x1) ? (x2 - x1):(x1 - x2) ;
//    int yLen = (y2 > y1) ? (y2 - y1) : (y1 - y2);
//    int i;
//
//    // Draws horizontal lines to form a rectangle
//    for(i = 0; i < yLen; i++) {
//        HLine(x1, y1 + i, hLen, colour);
//    }
//}
//
//void filledRectangleBorder(int x1, int y1, int x2, int y2, int fillCol, int borderCol)
//{
//    rectangle(x1, y1, x2, y2, borderCol); // Border
//    filledRectangle(x1 + 1, y1 + 1, x2 - 1, y2 - 1, fillCol); // Inside of rectangle
//}
//
//void triangle(int x1, int y1, int x2, int y2, int x3, int y3, int colour)
//{
//    Line(x1, y1, x2, y2, colour);
//    Line(x1, y1, x3, y3, colour);
//    Line(x2, y2, x3, y3, colour);
//}
//
//// https://en.wikipedia.org/wiki/Midpoint_circle_algorithm
//void circle(int x0, int y0, int radius, int colour)
//{
//    int x = radius-1;
//    int y = 0;
//    int dx = 1;
//    int dy = 1;
//    int err = dx - (radius << 1);
//
//    while (x >= y)
//    {
//        WriteAPixel(x0 + x, y0 + y, colour);
//        WriteAPixel(x0 + y, y0 + x, colour);
//        WriteAPixel(x0 - y, y0 + x, colour);
//        WriteAPixel(x0 - x, y0 + y, colour);
//        WriteAPixel(x0 - x, y0 - y, colour);
//        WriteAPixel(x0 - y, y0 - x, colour);
//        WriteAPixel(x0 + y, y0 - x, colour);
//        WriteAPixel(x0 + x, y0 - y, colour);
//
//        if (err <= 0)
//        {
//            y++;
//            err += dy;
//            dy += 2;
//        }
//        else
//        {
//            x--;
//            dx += 2;
//            err += dx - (radius << 1);
//        }
//    }
//}
//
///*
// * Creates circular arc between the two set angles
// * Angles in degrees
// */
//void arc(int x, int y, int radius, int angle1,int angle2)
//{
//    int endx1 = x + radius * cos(angle1);
//    int endy1 = y + radius * sin(angle1);
//    int endx2 = x + radius * cos(angle2);
//    int endy2 = y + radius * sin(angle2);
//
//    // idk how to do this lol
//}
//
//void square(int x, int y, int length, int colour)
//{
//    HLine(x, y, length, colour); // Top
//    HLine(x, y + length, length, colour); // Bottom
//    VLine(x, y, length, colour); // Left
//    VLine(x + length, y, length, colour); // Right
//}
