//Assignment #5 - Ibrahim Alshubaily

#include <stdio.h>
#include <stdlib.h>
#include "list.h"



void printAll(Node* list) {
    Node* curr = list;
    printf("List: ");
    while (curr != NULL) {  // Watch Out: curr->next !=  NULL
        printf("%d ", curr->value);
        curr = curr->next;
    }
    printf("\n");
}

Node *add_to_list(Node *list, int n) {
    Node *new_node;
    new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Error: malloc failed in add_to_list\n");
        exit(EXIT_FAILURE);
    }
    new_node->value = n;
    new_node->next = list;
    return new_node;
}

void add_to_listP2P( Node **list  ,int n) {
    Node *new_node;
    new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Error: malloc failed in add_to_list\n");
        exit(EXIT_FAILURE);
    }
    new_node->value = n;
    new_node->next = *list;
    *list = new_node;
}

int inOrder(Node *list) {
    Node *curr = list;
    if (curr == NULL)
        return 1;
    while (curr->next != NULL) {  // SAFETY CHECK: curr  != NULL
        if (curr->value > curr->next->value) {  // SAFETY CHECK:  curr->next != NULL
            return 0;
        }
        curr = curr->next;
    }
    return 1;
} 

Node *delete_from_list(Node *list, int n) {
   Node *cur, *prev;
   for (cur = list, prev = NULL;
        cur != NULL ;
        prev = cur, cur = cur->next) {
        if (cur->value == n) {
            if (prev == NULL)
                list = list->next; /* n is in the first node */
            else
                prev->next = cur->next; /* n is in some other node */
            free(cur);
            break;
        }
   }
   return list;
}

Node *deleteAll(Node *list, int n) {
    Node *cur, *prev;
    for (cur = list, prev = NULL; cur != NULL ; prev = cur, cur = cur->next) {
        if (cur->value == n) {
            if (cur == list){
                list = list->next; /* n is in the first node */
                free(cur);
            }else{
                prev->next = cur->next; /* n is in some other node */
                free(cur);
                cur = prev;
            }
        }
    }
    return list;
}


Node *doubleAll(Node* list) {
    Node *cur;
    for (cur = list; cur != NULL; cur = cur->next) {
        Node * cpy = malloc(sizeof(Node));
        cpy->value  = cur->value;
        cpy->next = cur->next;
        cur->next = cpy;
        cur = cpy;
    }
    return list;
}

int nodupdata(Node *list) {
    Node *cur;
    Node *next;
    int curValue;
    for (cur = list; cur != NULL; cur = cur->next) {
        curValue = cur->value;
        for (next = cur->next; next != NULL; next = next->next) {
            if (next->value == cur->value) {
                return 0;
            }
        }
    }
    return 1;
}

Node *merge(Node* list1, Node* list2) {

    if (list1 == NULL){
        return list2;
    }else if (list2 == NULL) {
        return list1;
    }


    Node * cur1 = list1;
    Node * cur2 = list2;
    Node * result = malloc(sizeof(Node));
    Node * reshead = result;

    while(1){

        result->next = malloc(sizeof(Node));

        if (cur1->value <= cur2->value) {
            result->next->value = cur1->value;
            if (cur1->next == NULL) {
                result->next->next = malloc(sizeof(Node));
                result->next->next = cur2;
                return reshead->next;
            }
            cur1 = cur1->next;
        } else {
            result->next->value = cur2->value;
            if (cur2->next == NULL) {
                result->next->next = malloc(sizeof(Node));
                result->next->next = cur1;
                return reshead->next;
            }
            cur2 = cur2->next;
        }

        result = result->next;

    }
}

int looplesslength(Node *list){

    Node *cur;
    int  i = 0;
    for (cur = list; cur != NULL; cur = cur->next) {
        if (cur == cur -> next) {
            i++;
            return -i;
        }
        Node * runner;
        int j = 0;
        for (runner = list; runner != cur->next; runner = runner->next){
            if (runner == cur && j != i) {
                return -i;
            }
            j++;
        }
        i++;
    }
    return i;
}
