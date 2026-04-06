#ifndef FILE_H
#define FILE_H

#include "queue.h"

// file.h
// This file declares save/load functions

void save_game(Queue* q, const char* filename);
void load_game(Queue* q, const char* filename);

#endif 