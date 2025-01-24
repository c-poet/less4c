#include "inc/core/func.h"
#include <malloc.h>
#include <string.h>

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

BOOL charsToDouble(const char *chars, double *result) {
    return charsToDoubleByRange(chars, 0, (int) strlen(chars), result);
}

BOOL charsToDoubleByRange(const char *chars, int start, int end, double *result) {
    if (start >= end) {
        return BOOL_FALSE;
    }
    double num = 0;
    int s = 0;
    while (start < end) {
        if (chars[start] == '.' && s == 0) {
            s = 10;
            ++start;
            continue;
        } else if (chars[start] < '0' || chars[start] > '9') {
            return BOOL_FALSE;
        }
        if (s == 0) {
            num = num * 10 + chars[start] - '0';
        } else {
            num = num + ((double) (chars[start] - '0') / s);
            s *= 10;
        }
        ++start;
    }
    *result = num;
    return BOOL_TRUE;
}

BOOL charsEqChar(const char *str, char c) {
    return strlen(str) == 1 && str[0] == c;
}

BOOL charsEq(const char *str1, const char *str2) {
    return strcmp(str1, str2) == 0;
}

char *charsClone(const char *str) {
    int len = (int) strlen(str);
    char *newStr = malloc(sizeof(char) * (len + 1));
    for (int i = 0; i < len; ++i) {
        newStr[i] = str[i];
    }
    newStr[len] = STR_EOF;
    return newStr;
}

UINT charsHashCode(const char *str) {
    char c;
    UINT hash = 5381;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}
