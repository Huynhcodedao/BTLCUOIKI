#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <unistd.h> // sleep function

#include "config.h"
#include "botbaseline.h"

using namespace std;

int board_game[HEIGHT][WIDTH];
Point win_path[5];

void init_board_game();
int who_win();
void draw_win_path(int winner);
void play_game();
void play_game2();
Point check_n_tile(int board_game[][WIDTH], int player_id, int n);
Point player1_run();
Point player2_run();

void draw_background();

int main(){
    srand (time(NULL));

    set_text_color(WHITE_COLOR);
    int ChucNang = 1;
    do{
        reset:
        Menu(ChucNang);
        switch(ChucNang){
                case 1:{
                    play_game();
                    goto reset;
                }
                case 2:{
                    play_game2();
                    goto reset;
                }
                case 3:{
                    go_to_xy(Point(20, 11)); cout << "Cach choi: ";
                    go_to_xy(Point(20, 12)); cout << "Su dung cac nut a, w, d, x de di chuyen";
                    go_to_xy(Point(20, 13)); cout << "Nut s de danh";
                    go_to_xy(Point(20, 14)); cout << "Bam nut bat ki de thoat";
                    goto reset;
                }
                case 4:{
                    return 0;
                }
            }
    }while(true);
    return 0;
}

void init_board_game(){
    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            board_game[i][j] = 0;
            draw_tile(Point(BLOCK_RATIO*j, i), BLACK_COLOR);
        }
    }
}


void draw_win_path(int winner){

    bool turn = true;
    int color;
    int blink_count = 10;
    while(blink_count >= 0){
        if(winner == 1){
            if(turn) color = WHITE_COLOR;
            else color = BLACK_COLOR;
        } else {
            if(turn) color = RED_COLOR;
            else color = BLACK_COLOR;
        }
        for(int i = 0; i < 5; i++){
            draw_tile(win_path[i], color);
        }
        Sleep(500);
        turn = !turn;
        blink_count--;
    }

}

// 1. player 1 win . 0 means hoa, -1. player 2 win
int who_win(){
    return CheckWin(board_game);
}


//goc toa do (0;0) o goc tren ben trai
void draw_background(){
    set_text_color(BLUE_COLOR);

    //Ve khung cho ban co
    for(int i=0; i <= WIDTH; i++){
        go_to_xy(Point(10+i, 3));
        cout << char(220);
        go_to_xy(Point(10+i, HEIGHT));
        cout << char(220);
    }

    for(int i=4 ;i<= HEIGHT;i++){
        go_to_xy(Point(10, i));
        cout << char(219);
        go_to_xy(Point(10+WIDTH,i));
        cout << char(219);
    }

    // Ve cac o trong ban co
    Point p;
    int x, y;
    for(int i = 11; i <= WIDTH; i += 2){
        for(int j = 4; j <= HEIGHT; j++){
            x = (i-1)/2;
            y = j;
            p.x = i;
            p.y = j;
            if(x % 2==0){
                if(y % 2==0){
                    draw_tile(p, BLACK_COLOR);
                }else{
                    draw_tile(p, WHITE_COLOR);
                }
            }
            else{
                if(y % 2==0){
                    draw_tile(p, WHITE_COLOR);
                }
                else{
                    draw_tile(p, BLACK_COLOR);
                }
            }
        }
    }
    set_text_color(WHITE_COLOR);
}

Point player1_run(){
    return BotNhomNice(board_game, 1);
}

Point player2_run(Point truoc){
    return Player(board_game, truoc);
}

void play_game(){
    bool turn_player1 = true;
    int turn_limit = 3000;
    int row, col, winner, repeat_pos;
    Point position;
    char c;
    int d = 0;
    do{
        init_board_game();
        turn_player1 = true;
        turn_limit = 3000;

        while(turn_limit > 0){
            repeat_pos = 5;
            if(turn_player1){
                go_to_xy(Point(15, 0));  cout << "O danh";
                do{
                    position = player1_run();
                    if(repeat_pos == 0){
                        cout<<"player 1 is so stupid"<<endl;
                        return;
                    }
                    repeat_pos--;
                }while(board_game[position.x][position.y] != 0);

                board_game[position.x][position.y] = 1;
                draw_tile(Point(BLOCK_RATIO*position.y, position.x), WHITE_COLOR);
            } else {
                go_to_xy(Point(15, 0));  cout << "X danh";
                do{
                    position = player2_run(position);
                    if(repeat_pos == 0){
                        cout<<"player 2 is so stupid"<<endl;
                        return;
                    }
                    repeat_pos--;
                }while(board_game[position.x][position.y] != 0);
                board_game[position.x][position.y] = -1;
                draw_tile(Point(BLOCK_RATIO*position.y, position.x), RED_COLOR);
            }

            winner = who_win();
            if(winner != 0){
                go_to_xy(Point(WIDTH/2, HEIGHT+5));
                cout<<winner<<" win"<<endl;
                draw_win_path(winner);
                return;
            }

            turn_player1 = !turn_player1;

            turn_limit--;
            Sleep(PAUSE_TIME);
        }
    }while(true);
}

void play_game2(){
    bool turn_player1 = true;
    int turn_limit = 3000;
    int row, col, winner, repeat_pos;
    Point position;
    char c;
    int d = 0;
    do{
        init_board_game();
        turn_player1 = true;
        turn_limit = 3000;

        while(turn_limit > 0){
            repeat_pos = 5;
            if(turn_player1){
                go_to_xy(Point(15, 0));  cout << "O danh";
                do{
                    if(d == 0){
                        d = 1;
                        position = Point(13, 25);
                    }else   position = player2_run(position);
                    if(repeat_pos == 0){
                        cout<<"player 1 is so stupid"<<endl;
                        return;
                    }
                    repeat_pos--;
                }while(board_game[position.x][position.y] != 0);

                board_game[position.x][position.y] = 1;
                draw_tile(Point(BLOCK_RATIO*position.y, position.x), WHITE_COLOR);
            } else {
                go_to_xy(Point(15, 0));  cout << "X danh";
                do{
                    position = player2_run(position);
                    if(repeat_pos == 0){
                        cout<<"player 2 is so stupid"<<endl;
                        return;
                    }
                    repeat_pos--;
                }while(board_game[position.x][position.y] != 0);
                board_game[position.x][position.y] = -1;
                draw_tile(Point(BLOCK_RATIO*position.y, position.x), RED_COLOR);
            }

            winner = who_win();
            if(winner != 0){
                go_to_xy(Point(WIDTH/2, HEIGHT+5));
                cout<<winner<<" win"<<endl;
                draw_win_path(winner);
                return;
            }

            turn_player1 = !turn_player1;

            turn_limit--;
            Sleep(PAUSE_TIME);
        }
    }while(true);
}
