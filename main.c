//Assignment #5 - Ibrahim Alshubaily
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

Node * emptyList(Node *list){
    Node* curr = list;
    Node* tmp = NULL;
    while (curr != NULL) {
        tmp = curr;
        curr = curr->next;
        free(tmp);
    }
    return NULL;
}

int printAllLoppList(Node* list) {

    Node *cur;
    int  i = 0;
    printf("List: ");
    for (cur = list; cur != NULL; cur = cur->next) {
        if (cur == cur -> next) {
            printf("%d ..Next is %d again..\n",cur->value, cur->value);
            return 0;
        }

        Node * runner;
        int j = 0;
        for (runner = list; runner != cur->next; runner = runner->next){
            if (runner == cur && j != i) {
                j = -1;
                break;
            }
            j++;
        }
        if (j == -1){
            printf("..Next is %d again..", runner->value);
            break;
        }
        i++;
        printf("%d ", cur->value);
    }
    printf("\n");
    return 0;
}


void testDeleteAll(){

    printf("\n\n\n---------------test delete All--------------------\n");
    printf("--DeleteAllfromEmptyList-- \n");
    printf("ListBefore ");
    Node *intlist = NULL;
    printAll(intlist);

    printf("ListAfter ");
    intlist = deleteAll(intlist, 1);
    printAll(intlist);
    printf("\n------------------------------------\n\n");

    for (int i = 9; i >= 0; i --) {
        intlist = add_to_list(intlist ,i );
        intlist = add_to_list(intlist ,i+1 );
        intlist = add_to_list(intlist ,i );
    }
    
    printf("--DeleteAll99's (DNE) -- \n");
    printf("ListBefore ");
    printAll(intlist);
    printf("\nListAfter ");
    intlist = deleteAll(intlist, 99);
    printAll(intlist);
    printf("\n------------------------------------\n\n");


    printf("Delete 9s (LastNode)\n");
    printf("ListBefore ");
    printAll(intlist);
    intlist = deleteAll(intlist, 9);
    printf("\nList AFTER delete all 9s\n");
    printAll(intlist);
    printf("\n------------------------------------\n\n");


    printf("Delete 5s (MiddleNode) \n");
    printf("ListBefore ");
    printAll(intlist);
    intlist = deleteAll(intlist, 5);
    printf("\nAFTER delete all 5s\n");
    printAll(intlist);
    printf("\n------------------------------------\n\n");

    printf("Delete 0s (FirstNode)\n");
     printf("ListBefore \n");
    printAll(intlist);
    intlist = deleteAll(intlist, 0);
    printf("\nAFTER delete all 0s\n");
    printAll(intlist);
    printf("\n------------------------------------\n\n");
    printf("---------------test delete All Completed--------------------\n\n\n");

    intlist = emptyList(intlist);


}

void testDoubleAll() {
    printf("\n\n\n---------------test Double All--------------------\n");
    Node *intlist = NULL;

    printf("Double Empty List\n");
    printf("List Before ");
    printAll(intlist);
    intlist = doubleAll(intlist);
    printf("List After ");
    printAll(intlist);
    printf("\n------------------------------------\n\n");

    printf("Double a One Node List\n");
    intlist = add_to_list(intlist , 1 );
    printf("List Before ");
    printAll(intlist);
    intlist = doubleAll(intlist);
    printf("List After ");
    printAll(intlist);
    printf("\n------------------------------------\n\n");

    intlist = emptyList(intlist);

    printf("Double List (Neg Values)\n");
    intlist = add_to_list(intlist , -3 );
    intlist = add_to_list(intlist , -2 );
    intlist = add_to_list(intlist , -1 );
    printf("List Before ");
    printAll(intlist);
    intlist = doubleAll(intlist);
    printf("List After ");
    printAll(intlist);
    printf("\n------------------------------------\n\n");

    intlist = emptyList(intlist);

    printf("Double a Normal List\n");
    for (int i = 10; i > 0; i --) {
        intlist = add_to_list(intlist ,i );
    }
    printf("List Before ");
    printAll(intlist);
    intlist = doubleAll(intlist);
    printf("List After ");
    printAll(intlist);
    printf("\n------------------------------------\n\n");
    printf("---------------test Double All Completed--------------------\n\n\n");
    intlist = emptyList(intlist);
}

