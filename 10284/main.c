#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int chess[8][8];
int kingKnightMoves[][8][2] = {
    {{-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}},
    {{-1, -2}, {-2, -1}, {1, -2}, {2, -1}, {1, 2}, {2, 1}, {-2, 1}, {-1, 2}}
};

int valid(int x, int y){
    return x >= 0 && y >= 0 && x < 8 && y < 8;
}

void setAttack(int x, int y){
    if(chess[x][y] == 0)
        chess[x][y] = 1;
}

void move(int x, int y, int mx, int my,int self){
    if(!valid(x, y)) return;
    if(self || chess[x][y] < 2){
        if(!self) setAttack(x, y);
    return move(x+mx, y+my, mx, my, 0);
    }

}

void kingknight(int x, int y, int type){
    int i;
    for(i = 0; i < 8; i++)
        if(valid(x + kingKnightMoves[type][i][0], y + kingKnightMoves[type][i][1]))
            setAttack(x + kingKnightMoves[type][i][0], y + kingKnightMoves[type][i][1]);
}

void rook(int x, int y){
    move(x, y, -1, 0, 1);
    move(x, y, 0, -1, 1);
    move(x, y, 1, 0, 1);
    move(x, y, 0, 1, 1);
}

void bishop(int x, int y){
    move(x, y, -1, -1, 1);
    move(x, y, 1, 1, 1);
    move(x, y, 1, -1, 1);
    move(x, y, -1, 1, 1);
}

void queen(int x, int y){
    rook(x, y);
    bishop(x, y);
}

void pawn(int x, int y, int type){
    if(type){
        if(valid(x-1, y-1)) setAttack(x-1, y-1);
        if(valid(x-1, y+1)) setAttack(x-1, y+1);
    }
    else{
        if(valid(x+1, y-1)) setAttack(x+1, y-1);
        if(valid(x+1, y+1)) setAttack(x+1, y+1);
    }
}

void putchess(){
    int i,j, db = 0;
    for(i = 0; i < 8; i++)
        for(j = 0; j < 8; j++)
            if(chess[i][j] == 0) db++;
    printf("%d\n", db);
}
int main()
{

    int i = 0,j = 0,k, db = 0;
    char s[80];
    while(scanf("%s", s) != EOF){
        for(i = 0; i < 8; i++)
            for(j = 0; j < 8; j++)
                chess[i][j] = 0;
        char *token = strtok(s, "/");
        i = j = db = 0;
        while(token){
            for(k = j = 0; token[k]; k++){
                if(isdigit(token[k])) j += token[k] - '0';
                else chess[i][j++] = token[k];
            }
            i++;
            token = strtok(NULL, "/");
        }

        for(i = 0; i < 8; i++){
            for(j = 0; j < 8; j++){
                if(chess[i][j] == 'q' || chess[i][j] == 'Q') queen(i, j);
                    else if(chess[i][j] == 'r' || chess[i][j] == 'R') rook(i, j);
                    else if(chess[i][j] == 'k' || chess[i][j] == 'K') kingknight(i, j, 0);
                    else if(chess[i][j] == 'n' || chess[i][j] == 'N') kingknight(i, j, 1);
                    else if(chess[i][j] == 'b' || chess[i][j] == 'B') bishop(i, j);
                    else if(chess[i][j] == 'p') pawn(i, j, 0);
                    else if(chess[i][j] == 'P') pawn(i, j, 1);
            }
        }
    putchess();
    }

    return 0;
}
