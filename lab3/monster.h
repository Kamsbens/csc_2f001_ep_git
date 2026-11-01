#ifndef MONSTER_H
#define MONSTER_H

#include "macro.h"

struct monster {
    char name[NAME_SIZE];
    int health;
};

struct monster* create_monster(char* name, int health);
void display_monster(struct monster* monstre);
void delete_monster(struct monster* monstre);

#endif
