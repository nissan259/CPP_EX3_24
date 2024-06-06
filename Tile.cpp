#include "Tile.hpp"

namespace ariel {

Tile::Tile() : id(0), value_roll(0), type("") {
    this->edges = {0, 0, 0, 0, 0, 0};
    this->vertexes = {{0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}};
    for (int i = 0; i < 6; ++i) {
        neighbors[i] = nullptr;
    }
}

Tile::Tile(int id, int value_roll, const std::string& type) : id(id), value_roll(value_roll), type(type) {
    this->edges = {0, 0, 0, 0, 0, 0};
    this->vertexes = {{0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}};
    for (int i = 0; i < 6; ++i) {
        neighbors[i] = nullptr;
    }
}

Tile::Tile(const Tile& other) : id(other.id), value_roll(other.value_roll), type(other.type), edges(other.edges), vertexes(other.vertexes) {
    for (int i = 0; i < 6; ++i) {
        neighbors[i] = other.neighbors[i];
    }
}

Tile::~Tile() {
    // No need to clear vectors as they are managed by the standard library
}

int Tile::getid() const {
    return id;
}

int Tile::getvalue_roll() const {
    return value_roll;
}

std::string Tile::gettype() const {
    return type;
}

std::vector<int> Tile::getedges() const {
    return edges;
}

std::vector<std::vector<int>> Tile::getvertexes() const {
    return vertexes;
}

std::vector<Tile*> Tile::getneighborhood() const {
    std::vector<Tile*> neighborhood_list(neighbors, neighbors + 6);
    return neighborhood_list;
}

int Tile::setedges(int index, int id) {
    if (index < 0 || index >= 6) return 0;
    if (neighbors[(index + 1) % 6] && neighbors[(index + 1) % 6]->edges[(index + 3) % 6] == 0) {
        if (edges[index] == 0) {
            edges[index] = id;
            neighbors[(index + 1) % 6]->edges[(index + 3) % 6] = id;
            return 1;
        }
    }
    return 0;
}

int Tile::setvertexes(int index, int id, int type) {
    if (index < 0 || index >= 6 || id < 0 || id >= 3 || (type != 0 && type != 1)) return 0;
    if (vertexes[0][index] == 0) {
        bool valid = true;
        for (int i : {index % 6, (index + 1) % 6}) {
            if (neighbors[i]) {
                if (i == index % 6 && neighbors[i]->vertexes[0][(index + 2) % 6] != 0) valid = false;
                if (i == (index + 1) % 6 && neighbors[i]->vertexes[0][(index + 4) % 6] != 0) valid = false;
            }
        }
        if (valid) {
            vertexes[0][index] = id;
            vertexes[1][index] = type;
            return 1;
        }
    }
    return 0;
}


void Tile::setneighborhood(Tile& neighbor, int index) {
    if (index >= 0 && index < 6) {
        neighbors[index] = &neighbor;
    }
}

bool Tile::operator==(const Tile& other) const {
    return id == other.id && value_roll == other.value_roll && type == other.type &&
           edges == other.edges && vertexes == other.vertexes;
}

Tile& Tile::operator=(const Tile& other) {
    if (this == &other) return *this;
    id = other.id;
    value_roll = other.value_roll;
    type = other.type;
    edges = other.edges;
    vertexes = other.vertexes;
    for (int i = 0; i < 6; ++i) {
        neighbors[i] = other.neighbors[i];
    }
    return *this;
}

}