void testNoDupData(){
    printf("\n\n\n---------------test No Duplicate Data--------------------\n");
    Node *intlist = NULL;

    printf("Case 1 : Empty List\n");

    printAll(intlist);
    if(nodupdata(intlist)){
        printf("There is no duplicates\n");
    }else {
        printf("There is duplicates\n");
    }
    printf("\n------------------------------------\n\n");

    printf("Case 2 : One Node List\n");

    intlist = add_to_list(intlist , 1);
    printAll(intlist);
    if(nodupdata(intlist)){
        printf("There is no duplicates\n");
    }else {
        printf("There is duplicates\n");
    }
    printf("\n------------------------------------\n\n");

    printf("Case 2 : no duplicate List\n");

    intlist = emptyList(intlist);
    for (int i = 10; i >= -10; i --) {
        intlist = add_to_list(intlist ,i );
    }
    printAll(intlist);
    if(nodupdata(intlist)){
        printf("There is no duplicates\n");
    }else {
        printf("There is duplicates\n");
    }
    printf("\n------------------------------------\n\n");

    printf("Case 3 : neighbor duplicate\n");

    intlist = emptyList(intlist);
    for (int i = 10; i >= 0; i --) {
        intlist = add_to_list(intlist ,i );
    }
    intlist = add_to_list(intlist ,0 );
    printAll(intlist);
    if(nodupdata(intlist)){
        printf("There is no duplicates\n");
    }else {
        printf("There is duplicates\n");
    }
    printf("\n------------------------------------\n\n");

    printf("Case 4 : polar duplicate\n");

    intlist = emptyList(intlist);
    for (int i = 10; i >= 0; i --) {
        intlist = add_to_list(intlist ,i );
    }
    intlist = add_to_list(intlist ,10 );
    printAll(intlist);
    if(nodupdata(intlist)){
        printf("There is no duplicates\n");
    }else {
        printf("There is duplicates\n");
    }
    printf("\n------------------------------------\n\n");

    printf("Case 4 : All duplicate\n");

    intlist = emptyList(intlist);
    for (int i = 10; i >= 0; i --) {
        intlist = add_to_list(intlist ,i );
    }
    intlist = doubleAll(intlist);
    printAll(intlist);
    if(nodupdata(intlist)){
        printf("There is no duplicates\n");
    }else {
        printf("There is duplicates\n");
    }
    printf("\n------------------------------------\n\n");
    printf("---------------test No Duplicate Data Completed--------------------\n\n\n");
}

void testMerge(){

    printf("\n\n\n---------------test Merge--------------------\n");

    printf("Case 1 : Merge Empty Lists\n");
    printf("Lists Before \n");

    Node * intlist = NULL;
    Node * intlist2 = NULL;
    printAll(intlist);
    printAll(intlist);

    Node * merged = merge(intlist, intlist2);
    printf("Merged ");
    printAll(merged);
    printf("\n------------------------------------\n\n");


    intlist = emptyList(intlist);
    intlist2 = emptyList(intlist2);
    printf("Case 2 : Merge Normal Lists\n");
    printf("Lists Before \n");
    for (int i = 10; i >= 0; i --) {
        intlist = add_to_list(intlist ,i );
        intlist2 = add_to_list(intlist2 ,i );
    }
    printAll(intlist);
    printAll(intlist2);
    merged = emptyList(merged);
    merged = merge(intlist, intlist2);
    printf("Merged ");
    printAll(merged);

    printf("\n------------------------------------\n\n");

    printf("Case 3 : Merge Costume Fit Lists\n");
    printf("Lists Before \n");
    intlist = emptyList(intlist);
    intlist2 = emptyList(intlist2);
    for (int i = 10; i >= 0; i -=2) {
        intlist = add_to_list(intlist ,i );
        intlist2 = add_to_list(intlist2 ,i-1 );
    }
    printAll(intlist);
    printAll(intlist2);

    merged = merge(intlist, intlist2);
    printf("\n\nMerged ");
    printAll(merged);

    printf("\n------------------------------------\n\n");

    intlist = emptyList(intlist);
    intlist2 = emptyList(intlist2);

    printf("Case 4 : Merge Neg & Pos Lists\n");
    printf("Lists Before \n");
    for (int i = 10; i >= -10; i -=2) {
        intlist = add_to_list(intlist ,i );
       intlist2 = add_to_list(intlist2 ,i-1 );
    }
    printAll(intlist);
    printAll(intlist2);

    Node * merged2 = merge(intlist, intlist2);
    printf("Merged ");
    printAll(merged2);

    printf("\n------------------------------------\n\n");



    intlist = emptyList(intlist);
    intlist2 = emptyList(intlist2);

    printf("Case 5 : Merge 0s and 1s\n");
    printf("Lists Before ");
    for (int i = 10; i >= 0; i --) {
        intlist = add_to_list(intlist ,0 );
        intlist2 = add_to_list(intlist2 ,1 );
    }
    printAll(intlist);
    printAll(intlist2);
    Node * merged3 = merge(intlist, intlist2);
    printf("Merged ");
    printAll(merged3);

    printf("\n------------------------------------\n\n");

    intlist = emptyList(intlist);
    intlist2 = emptyList(intlist2);

    printf("Case 6 : Merge 1s and 0s\n");
    printf("Lists Before ");
    for (int i = 10; i >= 0; i --) {
        intlist = add_to_list(intlist ,1 );
        intlist2 = add_to_list(intlist2 ,0 );
    }
    printAll(intlist);
    printAll(intlist2);
    Node * merged4 = merge(intlist, intlist2);
    printf("Merged ");
    printAll(merged4);
    printf("\n------------------------------------\n\n");


    printf("Case 7 : Merge a List with empty List\n");
    intlist = emptyList(intlist);
    intlist2 = emptyList(intlist2);
    for (int i = 10; i >= 0; i --) {
        intlist = add_to_list(intlist ,i );
    }
    printAll(intlist);
    printAll(intlist2);
    Node * merged5 = merge(intlist, intlist2);
    printf("Merged ");
    printAll(merged5);
    printf("\n------------------------------------\n\n");


    printf("---------------test Merge Completed--------------------\n\n\n");
}


