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
int jump = 16; bool kt_jump = false;
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
void play();
void draw_dino(int x, int y);
void khoi_tao_mat_dat();
void tao_dat(int i);
void draw_mat_dat();
void draw_wall();
void xoa(int a[], int &n, int vt);
void di_chuyen_tree(int t[], int &nt);
void clear_tree(int x);
void XuatFile();
void GhiFile();
int main()
{
        
}
void play()
{
	//============== setup ========
	int score = 0;
	draw_wall();
	int t[100];int nt = 0;int count = 0;
	draw_dino(xdino,ydino);
	khoi_tao_mat_dat();
	draw_mat_dat();
	int x = xdino;int y = ydino;
	int check = 2;//2: dung im
					//1: di len
					//0: di xuong
	//============ play ==========
	while (true)
	{
		gotoXY(50, 1);
		cout <<"Score: "<<score++;
		if (count == 0)
		{
			t[nt++] = 95;
			count = rand() % (65 - 35 + 1) + 35;//[35,65]
		}
		//---- xoa du lieu man hinh --------
		//---------- in data -----
		if (check != 2)
		{
			draw_dino(x, y);
		}
		di_chuyen_tree(t, nt);
		if (game_over(x, y, t, nt) == true)
		{
			break;
		}
		//draw_tree(xtree);
		//clear_tree(xtree);
		//----- kt cham -------
		/*if (kt_cham(xtree, x, y) == true)
		{
			gotoXY(x, y);
			cout << die;
			break;
		}
		xtree--;*/
		di_chuyen_mat_dat();
		//------- dieu khien --------
		if (_kbhit())
		{
			char c = _getch();
			if (c == -32)
			{
				c = _getch();
				if (c == 72 && check == 2)
				{
					check = 1;kt_jump = true;
				}
			}
		}
		//------ di chuyen -------
		if (check == 1)
		{
			gotoXY(x, y + h);
			cout << space;
			y--;
		}
		else if (check == 0)
		{
			gotoXY(x, y);
			cout << space;
			y++;
		}
		//------ kt bien -----
		if (y == ydino - jump)
		{
			check = 0;
		}
		else if(y==ydino)
		{
			if (check != 2)
			{
				draw_dino(x, y);
				check = 2;kt_jump = false;
			}
			
		}
		//------- speed -------
		count--;
		Sleep(10);
	}
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
void draw_wall()
{
    for (int y = 2; y <= ydat + 4; y++)
    {
        gotoXY(xdat - 1, y-2); cout << "|";
        gotoXY(xdat + sl_ground + 1, y - 3); cout << "|";
    }
    for (int x = xdat; x <= xdat + sl_ground + 1; x++)
    {
        gotoXY(x, 0); cout << "=";
        gotoXY(x, ydat + 3); cout << "=";
    }
}
void xoa(int a[], int &n, int vt)
{
	for (int i = vt;i < n - 1;i++)
	{
		a[i] = a[i + 1];
	}
	n--;
}
void di_chuyen_tree(int t[], int &nt)
{
	if (t[0] == xdat)
	{
		xoa(t, nt, 0);
		clear_tree(xdat);
		clear_tree(xdat-1);
		clear_tree(xdat-2);
	}
	for (int i = 0;i < nt;i++)
	{
		draw_tree(t[i]);
		clear_tree(t[i]);
		t[i]--;
	}
	void clear_tree(int x)
{
    int y = ydat - 5;
    for (int i = 0; i < 5; i++)
    {
        gotoXY(x + 3, y + i);
        cout << " ";
    }
}
}
void GhiFile()
{
    ofstream FileOut;
    FileOut.open("E:\\score.txt", ios_base::out);
    FileOut << hiscore;
    FileOut.close();
}
void XuatFile()
{
    ifstream FileIn;
    FileIn.open("E:\\score.txt", ios_base::in);
    FileIn >> hiscore;
    cout << "HI Score: " << hiscore;
    FileIn.close();
}
