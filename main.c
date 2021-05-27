#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *mkrndstr(size_t length);

int main(int const argc, char **const argv) {
    FILE *f = fopen("../testfile.txt", "w");
    int size = 10;
    fprintf(f, "digraph test { \n");
    for (int i = 1; i < size; ++i) {
        char *a;
        char *b;
        a = mkrndstr(2);
        b = mkrndstr(2);
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

char *mkrndstr(size_t length) {
    static char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    char *randomString = NULL;
    if (length > 0) {
        randomString = malloc(length + 1);
        if (randomString) {
            int l = (int) (sizeof(charset) - 1);
            int key;
            for (int n = 0; n < length; n++) {
                key = rand() % l;
                randomString[n] = charset[key];
            }

            randomString[length] = '\0';
        }
    }
    return randomString;
}
