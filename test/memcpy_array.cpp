#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main () {

    int a[10];
    int b[10];

    for (int i = 0; i < 10; i++) {
	a[i] = 2 * i;
    }

    memcpy(b, a, 10 * sizeof(int));

    for (int i = 0; i < 10; i++) {
	printf("a: %d, b: %d\n", a[i], b[i]);
    }

    return 0;
}
