#ifndef DIALOGUE_H
#define DIALOGUE_H

#include <stdbool.h>


typedef struct DialogueBox {
    char currentText[256]; // Texte actuellement affiché
    char speakerName[64];  // Nom de l'entité qui parle
    bool isActive;         // Indique si la boîte de dialogue est ouverte à l'écran
} DialogueBox;

DialogueBox* dialogue_create(void);

void dialogue_open(DialogueBox* box, const char* speaker, const char* text);

void dialogue_close(DialogueBox* box);

void dialogue_render(const DialogueBox* box, int screenWidth, int screenHeight);

void dialogue_destroy(DialogueBox* box);


#endif //DIALOGUE_H