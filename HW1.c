/*
 * TCSS 333 - HomeWork 1
 * Author: Ibrahim Ashubaily
 */
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

    void generateCode(char charToEncode) {
        int pow = 64;
        for (int i = 6; i >= 0; i--) {
            int random = (rand() % 25)+ 65;
            if (pow <= charToEncode) {
                charToEncode -= pow;
                if (! (random & 1) ){
                    random++;
                }
                printf("%c", random);
            }else {
                if (random & 1){
                     random++;
                }
                printf("%c", random);
            }
            pow = pow/2;
        }
    }
    void encode() {

        srand(time(NULL));
        char ch;
        do {
            scanf("%c", &ch);
            if (ch != 13 && ch != 10) {
                generateCode(ch);
            }
        } while( (ch != '\n'));
        printf("\n");
    }

    void decode () {
        int counter = 6;
        char ch;
        int asciiValue = 0;
        int pow = 64;
        do {
            scanf("%c", &ch);
            if (ch & 1) {
                asciiValue += pow;

            }
            pow = pow/2;
            counter--;
            if (counter == -1) {
                printf("%c", asciiValue);
                counter = 6;
                asciiValue = 0;
                pow = 64;
            }
        }while (ch != '\n');
        printf("\n");
    }

    void discard_to_end_of_line() {
        char ch;
        do   {
            scanf("%c", &ch);
        }  while(ch != '\n');
    }

    int main (void) {
        while (1) {
            printf("C/c =  Encode\n");
            printf("D/d =  Decode\n");
            printf("Q/q =  quit\n");
            printf("> ");
            fflush(stdout);
            char command;
            scanf("%c", &command);
            discard_to_end_of_line();
            if   (command >  'Z') {
                command -= 'a'-'A';
            }
            if (command == 'C' | command == 'D'){
                printf("? ");
                fflush(stdout);
            }
            switch(command) {
            case 'C':
                encode();
                break;
            case 'D':
                decode();
                break;
             case 'Q':
                 printf("Good bye!\n");
                 return 0;
                 break;
             default:
                 printf("That command was unexpected.\n");
                 break;
            }
        }
        return 0;
    }
