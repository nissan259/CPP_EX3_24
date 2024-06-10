#ifndef TILE_HPP
#define TILE_HPP
#include <iostream>
#include <vector>
#include <string>
#include "player.hpp"

namespace ariel {
    class Player;  // Forward declaration of Player class
class Tile {
public:
    Tile();
    Tile(int id, int value_roll, const std::string& type);
    Tile(const Tile& other);
    ~Tile();

    int getid() const;
    int getvalue_roll() const;
    std::string gettype();
    std::vector<int> getedges() ;
    std::vector<std::vector<int>> getvertexes() ;
    std::vector<Tile*> getneighborhood() ;
    int setedges(int index, int id);
   int  set_vertex(int index, int type, int player_id);
    void setneighborhood(Tile& neighbor, int index);
     void update_collision(int index, int id, int type);
     void display_edges();
     void display_vertixes();
    bool operator==(const Tile& other) const;
    Tile& operator=(const Tile& other);
    void display() const;
    int set_special_edges(int index, int id);
    int check_before_apply(int index, int id);
    int apply_edges(int index, int id);
    bool set_first_round_vertex(Player &player, int& index);
    bool set_first_round_edge(Player& p1, int &index);

private:
    int id;
    int value_roll;
    std::string type;
    std::vector<int> edges;
    std::vector<std::vector<int>> vertexes;
    bool check_roads_set_vertex(int index, int type, int player_id);
    bool check_edges(int index, int type, int player_id);
    Tile* neighbors[6];
};

} // namespace ariel

#endif // TILE_HPP