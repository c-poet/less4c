#include "inc/core/file.h"
#include <stdio.h>
#include <string.h>

String *fileReadAll(char *fileName) {
    FILE *file = fopen(fileName, "r");
    if (!file) {
        return NULL;
    }
    String *string = stringNew();
    if (!string) {
        fclose(file);
        return NULL;
    }
    int len;
    char buf[1024];
    while ((len = (int) fread(buf, sizeof(char), 1024, file)) > 0
           && stringAppendCharsRange(string, buf, 0, len)) {
    }
    fclose(file);
    return string;
}

BOOL fileHasExtensions(char *fileName) {
    int len = (int) strlen(fileName);
    int i = 0;
    while (i < len) {
        if (fileName[i] == FILE_EXT_SEPARATOR) {
            return BOOL_TRUE;
        }
        ++i;
    }
    return BOOL_FALSE;
}
