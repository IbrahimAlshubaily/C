// Assignment 7 - Ibrahim Alshubaily
#include <stdio.h>
#include <string.h>

typedef union {
    unsigned int i;
    float f;
}int_float;

void showbitsA(unsigned int i) {
    printf("Your float in 32 bits: ");
    for(int j = 0; j < 32; j++) {
        printf("%c",  '0' + ((i & 0x80000000) >> 31));
        i = i << 1;
    }
    printf("\n");
}

void showbitsB(unsigned int i) {
    printf("Sign: %c\n",  '0' + ((i & 0x80000000) >> 31)  );
    i = i << 1;

    printf("Exponent: ");
    for(int j = 0; j < 8; j++) {
        printf("%c",  '0' + ((i & 0x80000000) >> 31)  );
        i = i << 1;
    }

    printf("\nFraction: ");
    for(int j = 0; j < 23; j++) {
        printf("%c",  '0' + ((i & 0x80000000) >> 31)  );
        i = i << 1;
    }
    printf("\n\n");
}

void calculateAndReport(unsigned int i) {
    unsigned int cpy = i;
    printf("Creating the fraction:\n");
    printf("fraction = 1.000000 (the implicit 1)\n");
    float frac = 1.000000;
    int_float dec;
    dec.f = 0.500000;
    i <<= 9;
    for (int j = 0; j < 23; j++) {
        if (((i & 0x80000000))) {
            frac += dec.f;
            printf("fraction = %f, after adding %f\n", frac, dec.f);
        } else {
            printf("fraction = %f, after skipping %f\n", frac, dec.f);
        }
        dec.f /= 2;
        i <<= 1;
    }
    printf("\n");
    
    int isNegative = 0;
    if (cpy & 0x80000000){
        isNegative = 1;
    }
    cpy <<= 1;
    cpy >>= 24;

    printf("Applying the exponent:\n");
    int_float answer;
    answer.f = frac;

    int cpy2;
    memcpy(&cpy2, &cpy, sizeof(int));
    cpy2 -= 127;
    printf("unbiased exponent = %d\n", cpy2);
    if (cpy2 > 0) {
        for (int j = 0; j < cpy2; j++) {
            answer.f *= 2;
            printf("times 2 = %f\n", answer.f);
        }
    } else {
        for (int j = cpy2; j < 0; j++) {
            answer.f /= 2;
            printf("divided 2 = %f\n", answer.f);
        }
    }
    if(isNegative) {
         answer.i =   answer.i | 0x80000000;
    }
    printf("\nFinal Answer: %f\n\n", answer.f);
}

int main () {
    int_float input;
    printf("\nEnter a float: ");
    scanf("%f", &input.f);
    printf("Your float was read as: %f\n", input.f);

    showbitsA(input.i);
    showbitsB(input.i);
    calculateAndReport(input.i);
}
