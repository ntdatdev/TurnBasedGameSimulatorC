#ifndef QUEUE_H
#define QUEUE_H

#define NAME_LENGTH 50

//  queue.h
//  Tells other files what structs exists and what function exists, 
//  but not how they work (implementation is in queue.c) 

typedef struct Fighter {
    int id;
    char name[NAME_LENGTH];
    int team;
    int hp;
    int attack;
} Fighter;      // typedef (struct Fighter) Fighter -> can initialize as Fighter a 
                // instead of struct Fighter a

typedef struct Node {
    Fighter data;
    struct Node* next;
} Node;

typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

// Queue functions

void init_queue(Queue *q);
int is_empty(Queue *q);
Node *create_node(Fighter fighter);
void enqueue(Queue *q, Fighter fighter);
Fighter dequeue(Queue *q);
void display_fighters(Queue *q);
void free_queue(Queue *q);

// Battle functions
int team_alive(Queue *q, int team);
Node *find_first_enemy(Queue *q, int attacker_team);
void remove_dead_fighters(Queue *q);
void process_turn(Queue *q);

#endif