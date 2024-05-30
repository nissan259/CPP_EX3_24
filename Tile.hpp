#include <iostream>
#include <vector>
#include <string>
using namespace std;
namespace ariel
{
    class Tile
    {
   private :
        vector<int> edges; 
         vector<vector<int>> vertexes;        
         int value_roll;
        string type;
        int id;
        vector<Tile> neighborhoods{6};
        public: // Vector of Tile pointers        public:
        Tile(int id,int value_roll,string tyep);
        Tile getTile(int id) ;
        vector<int> getedges() ;
        vector<vector<int>> getvertexes() const;
        int getvalue_roll() const;
        string gettype()const;
        int getid() const;
        vector<Tile> getneighborhood() ;
        int setedges(int edge,int id);
        int setvertexes(int vetex,int id,int type);
        int setneighborhood(Tile neighborhood,int index);
        void operator=(const Tile& other);

    };
     
} // namespace ariel