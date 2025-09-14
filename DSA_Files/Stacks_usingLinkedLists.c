//Implementation of stack using linked List (singly linked list)
#include <stdio.h>
#include <stdlib.h>
//structure of node
struct node
{
    int data;
    struct node *next;
};

struct node *top=NULL;
int choice,x,thresh;

int overflowcheck()
{
    int x;
    struct  node *temp=top;
        while(temp!=NULL){
            x++;
            temp=temp->next;
        }    
    if(x>=thresh){
        printf("Overflow");
        return 0;
    }
}
void push()
{
    printf("Enter (1) to check overflow, Enter (0) to ignore overflow : ");
    int ch;
    scanf("%d",&ch);
    if(ch==1){
    if(overflowcheck()){
        struct node *newnode=(struct node*)malloc(sizeof(struct node));
if(newnode==NULL)
printf("Value cannot be inserted\n");
else
{
    printf("Enter the value to be inserted\n");
    scanf("%d",&x);
    newnode->data=x;
    newnode->next=top;
    top=newnode;
}

}
else{

struct node *newnode=(struct node*)malloc(sizeof(struct node));
if(newnode==NULL)
printf("Value cannot be inserted\n");
else
{
    printf("Enter the value to be inserted\n");
    scanf("%d",&x);
    newnode->data=x;
    newnode->next=top;
    top=newnode;
}

    }
}
}

void pop()
{   
    if(top==NULL)
    printf("Stack is empty - Underflow\n");
    else
    {
        struct node *temp=top;
        printf("Deleted element is %d\n",temp->data);
        top=top->next;
        free(temp);
    }
}
void print()
{
    if(top==NULL)
    printf("Empty stack\n");
    else
    {
        printf("The content of the stack\n");
        struct  node *temp=top;
        while(temp!=NULL){
            printf("------------------\n\t%d\n",temp->data);
            temp=temp->next;
        }
        printf("------------------\n");
    }
}
void peek()
{   
    if(top==NULL)
    printf("Stack is empty\n");
    else
        printf("Top element of stack : %d\n",top->data);
}

void main()
{
    printf("Enter the size of stack : ");
    scanf("%d",&thresh);
    printf("Enter the stack operations\n1)Push\n2)Pop\n3)Peek\n4)Print\n");
    while(1){
        printf("Enter the choice : ");
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
            case 0:
            printf("Exiting...");
            exit(0);
        }
    }

}