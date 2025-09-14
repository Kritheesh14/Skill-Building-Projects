#include <stdio.h>
#include <stdlib.h>
// enqueue, dequeue, peek, size
#define max 3
int queue[max];
int front=-1, rear=-1;


void enqueue()
{
int x;
    if (rear == max - 1) {
        printf("Queue is full\n");
    } else {
        printf("Enter the value\n");
        scanf("%d", &x);
        if (front == -1) {
            front = 0;
        }
        rear += 1;
        queue[rear] = x;
    }
}


void dequeue()
{
    if(front==-1||front>rear)
    printf("Queue is Empty\n");
    else
    {
        printf("%d\n",queue[front]);
        front++;
        if(front>rear)
        {
            front=rear=-1;
        }
    }
}   

void peek()
{
    if(front==-1||front>rear)
        printf("Queue is Empty");
    else
        printf(" Top element : %d\n",queue[front]);
    
}

void display()
{
    if(front==-1||front>rear){
    printf("Queue is empty\n");}
    else
    {   
        printf("Queue :\n ");
        for(int i=front;i<=rear;i++){
            printf("%d\t",queue[i]);}
        printf("\n");
    }
}


void main()
{
    printf("(1)Insert\n(2)Delete\n(3)Peek\n(4)Display\n(0)exit\n");
    int choice=-1;
    do{
        printf("Enter the choice\n");
        scanf("%d",&choice);
        switch(choice){
            case 1:
            enqueue();
            break;
            case 2:
            dequeue();
            break;
            case 3:
            peek();
            break;
            case 4:
            display();
            break;
        }
    }
    while(choice!=0);
}