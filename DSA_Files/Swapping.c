//program to swap content of 2 variables
#include <stdio.h>
void swapbit(int a,int b){
    
    int *c=&a;
    int *d=&b;
    *c=*c^*d;
    *d=*c^*d;
    *c=*c^*d;
    printf("bitwise : %d %d",*c,*d);

}
void swap(int a,int b){
    int *c=&a;
    int *d=&b;
    int temp;
    temp=*c;
    *d=*c;
    *d=temp;
    printf("%d %d",*c,*d);
}
void main(){
    int a=10;
    int b=20;
    swapbit(a,b);
    printf("\n");
    swap(a,b);
}