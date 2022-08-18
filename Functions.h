#pragma once

#include "Point.h"


#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctime>
#include <vector>
#include <string>

void gotoxy(int x, int y);
void setTextColor(Color color);
void hideCursor();
void clear_screen();

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;


#ifndef WINDOWS	
int _getch(void);
int _kbhit(void);
void Sleep(unsigned long);
#else
#include <stdlib.h>
#include <conio.h>
#endif



