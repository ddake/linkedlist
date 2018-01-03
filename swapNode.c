/**
 * Description: Swaps nodes of the linked list. 
**/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct newNode{
    int indx;
    char data;
    struct newNode *next;
}newNode;

newNode *head, *curr;
int nodeCount = 0;

void addNode(int a);
void swapNodes(int indexA, int indexB);
void printList(newNode *head);
void freeList(newNode *head);

int main()
{
    //create a linked list
    for(int a=0; a<10; a++){
        addNode(a);
    }
    printf("Before Swap\n");
    printList(head);

    //swapping nodes
    printf("\nAfter swap\n");
    swapNodes(9, 3);
    printList(head);

    //Delete list
    freeList(head);
    return 0;
}

void addNode(int a)
{
    //create a newNode
    newNode *new = (newNode *)malloc(sizeof(newNode));
    new->indx = a;
    new->data = a + 48;
    new->next = NULL;

    //Make the list
    if(head == NULL){
        head = new;
        curr = new;
    }
    else{
        curr->next = new;
        curr = curr->next;
    }
    nodeCount++;
}

void swapNodes(int indexA, int indexB)
{
    if(indexA > (nodeCount-1) || indexB > (nodeCount-1)){
        printf("Position error\n");
        return;
    }
    else if(indexA < 0 || indexB < 0){
        printf("Position error\n");
        return;
    }

    if(indexA == indexB){
        printf("Positions are same. No swap needed\n");
        return;
    }

    if(indexA > indexB){
        int temp = 0;
        temp = indexA;
        indexA = indexB;
        indexB = temp;
    }

    newNode *prevA, *currA, *prevB, *currB;
    prevA = head;
    currA = head;
    prevB = head;
    currB = head;

    //swap head and body node or tail node
    if(indexA == 0 && (indexB > 0 && indexB < nodeCount)){
        prevA = currA;
        currA = currA->next;

        for(int a=0; a<indexB; a++){
            prevB = currB;
            currB = currB->next;    //move currB to point to indexB
        }

        newNode *temp = currB->next;

        if(prevB != head){
            currB->next = head->next;
            prevB->next = head;
            prevB->next->next = temp;
            head = currB;
        }
        else{
            currB->next = head;
            head->next = temp;
            head = currB;
        }
    }//swap body and body node or swap body and tail node
    else if(indexA > 0 && indexA < nodeCount && indexB > 0 && indexB <= nodeCount){
        for(int a=0; a<indexA; a++){
            prevA = currA;
            currA = currA->next;
        }
        for(int b=0; b<indexB; b++){
            prevB = currB;
            currB = currB->next;
        }

        newNode *t = currB->next;
        prevA->next = currB;

        if(currA != prevB){
            currB->next = currA->next;
            currA->next = t;
            prevB->next = currA;
        }
        else{
            currB->next = currA;
            currA->next = t;
        }
    }
}

void printList(newNode *head)
{
    newNode *t = head;
    while(t != NULL){
        printf("%d %c\n", t->indx, t->data);
        t = t->next;
    }
}

void freeList(newNode *head)
{
    newNode *t = head;
    while(t != NULL){
        free(t);
        t = t->next;
    }
}