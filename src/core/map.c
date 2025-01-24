#include "inc/core/map.h"
#include <malloc.h>

int tableIndex(Map *map, POINTER k) {
    return (int) (map->hashCode(k) % map->tableSize);
}

int tableIndexItem(Map *map, MapItem *item) {
    return (int) (item->hashCode % map->tableSize);
}

void tableInit(MapItem **table, int len) {
    for (int i = 0; i < len; ++i) {
        table[i] = NULL;
    }
}

BOOL tableEnlarge(Map *map, int len) {
    if (map->table == NULL) {
        map->table = malloc(sizeof(MapItem *) * len);
        if (!map->table) {
            return BOOL_FALSE;
        }
        tableInit(map->table, len);
        map->tableSize = len;
    } else if (map->size + len >= (map->tableSize * 1.2)) {
        len = (int) (map->tableSize * 1.5);
        MapItem **table = malloc(sizeof(MapItem *) * len);
        if (!table) {
            return BOOL_FALSE;
        }
        tableInit(table, len);
        int oldTableSize = map->tableSize;
        map->tableSize = len;
        for (int i = 0; i < oldTableSize; ++i) {
            if (map->table[i] != NULL) {
                table[tableIndexItem(map, map->table[i])] = map->table[i];
            }
        }
        free(map->table);
        map->table = table;
    }
    return BOOL_TRUE;
}

MapItem *mapGetItem(Map *map, POINTER k) {
    if (map->size == 0) {
        return NULL;
    }
    int index = tableIndex(map, k);
    MapItem *item = map->table[index];
    while (item != NULL && !map->equals(item->k, k)) {
        item = item->next;
    }
    return item;
}

MapItem *mapItemNew(UINT hashCode, POINTER k, POINTER v) {
    MapItem *mapItem = malloc(sizeof(MapItem));
    if (!mapItem) {
        return NULL;
    }
    mapItem->hashCode = hashCode;
    mapItem->k = k;
    mapItem->v = v;
    mapItem->next = NULL;
    return mapItem;
}

void mapItemDel(MapItem *mapItem) {
    if (mapItem) {
        free(mapItem);
    }
}

Map *mapNew(BOOL (*equals)(POINTER, POINTER), UINT (*hashCode)(POINTER)) {
    return mapNewByInit(1 << 4, equals, hashCode);
}

Map *mapNewByInit(int initSize, BOOL (*equals)(POINTER, POINTER), UINT (*hashCode)(POINTER)) {
    Map *map = malloc(sizeof(Map));
    if (!map) {
        return NULL;
    }
    map->size = 0;
    map->tableSize = 0;
    map->equals = equals;
    map->hashCode = hashCode;
    map->table = NULL;
    if (!tableEnlarge(map, initSize)) {
        mapDel(map);
        return BOOL_FALSE;
    }
    return map;
}

POINTER mapGet(Map *map, POINTER k) {
    MapItem *item = mapGetItem(map, k);
    return item == NULL ? NULL : item->v;
}

BOOL mapPut(Map *map, POINTER k, POINTER v) {
    MapItem *item = mapGetItem(map, k);
    if (item != NULL) {
        item->v = v;
        return BOOL_TRUE;
    }
    if (!tableEnlarge(map, 1)) {
        return BOOL_FALSE;
    }
    item = mapItemNew(map->hashCode(k), k, v);
    if (item == NULL) {
        return BOOL_FALSE;
    }
    int index = tableIndexItem(map, item);
    if (map->table[index] == NULL) {
        map->table[index] = item;
    } else {
        MapItem *pre = map->table[index];
        while (pre->next != NULL) {
            pre = pre->next;
        }
        pre->next = item;
    }
    return BOOL_TRUE;
}

POINTER mapRemove(Map *map, POINTER k) {
    if (map->size == 0) {
        return NULL;
    }
    int index = tableIndex(map, k);
    MapItem *pre = NULL, *next = map->table[index];
    while (next != NULL && !map->equals(next->k, k)) {
        pre = next;
        next = next->next;
    }
    if (next == NULL) {
        return NULL;
    }
    if (pre == NULL) {
        map->table[index] = map->table[index]->next;
    } else {
        pre->next = next->next;
    }
    return next;
}

void mapEach(Map *map, void (*func)(POINTER, POINTER)) {
    if (map && map->size > 0) {
        MapItem *item;
        for (int i = 0; i < map->tableSize; ++i) {
            item = map->table[i];
            while (item != NULL) {
                func(item->k, item->v);
                item = item->next;
            }
        }
    }
}

void mapDel(Map *map) {
    if (map) {
        MapItem *pre, *next;
        for (int i = 0; i < map->tableSize; ++i) {
            next = map->table[i];
            while (next != NULL) {
                pre = next;
                next = pre->next;
                mapItemDel(pre);
            }
        }
        free(map->table);
        free(map);
    }
}
