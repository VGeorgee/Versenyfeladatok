#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int chess[8][8];

int moves[][8][2] = {
    { {-1, -1}, {-1,  0}, {-1,  1}, {0,  1},  {1,  1}, {1,  0}, { 1, -1}, { 0, -1} },
    { {-1, -2}, {-2, -1}, { 1, -2}, {2, -1},  {1,  2}, {2,  1}, {-2,  1}, {-1,  2} }
};


int valid(int x, int y){
    return x >= 0 && y >= 0 && x < 8 && y < 8;
}


void set_attack(int x, int y){
    if(chess[x][y] == 0)
        chess[x][y] = 1;
}


void move(int x, int y, int mx, int my,int self){
    if(!valid(x, y)) return;
    if(self || chess[x][y] < 2){
        if(!self) set_attack(x, y);
            move(x+mx, y+my, mx, my, 0);
    }
}


void king_knight(int x, int y, int type){
    int i;
    for(i = 0; i < 8; i++)
        if(valid(x + moves[type][i][0], y + moves[type][i][1]))
            set_attack(x + moves[type][i][0], y + moves[type][i][1]);
}


void rook(int x, int y){
    int i;
    for(i = 1; i < 8; i += 2)
        move(x, y, moves[0][i][0], moves[0][i][1], 1);
}


void bishop(int x, int y){
   int i;
    for(i = 0; i < 8; i += 2)
        move(x, y, moves[0][i][0], moves[0][i][1], 1);
}


void queen(int x, int y){
    rook(x, y);
    bishop(x, y);
}


void pawn(int x, int y, int type){
    if(type){
        if(valid(x-1, y-1)) set_attack(x-1, y-1);
        if(valid(x-1, y+1)) set_attack(x-1, y+1);
    }
    else{
        if(valid(x+1, y-1)) set_attack(x+1, y-1);
        if(valid(x+1, y+1)) set_attack(x+1, y+1);
    }
}


void print_result(){
    int i,j, db = 0;
    for(i = 0; i < 8; i++)
        for(j = 0; j < 8; j++)
            if(chess[i][j] == 0) db++;
    printf("%d\n", db);
}


void init_chess(){
    int i,j;
    for(i = 0; i < 8; i++)
        for(j = 0; j < 8; j++)
            chess[i][j] = 0;
}


void set_chess(char *s){
    char *token = strtok(s, "/");
    int i, j, k;
    for(i = 0; token; i++){
        for(k = j = 0; token[k]; k++){
            if(isdigit(token[k])) j += token[k] - '0';
            else chess[i][j++] = token[k];
        }
        token = strtok(NULL, "/");
    }
}


void solve_chess(){
    int i, j, ch;
    for(i = 0; i < 8; i++){
        for(j = 0; j < 8; j++){
            ch = chess[i][j];
            if(     ch == 'q' || ch == 'Q') queen (i, j);
            else if(ch == 'r' || ch == 'R') rook  (i, j);
            else if(ch == 'b' || ch == 'B') bishop(i, j);
            else if(ch == 'k' || ch == 'K') king_knight(i, j, 0);
            else if(ch == 'n' || ch == 'N') king_knight(i, j, 1);
            else if(ch == 'p')              pawn(i, j, 0);
            else if(ch == 'P')              pawn(i, j, 1);
        }
    }
}


int main()
{
    char s[40];
    while(scanf("%s", s) != EOF){
        init_chess();
        set_chess(s);
        solve_chess();
        print_result();
    }
    return 0;
}
