#ifndef INVENTORY_H
#define INVENTORY_H

#include "item.h"
#include <stdbool.h>
#include <raylib.h>

typedef struct node {
    
    Item item;
    struct node* next;


} InventoryNode;

typedef struct Inventory {

    InventoryNode* head;
    int count;
    int maxCapacity;
} Inventory;

Inventory* inventory_create(int maxCapacity);

bool inventory_add_item(Inventory* inventory, Item item);

bool inventory_remove_item(Inventory* inventory, int itemId);

void inventory_destroy(Inventory* inventory);

void inventory_render_debug(const Inventory* inventory, int posX, int posY);






#endif //INVENTORY_H
