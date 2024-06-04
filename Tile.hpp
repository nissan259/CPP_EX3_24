#ifndef TILE_HPP
#define TILE_HPP

#include <vector>
#include <string>

namespace ariel {

class Tile {
public:
    Tile();
    Tile(int id, int value_roll, const std::string& type);
    Tile(const Tile& other);
    ~Tile();

    int getid() const;
    int getvalue_roll() const;
    std::string gettype() const;
    std::vector<int> getedges() const;
    std::vector<std::vector<int>> getvertexes() const;
    std::vector<Tile*> getneighborhood() const;
    int setedges(int index, int id);
    int setvertexes(int index, int id, int type);
    void setneighborhood(Tile& neighbor, int index);

    bool operator==(const Tile& other) const;
    Tile& operator=(const Tile& other);

private:
    int id;
    int value_roll;
    std::string type;
    std::vector<int> edges;
    std::vector<std::vector<int>> vertexes;
    Tile* neighbors[6];
};

} // namespace ariel

#endif // TILE_HPP
