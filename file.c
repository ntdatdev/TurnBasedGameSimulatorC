#include <stdio.h>
#include <stdlib.h>
#include "file.h"
#include "queue.h"

// file.c
// Contains save/load logic (handles file I/O for saving and loading game state)

void save_game(Queue* q, const char* filename) {
    FILE* fp = fopen(filename, "w");

    if (fp == NULL) {
        printf("Could not open file for writing.\n");
        return;
    }

    Node* current = q->front;

    while (current != NULL) { // traverse the queue and write each fighter's data to the file
        fprintf(fp, "%d %s %d %d %d\n",
                current->data.id,
                current->data.name,
                current->data.team,
                current->data.hp,
                current->data.attack);

        current = current->next; // traversal pointer moves to the next node in the list
    }

    fclose(fp);
    printf("Game saved successfully.\n");
}

void load_game(Queue* q, const char* filename) {
    FILE* fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("Could not open file for reading.\n");
        return;
    }

    free_queue(q); // free any existing fighters in the queue before loading new data
    init_queue(q); // reset the queue to be empty before loading new data

    Fighter fighter;

    while (fscanf(fp, "%d %49s %d %d %d",
                  &fighter.id,
                  fighter.name,
                  &fighter.team,
                  &fighter.hp,
                  &fighter.attack) == 5) {  // because there are 5 values per line
                                            // only if all 5 are read successfully do we enqueue a new fighter
        enqueue(q, fighter);
    }

    fclose(fp);
    printf("Game loaded successfully.\n");
}