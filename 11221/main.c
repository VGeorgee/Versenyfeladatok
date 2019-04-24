#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

int getAlphas(char *dst, char *src){
    int i,j;
    for(i = j = 0; src[i]; i++)
        if(isalpha(src[i]))
            dst[j++] = tolower(src[i]);
    dst[j] = '\0';
    return j;
}

int isMagicSquarePalindrome(char *original, int len){

    if(len == 0) return 0; /* 0*0 magic square */

    int i, j, n;
    if((n = sqrt(len)) != sqrt(len)) return -1;
    char matrix[len + 1];

    for(i = 0; i < len; i++)
        matrix[i] = original[i/n + (i%n) * n];
    matrix[len] = '\0';

    for(i = 0, j = len-1; i < len; i++, j--)
        if((original[i] != original[j]) || (matrix[i] != matrix[j]))
            return -1;

    return n;
}

int main()
{
    int N, i;
    char sor[10001], alphas[10001];
    scanf("%d\n", &N);
    for(i = 0; i < N; i++){
        int len = getAlphas(alphas, gets(sor));
        int result = isMagicSquarePalindrome(alphas, len);

        printf("Case #%d:\n", i+1);
        if(result == -1) puts("No magic :(");
        else  printf("%d\n", result);
    }
    return 0;
}
