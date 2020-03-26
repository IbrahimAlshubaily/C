//Assignment 6 - Ibrahim Alshubaily

#include <stdio.h>
#include <stdlib.h>
#include "mallok.h"

/*
 * Create a pool of 1000 bytes.
 * Count how times you can successfully request a block of size 10.
 */
void test1() {
    printf("\n\n--------------------------------------------**test 1 beginning**-------------------------------------------\n\n\n");
    create_pool(1000);
    void * blocks [200];
    int i = 0;
    while(1){
        blocks[i]= my_malloc(10);
        if(blocks[i] == NULL){
            printf("test1 : successfully requested a 10 bytes block %d times from a 1000 bytes pool\n", i);
            printNodes();
            free_pool();
            printf("\n\n-----------------------------------------**test 1 End**-----------------------------------------\n\n\n");
            break;
        }
        i++;
    }
}

/*
 * Create a pool of 1000 bytes.
 * Make 5 requests for blocks of 200 bytes.
 * Free all 5 blocks.
 *  Repeat this request/free pattern several times to make sure you can reuse blocks after they are returned.
 */
void test2() {
    printf("\n\n--------------------------------------------**test 2 beginning**-------------------------------------------\n\n\n");
    create_pool(1000);
    void * blocks [5];

    for (int i = 0; i < 100; i++) {

        for (int j = 0; j < 5; j++){
            blocks[j]= my_malloc(200);
            if(blocks == NULL){
                printf("test2: my-malloc (200 bytes) failed \n");
                printNodes();
                free_pool();
                exit(0);
            }
        }

        for (int j = 0; j < 5; j++) {
            my_free(blocks[i]);
        }

    }
    printf("test 2 passed : successfully allocated and freed 5 blocks of 200 bytes from a 1000 bytes pool 100 times\n");
    printNodes();
    free_pool();
    printf("\n\n--------------------------------------------**test 2 End**-------------------------------------------\n\n\n");
}

/*
 *  Create a pool of 1000 bytes.
 *  Make 5 requests for blocks of 200 bytes.
 *  Free the middle block.
 *  Request a block of 210 bytes (it should fail)
 *  Request a block of 150 bytes (it should succeed)
 *  Request a block of 60 bytes (it should fail)
 *  Request a block of 50 bytes (it should succeed)
 *  etc.
 */
void test3 () {
    printf("\n\n--------------------------------------------**test 3 beginning**-------------------------------------------\n\n\n");
    create_pool(1000);
    void * blocks [5];
    for (int i = 0; i < 5; i++){
        blocks[i]= my_malloc(200);
        if(blocks == NULL){
            printf("test 3 - stage 1: my-malloc failed \n");
            printNodes();
            free_pool();
            exit(0);
        }
    }
    my_free(blocks[2]);

    if (my_malloc(210) != NULL) {
        printf("test 3: successfully allocated 210 bytes **(it should fail)\n");
        printNodes();
        free_pool();
        exit(0);
    }

    if (my_malloc(150) == NULL) {
        printf("test 3: failed to allocate 150 bytes **(it should succeed)\n");
        printNodes();
        free_pool();
        exit(0);
    }

    if (my_malloc(60) != NULL) {
        printf("test 3: successfully allocated 60 bytes **(it should fail)\n");
        printNodes();
        free_pool();
        exit(0);
    }

    if (my_malloc(50) == NULL) {
        printf("test 3: failed to allocate 50 bytes **(it should succeed)\n");
        printNodes();
        free_pool();
        exit(0);
    }
    printf("test 3 passed\n");
    printNodes();
    free_pool();
    printf("\n\n--------------------------------------------**test 3 End**-------------------------------------------\n\n\n");

}

/*
 *
 * create a pool of 1000 bytes.
 * Request  5 blocks of 200 bytes.
 * Fill the first block with the letter 'A', the second block with 'B', etc.
 * Verify that the values stored in each block are still there.  (Is the first block full of A's, second block full of B's, etc.)
 *
 */
void test4() {
    printf("\n\n--------------------------------------------**test 4 beginning**-------------------------------------------\n\n\n");
    create_pool(1000);
    char * blocks [5];
    char letter = 'A';
    for (int i = 0; i < 5; i++){
        blocks[i]= my_malloc(200);
        if(blocks == NULL){
            printf("test 4 - stage 1: my-malloc failed \n");
            printNodes();
            free_pool();
            exit(0);
        }

        for(int j = 0; j < 200; j++){
            *(blocks[i] + j) = letter;
        }

        letter++;
    }

    letter = 'A';
    for (int i = 0; i < 5; i ++) {
        for (int j = 0; j < 200; j++) {
            if ( *(blocks[i] + j)   != letter){
                printf("test4 failed: the %dth block contains a char that is not %c\n", i, letter);
                printNodes();
                free_pool();
                exit(0);
            }
        }
        letter++;
    }

    printf("test 4 passed\n");
    printNodes();
    free_pool();
    printf("\n\n--------------------------------------------**test 4 End**-------------------------------------------\n\n\n");
}

/*
 * Create a pool of 1000 bytes.
 * Request and return a block of 1000 bytes
 * Request and return four blocks of 250 bytes
 * Request and return ten blocks of 100 bytes
 */
void test5 () {
    printf("\n\n--------------------------------------------**test 5 beginning**-------------------------------------------\n\n\n");
    create_pool(1000);
    int size = 1000;
    int reps = 1;
    void * blocks [20];
    for (int i  = 0; i < 3; i++) {

        for (int j = 0; j < reps; j++){
            blocks[j]= my_malloc(size);
            if(blocks[j] == NULL){
                printf("test 5 failed: coulnd'nt allocate %d blocks of %d bytes \n", reps, size);
                exit(0);
            }
        }
        printf("test 5: allocated %d blocks of %d bytes \n", reps, size);
        printNodes();
        for (int r = 0; r < reps; r++){
            my_free(blocks[r]);
        }
        if (size == 1000){
            size = 250;
            reps = 4;
        } else {
            size = 100;
            reps = 10;
        }

    }

    printf("\n**test 5 passed**\n");
    free_pool();
    printf("-------------------------------------------------**Test 5 End**---------------------------------------------------\n\n");
}
void noContiguesFreeBlocksTest() {
    printf("\n\n--------------------------------------------**test 5 beginning**-------------------------------------------\n\n\n");
    create_pool(1000);
    void * blocks[5];
    for (int i = 0; i < 5; i++) {
        blocks[i]= my_malloc(200);
    }
    printNodes();
    for (int i = 0; i < 3; i++) {
        my_free(blocks[i]);
    }

    if(my_malloc(600) == NULL){
        printf("test 6: failed to allocate 600 bytes \n");
    }
    my_free(blocks[3]);
    my_free(blocks[4]);

    if(my_malloc(400) == NULL){
        printf("test 6: failed to allocate 400 bytes \n");
    }
    printf("\n**test 6 passed**\n");
    printNodes();
    free_pool();
    printf("-------------------------------------------------**Test 6 End**---------------------------------------------------\n\n");

}
int main (void) {

    test1();
    test2();
    test3();
    test4();
    test5();
    noContiguesFreeBlocksTest();

    printNodes();
//    create_pool(1000);
//    void * p [5];
//    for (int i = 0; i < 5; i++){
//        p[i]= my_malloc(200);
//        if(p == NULL){
//            printf("my-Malloc failed \n");
//        }
//    }
//    my_free(p[0]);
//    my_free(p[2]);
//    my_free(p[4]);

//    if(my_malloc(300) == NULL){
//        printf("my-malloc failed **(last)\n");
//    }
//
//    printNodes();
}
