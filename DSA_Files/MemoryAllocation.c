#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<malloc.h>
int main(){
    int *x;
    x=(int*)malloc(20);
    if(x==NULL){
    printf("Memory allocation isnt possible\n");
    return 1;}
    printf("the size in %d bytes\n",_msize(x));
    free(x);
    x=(int*)calloc(5,sizeof(int));
    if(x==NULL){
        printf("continguous memory allocation isnt possible\n");
        return 1;
    }
    printf("The size in %d bytes\n",_msize(x));
    x=(int*)realloc(x,40);
    if(x==NULL){
        printf("Reallocation of memory isnt possible");
        return 1;
    }
    printf("The size in %d bytes",_msize(x));
}