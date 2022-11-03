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
    
    }
}
