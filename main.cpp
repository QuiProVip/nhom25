#include "mylib.h"
#include <iostream>
#include <string>
#define sl_ground 90
#include<fstream> // doc ghi file
#include<windows.h> // xoa man hinh
using namespace std;
int h = 5;//hight
int xdino = 25; int ydino = 17;
int xdat = 10; int ydat = ydino + h;
char ground[3][sl_ground + 1];
int jump = 14; bool kt_jump = false;
int hiscore;
string dino[6] =
{
        "           e-e ",
        "         /(\\_/)",
        ".___.---' /`-' ",
        " `-._.  )/,,   ",
        "     //        ",//4
        "    ^^         ",//5
};
string die = "           x-x ";
string space = "               ";
string tree[5]
{
        "+++",
        "+++",
        "+++",
        " + ",
        " + ",
};
void draw_dino(int x, int y);
void khoi_tao_mat_dat();
void tao_dat(int i);
void draw_mat_dat();
int main()
{
        
}       
void draw_dino(int x, int y)
{
    for (int i = 0; i < 6; i++)
    {
        gotoXY(x, y);
        cout << dino[i];
        y++;
    }
}
void tao_dat(int i)
{
    int v = rand() % (15 - 1 + 1) + 1;// [1,15]
    switch (v)
    {
    case 1:
    {
        ground[1][i] = '.'; ground[2][i] = ' '; break;
    }
    case 2:
    {
        ground[1][i] = '-'; ground[2][i] = ' '; break;
    }
    case 3:
    {
        ground[1][i] = '`'; ground[2][i] = ' '; break;
    }
    case 4:
    {
        ground[1][i] = 248; ground[2][i] = ' '; break;
    }
    case 5:
    {
        ground[1][i] = ' '; ground[2][i] = '.'; break;
    }
    case 6:
    {
        ground[1][i] = ' '; ground[2][i] = '-'; break;
    }
    case 7:
    {
        ground[1][i] = ' '; ground[2][i] = '`'; break;
    }
    default:
    {
        ground[1][i] = ' '; ground[2][i] = ' '; break;
    }
    }
}
void khoi_tao_mat_dat()
{
    for (int i = 0; i < sl_ground; i++)
    {
        ground[0][i] = '_';
        //-------------
        tao_dat(i);
    }
    ground[0][sl_ground] = '\0';
    ground[1][sl_ground] = '\0';
    ground[2][sl_ground] = '\0';
}
void draw_mat_dat()
{
    if (kt_jump == false)
    {
        ground[0][xdino + 4 - xdat] = '^';
        ground[0][xdino + 5 - xdat] = '^';
    }
    else
    {
        ground[0][xdino + 4 - xdat] = '_';
        ground[0][xdino + 5 - xdat] = '_';
    }
    for (int i = 0; i < 3; i++)
    {
        gotoXY(xdat, ydat + i);
        cout << ground[i];
    }
}
