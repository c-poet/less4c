#include "inc/core/func.h"
#include <malloc.h>

char *intToChars(int num) {
    int len = 1;
    int n = num;
    while ((n = n / 10) != 0) {
        ++len;
    }
    char *chars = malloc(sizeof(char) * (len + 1));
    if (!chars) {
        return NULL;
    }
    chars[len] = STR_EOF;
    while (--len >= 0) {
        chars[len] = (char) (48 + (num % 10));
        num /= 10;
    }
    return chars;
}
