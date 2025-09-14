#include <stdio.h>
#include <stdlib.h>  // for malloc()

struct node {
    int data;
    struct node* next;
};

// Create a new node with given data
struct node* assign(int idata) {
    struct node* new = (struct node*)malloc(sizeof(struct node));
    if (!new) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    new->data = idata;
    new->next = NULL;
    return new;
}

// Insert at the beginning
struct node* insertbeg(struct node* head, int idata) {
    struct node* new = assign(idata);
    new->next = head;  // point new node to old head
    return new;        // new node becomes the new head
}

// Print linked list
void printList(struct node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    struct node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {
    struct node* head = NULL;
    int key = -1, value;

    while (key != 0) {
        printf("\nChoose an operation:\n");
        printf("(1) Insert at the beginning\n");
        printf("(9) Print Linked List\n");
        printf("(0) Exit\n");
        printf("Enter choice: ");
        scanf("%d", &key);

        switch (key) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                head = insertbeg(head, value);
                break;
            case 9:
                printList(head);
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}
