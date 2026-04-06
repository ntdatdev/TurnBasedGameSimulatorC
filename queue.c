# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "queue.h"

// queue.c
// Contains queue logic, linked list logic, battle logic

void init_queue(Queue* q) {
    q->front = NULL;
    q->rear = NULL;
}   // Initializes the queue by setting front and rear to NULL

int is_empty(Queue* q) {
    return q->front == NULL;
}   // Checks if the queue is empty by checking if front is NULL
    // returns 1 for true, 0 for false

Node* create_node(Fighter fighter)
// function name: create_node
// parameter: one Fighter named fighter
// return type: Node *
    {
    Node* new_node = (Node*)malloc(sizeof(Node));
    // create a new node by allocating memory for it using malloc, 
    // and create a pointer to it called new_node

    // malloc(sizeof(Node)) -> allocate raw memory big enough for one Node
    // malloc(...) returns a void * (generic pointer)
    // in simpler terms,malloc returns an address
    // (Node *) = Typecast -> “treat that generic pointer as a pointer to Node”

    if (new_node == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    new_node->data = fighter;   //set the data to the fighter passed in as a parameter
    new_node->next = NULL;      //created a new node that not point to anything yet

    return new_node;
    }   // allocates memory for one linked-list node

void enqueue(Queue* q, Fighter fighter) {
    Node* new_node = create_node(fighter);

    if (is_empty(q)) {
        q->front = new_node;
        q->rear = new_node;
    } 
    // if the queue is empty, this new node is both the front and rear of the queue

    else {  //  if queue not empty. 
            //  For example, adding Orc to queue: Knight = front -> Archer -> Mage = rear
        q->rear->next = new_node;   // old rear's next points to Orc (new node)
        q->rear = new_node;         // rear now becomes Orc (new node)
    }       //  queue now looks like: Knight (front) -> Archer -> Mage -> Orc (rear)
}

Fighter dequeue(Queue* q) {
    Fighter empty_fighter = {0, "", 0, 0, 0}; 

    if (is_empty(q)) {
        printf("Queue is empty.\n");
        return empty_fighter;
    }

    // Suppose queue is
    // Knight (front) -> Archer -> Orc (rear)

    Node* temp = q->front;  // temp points to the front of the queue, which is Knight
    Fighter fighter = temp->data;  // saves Knight's data to fighter variable

    q->front = q->front->next;  // move front to the next node, which is Archer. 
                                // Queue now looks like: Archer (front) -> Orc (rear)

    if (q->front == NULL) {
        q->rear = NULL;
    } // if queue becomes empty after removal, rear must also become NULL

    free(temp); // free the memory allocated for the old front node (Knight)
    return fighter; // return the data of the old front node (Knight's data)
                    // by copying into a local variable that we return by value (not pointer)
}

void display_fighters(Queue* q) {
    Node* current = q->front;   //  create a traversal pointer called current 
                                //  that starts at the front of the queue
    // uses a traversal pointer
    // then moves through the list
    // until current == NULL

    if (is_empty(q)){
        printf("No fighters in queue.\n");
        return;
    }

    printf("\nCurrent fighters in queue:\n");

    while (current != NULL) {
        printf("ID: %d, Name: %s, Team: %d, HP: %d, Attack: %d\n",
                current->data.id, 
                current->data.name, 
                current->data.team, 
                current->data.hp, 
                current->data.attack);

        current = current->next;    // move to the next node in the list
    }

    printf("\n");
}

int team_alive(Queue* q, int team) {    // checks if a team still has at least one living fighter
    Node* current = q->front;   // create a traversal pointer called current 
                                // that starts at the front of the queue
    while (current != NULL) {
        if (current->data.team == team && current->data.hp > 0) {
            return 1;   // if we find a fighter on the team with hp > 0, that team is alive
        }
        current = current->next;    // traversal pointer moves to the next node in the list
    }
    return 0;   // if we don't find any fighters on the team with hp > 0, that team is not alive
}

Node* find_first_enemy(Queue* q, int attacker_team) {
                    // If attacker is Team 1, find first fighter from Team 2
                    // If attacker is Team 2, find first fighter from Team 1

    Node* current = q->front;   // create a traversal pointer called current 
                                // that starts at the front of the queue
    while (current != NULL) {
        if (current->data.team != attacker_team && current->data.hp > 0) {
            return current;   // if we find a fighter on the enemy team with hp > 0, return a pointer to that node
        }
        current = current->next;    // traversal pointer moves to the next node in the list
    }
    return NULL;    // if we don't find any fighters on the enemy team with hp > 0, return NULL

    // We return a Node*, not a Fighter, because we want to 
    // mofidy that enemy's HP directly inside the queue
}

void remove_dead_fighters(Queue* q) {
    Node* current = q->front;
    Node* previous = NULL;

    while (current != NULL) {
        if (current->data.hp <= 0){
            Node* to_delete = current;
            if (previous == NULL) { // Case 1: dead node is front
                q->front = current->next; // move front foward
                current = q->front;
            } else { // Case 2: dead node is in middle or rear
                previous->next = current->next; // then previous skips over it
                current = current->next;
            }
            if (to_delete == q->rear) {
                q->rear = previous;

            }
            free(to_delete);
        } else {
            previous = current;
            current = current->next;    
        }
    }
}

void process_turn(Queue* q) {
    if (is_empty(q)) {
        printf("No fighters in queue.\n");
        return;
    }

    if (!team_alive(q, 1)) {
        printf("Team 2 wins!\n");
        return;
    }

    if (!team_alive(q, 2)) {
        printf("Team 1 wins!\n");
        return;
    }

    Fighter attacker = dequeue(q);

    if (attacker.hp <= 0) {
        printf("%s is already defeated and cannot act.\n", attacker.name);
        remove_dead_fighters(q);
        return;
    }

    Node* enemy = find_first_enemy(q, attacker.team);

    if (enemy == NULL) {
        printf("No enemy found.\n");
        return;
    }

    printf("%s attacks %s for %d damage!\n",
           attacker.name,
           enemy->data.name,
           attacker.attack);

    enemy->data.hp -= attacker.attack;

    if (enemy->data.hp <= 0) {
        printf("%s has been defeated!\n", enemy->data.name);
    } else {
        printf("%s now has %d HP.\n", enemy->data.name, enemy->data.hp);
    }

    if (attacker.hp > 0) {
        enqueue(q, attacker);
    }

    remove_dead_fighters(q);

    if (!team_alive(q, 1)) {
        printf("Team 2 wins!\n");
    } else if (!team_alive(q, 2)) {
        printf("Team 1 wins!\n");
    }
}

void free_queue(Queue* q) {
    while (!is_empty(q)) {
        dequeue(q);
    }
}