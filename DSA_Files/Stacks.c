//Write a program to push,pop and seek - followed by display
#include<stdio.h>
#include<stdlib.h>
int *stack,n,x,top,choice;
void push(){
if(top>=n-1)
    printf("The stack overflows");
else{
    printf("Enter the element to insert : ");
    scanf("%d",&x);
    top++;
    stack[top]=x;
}
}
void pop(){
if(top<=-1)
    printf("Stack Underflows");
else
{
    printf("Deleted element is : %d\n",stack[top]);
    top--;
}
}
void peek(){
if(top<=-1)
printf("Stack underflows");
else{
    printf("Deleted element is: %d\n",stack[top]);
    top--;
}
}
void print(){
    int temp=top;
    while(temp!=-1){
    printf("%d\t",stack[temp]);
    temp--;
    }
    printf("\n");
}
int main(){
    top=-1;
    printf("Enter the size of stack");
    scanf("%d",&n);
    stack=(int*)malloc(n*sizeof(int));
    printf("(1) Push\n(2) Pop\n(3)Peek\n(4)Display\n");

    do{
        printf("Enter the choice\n");
        scanf("%d",&choice);
        switch(choice){
            case 1:
            push();
            break;
            case 2:
            pop();
            break;
            case 3:
            peek();
            break;
            case 4:
            print();
            break;
        }
    }
    while(choice!=0);
}