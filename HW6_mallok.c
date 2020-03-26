//Assignment 6 - Ibrahim Alshubaily

#include <stdio.h>
#include <stdlib.h>
#include "mallok.h"

typedef struct node_tag{
    void * start;
    int size;
    int isFree;
    struct node_tag *next;
}Node;

static Node * myPool;

void create_pool(int size){
    myPool = malloc(sizeof(Node));
    myPool->start = malloc(size);
    myPool->size = size;
    myPool->isFree = 1;
    myPool->next = NULL;
}

void *my_malloc(int size){
    Node * cur = myPool;
    Node * prev = NULL;
    while ( (!cur->isFree && (cur->next) != NULL) || (cur->size < size && (cur->next) != NULL) ) {
            prev = cur;
            cur = cur->next;
    }

    if (!cur->isFree || cur->size < size) {
        //printNodes();
        return NULL;
    }

    Node *new_node;
    new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Error: malloc failed in my_malloc\n");
        exit(0);
    }

    if (cur->size == size) {
        cur->isFree = 0;
        return cur->start;
    }

    Node * tmp = cur->next;
    cur->next = new_node;
    new_node->next = tmp;


    new_node->start = cur->start + size;
    new_node->size = cur->size - size;
    new_node->isFree = 1;

    cur->isFree = 0;
    cur->size = size;
    return cur->start;
}


void my_free(void *block){
    Node * cur;
    Node * prev = NULL;
    for (cur = myPool; cur != NULL && cur->start != block; prev = cur, cur = cur->next) { }

    if (cur!=NULL) {

        if((prev != NULL && prev->isFree) && (cur->next != NULL && cur->next->isFree)){
            prev->size += (cur->size + cur->next->size);
            prev->next = cur->next->next;
            free(cur->next);
            free(cur);

        }else if (prev != NULL && prev->isFree) {
            prev->size += cur->size;
            prev->next = cur->next;
            free(cur);

        }else if (cur->next != NULL && cur->next->isFree) {
            cur->next->start -= cur->size;
            cur->next->size += cur->size;
            if(prev!=NULL){
                prev->next = cur->next;
            }else {
                myPool = cur->next;
            }
            free(cur);

        } else {
            cur->isFree = 1;
        }
    }
    //printNodes();
}

void free_pool(){

    Node * cur = myPool;
    while (cur != NULL){
        Node * tmp = cur;
        cur = cur->next;
        free(tmp);
    }
    myPool = NULL;
//    free(myPool);
}

void printNodes(){
    printf("\n\n---------------------------Printing Nodes-----------------------------------\n\n");
    int i = 0;
    for (Node * cur = myPool; cur != NULL; cur = cur->next) {
        i++;
        printf("%d - Start = %d , size = %d, isFree = %d, end = %d.\n\n",i, cur->start, cur->size, cur->isFree, cur->start+cur->size);
    }
    printf("\n-------------------------------------------------------------------------------\n\n\n");
}
