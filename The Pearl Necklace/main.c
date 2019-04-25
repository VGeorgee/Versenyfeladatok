#include <stdio.h>
#include <stdlib.h>

int matrix[1000][1001] = {0};
int mano[1001] = {0};
int szin[2][1001][20] = {0};
char *lanc;

int rec(int si, int mi){

    if(lanc[si] == 'D' || matrix[si][mi]) return matrix[si][mi];

    int i, player = lanc[si] == 'B' ? 0 : 1;

    for(i = 0; szin[player][mi][i]; i++){

        int ret = rec(si + 1, szin[player][mi][i]);

        if((mano[mi] == 0) && (ret > 0)){
            matrix[si][mi] = (szin[player][mi][i]);
            return ret;
        }
        if((mano[mi] == 1 )&& (ret < 0)){
          matrix[si][mi] = -1;
          return -1;
        }
    }

    return matrix[si][mi] = szin[player][mi][0];
}


void printmatrix(int N, int L){
    int i, j;
     puts("");
     puts("");
    for(j = 0; j < N+1; j++){
        for(i = 0; i < L+1; i++)
            printf("%2d", matrix[i][j]);
        puts("");
    }
}

int main()
{
    int L, N, F, i,j,k,l, lepes;
    scanf("%d %d %d", &L, &N, &F);
    char s[L];
    scanf("%s", s);
    lanc = s;
    for(i = 0; i < N; i++){
        scanf("%d", &mano[i+1]);
        int w,b;
        scanf("%d", &b);
        for(j = 0; j < b; j++) scanf("%d", &szin[0][i+1][j]);
        scanf("%d", &w);
        for(j = 0; j < w; j++) scanf("%d", &szin[1][i+1][j]);
    }

    for(i = 0; i < N; i++) matrix[L-1][i+1] = mano[i+1] == 1 ? -1 : 1;


    //printmatrix(N, L);

    rec(0, F);
    lepes = F;

    for(i = 0; lanc[i] != 'D'; i++){
        int csapat = mano[lepes];

        if(csapat){
            setNext(matrix[i][lepes]);
            lepes = matrix[i][lepes];
        }
        else lepes = getNext();
    }
    finish();

    // printmatrix(N, L);

    return 0;
}

