#include "inc/core/str.h"
#include "inc/core/func.h"
#include <malloc.h>
#include <string.h>

String *stringNew() {
    return stringNewByLen(0);
}

String *stringNewByLen(int len) {
    String *string = malloc(sizeof(String));
    if (!string) {
        return NULL;
    }
    string->len = 0;
    if (len > 0) {
        string->chars = malloc(sizeof(char) * len);
        if (!string->chars) {
            stringDel(string);
            return NULL;
        }
        string->actualLen = len;
        string->chars[0] = STR_EOF;
    } else {
        string->chars = NULL;
        string->actualLen = 0;
    }
    return string;
}

BOOL stringAppend(String *target, String *source) {
    return stringAppendCharsRange(target, source->chars, 0, source->len);
}

BOOL stringAppendChars(String *target, const char *source) {
    return stringAppendCharsRange(target, source, 0, (int) strlen(source));
}

BOOL stringAppendCharsRange(String *target, const char *source, int start, int end) {
    int len = end - start;
    if (target->len + len >= target->actualLen) {
        if (target->chars == NULL) {
            target->actualLen = len + CHARS_R_LEN;
            target->chars = malloc(sizeof(char) * target->actualLen);
            if (!target->chars) {
                return BOOL_FALSE;
            }
        } else {
            target->actualLen = target->len + len + CHARS_R_LEN;
            char *chars = realloc(target->chars, sizeof(char) * target->actualLen);
            if (!chars) {
                return BOOL_FALSE;
            }
            target->chars = chars;
        }
    }
    int i = 0;
    while (i < len) {
        target->chars[target->len + i] = source[start + i];
        ++i;
    }
    target->len += len;
    target->chars[target->len] = STR_EOF;
    return BOOL_TRUE;
}

BOOL stringAppendInt(String *target, int num) {
    char *chars = intToChars(num);
    if (!chars) {
        return BOOL_FALSE;
    }
    BOOL ret = stringAppendChars(target, chars);
    free(chars);
    return ret;
}

void stringDel(String *string) {
    if (string) {
        free(string->chars);
        free(string);
    }
}