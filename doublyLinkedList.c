#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct doublyLL{
    void *data;
    struct doublyLL *prev, *next;
}doublyLL;

doublyLL *head, *tail, *curr;
int nodeCount = 0;

void addNode(void *data);
void deleteNode(int index);
void insertNode(int index, void *data);
void printList(doublyLL *node);
void replaceNodeData(int index, void *data);

int main()
{
    head = NULL;
    tail = NULL;

    char data[] = "Dheeraj Dake";
    for(int a=0; a<strlen(data); a++){
        addNode((void *)&data[a]);
    }
    printList(head);
    printf("\n");
    printList(tail);

    printf("\nAfter deleting\n");
    deleteNode(0);
    printf("\n");
    printList(head);
    deleteNode(nodeCount-1);
    printf("\n");
    printList(tail);

    insertNode(0, (void *)&data[0]);
    insertNode(nodeCount-1, (void *)&data[strlen(data)-1]);
    printf("\nInserting...\n");

    char text[] = "hello ";
    for(int a=0; a<strlen(text); a++){
        insertNode(a, (void *)&text[a]);
    }
    printList(head);

    char r = 'Y';
    printf("\nReplacing %c in list\n", r);
    replaceNodeData(0, (void *)&r);
    printList(head);
    return 0;
}

void addNode(void *data)
{
    //create a node
    doublyLL *new = (doublyLL *)malloc(sizeof(doublyLL));
    new->data = malloc(sizeof(doublyLL));
    new->data = data;
    new->next = NULL;
    new->prev = NULL;

    if(head == NULL){
        head = new;
        tail = new;
        curr = new;
    }
    else{
        curr->next = new;
        new->prev = curr;
        curr = curr->next;
        tail = new;
    }

    nodeCount++;
}

void printList(doublyLL *node)
{
    doublyLL *t = node;

    if(t == head){
        while(t != NULL){
            printf("%c ", *(char *)t->data);
            t = t->next;
        }
    }
    else if(t == tail){
        while(t != NULL){
            printf("%c ", *(char *)t->data);
            t = t->prev;
        }
    }
}

void deleteNode(int index)
{
    if(index > nodeCount-1){
        printf("Cannot delete the node - out of range\n");
        return;
    }

    doublyLL *t = head;
    doublyLL *p = head;

    //delete head
    if(index == 0){
        head = t->next;
        head->prev = NULL;
    } //delete tail
    else if(index == (nodeCount - 1)){
        t = tail;
        tail = t->prev;
        tail->next = NULL;
    }//delete body node
    else{
        for(int a=0; a<index; a++){
            p = t;
            t = t->next;
        }
        p->next = t->next;
        t->next->prev = p;
    }

    free(t);
    nodeCount--;
}

void insertNode(int index, void *data)
{
    if(index > nodeCount-1){
        printf("Cannot delete the node - out of range\n");
        return;
    }

    //traverse pointers
    doublyLL *p = head, *t = head;

    //create a node
    doublyLL *new = (doublyLL *)malloc(sizeof(doublyLL));
    new->data = malloc(sizeof(doublyLL));
    new->data = data;
    new->next = NULL;
    new->prev = NULL;

    //inserting at head
    if(index == 0){
        new->next = head;
        head->prev = new;
        head = new;
    }else if(index == (nodeCount-1)){
        new->prev = tail;
        tail->next = new;
        tail = new;
    }else{
        for(int a=0; a<index; a++){
            p = t;
            t = t->next;
        }
        p->next = new;
        new->prev = p;
        new->next = t;
        t->prev = new;
    }

    nodeCount++;
}

void replaceNodeData(int index, void *data)
{
    if(index > nodeCount-1){
        printf("Cannot delete the node - out of range\n");
        return;
    }

    doublyLL *t = head;

    if(index == 0){
        t->data = data;
    }
    else{
        for(int a=0; a<index; a++){
            t = t->next;
        }

        t->data = data;
    }
}