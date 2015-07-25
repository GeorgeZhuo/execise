// Fri Sep 26 17:27:30 2014
// george@NOSPAM.Phycles

/*
 * sicily 1020 big integer 
 * big integer X is represented by string (less than 400
 * and no negative)
*/

#include <stdio.h>
#include <string.h>

int mod(char bigInt[], int divisor) {

    int pointer = 0;
    int remainder = bigInt[pointer++] - '0';
    int length = strlen(bigInt);

    while (1) {

	while (remainder < divisor) {
	    
	    if (pointer == length) {
		return remainder;
	    }
	    remainder = remainder * 10 + bigInt[pointer++] - '0';
	}
	remainder %= divisor;
    }
    
}

int main () {

    int T;
    scanf("%d", &T);

    int num;
    int b[100];
    int i;
    char bigInt[400];
    int remainder;
    while (T--) {
	
	scanf("%d", &num);
	for(i = 0; i < num; i++) {
	    scanf("%d", &b[i]);
	}

	scanf("%s", bigInt);
	printf("(");
	for (i = 0; i < num - 1; i++) {
	    remainder = mod(bigInt, b[i]);
	    printf("%d,",remainder);
	}
	printf("%d)\n", mod(bigInt, b[num -1]));
    }
}
