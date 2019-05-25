#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

void convert_line_to_alphas(char *src, char *dst){
    int i,j;
    for(i = j = 0; src[i]; i++)
        if(isalpha(src[i]))
            dst[j++] = tolower(src[i]);
    dst[j] = '\0';
}


void transpose_string(char *src, char *dst, int n){
    int i;
    for(i = 0; src[i]; i++)
        dst[i] = src[(i / n) + (i % n) * n];

    dst[i] = '\0';
}


int is_palindrome(char *string){
    int i, j;
    for(i = 0, j = strlen(string) - 1; i <= j; i++, j--)
        if((string[i] != string[j])) return 0;

    return 1;
}


int is_magic_square(char *alphas){

    int n, len = strlen(alphas);

    if(len == 0) return 0; /* 0*0 magic square */
    if((n = sqrt(len)) != sqrt(len)) return -1;

    char transpose[len + 1];
    transpose_string(alphas, transpose, n);

    return is_palindrome(alphas) && is_palindrome(transpose) ? n : -1;
}


void print(int index, int result){

    printf("Case #%d:\n", index + 1);

    if(result == -1) puts("No magic :(");
    else printf("%d\n", result);
}


int main()
{
    int N, i, result;
    char line[10001], alphas[10001];
    scanf("%d\n", &N);
    for(i = 0; i < N; i++){
        gets(line);
        convert_line_to_alphas(line, alphas);
        result = is_magic_square(alphas);
        print(i, result);
    }
    return 0;
}
