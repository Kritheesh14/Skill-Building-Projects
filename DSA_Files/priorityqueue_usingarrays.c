// write a program to implement priority queue using array
#include<stdio.h>
#include<stdlib.h>
/*
typedef struct pqueue
{
    int data;
    int priority;
} q;
 #include<stdlib.h>
 int n,rear,front;
 int*q;
 void insert(){
    if(rear==n-1)
    {
        print("queue is full\n");
        return;
    }
    if(front==-1) front++;
    rear++;
    printf("Enter the input : \n");
    scanf("%d",&q[rear]);
    print("done\n");
    for(int i=rear;i>front&&)
    return;
 }
 */
struct pqueue
{
   int  data;
   int pty;
}
struct pqueue pq[10];
void pqinsert(int x,int pty,struct pqueue *pq,int *count)
       {
        // x is item to be inserted
       // pty is the priority of the item
      // pq is the pointer to the priority queue
     // count is the number of items in the queue

           int j;
           struct pqueue key;
           key. data=x;
           key.pty=pty;
        j=*count-1; // index of the initial position of the element
              
       //compare the priority of the item being inserted with the        
       //priority of the items in the queue
      // shift the items down while the priority of the item being 
      //inserted is greater than priority of the item in the queue
             
       while((j>=0)&&(pq[j].pty>key.pty))
              {  
                     pq[j+1]=pq[j];
      	      j--;
   	}
   	pq[j+1]=key; // insert the element at its correct location
   	(*count)++;
         }

