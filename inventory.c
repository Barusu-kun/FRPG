#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <raylib.h>
#include "inventory.h"
#include "item.h"


Inventory* inventory_create(int maxCapacity){


Inventory* inventory = malloc(sizeof(Inventory));

if (inventory == NULL) return NULL;

inventory->head = NULL;       
inventory->count = 0;         
inventory->maxCapacity = maxCapacity;

return inventory;
}


bool inventory_add_item(Inventory* inventory, Item item) {


if (inventory == NULL) return false;
if (inventory->count >= inventory->maxCapacity) return false;

InventoryNode* inventorynode = malloc(sizeof(InventoryNode));

if (inventorynode == NULL) return false;

inventorynode->item = item;
inventorynode->next = inventory->head;
inventory->head = inventorynode;
inventory->count += 1;

return true;

}


bool inventory_remove_item(Inventory* inventory, int itemId) {

    if (inventory == NULL || inventory->head == NULL) return false;

    InventoryNode* current = inventory->head;
    InventoryNode* previous = NULL;

    while (current != NULL) {

        if (current->item.id == itemId) {

            if (current == inventory->head) {
                inventory->head = inventory->head->next;
                free(current);
                inventory->count -= 1;
            }
            else {
                previous->next = current->next;
                free(current);
                inventory->count -= 1;
            }
            return true;
        }
        previous = current;
        current = current->next;

    }
    return false;
}

void inventory_destroy(Inventory* inventory) {

    if (inventory == NULL) return;

    InventoryNode* current = inventory->head;
    InventoryNode* nextNode = NULL;

    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
    free(inventory);
}

void inventory_render_debug(const Inventory* inventory, int posX, int posY) {

    if (inventory == NULL) return;
    
    InventoryNode* current = inventory->head;
    InventoryNode* nextNode = NULL;
    

    while (current != NULL) {
        nextNode = current->next;
        DrawText(TextFormat("-'%s' ", current->item.name),posX,posY, 20, BLACK);
        current = nextNode;
        posY += 20;
    }
}
