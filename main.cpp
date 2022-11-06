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
int menu();
void help();
void INTROGAME();
void draw_dino(int x, int y);
void khoi_tao_mat_dat();
void draw_tree(int x); 
void tao_dat(int i);
void di_chuyen_mat_dat();
bool game_over(int x, int y, int t[], int nt); 
void draw_mat_dat();
void draw_wall();
void xoa(int a[], int &n, int vt);
void di_chuyen_tree(int t[], int &nt);
void clear_tree(int x);
void XuatFile();
void GhiFile();
int main()
{
     INTROGAME();
    while (1)
    {
        system("MODE CON: COLS=150 LINES=48");
        system("cls");
        if (fix1 != 0)
        {
            play();
            continue;

        }
        int choice = menu();

        switch (choice)
        {
        case 0:
            play();
            break;
        case 1:
            help();
            break;
        default:
            return KEY_ESC;
        }
    }   
}
void play()
{
    //============== setup ========
    int score = 0;
    draw_wall();
    int t[100]; int nt = 0; int count = 0;
    draw_dino(xdino, ydino);
    khoi_tao_mat_dat();
    draw_mat_dat();
    int x = xdino; int y = ydino;
    int check = 2;//2: dung im
    //1: di len
    //0: di xuong
//============ play ==========
    while (true)
    {
        gotoXY(65, 3);
        XuatFile();
        gotoXY(85, 3);
        cout << "Score: " << score++;
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
            if (score > hiscore) {
                hiscore = score;
                GhiFile();
            }
            break;
        }
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
                    check = 1; kt_jump = true;
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
        else if (y == ydino)
        {
            if (check != 2)
            {
                draw_dino(x,y);
                check = 2; kt_jump = false;
            }

        }
        //------- speed -------
        count--;
        Sleep(10);
    }
}
void help()
{
    system("cls");
    gotoXY(nScreenWidth / 2, 20);
    cout << "HELP";
    gotoXY(25, 22);
    cout << "Nhan SPACE hoac phim MUI TEN DI LEN de dieu khien khung long vuot qua chuong ngai vat la cay xuong hoac chim";
    gotoXY(65, 24);
    system("pause");
}
void INTROGAME()
{
    ShowCur();
    system("MODE CON: COLS=150 LINES=48");  //COLS nScreenWidth

    int x = nScreenWidth / 2 - 30;
    int y = nScreenHeight / 2 - 5;
    int n;
    gotoXY(x, y);
    cout << "________ _____                     _________                          ";
    gotoXY(x, y + 1);
    cout << "___  __ \\___(_)_______ ______      __  ____/______ ________ ___ _____ ";
    gotoXY(x, y + 2);
    cout << "__  / / /__  / __  __ \\_  __ \\     _  / __  _  __ `/__  __ `__ \\_  _ \\";
    gotoXY(x, y + 3);
    cout << "_  /_/ / _  /  _  / / // /_/ /     / /_/ /  / /_/ / _  / / / / //  __/";
    gotoXY(x, y + 4);
    cout << "/_____/  /_/   /_/ /_/ \\____/      \\____/   \\__,_/  /_/ /_/ /_/ \\___/ ";

    while (!keyPressed())
    {
        Sleep(200);
        gotoXY(x + 20, y + 6);
        cout << "Press any key to continue";

        Sleep(800);
        gotoXY(x + 20, y + 6);
        cout << "                         ";
    }
}
int menu()
{
    int x = nScreenWidth / 2 - 30;
    int y = nScreenHeight / 2 - 5;
    string str;
    ShowCur();
    int maxmenu = 3;
    string menu[3];
    menu[0] = "NEW GAME";
    menu[1] = "HELP";
    menu[2] = "EXIT";
    int line = 0;
    while (1)
    {
        system("cls");
        for (int i = 0; i < maxmenu; i++)
            if (i != line)
            {
                TextColor(15);
                gotoXY(nScreenWidth / 2 - 3, nScreenHeight / 2 - 3 + i);
                cout << menu[i] << endl;
            }
            else
            {
                TextColor(12);
                gotoXY(nScreenWidth / 2 - 3, nScreenHeight / 2 - 3 + i);
                cout << menu[i] << endl;
            }

        int status = KEY_RIGHT;
        if (keyPressed()) status = getKey();

        switch (status)
        {
        case KEY_UP:
            line--;
            if (line == -1) line = maxmenu - 1;
            break;
        case KEY_DOWN:
            line++;
            if (line == maxmenu) line = 0;
            break;
        case KEY_ENTER:
            system("cls");
            return line;
        }
        Sleep(100);
    }
}
void help()
{
    system("cls");
    gotoXY(nScreenWidth / 2, 20);
    cout << "HELP";
    gotoXY(25, 22);
    cout << "Nhan SPACE hoac phim MUI TEN DI LEN de dieu khien khung long vuot qua chuong ngai vat la cay xuong hoac chim";
    gotoXY(65, 24);
    system("pause");
}
void di_chuyen_mat_dat()
{
    //doi
    for (int i = 0; i < sl_ground - 1; i++)
    {
        ground[1][i] = ground[1][i + 1];
        ground[2][i] = ground[2][i + 1];
    }
    //chen
    tao_dat(sl_ground - 1);
    //draw
    draw_mat_dat();
}
bool game_over(int x, int y, int t[], int nt)
{
    int a;
    for (int i = 0; i < nt; i++)
    {
        if (kt_cham(t[i], x, y))
        {
            gotoXY(x, y);
            cout << die;
            gotoXY(x + 25, y - 5);
            cout << "GAME OVER";
            gotoXY(x + 17, y - 4);
            if (!keyPressed())
            {
                Sleep(800);
                gotoXY(x + 18, y - 3);
                cout << "Press SPACE to continue";
                a = getKey();
                if (a == KEY_SPACE) 
                {
                    system("cls");
                    fix1++;
                    break;
                }
                else
                {
                    fix1 = 0;
                    break;
                }
                return true;
            }
        }
        return false;
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
void draw_tree(int x)
{
    int y = ydat - 5;
    for (int i = 0; i < 5; i++)
    {
        gotoXY(x, y + i);
        cout << tree[i];
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
