#include<stdio.h>
#include<malloc.h>

struct node{int data;struct node* next;};

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
struct node* assign(int idata){ //function to assign new data value
    struct node* new=(struct node*)malloc(sizeof(struct node)); //this is the node to add into the linked list
    //data manually allocated
    new->data=idata;//assigning the inserted data value
    new->next=NULL;//to avoid garbage memory value stored
    return new;
}
struct node* insertbeg(struct node* head, int idata){
    struct node* new=assign(idata);//assigning data to new pointer
    new->next=head;//mapping end of the added node to the head of the existing linked list
    return new;
}
struct node* insertend(struct node* head, int idata){
    struct node* new= assign(idata);//creating new node
    if(head==NULL)//return node since linked list is empty
    return new;

    struct node* temp=head;
    while(temp->next!=NULL)//traverse to the end of the linked list
        temp=temp->next;
    temp->next=new;//assign new node mapping
    return head;
}
struct node* delbeg(struct node* head){
    if(head==NULL){
    printf("Empty Linked List");//nothing to delete in an empty list
    return NULL;}
    struct node* temp=head;//creating temporary node to store the data of the first node - in order to free this memory later
    head=head->next;//shifting pointer value - removes first node - head now points to second node  
    temp->next=NULL;
    free(temp);//freeing memory of the first node
    return head;
}
struct node* delend(struct node* head){
    if(head==NULL){
        printf("Empty Linked List");
        return NULL;}
        struct node* temp=head;
        if(head->next==NULL){
            free(head);
            return NULL;
        }
        while(temp->next->next!=NULL)
        temp=temp->next;
        free(temp->next);
        temp->next=NULL;
        return head;

    }
void Concat2lists(){
    printf("Handling first Linked List : \n");
    struct node* head1=NULL;
    struct node* head2=NULL;
    int l1,val1,l2,val2;
    printf("Enter the number of elements on the first Linked List\n");
    scanf("%d",&l1);
    for(int i=0;i<l1;i++){
        printf("Enter %dth element : ",i+1);
        scanf("%d",&val1);
        head1=insertend(head1,val1);
    }
    printf("First Linked List : ");
    printlist(head1);
    printf("\nHandling second Linked List: \n");
    printf("Enter the number of elements on the second Linked List\n");
    scanf("%d",&l2);
    for(int i=0;i<l2;i++){
        printf("Enter %dth element : ",i+1);
        scanf("%d",&val2);
        head2=insertend(head2,val2);    }
    printf("Second Linked List : ");
    printlist(head2);
    struct node* temp=head1;
    if(temp==NULL){
        head1=head2;}
    else{
    while(temp->next!=NULL){
    temp=temp->next;}
    temp->next=head2;
    }
    printf("Final Output : ");
    printlist(head1);
}
void searchval(struct node* head,int sval){
    if(head==NULL){
    printf("Empty List");
    return;}
    struct node* temp=head;
    int pos=0,found=0;
    while(temp!=NULL){
        if(temp->data==sval){
            printf("Value %d found at %dth position",sval,pos);
            found=1;
        }
        temp=temp->next;
        pos+=1;
    }
    if(found==0)
    printf("Value %d not found",pos);

}

struct node* reverse(struct node* head){
    if(head==NULL){
        printf("Empty List");
        return head;
    }
    struct node* temp = head;
    struct node* reversed = NULL;
    while(temp!=NULL){
        reversed = insertbeg(reversed,temp->data);
        temp = delbeg(temp);
    }
    return reversed;

}

void main(){
    int key=-1;
    int val;
    struct node* head=NULL;
    while(key!=0){
    printf("\nChoose an appropriate operation:\n(1)Insert in the beginning\n(2)Insert in the end\n(3)Delete in the beginning\n(4)Delete in the end\n(5)To search the Linked List\n(6)To reverse Linked List\n(8)Concatenation of Two Linked Lists\n(9)Print Linked List\n(0)Exit\n");
    scanf("%d",&key);
    switch(key){
        case 1:
        printf("Enter value to insert in the beginning : ");
        scanf("%d",&val);
        head=insertbeg(head,val);
        break;
        case 2:
        printf("Enter value to insert in the ending : ");
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
        case 6:
        printf("Reversing the Linked List");
        head=reverse(head);
        break;
        case 8:
        printf("concatenating two lists\n");
        Concat2lists();
        break;
        case 5:
        printf("Enter the value to search : ");
        int sval;
        scanf("%d",&sval);
        searchval(head,sval);
        break;
        case 9:
        printlist(head);
        break;
        case 0:
        printf("Exiting...");
        break;
        default:
        printf("Invalid Choice\n");

    }

    
    }
}