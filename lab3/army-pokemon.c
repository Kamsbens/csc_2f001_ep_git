#include "army.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct army {
    struct monster** monsters;
    int top;
    int capacity;
};

struct army* create_army(void) {
    struct army* armee = malloc(sizeof(*armee));
    if (armee == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    armee->monsters = NULL;
    armee->top = -1;
    armee->capacity = 0;
    return armee;
}

void add_monster_to_army(struct army* armee, struct monster* monstre) {
    if (armee->capacity == 0) {
        armee->monsters = malloc(sizeof(*armee->monsters));
        if (armee->monsters == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        armee->capacity = 1;
    } else if (armee->top + 1 == armee->capacity) {
        int nouvelle_capacite = armee->capacity * 2;
        struct monster** nouveau_tableau =
            malloc(nouvelle_capacite * sizeof(*nouveau_tableau));
        if (nouveau_tableau == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }

        // On copie les adresses des monstres, pas les monstres eux-memes.
        memcpy(nouveau_tableau, armee->monsters,
               (armee->top + 1) * sizeof(*nouveau_tableau));
        free(armee->monsters);
        armee->monsters = nouveau_tableau;
        armee->capacity = nouvelle_capacite;
    }

    armee->top++;
    armee->monsters[armee->top] = monstre;
}

void display_army(struct army* armee) {
    for (int i = 0; i <= armee->top; i++) {
        display_monster(armee->monsters[i]);
    }
}

void delete_army(struct army* armee) {
    free(armee->monsters);
    free(armee);
}
