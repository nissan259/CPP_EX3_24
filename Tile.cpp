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

std::string Tile::gettype()  {
    return type;
}

std::vector<int> Tile::getedges()  {
    return edges;
}

std::vector<std::vector<int>> Tile::getvertexes()  {
    return vertexes;
}

std::vector<Tile*> Tile::getneighborhood()  {
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


int Tile::setedges(int index, int id) // edge is the id of the edge and id is the id of the user
{
    if (index < 0 || index > 5 || id < 1 || id > 3)
    {
        cout << "index out of range" << endl;
        return 0;
    }
    if (this->edges.at(index) != 0)
    {
        cout << "you can't build a road here because this place is taken" << endl;
        return 0;
    } // check if the edge is occupied
    if (set_special_edges(index, id) == 1)
    {
        return 1;
    }

    bool check_firstedge = false, check_neighbor_edges1 = false, check_neighbor_edges2 = false;

    try
    {
        if (getneighborhood().at((index + 1) % 6) != nullptr)
        {
            check_firstedge = getneighborhood().at((index + 1) % 6)->getedges().at((index + 3) % 6) == 0;
        }
    }
    catch (const std::exception& e)
    {
        cout << "Error checking first edge: " << e.what() << endl;
        check_firstedge = true; // Assume failure if exception occurs
    }

    try
    {
        if (getneighborhood().at((index + 1) % 6) != nullptr)
        {
            check_neighbor_edges1 = getneighborhood().at((index + 1) % 6)->getedges().at((index + 2) % 6) == 0;
        }
    }
    catch (const std::exception& e)
    {
        cout << "Error checking neighbor edge 1: " << e.what() << endl;
        check_neighbor_edges1 = true; // Assume failure if exception occurs
    }

    try
    {
        if (getneighborhood().at((index + 1) % 6) != nullptr)
        {
            check_neighbor_edges2 = getneighborhood().at((index + 1) % 6)->getedges().at((index + 4) % 6) == 0;
        }
    }
    catch (const std::exception& e)
    {
        cout << "Error checking neighbor edge 2: " << e.what() << endl;
        check_neighbor_edges2 = true; // Assume failure if exception occurs
    }

    bool check_neighbor_edges = check_neighbor_edges1 || check_neighbor_edges2;
    if (check_firstedge || check_neighbor_edges || check_before_apply(index, id))
    {
        return apply_edges(index, id);
    }
    else
    {
        cout << "you can't build a road here" << endl;
        return 0;
    }
}

int Tile::check_before_apply(int index, int id) // the general checks that are common to all the tiles
{
    // check if one of the neighbor edges are the player's, the plus 6 is to make sure that the index is not negative
    bool is_edges_occuipied_by_player = this->edges.at((6 + index - 1) % 6) == id || this->edges.at((index + 1) % 6) == id;
    // check if the vertexes are occupied by the player who is building the road
    bool is_vertexes_occuiped_by_player = this->vertexes.at((6 + index - 1) % 6).at(0) == id || this->vertexes.at((index + 1) % 6).at(0) == id;
    return is_edges_occuipied_by_player || is_vertexes_occuiped_by_player;
}

// function for special tiles that need special checks
int Tile::set_special_edges(int index, int id)
{
    bool check_upper = false, left_side = false, right_side = false, bottom = false;
    bool is_edges_occuipied_by_player = this->edges.at((6 + index - 1) % 6) == id || this->edges.at((index + 1) % 6) == id;
    int no_neighbors_edges[] = {0, 7, 10, 16, 18, 11, 2};
    for (int i = 0; i < 6; i++)
    {
        if (no_neighbors_edges[i] == this->id && index == i || is_edges_occuipied_by_player)
        {
            this->edges.at(index) = id;
            return 1;
        }
    }
    if (this->id < 3 && (index == 0 || index == 5))
    {
        for (int i = 0; i < 2; i++)
        {
            if (this->id == i && index == 5)
            {
                try
                {
                    if (getneighborhood().at(5) != nullptr)
                    {
                        check_upper = getneighborhood().at(5)->getedges().at(0) == id || getneighborhood().at(5)->getedges().at(1) == id;
                    }
                }
                catch (const std::exception& e)
                {
                    cout << "Error checking upper edge: " << e.what() << endl;
                }
            }
        }
        if (index == 0 && (this->id == 1 || this->id == 2))
        {
            try
            {
                if (getneighborhood().at(2) != nullptr)
                {
                    check_upper = getneighborhood().at(2)->getedges().at(5) == id || getneighborhood().at(2)->getedges().at(4) == id;
                }
            }
            catch (const std::exception& e)
            {
                cout << "Error checking upper edge: " << e.what() << endl;
            }
        }
        if (check_before_apply(index, id) || check_upper)
        {
            return apply_edges(index, id);
        }
    }
    if ((index == 1 || index == 2 || index == 3) && (this->id == 0 || this->id == 3 || this->id == 7 || this->id == 12 || this->id == 16))
    { // the tiles on the left side
        if (this->id == 0 && index == 1)
        {
            if (this->edges.at(0) == id || this->edges.at(2) == id || this->getneighborhood().at(3)->getedges().at(5) == id || check_before_apply(index, id))
            {
                return apply_edges(index, id);
            }
        }
        else if ((this->id == 3 && index == 0) || (this->id == 7 && index == 0))
        {
            if (this->edges.at(5) == id || this->edges.at(1) == id || this->getneighborhood().at(0)->getedges().at(1) == id || check_before_apply(index, id))
            {
                return apply_edges(index, id);
            }
        }
        else if (this->id == 3 && index == 1)
        {
            if (this->edges.at(2) == id || this->edges.at(0) == id || this->getneighborhood().at(3)->getedges().at(0) == id || check_before_apply(index, id))
            {
                return apply_edges(index, id);
            }
        }
        else if ((this->id == 7 && index == 2) || (this->id == 12 && index == 2))
        {
            if (this->edges.at(3) == id || this->edges.at(1) == id || this->getneighborhood().at(3)->getedges().at(1) == id || check_before_apply(index, id))
            {
                return apply_edges(index, id);
            }
        }
        else if (this->id == 16 && index == 1)
        {
            if (this->edges.at(0) == id || this->edges.at(2) == id || this->getneighborhood().at(1)->getedges().at(2) == id || check_before_apply(index, id))
            {
                return apply_edges(index, id);
            }
        }
    }
    if (index == 16 || index == 17 || index == 18)
    { // the tiles at the bottom
        if (this->id == 16 && index == 3)
        {
            if (this->edges.at(2) == id || this->edges.at(4) == id || this->getneighborhood().at(5)->getedges().at(2) == id || check_before_apply(index, id))
            {
                return apply_edges(index, id);
            }
        }
        else if ((this->id == 17 && index == 2) || (this->id == 18 && index == 2))
        {
            if (this->edges.at(1) == id || this->edges.at(3) == id || this->getneighborhood().at(2)->getedges().at(3) == id || check_before_apply(index, id))
            {
                return apply_edges(index, id);
            }
        }
        else if (this->id == 17 && index == 3)
        {
            if (this->edges.at(2) == id || this->edges.at(4) == id || this->getneighborhood().at(1)->getedges().at(4) == id || check_before_apply(index, id))
            {
                return apply_edges(index, id);
            }
        }
        else if (this->id == 18 && index == 3)
        {
            if (this->edges.at(2) == id || this->edges.at(4) == id || this->getneighborhood().at(0)->getedges().at(4) == id || check_before_apply(index, id))
            {
                return apply_edges(index, id);
            }
        }
    }
    if (index == 4 || index == 5)
    { // the tiles at the right side
        if (this->id == 10 && index == 4)
        {
            if (this->edges.at(3) == id || this->edges.at(5) == id || this->getneighborhood().at(4)->getedges().at(5) == id || check_before_apply(index, id))
            {
                return apply_edges(index, id);
            }
        }
        else if (this->id == 11 && index == 5)
        {
            if (this->edges.at(0) == id || this->edges.at(4) == id || this->getneighborhood().at(1)->getedges().at(4) == id || check_before_apply(index, id))
            {
                return apply_edges(index, id);
            }
        }
        else if ((this->id == 11 && index == 3) || (this->id == 15 && index == 3))
        {
            if (this->edges.at(2) == id || this->edges.at(4) == id || this->getneighborhood().at(3)->getedges().at(4) == id || check_before_apply(index, id))
            {
                return apply_edges(index, id);
            }
        }
        else if ((this->id == 15 && index == 4) || (this->id == 18 && index == 4))
        {
            if (this->edges.at(3) == id || this->edges.at(5) == id || this->getneighborhood().at(0)->getedges().at(3) == id || check_before_apply(index, id))
            {
                return apply_edges(index, id);
            }
        }
    }

    return 0;
}

int Tile::apply_edges(int index, int id)
{
    this->edges.at(index) = id;
    try
    {
        if (getneighborhood().at((index + 1) % 6) != nullptr)
        {
            getneighborhood().at((index + 1) % 6)->getedges().at((index + 3) % 6) = id;
        }
    }
    catch (const std::exception& e)
    {
        cout << "Error applying edge to neighbor: " << e.what() << endl;
    }
    return 1;
}




 int Tile::set_vertex(int index, int type, int player_id)
{
        std::cout<<"dani"<<std::endl;
    bool check1=check_roads_set_vertex(index,type,player_id);
    std::cout<<"uri"<<check1<<std::endl;
    bool check2=check_edges(index,type,player_id);
    std::cout<<"orel"<<check2<<std::endl;
    if(check1 && check2)
    {
        vertexes[0][index]=player_id;
        vertexes[1][index]=type;
        return 1;
    }
    else
    {
        return 0;
    }
}
bool Tile::check_roads_set_vertex(int index, int type, int player_id) {
    std::cout << "Entering check_roads_set_vertex with index: " << index << std::endl;
    try {
        if (index == 0) {
            std::cout << "Checking index 0" << std::endl;
            bool check_first_side = (vertexes[0][0] != player_id && vertexes[0][0] != 0) || 
                                    (vertexes[0][5] != player_id && vertexes[0][5] != 0);
            bool check_second_side = check_first_side;

            try {
                if (getneighborhood()[0] != nullptr) {
                    check_first_side = check_first_side || (getneighborhood()[0]->getvertexes()[0][1] != player_id && getneighborhood()[0]->getvertexes()[0][1] != 0);
                }
                std::cout << "Checked getneighborhood() for check_first_side at index 0" << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "Error in check_first_side: " << e.what() << "\n";
                check_first_side = true; // Assume failure if exception occurs
            }

            try {
                if (getneighborhood()[1] != nullptr) {
                    check_second_side = check_second_side || (getneighborhood()[1]->getvertexes()[0][5] != player_id && getneighborhood()[1]->getvertexes()[0][5] != 0);
                }
                std::cout << "Checked getneighborhood() for check_second_side at index 0" << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "Error in check_second_side: " << e.what() << "\n";
                check_second_side = true; // Assume failure if exception occurs
            }

            if (check_first_side || check_second_side) {
                return false;
            }
            return true;
        } else if (index == 1) {
            std::cout << "Checking index 1" << std::endl;
            bool check_first_side = (vertexes[0][1] != player_id && vertexes[0][1] != 0) || 
                                    (vertexes[0][0] != player_id && vertexes[0][0] != 0);
            bool check_second_side = check_first_side;

            try {
                if (getneighborhood()[1] != nullptr) {
                    check_first_side = check_first_side || (getneighborhood()[1]->getvertexes()[0][3] != player_id && getneighborhood()[1]->getvertexes()[0][3] != 0);
                }
                std::cout << "Checked getneighborhood() for check_first_side at index 1" << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "Error in check_first_side: " << e.what() << "\n";
                check_first_side = true; // Assume failure if exception occurs
            }

            try {
                if (getneighborhood()[2] != nullptr) {
                    check_second_side = check_second_side || (getneighborhood()[2]->getvertexes()[0][5] != player_id && getneighborhood()[2]->getvertexes()[0][5] != 0);
                }
                std::cout << "Checked getneighborhood() for check_second_side at index 1" << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "Error in check_second_side: " << e.what() << "\n";
                check_second_side = true; // Assume failure if exception occurs
            }

            if (check_first_side || check_second_side) {
                return false;
            }
            return true;
        } else if (index == 2) {
            std::cout << "Checking index 2" << std::endl;
            bool check_first_side = (vertexes[0][2] != player_id && vertexes[0][2] != 0) || 
                                    (vertexes[0][1] != player_id && vertexes[0][1] != 0);
            bool check_second_side = check_first_side;

            try {
                if (getneighborhood()[2] != nullptr) {
                    check_first_side = check_first_side || (getneighborhood()[2]->getvertexes()[0][4] != player_id && getneighborhood()[2]->getvertexes()[0][4] != 0);
                }
                std::cout << "Checked getneighborhood() for check_first_side at index 2" << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "Error in check_first_side: " << e.what() << "\n";
                check_first_side = true; // Assume failure if exception occurs
            }

            try {
                if (getneighborhood()[3] != nullptr) {
                    check_second_side = check_second_side || (getneighborhood()[3]->getvertexes()[0][0] != player_id && getneighborhood()[3]->getvertexes()[0][0] != 0);
                }
                std::cout << "Checked getneighborhood() for check_second_side at index 2" << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "Error in check_second_side: " << e.what() << "\n";
                check_second_side = true; // Assume failure if exception occurs
            }

            if (check_first_side || check_second_side) {
                return false;
            }
            return true;
        } else if (index == 3) {
            std::cout << "Checking index 3" << std::endl;
            bool check_first_side = (vertexes[0][3] != player_id && vertexes[0][3] != 0) || 
                                    (vertexes[0][2] != player_id && vertexes[0][2] != 0);
            bool check_second_side = check_first_side;

            try {
                if (getneighborhood()[3] != nullptr) {
                    check_first_side = check_first_side || (getneighborhood()[3]->getvertexes()[0][5] != player_id && getneighborhood()[3]->getvertexes()[0][5] != 0);
                }
                std::cout << "Checked getneighborhood() for check_first_side at index 3" << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "Error in check_first_side: " << e.what() << "\n";
                check_first_side = true; // Assume failure if exception occurs
            }

            try {
                if (getneighborhood()[4] != nullptr) {
                    check_second_side = check_second_side || (getneighborhood()[4]->getvertexes()[0][1] != player_id && getneighborhood()[4]->getvertexes()[0][1] != 0);
                }
                std::cout << "Checked getneighborhood() for check_second_side at index 3" << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "Error in check_second_side: " << e.what() << "\n";
                check_second_side = true; // Assume failure if exception occurs
            }

            if (check_first_side || check_second_side) {
                return false;
            }
            return true;
        } else if (index == 4) {
            std::cout << "Checking index 4" << std::endl;
            bool check_first_side = (vertexes[0][4] != player_id && vertexes[0][4] != 0) || 
                                    (vertexes[0][3] != player_id && vertexes[0][3] != 0);
            bool check_second_side = check_first_side;

            try {
                if (getneighborhood()[4] != nullptr) {
                    check_first_side = check_first_side || (getneighborhood()[4]->getvertexes()[0][0] != player_id && getneighborhood()[4]->getvertexes()[0][0] != 0);
                }
                std::cout << "Checked getneighborhood() for check_first_side at index 4" << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "Error in check_first_side: " << e.what() << "\n";
                check_first_side = true; // Assume failure if exception occurs
            }

            try {
                if (getneighborhood()[5] != nullptr) {
                    check_second_side = check_second_side || (getneighborhood()[5]->getvertexes()[0][2] != player_id && getneighborhood()[5]->getvertexes()[0][2] != 0);
                }
                std::cout << "Checked getneighborhood() for check_second_side at index 4" << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "Error in check_second_side: " << e.what() << "\n";
                check_second_side = true; // Assume failure if exception occurs
            }

            if (check_first_side || check_second_side) {
                return false;
            }
            return true;
        } else if (index == 5) {
            std::cout << "Checking index 5" << std::endl;
            bool check_first_side = (vertexes[0][5] != player_id && vertexes[0][5] != 0) || 
                                    (vertexes[0][4] != player_id && vertexes[0][4] != 0);
            bool check_second_side = check_first_side;

            try {
                if (getneighborhood()[5] != nullptr) {
                    check_first_side = check_first_side || (getneighborhood()[5]->getvertexes()[0][1] != player_id && getneighborhood()[5]->getvertexes()[0][1] != 0);
                }
                std::cout << "Checked getneighborhood() for check_first_side at index 5" << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "Error in check_first_side: " << e.what() << "\n";
                check_first_side = true; // Assume failure if exception occurs
            }

            try {
                if (getneighborhood()[0] != nullptr) {
                    check_second_side = check_second_side || (getneighborhood()[0]->getvertexes()[0][3] != player_id && getneighborhood()[0]->getvertexes()[0][3] != 0);
                }
                std::cout << "Checked getneighborhood() for check_second_side at index 5" << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "Error in check_second_side: " << e.what() << "\n";
                check_second_side = true; // Assume failure if exception occurs
            }

            if (check_first_side || check_second_side) {
                return false;
            }
            return true;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error in outer try block: " << e.what() << "\n";
        return false;
    }
    return false; // Default return value in case index does not match any condition
}


bool Tile::check_edges(int index, int type, int player_id) {
    try {
        if (index == 0) {
            bool check_first_side = (edges[0] != player_id && edges[0] != 0) || 
                                    (edges[5] != player_id && edges[5] != 0);
            bool check_second_side = check_first_side;

            try {
                if (getneighborhood()[0] != nullptr) {
                    check_first_side = check_first_side || (getneighborhood()[0]->getedges()[1] != player_id && getneighborhood()[0]->getedges()[1] != 0);
                }
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << '\n';
                check_first_side = true; // Assume failure if exception occurs
            }

            try {
                if (getneighborhood()[1] != nullptr) {
                    check_second_side = check_second_side || (getneighborhood()[1]->getedges()[5] != player_id && getneighborhood()[1]->getedges()[5] != 0);
                }
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << '\n';
                check_second_side = true; // Assume failure if exception occurs
            }

            if (check_first_side || check_second_side) {
                return false;
            }
            return true;
        } else if (index == 1) {
            bool check_first_side = (edges[1] != player_id && edges[1] != 0) || 
                                    (edges[0] != player_id && edges[0] != 0);
            bool check_second_side = check_first_side;

            try {
                if (getneighborhood()[1] != nullptr) {
                    check_first_side = check_first_side || (getneighborhood()[1]->getedges()[3] != player_id && getneighborhood()[1]->getedges()[3] != 0);
                }
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << '\n';
                check_first_side = true; // Assume failure if exception occurs
            }

            try {
                if (getneighborhood()[2] != nullptr) {
                    check_second_side = check_second_side || (getneighborhood()[2]->getedges()[5] != player_id && getneighborhood()[2]->getedges()[5] != 0);
                }
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << '\n';
                check_second_side = true; // Assume failure if exception occurs
            }

            if (check_first_side || check_second_side) {
                return false;
            }
            return true;
        } else if (index == 2) {
            bool check_first_side = (edges[2] != player_id && edges[2] != 0) || 
                                    (edges[1] != player_id && edges[1] != 0);
            bool check_second_side = check_first_side;

            try {
                if (getneighborhood()[2] != nullptr) {
                    check_first_side = check_first_side || (getneighborhood()[2]->getedges()[4] != player_id && getneighborhood()[2]->getedges()[4] != 0);
                }
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << '\n';
                check_first_side = true; // Assume failure if exception occurs
            }

            try {
                if (getneighborhood()[3] != nullptr) {
                    check_second_side = check_second_side || (getneighborhood()[3]->getedges()[0] != player_id && getneighborhood()[3]->getedges()[0] != 0);
                }
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << '\n';
                check_second_side = true; // Assume failure if exception occurs
            }

            if (check_first_side || check_second_side) {
                return false;
            }
            return true;
        } else if (index == 3) {
            bool check_first_side = (edges[3] != player_id && edges[3] != 0) || 
                                    (edges[2] != player_id && edges[2] != 0);
            bool check_second_side = check_first_side;

            try {
                if (getneighborhood()[3] != nullptr) {
                    check_first_side = check_first_side || (getneighborhood()[3]->getedges()[5] != player_id && getneighborhood()[3]->getedges()[5] != 0);
                }
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << '\n';
                check_first_side = true; // Assume failure if exception occurs
            }

            try {
                if (getneighborhood()[4] != nullptr) {
                    check_second_side = check_second_side || (getneighborhood()[4]->getedges()[1] != player_id && getneighborhood()[4]->getedges()[1] != 0);
                }
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << '\n';
                check_second_side = true; // Assume failure if exception occurs
            }

            if (check_first_side || check_second_side) {
                return false;
            }
            return true;
        } else if (index == 4) {
            bool check_first_side = (edges[4] != player_id && edges[4] != 0) || 
                                    (edges[3] != player_id && edges[3] != 0);
            bool check_second_side = check_first_side;

            try {
                if (getneighborhood()[4] != nullptr) {
                    check_first_side = check_first_side || (getneighborhood()[4]->getedges()[0] != player_id && getneighborhood()[4]->getedges()[0] != 0);
                }
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << '\n';
                check_first_side = true; // Assume failure if exception occurs
            }

            try {
                if (getneighborhood()[5] != nullptr) {
                    check_second_side = check_second_side || (getneighborhood()[5]->getedges()[2] != player_id && getneighborhood()[5]->getedges()[2] != 0);
                }
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << '\n';
                check_second_side = true; // Assume failure if exception occurs
            }

            if (check_first_side || check_second_side) {
                return false;
            }
            return true;
        } else if (index == 5) {
            bool check_first_side = (edges[5] != player_id && edges[5] != 0) || 
                                    (edges[4] != player_id && edges[4] != 0);
            bool check_second_side = check_first_side;

            try {
                if (getneighborhood()[5] != nullptr) {
                    check_first_side = check_first_side || (getneighborhood()[5]->getedges()[1] != player_id && getneighborhood()[5]->getedges()[1] != 0);
                }
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << '\n';
                check_first_side = true; // Assume failure if exception occurs
            }

            try {
                if (getneighborhood()[0] != nullptr) {
                    check_second_side = check_second_side || (getneighborhood()[0]->getedges()[3] != player_id && getneighborhood()[0]->getedges()[3] != 0);
                }
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << '\n';
                check_second_side = true; // Assume failure if exception occurs
            }

            if (check_first_side || check_second_side) {
                return false;
            }
            return true;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return false;
    }
    return false; // Default return value in case index does not match any condition
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

      bool Tile::set_first_round_vertex(Player &player, int& index) {
        if (index < 0 || index >= 7) {
            std::cerr << "Index out of bounds." << std::endl;
            return false;
        }
        if (vertexes[0][index] == 0) { // Check if the vertex is empty
            vertexes[0][index] = player.getid(); // Set player ID
            vertexes[1][index] = 1;        // Set initial building type (settlement)
             std ::string path= "the player set the vertex  the player name"+player.getName()+"\n";
            player.add_settlement(path);
            return true;
        } else {
            std::cerr << "Vertex is already occupied." << std::endl;
            return false;
        }
        }
    

    bool  Tile::set_first_round_edge(Player& p1, int &index) {
        if (index < 0 || index >= 7) {
            std::cerr << "Index out of bounds." << std::endl;
            return false;
        }
        if (edges[index] == 0) { // Check if the edge is empty
            edges[index] = p1.getid(); // Assign road to player
            std ::string path="the player "+p1.getName()+" put road in edge "+to_string(index)+"\n";
            p1.add_road(path);
            return true;
        } else {
            std::cerr << "Edge is already occupied." << std::endl;
            return false;
        }
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