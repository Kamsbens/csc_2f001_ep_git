#include <stdio.h>
#include <stdlib.h>
// gcc -Wall -Werror hello.c -o hello

int main(){
    int grid[10] = {0};
    int i = 0;
    while(i<10){
    printf("%i\n",grid[i]);
    i++;
    }
    return 0;
}

