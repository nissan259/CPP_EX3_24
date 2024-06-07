#include "Tile.hpp"
using namespace std;
namespace ariel {

Tile::Tile() : id(0), value_roll(0), type("") {
    this->edges = {0, 0, 0, 0, 0, 0};
    this->vertexes = {{0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}};
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
void Tile::display_edges() {
    for(int i=0;i<edges.size();i++)
    {
        std::cout<<edges.at(i)<<std::endl;
    }
}
void Tile::display_vertixes()
{
    int counter=0;
    for(int i=0;i<vertexes.size();i++)
    {
          counter++;  
    }
    std:cout<< "ll"<<counter<<std::endl;
}


int Tile::setedges(int index, int id) {
    std::cout << "orel: Starting setedges\n"; // Debug statement
    display_edges();
        std::cout << "orel: Starting vertex\n"; // Debug statement
    display_vertixes();
    std::cout << "orel2\n"; // Debug statement
    // Check if the edge is occupied
    std::cout << index<<std::endl; // Debug statement
    std::cout << edges.at(5)<<std::endl; // Debug statement
    bool is_edge_occupied = edges.at(5) != 0;

    // Consider if we set at second edge that we
    std::cout<<this->getneighborhood().at((index + 1) % 6)->getedges().at((index + 3) % 6)<<std::endl;
    bool check_firstedge = this->getneighborhood().at((index + 1) % 6)->getedges().at((index + 3) % 6) != 0;
    std::cout << "in"; // Debug statement
    std::cout << "orel: Checked first edge\n"; // Debug statement

    // Check if the vertexes are occupied by the player who is building the road
    bool is_vertexes_occuiped_by_player = false;
    std::cout << "orel: Initialized is_vertexes_occuiped_by_player\n"; // Debug statement
    if (index != 0) {
        std::cout << "ore1223l: Checked vertexes for index != 0\n"; // Debug statement
        // for(int i=1;i<this->getvertexes().size();i++)
        // {
        //     std::cout<<this->getvertexes().at(i).size()<< " " << id << std::endl;
        // }
        std::cout<<this->getvertexes().at(0).at(0)<< " " << id << std::endl;
        is_vertexes_occuiped_by_player = this->getvertexes().at(index).at(0) == id || this->getvertexes().at(index - 1).at(0) == id;
        std::cout << "orel: Checked vertexes for index != 0\n"; // Debug statement
    } else {
        is_vertexes_occuiped_by_player = this->getvertexes().at(index).at(0) == id || this->getvertexes().at(5).at(0) == id;
        std::cout << "orel: Checked vertexes for index == 0\n"; // Debug statement
    }

    // Check if one of the neighbor edges are the player's
    bool is_edges_occuipied_by_player = false;
    std::cout << "orel: Initialized is_edges_occuipied_by_player\n"; // Debug statement
    if (index != 0 && index != 5) {
        is_edges_occuipied_by_player = this->edges.at(index - 1) == id || this->edges.at(index + 1) == id;
        std::cout << "orel: Checked edges for index != 0 and index != 5\n"; // Debug statement
    } else if (index == 0) {
        is_edges_occuipied_by_player = this->edges.at(5) == id || this->edges.at(1) == id;
        std::cout << "orel: Checked edges for index == 0\n"; // Debug statement
    } else { // index == 5
        is_edges_occuipied_by_player = this->edges.at(4) == id || this->edges.at(0) == id;
        std::cout << "orel: Checked edges for index == 5\n"; // Debug statement
    }

    // If the conditions are met, set the edges
    if (!is_edge_occupied && (check_firstedge || is_vertexes_occuiped_by_player || is_edges_occuipied_by_player)) {
        this->edges.at(index) = id;
        std::cout << "orel: Set edge\n"; // Debug statement
        this->getneighborhood().at((index + 1) % 6)->getedges().at((index + 3) % 6) = id;
        std::cout << "orel: Set edge in neighbor\n"; // Debug statement
        return 1;
    } else {
        std::cout << "you can't build a road here" << std::endl;
        std::cout << "orel: Cannot build road\n"; // Debug statement
        return 0;
    }
}



 int Tile::set_vertex(int index, int type, int player_id)
{
    // Recall: the vertex vector has the first element as the player id and the second is city/suburb
    if (this->vertexes.at(index).at(0) == 0 && (type == 1 || type == 0) && (player_id >= 1 && player_id < 4) && index >= 0 && index < 6)
    {
        int first = this->getneighborhood().at(index % 6)->getid();
        int second = this->getneighborhood().at((index + 1) % 6)->getid();
        bool first_check = false, second_check = false;

        if (first >= 0 && second >= 0 && first < 19 && second < 19) // check if the neighbors are valid
        {
            // Remember to check that if I want to upgrade my suburb to a town, there could be problems
            bool check_firstvertex = this->getneighborhood().at(index % 6)->getvertexes().at((index + 2) % 6).at(0) == 0;
            bool check_secondvertex = this->getneighborhood().at((index + 1) % 6)->getvertexes().at((index + 4) % 6).at(0) == 0;
            bool check_road_back = this->getedges().at((index - 1) % 6) == player_id;
            bool check_road_forward = this->getedges().at((index + 1) % 6) == player_id;

            switch (index)
            {
            case 0:
                first_check = this->getneighborhood().at(0)->getvertexes().at(1).at(0) == 0;
                second_check = this->getvertexes().at(5).at(0) == 0;
                break;
            case 1:
                first_check = this->getneighborhood().at(1)->getvertexes().at(2).at(0) == 0;
                second_check = this->getvertexes().at(2).at(0) == 0;
                break;
            case 2:
                first_check = this->getneighborhood().at(2)->getvertexes().at(3).at(0) == 0;
                second_check = this->getvertexes().at(1).at(0) == 0;
                break;
            case 3:
                first_check = this->getneighborhood().at(4)->getvertexes().at(2).at(0) == 0;
                second_check = this->getvertexes().at(2).at(0) == 0;
                break;
            case 4:
                first_check = this->getneighborhood().at(4)->getvertexes().at(5).at(0) == 0;
                second_check = this->getvertexes().at(5).at(0) == 0;
                break;
            case 5:
                first_check = this->getneighborhood().at(0)->getvertexes().at(4).at(0) == 0;
                second_check = this->getvertexes().at(4).at(0) == 0;
                break;
            default:
                break;
            }

            bool total_check = first_check && second_check;
            bool is_near_by_edge = false;
            if (index != 5)
            {
                is_near_by_edge = this->getedges().at(index) == player_id && this->getedges().at(index + 1) == player_id;
            }
            else
            {
                is_near_by_edge = this->getedges().at(5) == player_id && this->getedges().at(0) == player_id;
            }

            if (check_firstvertex && check_secondvertex && this->vertexes.at(index).at(0) == 0 && (check_road_back || check_road_forward) && total_check && is_near_by_edge)
            {
                this->vertexes.at(index).at(0) = player_id;
                this->vertexes.at(index).at(1) = type;
                this->getneighborhood().at(index % 6)->getvertexes().at((index + 2) % 6).at(0) = player_id; // set the vertex of the neighbor
                this->getneighborhood().at(index % 6)->getvertexes().at((index + 2) % 6).at(1) = type;
                this->getneighborhood().at((index + 1) % 6)->getvertexes().at((index + 4) % 6).at(0) = player_id; // set the vertex of the 2nd neighbor
                this->getneighborhood().at((index + 1) % 6)->getvertexes().at((index + 4) % 6).at(1) = type;
                update_collision(index, player_id, type);
                return 1;
            }
        }
        else
        {
            return 0;
        }
    }
    return 0;
}
    void Tile::display() const {
        std::cout << "Tile ID: " << id << std::endl;
        std::cout << "Value Roll: " << value_roll << std::endl;
        std::cout << "Type: " << type << std::endl;
        std::cout << "Edges: ";
        for (int i = 0; i < 6; ++i) {
            std::cout << edges[i] << " ";
        }
        std::cout << std::endl;
        std::cout << "Vertexes: ";
        for (int i = 0; i < 6; ++i) {
            std::cout << vertexes[0][i] << " ";
        }
        std::cout << std::endl;
        std::cout << "Neighborhood: ";
        for (int i = 0; i < 6; ++i) {
            if (neighbors[i]) {
                std::cout << neighbors[i]->getid() << " ";
            } else {
                std::cout << "0 ";
            }
        }
        std::cout << std::endl;
    }

    //   bool Tile::set_first_round_vertex(int player_id, int index) {
    //     if (index < 0 || index >= 7) {
    //         std::cerr << "Index out of bounds." << std::endl;
    //         return false;
    //     }
    //     if (vertexes[index][0] == 0) { // Check if the vertex is empty
    //         vertexes[index][0] = player_id; // Set player ID
    //         vertexes[index][1] = 1;        // Set initial building type (settlement)
    //         return true;
    //     } else {
    //         std::cerr << "Vertex is already occupied." << std::endl;
    //         return false;
    //     }
    // }

    // bool  Tile::set_first_round_edge(Player& p1, int index) {
    //     if (index < 0 || index >= 7) {
    //         std::cerr << "Index out of bounds." << std::endl;
    //         return false;
    //     }
    //     if (edges[index] == 0) { // Check if the edge is empty
    //         edges[index] = p1.getid(); // Assign road to player
    //         std ::string path="the player "+p1.getName()+" put road in edge "+to_string(index)+"\n";
    //         p1.add_road(path);
    //         return true;
    //     } else {
    //         std::cerr << "Edge is already occupied." << std::endl;
    //         return false;
    //     }
    // }

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
void Tile::update_collision(int index, int id, int type) {
    for (int i : {index % 6, (index + 1) % 6}) {
        if (neighbors[i]) {
            if (i == index % 6) {
                neighbors[i]->vertexes[0][(index + 2) % 6] = id;
                neighbors[i]->vertexes[1][(index + 2) % 6] = type;
            }
            if (i == (index + 1) % 6) {
                neighbors[i]->vertexes[0][(index + 4) % 6] = id;
                neighbors[i]->vertexes[1][(index + 4) % 6] = type;
            }
        }
    }
}
}