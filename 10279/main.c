#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int MOVES[][2] = { {0, 1}, {1, 0}, {1, 1}, {-1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, -1} };

void print(int n, char t[2][n][n+1], int result){
    int i;
    for(i = 0; i < n; i++)
        puts(t[result][i]);
}


int moves_x(int i){
    return MOVES[i][0];
}


int moves_y(int i){
    return MOVES[i][1];
}


void input(int n, char grid[2][n][n+1]){
    int j,k;
    for(j = 0; j < 2; j++)
        for(k = 0; k < n; k++)
            scanf("%s", grid[j][k]);
}


int valid(int x, int y, int n){
    return x >= 0 && y >= 0 && x < n && y < n;
}


void set_zone(int x, int y, int n, char grid[2][n][n+1], int m){
    int i;
    grid[m][x][y] = '0';
    for(i = 0; i < 8; i++){
        int xplus = x + moves_x(i),
            yplus = y + moves_y(i);

        if(valid(xplus, yplus, n) && grid[0][xplus][yplus] == '*')
            grid[m][x][y]++;
    }
}


int solve(int n, char grid[2][n][n+1]){
    int i,j,k = 1;
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            if(grid[1][i][j] == 'x'){
                if(grid[0][i][j] == '*') k = 0;
                else set_zone(i, j, n, grid, 0);
                set_zone(i, j, n, grid, 1);
            }
        }
    }
    return k;
}


int main()
{
    int N, i, n;
    scanf("%d", &N);

    for(i = 0; i < N; i++){
        scanf("%d", &n);
        char grid[2][n][n+1];
        memset(grid, 0, 2 * n * (n + 1));
        input(n, grid);
        print(n, grid, solve(n, grid));
        if(i < N - 1) puts("");
    }
    return 0;
}