void testLoplessLength() {

    printf("\n\n\n---------------test Loop Less Length--------------------\n\n");

    printf("Case 1 :  Empty List\n");

    Node * intlist = NULL;

    printAll(intlist);
    printf("List Length = %d \n ", looplesslength(intlist));
    printf("\n------------------------------------\n\n");


    printf("Case 2 : One Node List \n");

    intlist = add_to_list(intlist ,1 );

    printAll(intlist);
    printf("List Length = %d \n ", looplesslength(intlist));

    printf("\n------------------------------------\n\n");


    printf("Case 3 : One Node that point at it self \n");

    intlist = add_to_list(intlist ,1 );
    intlist->next = intlist;

    printAllLoppList(intlist);
    printf("List Length = %d \n ", looplesslength(intlist));

    printf("\n------------------------------------\n\n");


    printf("Case 4 : Normal List (no loops)\n");

    Node * intlist2 = NULL;
    for (int i = 10; i >= 0; i --) {
        intlist2 = add_to_list(intlist2 ,i );
    }

    printAllLoppList(intlist2);
    printf("List Length = %d \n ", looplesslength(intlist2));
    printf("\n------------------------------------\n\n");


    printf("Case 5 : Last Node Point At First Node \n");
    Node * intlist3 = NULL;
    for (int i = 10; i >= 0; i --) {
        intlist3 = add_to_list(intlist3 ,i );
    }
    //Make last node point at first;

    for (Node * runner = intlist3; runner != NULL; runner = runner->next) {
        if (runner-> next == NULL){
            runner -> next  = intlist3;
            break;
        }
    }
    printAllLoppList(intlist3);
    printf("length: %d \n",looplesslength(intlist3));

    printf("\n------------------------------------\n\n");

    printf("Case 6 : Last Node Point At Middle Node \n");
    Node * intlist4 = NULL;
    for(int i = 10; i >= 0; i --){
        intlist4 = add_to_list(intlist4 ,i );
    }
    //Make last node point at first;
    Node * midPtr = NULL;
    int i = 0;
    for (Node * runner = intlist4; runner != NULL; runner = runner->next) {
        i++;
        if (i == 6){
            midPtr = runner;
        }
        if (runner->next == NULL) {
            runner -> next  = midPtr;
            break;
        }
    }
    printAllLoppList(intlist4);
    printf("length: %d \n",looplesslength(intlist4));
    printf("\n------------------------------------\n\n");

    printf("Case 7 : Last Node Point At Last Node \n");
    Node * intlist5 = NULL;
    for(int i = 10; i >= 0; i --){
        intlist5 = add_to_list(intlist5 ,i );
    }
    i = 0;
    for (Node * runner = intlist5; runner != NULL; runner = runner->next) {
        i++;
        if (runner-> next == NULL){
            runner -> next  = runner;
            break;
        }
    }
    printAllLoppList(intlist5);
    printf("length: %d \n", looplesslength(intlist5));
    printf("\n------------------------------------\n\n");
    printf("---------------test LoopLessLength Completed--------------------\n\n\n");


}

int main(void) {

    testDeleteAll();

    testDoubleAll();

    testNoDupData();

    testMerge();

    testLoplessLength();


    return 0;
}
