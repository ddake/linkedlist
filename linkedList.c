/**
 *  Description: Single linked list implementation
**/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct newNode{
    void *data;
    struct newNode *next;
}newNode;

typedef struct linkedList{
    newNode *head, *curr, *tail;
    int length;
}linkedList;

void add(int a, linkedList **list);
void copyList(linkedList **list1, linkedList **list2);
void print(linkedList **list);
void insert(int value, int position, linkedList **list);
void delete(int value, linkedList **list);
void deletePos(int position, linkedList **list);
void reversePrint(newNode *head);

int main()
{
    
    linkedList *list1, *list2;
 
    list1 = (linkedList *)malloc(sizeof(linkedList));
    list2 = (linkedList *)malloc(sizeof(linkedList));
  
    list1->head = NULL;
    list2->head = NULL;
    list1->length = 0;
    list2->length = 0;
   
    for(int a=0; a<10; a++){
	    add(a, &list1);
    }
    printf("List 1: ");
    print(&list1);
    copyList(&list1, &list2);

    printf("\nList 2: ");
    print(&list2);
    printf("\nAfter Insert\n");
    insert(23, 13, &list1);
    insert(34, 3, &list1);
    insert(123, 8, &list1);
    insert(999, 0, &list1);   
 
    printf("List 1: ");
    print(&list1);
    printf("\n");
    for(int a=0; a<10; a++){
        add(a, &list1);
    }

    insert(12, 4, &list1);
    insert(1234, 7, &list1);
    add(100, &list1);

    //Delete
    add(7, &list1);
    for(int a=0; a<5; a++){
	add(5, &list1);
    }
    printf("\nBefore deleting....\n");
    print(&list1);
 
    delete(5, &list1);

    printf("\nAfter deleting 5....\n");
    print(&list1);

    delete(7, &list1);

    printf("\nAfter deleting 7....\n");
    print(&list1);

    delete(1, &list1);

    printf("\nAfter deleting 1....\n");
    print(&list1);

    delete(0, &list1);

    printf("\nAfter deleting 0....\n");
    print(&list1);
 
    insert(500, 0, &list1);
    printf("\nAfter inserting 500....\n");
    print(&list1);

    printf("\nReverse printing linked list\n"); 
    reversePrint(list1->head);
    return 0;
}

void add(int a, linkedList **list)
{
    //create a newNode for this list
    newNode *n = (newNode *)malloc(sizeof(newNode));
    n->data = (int *)malloc(sizeof(int));
    n->next = NULL;

    //store data
    *(int *)(n->data) = a;

    //Add this node to the linkedlist
    if((*list)->head == NULL){
	(*list)->head = n;
	(*list)->curr = n;
	(*list)->tail = n;
    }
    else{
	(*list)->curr->next = n;
	(*list)->curr = n;
	(*list)->tail = n;
    }

    //increase length
    (*list)->length++;
}

void print(linkedList **list)
{
    newNode *t = (*list)->head;
    while(t != NULL){
	printf("%d ", *((int *)(t->data)));
	t = t->next;
    } 
}

void copyList(linkedList **list1, linkedList **list2)
{
    newNode *t = (*list1)->head;
 
    while(t != NULL){
	add( *(int *)(t->data), list2);
	t = t->next;
    }
}

void insert(int value, int position, linkedList **list)
{
    int index;

    if(position > (*list)->length){
	printf("Not a valid position, inserting at the end of the list\n");
	index = (*list)->length;
    }
    else{
	index = position;
    }

    index = index - 1; //Index starts from 0
    newNode *t = (*list)->head;
    if( t == NULL){
	printf("Cannot insert into an empty list\n");
	return;
    }    

    //Advance t to index
    for(int a=0; a<index; a++){
        if(t->next == NULL){
		printf("NULL POINTER ABORT %d\n", a);
		return;
	}
	t = t->next;
    }

    //Create the node
    newNode *n = (newNode *)malloc(sizeof(newNode));
    n->data = (int *)(malloc(sizeof(int)));
    n->next = NULL;

    //store value
    *(int *)(n->data) = value;

    if(t == (*list)->tail){
        printf("Inserting at last\n");
	add(value, list);
    }
    else if(t == (*list)->head){
	n->next = t;
	(*list)->head = n;
    }
    else{
        //join the node
        n->next = t->next;
        t->next = n;
        (*list)->length++;
    }
}

void delete(int value, linkedList **list)
{
    //Find the index(s) of the node(s) containing the value
    int *index = (int *)malloc((*list)->length * sizeof(int));
    int duplicateI = 0;
    newNode *t = (*list)->head;

    int listI = 0;
    while(t != NULL){
	if( *(int*)(t->data) == value){
	    index[duplicateI] = listI;
	    duplicateI++;
	}
 	listI++;
	t = t->next;
    }    

    //Remove duplicates
    //If an element is removed from the list, the indexes slide down by 1
    for(int i=0; i<duplicateI; i++)
    {
	deletePos(index[i], list);
	
	//reduce all the indices by 1
	int x = i;
	for(; x<duplicateI; x++){
		index[x] = index[x] - 1;
		if(index[x] < 0){
			index[x] = 0;
		}
	}
    }
}

void deletePos(int position, linkedList **list)
{
    if(position > (*list)->length){
	printf("Invalid position, cannot delete\n");
	return;
    }

    int prevIndex = position - 1;
    
    newNode *t = (*list)->head;

    if(prevIndex >= 0){
	for(int a=0; a<prevIndex; a++){
	    t = t->next;
        }

        newNode *del = t->next;

        t->next = t->next->next;
        free(del);
    }
    else{
	//delete the first element
        (*list)->head = t->next; 
	free(t);
    }
    (*list)->length--;
}

void reversePrint(newNode *head)
{
    newNode *t = head;
    if(t == NULL){
    	return;
    }
    reversePrint(t->next);
    printf("%d ", *(int*)(t->data));
}
