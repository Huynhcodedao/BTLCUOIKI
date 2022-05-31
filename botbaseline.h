#ifndef BOTBASELINE
#define BOTBASELINE

#include <iostream>
#include <stdlib.h>
#include "config.h"

#include <windows.h>
#include <conio.h>
#include <time.h>       /* time */
#include <unistd.h>
using namespace std;

void go_to_xy(Point p);
void draw_tile(Point p, int color);
void set_text_color(int color);

int CheckWin(int a[30][50]);
Point Player(int a[30][50], Point dich);
//BOT
long DuyetTCDoc(int x, int y, int a[][50], int id);
long DuyetTCNgang(int x, int y, int a[][50], int id);
long DuyetTCCheoLen(int x, int y, int a[][50], int id);
long DuyetTCCheoXuong(int x, int y, int a[][50], int id);
long DuyetPNDoc(int x, int y, int a[][50], int id);
long DuyetPNNgang(int x, int y, int a[][50], int id);
long DuyetPNCheoLen(int x, int y, int a[][50], int id);
long DuyetPNCheoXuong(int x, int y, int a[][50], int id);
Point BotNhomNice(int a[][50], int id);

void Menu(int &ChucNang);
#endif // BOTBASELINE
