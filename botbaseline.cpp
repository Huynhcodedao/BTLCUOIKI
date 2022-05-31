#include "botbaseline.h"

using namespace std;
long TC[7] = {0, 3, 24, 192, 1536, 12200, 90304};
long PN[7] = {0, 1, 9, 81, 729, 6561, 59999};
void go_to_xy(Point p){
    COORD coord;
    coord.X = p.x;
    coord.Y = p.y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void draw_tile(Point p, int color){
    go_to_xy(p);
    set_text_color(color);
    for(int i = 0; i < BLOCK_RATIO; i++) {
        if(color == WHITE_COLOR)
            cout<<"O";
        else cout<<"X";
    }
}
void set_text_color(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int CheckWin(int a[30][50]){
	int d;
	for(int i=0; i<30; i++)
		for(int j=0; j<50; j++)
			if(a[i][j] != 0){
				if(i + 4 < 30 && a[i][j] == a[i+1][j] && a[i][j] == a[i+2][j] && a[i][j] == a[i+3][j] && a[i][j] == a[i+4][j]
                    && i > 0 && !(a[i - 1][j] == -a[i][j] && a[i + 5][j] == -a[i][j])){
					return a[i][j];
				}
				if(j + 4 < 50 && a[i][j] == a[i][j+1] && a[i][j] == a[i][j+2] && a[i][j] == a[i][j+3] && a[i][j] == a[i][j+4]
                    && j > 0 && !(a[i][j - 1] == -a[i][j] && a[i][j + 5] == -a[i][j])){
					return a[i][j];
				}
				if(i + 4 < 30 && j + 4 < 50 && a[i][j] == a[i+1][j+1] && a[i][j] == a[i+2][j+2] && a[i][j] == a[i+3][j+3] && a[i][j] == a[i+4][j+4]
                    && i > 0 && j > 0 && !(a[i-1][j-1] == -a[i][j] && a[i+5][j+5] == -a[i][j])){
					return a[i][j];
				}
				if(i + 4 < 30 && j - 4 >= 0 && a[i][j] == a[i+1][j-1] && a[i][j] == a[i+2][j-2] && a[i][j] == a[i+3][j-3] && a[i][j] == a[i+4][j-4]
                    && i > 0 && j < 30 && !(a[i-1][j+1] == -a[i][j] && a[i+5][j-1] == -a[i][j])){
					return a[i][j];
				}
			}
	return 0;
}

//===== Choi ===
Point Player(int a[30][50], Point dich){
    char dk;
    int x = dich.y;
    int y = dich.x;
    do{
        if(kbhit()){
            dk = getch();
            switch(dk){
                case 'w':{
                    y--;
                    if(y == -1)
                        y = 0;
                    break;
                }
                case 'x':{
                    y++;
                    if(y == 30)
                        y = 29;
                    break;
                }
                case 'a':{
                    x--;
                    if(x == -1)
                        x = 0;
                    break;
                }
                case 'd':{
                    x++;
                    if(x == 50)
                        x = 49;
                    break;
                }
                case 's':{
                    if(a[x][y] == 0)
                        return Point(y, x);
                }
            }
          go_to_xy(Point(x, y));
        }
    }while(1);
}
// BOT
long DuyetTCDoc(int x, int y, int a[][50], int id){
	long diemTong = 0;
	long diemTC = 0;
	int ta = 0, dich = 0;
	for(int i=1; i< 6 && x + i < 30; i++)
		if(a[x+i][y] == id){
			ta++;
		}else if(a[x+i][y] == -id){
			dich++;
			break;
		}else	break;

	for(int i=1; i< 6 && x - i >= 0; i++)
		if(a[x-i][y] == id){
			ta++;
		}else if(a[x-i][y] == -id){
			dich++;
			break;
		}else	break;
	if(dich == 2)	return 0;
	diemTong -= PN[dich + 1];
	diemTong += TC[ta];
	return diemTong;
}
long DuyetTCNgang(int x, int y, int a[][50], int id){
	long diemTong = 0;
	long diemTC = 0;
	int ta = 0, dich = 0;
	for(int i=1; i< 6 && y + i < 50; i++)
		if(a[x][y+i] == id){
			ta++;
		}else if(a[x][y+i] == -id){
			dich++;
			break;
		}else	break;

	for(int i=1; i< 6 && y - i >= 0; i++)
		if(a[x][y-i] == id){
			ta++;
		}else if(a[x][y-i] == -id){
			dich++;
			break;
		}else	break;
	if(dich == 2)	return 0;
	diemTong -= PN[dich + 1];
	diemTong += TC[ta];
	return diemTong;
}
long DuyetTCCheoLen(int x, int y, int a[][50], int id){
	long diemTong = 0;
	long diemTC = 0;
	int ta = 0, dich = 0;
	for(int i=1; i< 6 && y + i < 50 && x - i >= 0; i++)
		if(a[x-i][y+i] == id){
			ta++;
		}else if(a[x-i][y+i] == -id){
			dich++;
			break;
		}else	break;

	for(int i=1; i< 6 && x + i < 30 && y - i >= 0; i++)
		if(a[x+i][y-i] == id){
			ta++;
		}else if(a[x+i][y-i] == -id){
			dich++;
			break;
		}else	break;
	if(dich == 2)	return 0;
	diemTong -= PN[dich + 1];
	diemTong += TC[ta];
	return diemTong;
}
long DuyetTCCheoXuong(int x, int y, int a[][50], int id){
	long diemTong = 0;
	long diemTC = 0;
	int ta = 0, dich = 0;
	for(int i=1; i< 6 && x + i < 30 && y + i < 50; i++)
		if(a[x+i][y+i] == id){
			ta++;
		}else if(a[x+i][y+i] == -id){
			dich++;
			break;
		}else	break;

	for(int i=1; i< 6 && x - i >= 0 && y - i >= 0; i++)
		if(a[x-i][y-i] == id){
			ta++;
		}else if(a[x-i][y-i] == -id){
			dich++;
			break;
		}else	break;
	if(dich == 2)	return 0;
	diemTong -= PN[dich + 1];
	diemTong += TC[ta];
	return diemTong;
}

long DuyetPNDoc(int x, int y, int a[][50], int id){
	long diemTong = 0;
	long diemTC = 0;
	int ta = 0, dich = 0;
	for(int i=1; i< 6 && x + i < 30; i++)
		if(a[x+i][y] == id){
			ta++;
			break;
		}else if(a[x+i][y] == -id){
			dich++;
		}else	break;

	for(int i=1; i< 6 && x - i >= 0; i++)
		if(a[x-i][y] == id){
			ta++;
			break;
		}else if(a[x-i][y] == -id){
			dich++;
		}else	break;
	if(ta == 2)	return 0;
	diemTong += PN[dich];
	return diemTong;
}
long DuyetPNNgang(int x, int y, int a[][50], int id){
	long diemTong = 0;
	long diemTC = 0;
	int ta = 0, dich = 0;
	for(int i=1; i< 6 && y + i < 30; i++)
		if(a[x][y+i] == id){
			ta++;
			break;
		}else if(a[x][y+i] == -id){
			dich++;
		}else	break;

	for(int i=1; i< 6 && y - i >= 0; i++)
		if(a[x][y-i] == id){
			ta++;
			break;
		}else if(a[x][y-i] == -id){
			dich++;
		}else	break;
	if(ta == 2)	return 0;
	diemTong += PN[dich];
	return diemTong;
}
long DuyetPNCheoLen(int x, int y, int a[][50], int id){
	long diemTong = 0;
	long diemTC = 0;
	int ta = 0, dich = 0;
	for(int i=1; i< 6 && y + i < 50 && x - i >= 0; i++)
		if(a[x-i][y+i] == id){
			ta++;
			break;
		}else if(a[x-i][y+i] == -id){
			dich++;
		}else	break;

	for(int i=1; i< 6 && y - i >= 0 && x + i < 30; i++)
		if(a[x+i][y-i] == id){
			ta++;
			break;
		}else if(a[x+i][y-i] == -id){
			dich++;
		}else	break;
	if(ta == 2)	return 0;
	diemTong += PN[dich];
	return diemTong;
}
long DuyetPNCheoXuong(int x, int y, int a[][50], int id){
	long diemTong = 0;
	long diemTC = 0;
	int ta = 0, dich = 0;
	for(int i=1; i< 6 && x + i < 30 && y + i < 50; i++)
		if(a[x+i][y+i] == id){
			ta++;
			break;
		}else if(a[x+i][y+i] == -id){
			dich++;
		}else	break;

	for(int i=1; i< 6 && x - i >= 0 && y - i >= 0; i++)
		if(a[x-i][y-i] == id){
			ta++;
			break;
		}else if(a[x-i][y-i] == -id){
			dich++;
		}else	break;
	if(ta == 2)	return 0;
	diemTong += PN[dich];
	return diemTong;
}
Point BotNhomNice(int a[][50], int id){
	int max = 0;
	int x, y;
	for(int i=0; i<30; i++)
		for(int j=0; j<50; j++)
			if(a[i][j] == 0){
				long AT = DuyetTCDoc(i, j, a, id) + DuyetTCNgang(i, j, a, id) + DuyetTCCheoLen(i, j, a, id) + DuyetTCCheoXuong(i, j, a, id);
				long DF = DuyetPNDoc(i, j, a, id) + DuyetPNNgang(i, j, a, id) + DuyetPNCheoLen(i, j, a, id) + DuyetPNCheoXuong(i, j, a, id);
				long diem = AT > DF ? AT : DF;
				if(max < diem){
					max = diem;
					x = i;
					y = j;
				}
			}
    if(max == 0)    return Point(13, 25);
    return Point(x, y);
}
void Menu(int &ChucNang){
    char c;
    set_text_color(14);
    go_to_xy(Point(20, 10));    cout << "Choi voi may";
    go_to_xy(Point(20, 11));    cout << "Choi voi nguoi";
    go_to_xy(Point(20, 12));    cout << "Gioi thieu";
    go_to_xy(Point(20, 13));    cout << "Thoat";
    do{
        if(kbhit()){
            c = getch();
            set_text_color(14);
            go_to_xy(Point(20, 10));    cout << "Choi voi may";
            go_to_xy(Point(20, 11));    cout << "Choi voi nguoi";
            go_to_xy(Point(20, 12));    cout << "Gioi thieu";
            go_to_xy(Point(20, 13));    cout << "Thoat";
            switch(c){
                case 'w':{
                    ChucNang--;
                    if(ChucNang == 0)
                        ChucNang = 4;
                    break;
                }
                case 'x':{
                    ChucNang++;
                    if(ChucNang == 5)
                        ChucNang = 1;
                    break;
                }
                case 's':{
                    return;
                }
            }
            set_text_color(4);
            switch(ChucNang){
                case 1:{
                    go_to_xy(Point(20, 10));    cout << "Choi voi may";
                    break;
                }
                case 2:{
                     go_to_xy(Point(20, 11));    cout << "Choi voi nguoi";
                      break;
                }
                case 3:{
                      go_to_xy(Point(20, 12));    cout << "Gioi thieu";
                        break;
                }
                case 4:{
                       go_to_xy(Point(20, 13));    cout << "Thoat";
                }
            }
        }
    }while(true);
}
