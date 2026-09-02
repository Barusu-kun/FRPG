#include "dialogue.h"
#include <raylib.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


DialogueBox* dialogue_create(void) {
    DialogueBox* box = malloc(sizeof(DialogueBox));
    if (box == NULL) return NULL;

    
    snprintf(box->currentText, sizeof(box->currentText), "%s", "XXX");
    snprintf(box->speakerName, sizeof(box->speakerName), "%s", "Admin");
    box->isActive = false;
    
    return box;
}


void dialogue_open(DialogueBox* box, const char* speaker, const char* text) {
    if (box == NULL || speaker == NULL || text == NULL) return;

    snprintf(box->currentText, sizeof(box->currentText), "%s", text);
    snprintf(box->speakerName, sizeof(box->speakerName), "%s", speaker);
    box->isActive = true;
}


void dialogue_close(DialogueBox* box) {
    if (box == NULL) return;

    box->isActive = false;
    box->currentText[0] = '\0';
    box->speakerName[0] = '\0';
}


void dialogue_render(const DialogueBox* box, int screenWidth, int screenHeight) {

    if (box->isActive) {
    DrawRectangle( 20.0f,screenHeight - 340.0f, screenWidth -40.0f,320.0f, PINK );
    DrawText(box->currentText, 40.0f, screenHeight - 320.0f, 20, BLACK );

    }

}

void dialogue_destroy(DialogueBox* box) {
    
    if (box != NULL) {
    free(box);
    }

}

