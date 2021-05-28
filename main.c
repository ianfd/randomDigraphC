#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

char *mkrndstr(size_t length);

unsigned randu(unsigned max);

void rand_init();

int main(int const argc, char **const argv) {
    rand_init();
    FILE *f = fopen("../testfile.txt", "w");
    int size = 100000; // length of random
    fprintf(f, "digraph test { \n");
    for (int i = 1; i < size; ++i) {
        char *a;
        char *b;
        a = mkrndstr(1);
        b = mkrndstr(1);
        if (a != NULL && b != NULL) {
            fprintf(f, "%s -> %s;\n", a, b);
            free(a);
            free(b);
        }
    }
    fprintf(f, "}");
    fclose(f);
    return 0;
}

void rand_init() {
    /* get three integers for seeding the RNG */
    unsigned long a = clock();
    unsigned long b = time(NULL);
    unsigned long c = getpid();

    /* now mix them
     * (this is Robert Jenkins' 96 bit Mix Function) */
    a = a - b;
    a = a - c;
    a = a ^ (c >> 13);
    b = b - c;
    b = b - a;
    b = b ^ (a << 8);
    c = c - a;
    c = c - b;
    c = c ^ (b >> 13);
    a = a - b;
    a = a - c;
    a = a ^ (c >> 12);
    b = b - c;
    b = b - a;
    b = b ^ (a << 16);
    c = c - a;
    c = c - b;
    c = c ^ (b >> 5);
    a = a - b;
    a = a - c;
    a = a ^ (c >> 3);
    b = b - c;
    b = b - a;
    b = b ^ (a << 10);
    c = c - a;
    c = c - b;
    c = c ^ (b >> 15);

    /* use this mix to initialize RNG */
    srand(c);
}

unsigned randu(unsigned max) {
    const unsigned int buckets = RAND_MAX / max;
    const unsigned int limit = buckets * max;

    unsigned int r;
    do {
        r = rand();
    } while (r >= limit);

    return r / buckets;
}


char *mkrndstr(size_t length) {
    // "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
    static char charset[] = "abcdefghijklmn";
    char *randomString = NULL;
    if (length > 0) {
        randomString = malloc(length + 1);
        if (randomString) {
            int l = (int) (sizeof(charset) - 1);
            int key;
            for (int n = 0; n < length; n++) {
                key = randu(l);
                randomString[n] = charset[key];
            }

            randomString[length] = '\0';
        }
    }
    return randomString;
}
