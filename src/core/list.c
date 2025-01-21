#include "inc/core/list.h"
#include <malloc.h>

List *listNew(int valueSize) {
    return listNewByInit(0, valueSize);
}

List *listNewByInit(int initSize, int valueSize) {
    if (initSize < 0 || valueSize <= 0) {
        return NULL;
    }
    List *list = malloc(sizeof(List));
    if (!list) {
        return NULL;
    }
    list->size = 0;
    list->actualSize = 0;
    list->valueSize = valueSize;
    list->values = NULL;
    if (initSize > 0) {
        list->actualSize = initSize;
        list->values = malloc(valueSize * list->actualSize);
        if (!list->values) {
            listDel(list);
            return NULL;
        }
    }
    return list;
}

BOOL listAdd(List *list, POINTER val) {
    return listInsert(list, list->size, val);
}

BOOL listInsert(List *list, int index, POINTER val) {
    if (index < 0 || list->size < index) {
        return BOOL_FALSE;
    }
    if (list->values == NULL) {
        list->actualSize = LIST_VALUES_R_LEN + 1;
        list->values = malloc(list->valueSize * list->actualSize);
        if (!list->values) {
            return BOOL_FALSE;
        }
    } else if (list->size + 1 >= list->actualSize) {
        list->actualSize = LIST_VALUES_R_LEN + 1 + list->size;
        POINTER*values = realloc(list->values, list->valueSize * list->actualSize);
        if (!values) {
            return BOOL_FALSE;
        }
        list->values = values;
    }
    if (list->size == index) {
        list->values[list->size] = val;
    } else {
        int i = list->size;
        while (i > index) {
            list->values[i] = list->values[i - 1];
            --i;
        }
        list->values[index] = val;
    }
    ++list->size;
    return BOOL_TRUE;
}

BOOL listRemove(List *list, POINTER val) {
    int index = 0;
    while (index < list->size) {
        if (val == list->values[index]) {
            break;
        }
        ++index;
    }
    return index != list->size && listRemoveByIndex(list, index) != NULL;
}

POINTER listRemoveLast(List *list) {
    return listRemoveByIndex(list, list->size - 1);
}

POINTER listRemoveByIndex(List *list, int index) {
    if (index < 0 || index >= list->size) {
        return NULL;
    }
    POINTER val = list->values[index];
    if (index != list->size - 1) {
        while (index < list->size - 1) {
            list->values[index] = list->values[index + 1];
            ++index;
        }
    }
    --list->size;
    return val;
}

BOOL listEmpty(List *list) {
    return list == NULL || list->size <= 0;
}

void listEach(List *list, void func(POINTER val)) {
    if (list) {
        int i = 0;
        while (i < list->size) {
            func(list->values[i]);
            ++i;
        }
    }
}

void listDel(List *list) {
    if (list) {
        free(list->values);
        free(list);
    }
}
