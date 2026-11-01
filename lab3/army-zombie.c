#include "army.h"
#include <stdio.h>
#include <stdlib.h>

struct node {
    struct monster* monstre;
    struct node* next;
};

struct army {
    struct node* premier;
    struct node* dernier;
    int stars;
};

struct army* create_army(void) {
    struct army* armee = malloc(sizeof(*armee));
    if (armee == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    armee->premier = NULL;
    armee->dernier = NULL;
    armee->stars = 0;
    return armee;
}

void add_monster_to_army(struct army* armee, struct monster* monstre) {
    struct node* nouveau = malloc(sizeof(*nouveau));
    if (nouveau == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    nouveau->monstre = monstre;
    nouveau->next = NULL;

    if (armee->premier == NULL) {
        armee->premier = nouveau;
    } else {
        armee->dernier->next = nouveau;
    }
    armee->dernier = nouveau;
}

void display_army(struct army* armee) {
    printf("This is a %d stars army\n", armee->stars);

    struct node* courant = armee->premier;
    while (courant != NULL) {
        display_monster(courant->monstre);
        courant = courant->next;
    }
}

void delete_army(struct army* armee) {
    struct node* courant = armee->premier;
    while (courant != NULL) {
        struct node* suivant = courant->next;
        free(courant); // On ne libere pas les monstres ici.
        courant = suivant;
    }
    free(armee);
}
