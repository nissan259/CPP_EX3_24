#include  <iostream>
#include <vector>
#include <string>
#include "Tile.hpp"

using namespace std;
namespace ariel
{
    Tile::Tile(int id,int value_roll,string type):id(id),value_roll(value_roll),type(type)
    {
        this->edges={0,0,0,0,0,0};
        this->vertexes={{0,0,0,0,0,0,0},{0,0,0,0,0,0,}}; // first matrix is the id of the vertex and the second is the type of the vertex moshav or city
        this->neighborhoods={}; 
            }
    Tile Tile::getTile(int id)
    {
        return *this;
    }
    vector<int> Tile::getedges()
    {
        return this->edges;
    }
    vector<std::vector<int>> Tile::getvertexes() const // first matrix is the id of the vertex and the second is the type of the vertex moshav or city
    {
        return this->vertexes;
    }
    int Tile::getvalue_roll() const
    {
        return this->value_roll;
    }
    string Tile::gettype()const
    {
        return this->type;
    }
    int Tile::getid() const // id of the tile
    {
        return this->id;
    }
    vector<Tile> Tile::getneighborhood() // Vector of Tile pointers
    {
        return this->neighborhoods;
    }
    int Tile::setedges(int edge ,int id) // edge is the id of the edge and id is the id of the tile
    {
        if(this->edges.at(edge)==0)
        {
            this->edges.at(id)=edge;
            return 1;
        }
        else
        {
            return 0;
        }
    }
    int Tile::setvertexes(int index,int id,int type)
    {
        if(this->vertexes.at(0).at(index)==0 &&(type==1||type==0)&&(id>=0&&id<3)&&index>=0&&index<6 )
        {
            this->vertexes.at(0).at(index)=id;
            this->vertexes.at(1).at(index)=type;
            return 1;
        }
        else
        {
            return 0;
        }
    }
    void Tile::operator=(const Tile& other)
    {
        this->edges=other.edges;
        this->vertexes=other.vertexes;
        this->value_roll=other.value_roll;
        this->type=other.type;
        this->id=other.id;
        this->neighborhoods=other.neighborhoods;
    }
    int Tile::setneighborhood(Tile neighborhood,int index)
    {
        if(this->neighborhoods.at(index).getid()==0)
        {
            this->neighborhoods.at(index)=neighborhood;
            return 1;
        }
        else
        {
            return 0;
        }
    }
    Tile::Tile(const Tile& other)
    {
        this->edges = other.edges;
        this->vertexes = other.vertexes;
        this->value_roll = other.value_roll;
        this->type = other.type;
        this->id = other.id;
        this->neighborhoods = other.neighborhoods;
    }

    Tile::~Tile()
    {
        this->edges.clear();
        this->vertexes.clear();
        this->neighborhoods.clear();
    }
}