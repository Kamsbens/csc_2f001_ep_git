#include "shortest_path.h"
#include <iostream>

shortest_path_t::shortest_path_t(location_t* depart, location_t* arrivee)
    : head{nullptr}, base{nullptr}, from{depart}, to{arrivee} {
}

void shortest_path_t::compute() {
    head = new node_t{nullptr, from, nullptr, 0, from->distance_to(to), false};

    while (true) {
        base = nullptr;
        for (node_t* n = head; n != nullptr; n = n->next) {
            if (!n->visited && (base == nullptr || n->total < base->total)) {
                base = n;
            }
        }

        if (base == nullptr || base->location == to) {
            break;
        }

        base->visited = true;
        for (size_t i = 0; i < base->location->nb_neighbors; i++) {
            location_t* cur = base->location->neighbors[i];
            double distance = base->from_origin + base->location->distance_to(cur);
            double total = distance + cur->distance_to(to);

            node_t* n = head;
            while (n != nullptr && n->location != cur) {
                n = n->next;
            }

            if (n == nullptr) {
                n = new node_t{head, cur, base, distance, total, false};
                head = n;
            } else if (distance < n->from_origin) {
                n->from = base;
                n->from_origin = distance;
                n->total = total;
                n->visited = false;
            }
        }
    }
}

// Affiche les villes dans l'ordre du depart vers l'arrivee.
static void display_nodes(node_t* n, const std::string& depart) {
    if (n->from != nullptr) {
        display_nodes(n->from, depart);
    }
    std::cout << "  * " << n->location->name << " at " << n->from_origin
              << " km from " << depart << '\n';
}

void shortest_path_t::display() {
    if (base == nullptr || base->location != to) {
        std::cout << "unable to find a path from " << from->name
                  << " to " << to->name << '\n';
        return;
    }

    std::cout << "path from " << from->name << " to " << to->name << '\n';
    display_nodes(base, from->name);
}

shortest_path_t::~shortest_path_t() {
    node_t* cur = head;
    while (cur != nullptr) {
        node_t* suivant = cur->next;
        delete cur;
        cur = suivant;
    }
}
