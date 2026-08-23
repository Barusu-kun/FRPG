#ifndef ITEM_H
#define ITEM_H

typedef enum {ITEM_KEY, ITEM_POTION, ITEM_SWORD} ItemType;

typedef struct {

    int id;
    char name[32];
    ItemType type;
    int value;
} Item;



#endif //ITEM_H
