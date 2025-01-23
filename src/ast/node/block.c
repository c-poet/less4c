#include "inc/ast/node/block.h"
#include <malloc.h>

Block *blockNew() {
    Block *block = malloc(sizeof(Block));
    if (!block) {
        return NULL;
    }
    nodeInit((POINTER) block);
    block->type = NT_Block;
    block->addChild = (POINTER) blockAddChild;
    block->print = (POINTER) blockPrint;
    block->destroy = (POINTER) blockDel;
    block->getChildren = (POINTER) blockGetChildren;
    block->children = listNew(sizeof(Node *));
    if (!block->children) {
        blockDel(block);
        return NULL;
    }
    return block;
}

BOOL blockAddChild(Block *block, Node *child) {
    return listAdd(block->children, child);
}

List *blockGetChildren(Block *block) {
    return block->children;
}

void blockPrint(Block *block, int level) {
    nodePrintTypeByLevel((POINTER) block, level);
    nodeListPrintByLevel(block->children, level + 1);
}

void blockDel(Block *block) {
    if (block) {
        nodeListDel(block->children);
        listDel(block->children);
        free(block);
    }
}

