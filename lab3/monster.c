#include "monster.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct monster* create_monster(char* nom, int vie) {
    struct monster* monstre = malloc(sizeof(*monstre));
    if (monstre == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    strncpy(monstre->name, nom, NAME_SIZE - 1);
    monstre->name[NAME_SIZE - 1] = '\0';
    monstre->health = vie;
    return monstre;
}

void display_monster(struct monster* monstre) {
    printf("name : %s\n", monstre->name);
    printf("number of health points : %d\n", monstre->health);
}

void delete_monster(struct monster* monstre) {
    free(monstre);
}
