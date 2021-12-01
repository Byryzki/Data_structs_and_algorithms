// Datastructures.hh
//
// Student name:
// Student email:
// Student number:

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>
#include <tuple>
#include <utility>
#include <limits>
#include <functional>
#include <exception>
#include <map>

// Types for IDs
using TownID = std::string;
using Name = std::string;

// Return values for cases where required thing was not found
TownID const NO_TOWNID = "----------";

// Return value for cases where integer values were not found
int const NO_VALUE = std::numeric_limits<int>::min();

// Return value for cases where name values were not found
Name const NO_NAME = "!!NO_NAME!!";

// Type for a coordinate (x, y)
struct Coord
{
    int x = NO_VALUE;
    int y = NO_VALUE;
};

// Example: Defining == and hash function for Coord so that it can be used
// as key for std::unordered_map/set, if needed
inline bool operator==(Coord c1, Coord c2) { return c1.x == c2.x && c1.y == c2.y; }
inline bool operator!=(Coord c1, Coord c2) { return !(c1==c2); } // Not strictly necessary

struct CoordHash
{
    std::size_t operator()(Coord xy) const
    {
        auto hasher = std::hash<int>();
        auto xhash = hasher(xy.x);
        auto yhash = hasher(xy.y);
        // Combine hash values (magic!)
        return xhash ^ (yhash + 0x9e3779b9 + (xhash << 6) + (xhash >> 2));
    }
};

// Example: Defining < for Coord so that it can be used
// as key for std::map/set
inline bool operator<(Coord c1, Coord c2)
{
    if (c1.y < c2.y) { return true; }
    else if (c2.y < c1.y) { return false; }
    else { return c1.x < c2.x; }
}

// Return value for cases where coordinates were not found
Coord const NO_COORD = {NO_VALUE, NO_VALUE};

// Type for a distance (in metres)
using Distance = int;

// Return value for cases where Distance is unknown
Distance const NO_DISTANCE = NO_VALUE;

// This exception class is there just so that the user interface can notify
// about operations which are not (yet) implemented
class NotImplemented : public std::exception
{
public:
    NotImplemented() : msg_{} {}
    explicit NotImplemented(std::string const& msg) : msg_{msg + " not implemented"} {}

    virtual const char* what() const noexcept override
    {
        return msg_.c_str();
    }
private:
    std::string msg_;
};


// This is the class you are supposed to implement

class Datastructures
{
public:
    Datastructures();
    ~Datastructures();

    // Estimate of performance: O(1)
    // Short rationale for estimate: Function has to return only the size value that is already known.
    unsigned int town_count();

    // Estimate of performance: O(N)
    // Short rationale for estimate: Program has to delete an element at a time.
    void clear_all();

    // Estimate of performance: O(N)
    // Short rationale for estimate: Inserting to unordered_map is O(N) + searching if ID already in use
    // std::find is O(N) complex.
    bool add_town(TownID id, Name const& name, Coord coord, int tax);

    // Estimate of performance: O(2N) (Theta(N))
    // Short rationale for estimate: Finding if town exists is O(N) and returning name is O(N) (Theta(1))
    Name get_town_name(TownID id);

    // Estimate of performance: O(2N) (Theta(N))
    // Short rationale for estimate: Finding if town exists is O(N) and returning coord is O(N) (Theta(1))
    Coord get_town_coordinates(TownID id);

    // Estimate of performance: O(2N) (Theta(N))
    // Short rationale for estimate: Finding if town exists is O(N) and returning tax is O(N) (Theta(1))
    int get_town_tax(TownID id);

    // Estimate of performance: O(1)
    // Short rationale for estimate: returns a ready vector or an empty one
    std::vector<TownID> all_towns();

    // Estimate of performance: O(N)
    // Short rationale for estimate: For looping through items is O(N)
    std::vector<TownID> find_towns(Name const& name);

    // Estimate of performance: O(N)
    // Short rationale for estimate: If ID is not found, find goes through all items
    bool change_town_name(TownID id, Name const& newname);

    // Estimate of performance: O(nlog(n)+n) (Omega(1))
    // Short rationale for estimate: Copying values to map is O(nlog(n)) complex and then the vector takes another O(N)
    std::vector<TownID> towns_alphabetically();

    // Estimate of performance: O(nlog(n)+n) Omega(1)
    // Short rationale for estimate: forloop O(n) + map insertion O(nlog(n)) = O(nlog(n)+n)
    std::vector<TownID> towns_distance_increasing();

    // Estimate of performance: O(nlog(n)+n) (Omega(1))
    // Short rationale for estimate: If distance_increasing not previously run, that have to be done, else
    // the maps's first value is returned
    TownID min_distance();

    // Estimate of performance: O(nlog(n)+n) (Omega(1))
    // Short rationale for estimate: If distance_increasing not previously run, that have to be done, else
    // the maps's last value is returned
    TownID max_distance();

    // Estimate of performance: O(N)
    // Short rationale for estimate: Instering data to map's index in O(N) complex
    bool add_vassalship(TownID vassalid, TownID masterid);

    // Estimate of performance: O(N) (Omega(1))
    // Short rationale for estimate: Only one for loop with O(n) complexity, if no vassals at all Omega(1)
    std::vector<TownID> get_town_vassals(TownID id);

    // Estimate of performance: O(2N)
    // Short rationale for estimate: While loop is O(n) and if town found in last slot find is N complex
    std::vector<TownID> taxer_path(TownID id);

    // Non-compulsory phase 1 operations

    // Estimate of performance: O(4N)
    // Short rationale for estimate: Function has 2 separate for loops and one map remove by key with O(N) complexity
    //also a check if town is found in N complex.
    bool remove_town(TownID id);

    // Estimate of performance: O(nlog(n)+2N)
    // Short rationale for estimate: 2 forloops with complexity of O(N) separately from a std::sort with O(nlog(n)) complexity
    std::vector<TownID> towns_nearest(Coord coord);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> longest_vassal_path(TownID id);

    // Estimate of performance:
    // Short rationale for estimate:
    int total_net_tax(TownID id);

    TownID get_id();

    // Phase 2 operations

    // Estimate of performance:
    // Short rationale for estimate:
    void clear_roads();

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<std::pair<TownID, TownID>> all_roads();

    // Estimate of performance:
    // Short rationale for estimate:
    bool add_road(TownID town1, TownID town2);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> get_roads_from(TownID id);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> any_route(TownID fromid, TownID toid);

    // Non-compulsory phase 2 operations

    // Estimate of performance:
    // Short rationale for estimate:
    bool remove_road(TownID town1, TownID town2);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> least_towns_route(TownID fromid, TownID toid);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> road_cycle_route(TownID startid);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> shortest_route(TownID fromid, TownID toid);

    // Estimate of performance:
    // Short rationale for estimate:
    Distance trim_road_network();

private:
    struct Town{
      std::string name_;
      Coord coord_;
      int tax_;
      TownID master_;

    };

    std::unordered_map<TownID ,Town> Towns;
    std::vector<TownID> alltowns;
    std::vector<TownID> alphtowns;
    std::map<float,TownID> alldists;
    std::vector<TownID> d_increasing;

};

#endif // DATASTRUCTURES_HH
