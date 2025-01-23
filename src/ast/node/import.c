#include "inc/ast/node/import.h"
#include <stdio.h>
#include <malloc.h>

Import *importNew(char *fileName, Node *root) {
    Import *import = malloc(sizeof(Import));
    if (!import) {
        return NULL;
    }
    nodeInit((POINTER) import);
    import->type = NT_IMPORT;
    import->fileName = fileName;
    import->root = root;
    import->print = (POINTER) importPrint;
    import->destroy = (POINTER) importDel;
    root->parent = (POINTER) import;
    return import;
}

void importPrint(Import *import, int level) {
    nodePrintTypeByLevel((POINTER) import, level);
    printf("[fileName=%s]", import->fileName);
    nodePrintByLevel(import->root, level + 1);
}

void importDel(Import *import) {
    if (import) {
        nodeDel(import->root);
        free(import->fileName);
        free(import);
    }
}
