#ifndef ARMY_H
#define ARMY_H

#include "monster.h"

/* Structure définie séparément dans chaque implementation. */
struct army;

struct army* create_army(void);
void add_monster_to_army(struct army* armee, struct monster* monstre);
void display_army(struct army* armee);
void delete_army(struct army* armee);

#endif
