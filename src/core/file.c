#include "inc/core/file.h"
#include <stdio.h>

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
