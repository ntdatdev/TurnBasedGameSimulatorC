#include <stdio.h>
#include <string.h>
#include "queue.h"
#include "file.h"

// main.c
// this is the menu and user interaction file

int main() {
    Queue q;
    int choice;
    char filename[100];

    init_queue(&q); // because init expects a pointer, we pass in the address of q using &q

    do {
        printf("==== TURN-BASED BATTLE QUEUE SIMULATOR ====\n");
        printf("1. Add fighter\n");
        printf("2. Show fighters\n");
        printf("3. Process next turn\n");
        printf("4. Save game\n");
        printf("5. Load game\n");
        printf("6. Exit\n");
        printf("Choose: ");
        scanf("%d", &choice); // read the user's menu choice and store it in the variable choice
                              // store it in the address of choice using &choice 
                              // because scanf needs a pointer to where it should store the input value

        if (choice == 1) {
            Fighter fighter;    // local variable to hold the new fighter's data before we enqueue it

            printf("Enter fighter ID: ");
            scanf("%d", &fighter.id);       // read the fighter's ID and store it in fighter.id

            printf("Enter fighter name: ");
            scanf("%49s", fighter.name);    // read the fighter's name and store it in fighter.name
                                        // %49s to prevent buffer overflow (leave space for null terminator)

            printf("Enter team (1 or 2): ");
            scanf("%d", &fighter.team);     // read the fighter's team and store it in fighter.team

            printf("Enter HP: ");
            scanf("%d", &fighter.hp);   // read the fighter's HP and store it in fighter.hp

            printf("Enter attack: ");
            scanf("%d", &fighter.attack);   // read the fighter's attack and store it in fighter.attack

            enqueue(&q, fighter);   // enqueue, therefore data is not lost
            printf("Fighter added.\n\n");
        }
        else if (choice == 2) {
            display_fighters(&q);
        }
        else if (choice == 3) {
            process_turn(&q);
            printf("\n");
        }
        else if (choice == 4) {
            printf("Enter filename: ");
            scanf("%99s", filename);
            save_game(&q, filename);
            printf("\n");
        }
        else if (choice == 5) {
            printf("Enter filename: ");
            scanf("%99s", filename);
            load_game(&q, filename);
            printf("\n");
        }
        else if (choice == 6) {
            printf("Exiting program.\n");
        }
        else {
            printf("Invalid choice. Try again.\n\n");
        }

    } while (choice != 6); // keep showing the menu until the user chooses to exit by entering 6
                            // do-while loop checks the while condition afterward
                            // so the menu will always show at least once, and then it will keep showing as long as choice is not 6

    free_queue(&q);         // free any remaining fighters in the queue before exiting the program
    return 0;
}