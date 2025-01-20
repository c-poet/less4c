#include "inc/core/chars_ref.h"
#include "malloc.h"
#include <string.h>

CharsRef *charsRefNew(const char *chars, int start, int end) {
    CharsRef *ref = malloc(sizeof(CharsRef));
    if (!ref) {
        return NULL;
    }
    ref->start = start;
    ref->end = end;
    ref->chars = chars;
    return ref;
}

void charsRefMoveStartIndex(CharsRef *charsRef, int index) {
    charsRef->start = charsRef->start + index;
}

void charsRefMoveEndIndex(CharsRef *charsRef, int index) {
    charsRef->end = charsRef->end + index;
}

BOOL charsRefEquals(CharsRef *charsRef1, CharsRef *charsRef2) {
    if (charsRef1 == charsRef2) {
        return BOOL_TRUE;
    }
    if (charsRef1->end - charsRef1->start != charsRef2->end - charsRef2->start) {
        return BOOL_FALSE;
    }
    int i = charsRef1->end - charsRef1->start;
    while (--i >= 0) {
        if (charsRef1->chars[charsRef1->start + i] != charsRef2->chars[charsRef2->start + i]) {
            return BOOL_FALSE;
        }
    }
    return BOOL_TRUE;
}

BOOL charsRefEqualsChars(CharsRef *charsRef, const char *chars) {
    if (charsRef->chars == chars) {
        return BOOL_TRUE;
    }
    int len = (int) strlen(chars);
    if (charsRef->end - charsRef->start != len) {
        return BOOL_FALSE;
    }
    while (--len >= 0) {
        if (charsRef->chars[charsRef->start + len] != chars[len]) {
            return BOOL_FALSE;
        }
    }
    return BOOL_TRUE;
}

char *charsRefToChars(CharsRef *charsRef) {
    if (!charsRef || charsRef->end <= charsRef->start) {
        return NULL;
    }
    int len = charsRef->end - charsRef->start;
    char *chars = malloc(sizeof(char) * (len + 1));
    if (!chars) {
        return NULL;
    }
    int i = 0;
    while (i < len) {
        chars[i] = charsRef->chars[charsRef->start + i];
        ++i;
    }
    chars[len] = STR_EOF;
    return chars;
}

void charsRefDel(CharsRef *charsRef) {
    if (charsRef) {
        free(charsRef);
    }
}
