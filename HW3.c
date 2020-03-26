/*
 * HomeWork3
 * Ibrahim Alshubaily
 */
#include <stdio.h>
#include <string.h>

#define MAX_NAME_LEN 30
#define MAX_NUM_OF_NAMES 1000
#define NUM_OF_RANKS 10

/*
 * This method traverse through names and check if the new name have already been added.
 * if the name have been added, the return value will be the position of that name.
 * if not, it will return -1.
 */
int findName(char names[][MAX_NAME_LEN] ,char newName[], int rows) {
    int pos = -1;
    for (int i=0 ; i < rows; i ++) {
        if(strcmp(names [i], newName)  == 0) {
            pos = i;
            break;
        }
    }
    return pos;
}

/*
 * This method discards the rest of the line
 * Reference: I took this from menu.c
 */
void discard_to_end_of_line(FILE * infile) {

    char ch;
    do {
        fread(&ch, sizeof(char), 1, infile);
    }  while(ch != '\n');
}

/*
 * This method process a single name and rank.
 * if the name was previously added, it will update the rank for a specific year.
 * if it was not, it will append the name and add the rank for a specific year.
 *
 * @return 1 if the name was new, and 0 if it's not.
 */
int processName (char names[][MAX_NAME_LEN], int ranks[][NUM_OF_RANKS]
                                                         , char newName[], int rows, FILE * infile, int r , int c, int n) {
    int newNames = 0;
    int pos = findName(names, newName,  rows);
    if(pos == -1) {
        for (int i = 0; i <= c; i++) {
            names[rows] [i] = newName [i];
        }
        newNames++;
        ranks[ rows][n] = r+1;
    } else {
        ranks[pos][n] = r+1;
    }
    discard_to_end_of_line(infile);
    return newNames;
}

/*
 * This method process an input file by reading names and storing them with the proper rank.
 * @ return the number of new names that have been appended to keep track of the name array size.
 */
int readFile(char names[][MAX_NAME_LEN], int ranks [][NUM_OF_RANKS], FILE * infile, int n, int rows) {
    int newRows = 0;
    int r = 0;
    int c = 0;
    char newName [MAX_NAME_LEN];
    char ch;
    while (fread(&ch, sizeof(char), 1, infile) != 0) {

        if (ch == ',') {
            newName[c] = 0;
            newRows += processName(names, ranks, newName, rows+newRows, infile, r, c, n);
            if(r == 99) {
                break;
            }
            r++;
            c = 0;

        }else {
            newName[c] = ch;
            c++;
        }
    }
    return newRows;
}

/*
 * Process the 10 input files by calling readfile on each one.
 */
int readInputFiles(char names [][MAX_NAME_LEN], int ranks[][NUM_OF_RANKS]) {

    FILE* infile;
    int rows = 1;
    char fileName [] = {'y','o','b','1','9', '0' ,'0', '.', 't', 'x', 't'};

    for (int i  = 2; i < 10; i ++) {
        fileName [5] = i+'0';
        ranks[0][i-2] = 1900 +i * 10;
        infile = fopen(fileName,"r");
        rows += readFile(names, ranks ,infile, i-2, rows);
        fclose(infile);
    }

    char fileName2 [] = {'y','o','b','2','0', '0' ,'0', '.', 't', 'x', 't'};
    for (int i = 0; i < 2; i ++) {
        fileName2 [5] = i+'0';
        ranks[0][i+8] = 2000 + i * 10;
        infile = fopen(fileName2,"r");
        rows += readFile(names, ranks ,infile, i+8, rows);
        fclose(infile);
    }
    return rows;
}

/*
 * Swap two names and two ranks.
 */
void swap (char names [][MAX_NAME_LEN], int ranks [][NUM_OF_RANKS], char tmpName [], int tmpRank[], int i) {
    strcpy(tmpName,names[i]);
    memcpy(tmpRank,ranks [i], sizeof(int)*NUM_OF_RANKS);
    strcpy(names[i], names[i+1]);
    memcpy(ranks [i], ranks [i+1], sizeof(int)*NUM_OF_RANKS);
    strcpy(names[i+1],tmpName);
    memcpy(ranks [i+1],tmpRank, sizeof(int)*NUM_OF_RANKS);
}

/*
 * Sorts names in alphabetical order.
 */
void sort_names(char names[][MAX_NAME_LEN], int ranks [][NUM_OF_RANKS] ,int name_count) {
    for (int p = 1; p < name_count; p++) {
        for (int i = 1; i+1 < name_count; i++) {
            char tmpName[MAX_NAME_LEN];
            int tmpRank [NUM_OF_RANKS];
            if (strcmp(names[i], names[i+1]) > 0) {
                swap(names, ranks, tmpName, tmpRank, i);
            }
        }
    }
}

/*
 * prints the sorted names and ranks to the output file.
 */
void createOutputFile(char names [][MAX_NAME_LEN], int ranks [][NUM_OF_RANKS], int rows) {

    FILE* outfile = fopen("summary.csv","w");
    strcpy(names[0], "Name");
    for (int i = 0; i < rows; i ++) {
        for (int j = 0; names[i][j] != 0; j++) {
            fprintf(outfile, "%c", names[i][j]);
        }
        fprintf(outfile,",");
        for (int z = 0; z < 9; z++) {

            if (ranks[i][z] == 0) {
                fprintf(outfile,",");
            }else {
                fprintf(outfile, "%d,", ranks[i][z]);
            }
        }
        if(ranks[i][9] == 0) {
            fprintf(outfile,"\n");
        } else{
            fprintf(outfile, "%d\n", ranks[i][9]);
        }
    }
    fclose(outfile);
}

int main(void) {
    char names[MAX_NUM_OF_NAMES][MAX_NAME_LEN];
    int ranks [MAX_NUM_OF_NAMES][NUM_OF_RANKS];

    int rows = readInputFiles(names, ranks);
    sort_names(names, ranks, rows);
    createOutputFile(names, ranks, rows);
}
