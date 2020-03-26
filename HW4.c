//Assignment #4 - Ibrahim Alshubaily

#include <stdio.h>
#include <string.h>

#define MAX_NAME_LEN 30
#define MAX_NUM_COSTUMERS 20
#define MAX_NUM_ITEMS 10

typedef struct {
    int numItems;
    char itemName [MAX_NAME_LEN];
    double itemPrice;
}item;

typedef struct {
    char name [MAX_NAME_LEN];
    item items[MAX_NUM_ITEMS];
    int numitems;
    double total;
}costumer;

int costumersContain (costumer costumers[], char newName[], int numCostumers) {
    for (int i = 0; i < numCostumers; i++) {
        if(!strcmp(costumers[i].name, newName)) {
            return i;
        }
    }
    return -1;
}

void sortCostumers(costumer costumers[], int rows) {
    costumer tmp;
    for (int p = 0; p < rows; p++) {
        for (int i = 0; i+1 < rows; i++) {
            if (costumers[i].total < costumers[i+1].total) {
                tmp = costumers [i];
                costumers [i]=  costumers [i+1];
                costumers [i+1]=  tmp;
            }
        }
    }
}

void sortItems(costumer costumers[], int rows) {
    item tmp;
    for (int p = 0; p < rows; p++) {
        for (int i = 0; i < costumers[i].numitems; i++) {
            for (int j = 0; j+1 < rows; j++) {
                if (costumers[i].items[j].numItems * costumers[i].items[j].itemPrice
                        < costumers[i].items[j+1].numItems * costumers[i].items[j+1].itemPrice) {

                    tmp = costumers [i].items[j];
                    costumers [i].items[j] = costumers [i].items[j+1];
                    costumers [i].items[j+1] = tmp;
                }
            }
        }
    }
}

void readInput (costumer costumers[], int * numCostumers) {
    FILE* infile = fopen("hw4input.txt", "r");
    char tmpName[MAX_NAME_LEN];
    char ch;
    while(fscanf(infile, " %s " ,tmpName) == 1) {

        int pos = costumersContain(costumers, tmpName, *numCostumers);
        if(pos == -1) {
            strcpy(costumers[*numCostumers].name, tmpName);
            fscanf(infile, " %d %s %c %lf "
                    , &costumers[*numCostumers].items[costumers[*numCostumers].numitems].numItems
                    , costumers[*numCostumers].items[costumers[*numCostumers].numitems].itemName
                    , &ch
                    , &costumers[*numCostumers].items[costumers[*numCostumers].numitems].itemPrice );

            costumers[*numCostumers].total +=
                    (costumers[*numCostumers].items[costumers[*numCostumers].numitems].itemPrice
                            * costumers[*numCostumers].items[costumers[*numCostumers].numitems].numItems);

            costumers[*numCostumers].numitems++;
            (*numCostumers)++;
        }else {
            fscanf(infile, " %d %s %c %lf"
                    , &costumers[pos].items[costumers[pos].numitems].numItems
                    , costumers[pos].items[costumers[pos].numitems].itemName
                    , &ch
                    , &costumers[pos].items[costumers[pos].numitems].itemPrice );

            costumers[pos].total +=
                    (costumers[pos].items[costumers[pos].numitems].itemPrice
                            * costumers[pos].items[costumers[pos].numitems].numItems);

            costumers[pos].numitems++;
            }
        }
    fclose(infile);
}

void writeTimeOutput(costumer costumers[], int numCostumers) {
    FILE* outfile = fopen("hw4time.txt", "w");
    for (int i = 0; i < numCostumers; i ++) {
        fprintf(outfile, "%s\n", costumers[i].name);
            for(int j = 0; j < costumers[i].numitems; j++){
                fprintf(outfile, "%s %d $%.2lf\n"
                        ,costumers[i].items[j].itemName
                        ,costumers[i].items[j].numItems
                        ,costumers[i].items[j].itemPrice);
            }
            if (i != numCostumers-1) {
                fprintf(outfile, "\n");
            }
        }
    fclose(outfile);
}

void writeSortedOutput(costumer costumers[], int numCostumers) {
    FILE* outfile = fopen("hw4money.txt", "w");
    for (int i = 0; i < numCostumers; i ++) {
        fprintf(outfile, "%s, Total Order = $%.2lf\n", costumers[i].name, costumers[i].total);
        for (int j = 0; j < costumers[i].numitems; j++) {
            //Plate 5 $10.00, Item Value = $50.00
            fprintf(outfile, "%s %d $%.2lf, Item Value = $%.2lf\n"
                    , costumers[i].items[j].itemName
                    ,costumers[i].items[j].numItems
                    ,costumers[i].items[j].itemPrice
                    ,costumers[i].items[j].numItems * costumers[i].items[j].itemPrice);
        }
        if (i != numCostumers-1) {
            fprintf(outfile, "\n");
        }
    }
    fclose(outfile);
}

int main (void) {

    int numCostumers = 0;
    costumer costumers[MAX_NUM_COSTUMERS];

    readInput(costumers, &numCostumers);

    writeTimeOutput(costumers, numCostumers);

    sortCostumers(costumers, numCostumers);
    sortItems(costumers, numCostumers);

    writeSortedOutput(costumers, numCostumers);
}
