#include <stdio.h>
#include <stdlib.h>
struct node {
    int data;
    struct node* next;
    struct node* prev;
};
void printlist(struct node* head) {
    if(head==NULL) {
        printf("List is empty\n");
        return;
    }
    struct node* temp=head;
    while(temp!=NULL) { //Traverse the list until the end - checking value of next == null
        printf("%d <-> ",temp->data);
        temp=temp->next;
    }
    printf("NULL\n");
}
struct node* assign(int idata) {
    struct node* new=(struct node*)malloc(sizeof(struct node));
    new->data=idata;
    new->next=NULL;
    new->prev=NULL;
    return new;
}
struct node* insertbeg(struct node* head, int idata) {
    struct node* new=assign(idata);
    new->next=head; //current head assigned to new node
    if(head!=NULL) 
        head->prev=new; //previous address reassigned to new node
    return new;
}
struct node* insertend(struct node* head, int idata) {
    struct node* new=assign(idata); 
    if(head==NULL) 
        return new; 
    struct node* temp=head;
    while(temp->next!=NULL) //acquiring last node
        temp=temp->next;
    temp->next=new; 
    new->prev=temp;
    return head;
}
struct node* delbeg(struct node* head) {
    if(head==NULL) {
        printf("Empty Linked List\n");
        return NULL;
    }
    struct node* temp=head;
    head=head->next;
    if(head!=NULL) 
        head->prev=NULL;
    free(temp); 
    return head;
}

struct node* delend(struct node* head) {
    if(head==NULL) {
        printf("Empty Linked List\n");
        return NULL;
    }
    struct node* temp=head;
    if(head->next==NULL) { 
        free(head);
        return NULL;
    }
    while(temp->next!=NULL)
        temp=temp->next;
    temp->prev->next=NULL; //set next pointer of new last node to null
    free(temp); //free old last node
    return head;
}

void searchval(struct node* head, int sval) {
    if(head==NULL) { 
        printf("Empty List\n");
        return;
    }
    struct node* temp=head; 
    int pos=0, found=0; 
    while(temp!=NULL) { 
        if(temp->data==sval) {
            printf("Value %d found at %dth position\n",sval,pos+1);
            found=1; 
        }
        temp=temp->next; 
        pos+=1; 
    }
    if(!found) 
        printf("Value %d not found\n",sval);
}

struct node* reverse(struct node* head) {
    if(head==NULL) { 
        printf("Empty List\n");
        return head;
    }
    struct node* current=head; 
    struct node* temp=NULL; 

    while(current!=NULL) { 
        temp=current->prev; //store the previous pointer
        current->prev=current->next; //swap the previous and next pointers
        current->next=temp;
        head=current; //reassiging the head to the current node - new head
        current=current->prev; //shift to next node in original
    }
    return head;
}
void Concat2lists() {
    printf("Handling first Linked List:\n");
    struct node* head1=NULL;
    struct node* head2=NULL;
    int l1, val1, l2, val2;
    printf("Enter the number of elements on the first Linked List\n");
    scanf("%d",&l1);
    for(int i=0;i<l1;i++) {
        printf("Enter %dth element: ",i+1);
        scanf("%d",&val1);
        head1=insertend(head1,val1);
    }
    printf("First Linked List: ");
    printlist(head1);

    printf("\nHandling second Linked List:\n");
    printf("Enter the number of elements on the second Linked List\n");
    scanf("%d",&l2);
    for(int i=0;i<l2;i++) {
        printf("Enter %dth element: ",i+1);
        scanf("%d",&val2);
        head2=insertend(head2,val2);
    }
    printf("Second Linked List: ");
    printlist(head2);

    if(head1==NULL) {
        head1=head2;
    } else {
        struct node* temp=head1;
        while(temp->next!=NULL)
            temp=temp->next;
        temp->next=head2;
        if(head2!=NULL)
            head2->prev=temp;
    }
    printf("Final Output: ");
    printlist(head1);
}

int main() {
    int key=-1;
    int val;
    struct node* head=NULL;
    while(key!=0) {
        printf("\nChoose an appropriate operation:\n(1)Insert in the beginning\n(2)Insert in the end\n(3)Delete in the beginning\n(4)Delete in the end\n(5)Search the Linked List\n(6)Reverse Linked List\n(8)Concatenation of Two Linked Lists\n(9)Print Linked List\n(0)Exit\n");
        scanf("%d",&key);
        switch(key) {
            case 1:
                printf("Enter value to insert in the beginning: ");
                scanf("%d",&val);
                head=insertbeg(head,val);
                break;
            case 2:
                printf("Enter value to insert in the ending: ");
                scanf("%d",&val);
                head=insertend(head,val);
                break;
            case 3:
                head=delbeg(head);
                printf("Element in the beginning is deleted\n");
                break;
            case 4:
                head=delend(head);
                printf("Element in the ending is deleted\n");
                break;
            case 5:
                printf("Enterthe value to search: ");
                int sval;
                scanf("%d",&sval);
                searchval(head,sval);
                break;
            case 6:
                printf("Reversing the Linked List\n");
                head=reverse(head);
                break;
            case 8:
                printf("Concatenating two lists\n");
                Concat2lists();
                break;
            case 9:
                printlist(head);
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid Choice\n");
        }
    }
    return 0;
}