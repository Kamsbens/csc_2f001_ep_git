#include <stdio.h>
#include "monster.h"
#include "army.h"

int main(void) {
    struct monster* tab[10];
    struct army* armee = create_army();
    char buffer[32];

    for (int i = 0; i < 10; i++) {
        snprintf(buffer, sizeof(buffer), "Pikachu-%d", i);
        tab[i] = create_monster(buffer, 100);
        add_monster_to_army(armee, tab[i]);
    }

    display_army(armee);

    // Chaque monstre a sa propre allocation sur la heap.
    for (int i = 0; i < 10; i++) {
        delete_monster(tab[i]);
    }
    delete_army(armee);
    return 0;
}
