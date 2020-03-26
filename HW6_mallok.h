//Assignment 6 - Ibrahim Alshubaily

#ifndef MALLOK_H_
#define MALLOK_H_

void create_pool(int size);
void *my_malloc(int size);
void my_free(void *block);

void printNodes();
void free_pool();

#endif
