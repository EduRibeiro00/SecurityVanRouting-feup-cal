//#pragma once
//
///**
// * Module provided previously, on the course Programming (1st year, 2nd semester),
// * for the final project on the course.
// * It allows for customization of colors on console text applications.
// */
//
//// Example of a program that prints colored characters on the console (in text mode)
//#include <iostream>
//#include <ctime>
//#include <cstdlib>
//#include <windows.h>
//using namespace std;
////==========================================================================================
////COLOR CODES: (alternative: use symbolic const’s)
//#define CONSOLE_BLACK 0
//#define CONSOLE_BLUE 1
//#define CONSOLE_GREEN 2
//#define CONSOLE_CYAN 3
//#define CONSOLE_RED 4
//#define CONSOLE_MAGENTA 5
//#define CONSOLE_BROWN 6
//#define CONSOLE_LIGHTGRAY 7
//#define CONSOLE_DARKGRAY 8
//#define CONSOLE_LIGHTBLUE 9
//#define CONSOLE_LIGHTGREEN 10
//#define CONSOLE_LIGHTCYAN 11
//#define CONSOLE_LIGHTRED 12
//#define CONSOLE_LIGHTMAGENTA 13
//#define CONSOLE_YELLOW 14
//#define CONSOLE_WHITE 15
////==========================================================================================
//
///**
// * Clears the terminal window.
// */
//void clearScreen(void);
//
///**
// * Position the cursor at column 'x', line 'y'
// * (The coodinates of upper left corner of the screen are (x,y)=(0,0))
// *
// * @param x x coordinate
// * @param y y coordinate
// */
//void goToXY(int x, int y);
//
///**
// * Sets console text color
// *
// * @param color color to be set
// */
//void setColor(unsigned int color);
//
///**
// * Sets console text & background colors
// *
// * @param color color to be set for the text
// * @param background_color color to be set for the background
// */
//void setColor(unsigned int color, unsigned int background_color);
