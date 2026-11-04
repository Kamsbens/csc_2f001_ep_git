#include "location.h"
#include <cmath>
#include <numbers>

location_t::location_t(std::string n, double lat, double lon)
    : name{n}, latitude{lat}, longitude{lon}, neighbors{nullptr}, nb_neighbors{0} {
}

void location_t::set_neighbors(location_t* list[]) {
    neighbors = list;
    nb_neighbors = 0;
    while (neighbors[nb_neighbors] != nullptr) {
        nb_neighbors++;
    }
}

double location_t::distance_to(location_t* to) {
    double x = std::sin(latitude) * std::sin(to->latitude)
             + std::cos(to->longitude - longitude) * std::cos(latitude) * std::cos(to->latitude);
    return 6378 * (std::numbers::pi / 2 - std::asin(x));
}

location_t::~location_t() {
    delete[] neighbors;
}
