#include<stdio.h>
#include<stdlib.h>
struct node{int data;struct node* next};
void printlist(struct node* head) {
    if (head==NULL) {
        printf("List is empty\n");
        return;
    }
    struct node* temp=head; 
    while (temp!=NULL) {
        printf("%d -> ",temp->data);
        temp=temp->next;
    }
    printf("NULL\n");
}
void concat(struct node*head1,struct node*head2){
    struct node* temp=head1;
    if(temp==NULL){
        head1=head2;
    }
    else{
        while(temp->next!=NULL){
            temp=temp->next;}
            temp->next=head2;
    printlist(head1);
    }
}
void main(){
    
}