// Datastructures.cc
//
// Student name: Pyry Laine
// Student email: pyry.j.laine@tuni.fi
// Student number: 50282836

#include "datastructures.hh"
#include <random>
#include <cmath>
#include <algorithm>

std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = std::uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

    return static_cast<Type>(start+num);
}

// Modify the code below to implement the functionality of the class.
// Also remove comments from the parameter names when you implement
// an operation (Commenting out parameter name prevents compiler from
// warning about unused parameters on operations you haven't yet implemented.)

Datastructures::Datastructures()
{
    // Write any initialization you need here
}

Datastructures::~Datastructures()
{
    // Write any cleanup you need here
}

unsigned int Datastructures::town_count()
{
    return Towns.size();
}

void Datastructures::clear_all()
{
    Towns.clear();
    town_count();
}

bool Datastructures::add_town(TownID id, const Name &name , Coord coord, int tax)
{    
    if(Towns.find(id) != Towns.end()){ // ID already in use!
        return false;
    }

    else{
        Town newtown;
        newtown.name_ = name;
        newtown.coord_ = coord;
        newtown.tax_ = tax;

        Towns.insert({id, newtown});
    }

    return true;
}

Name Datastructures::get_town_name(TownID id)
{
    return Towns[id].name_;
}

Coord Datastructures::get_town_coordinates(TownID id)
{
    return Towns[id].coord_;
}

int Datastructures::get_town_tax(TownID id)
{
    return Towns[id].tax_;
}

std::vector<TownID> Datastructures::all_towns()
{
    std::vector<TownID> allIDs;
    for(std::map<TownID ,Town>::iterator i= Towns.begin(); i != Towns.end(); ++i){
        allIDs.push_back(i -> first);
    }

    return allIDs;
}

std::vector<TownID> Datastructures::find_towns(const Name &name)
{
    std::vector<TownID> withname;
    for(std::map<TownID ,Town>::iterator i= Towns.begin(); i != Towns.end(); ++i){
        if( i->second.name_ == name){
            withname.push_back(i -> first);
        }
    }

    return withname;
}

bool Datastructures::change_town_name(TownID id, const Name &newname)
{
    std::map<TownID ,Town>::iterator i = Towns.find(id);
    if(i == Towns.end()){ // ID doesn't exist!
        return false;
    }
    else{
        i -> second.name_ = newname;
    }

    return true;
}

std::vector<TownID> Datastructures::towns_alphabetically()
{
    /* ID the same as the beginning of towns name and map is already in alph. order... */
    return all_towns();

}

std::vector<TownID> Datastructures::towns_distance_increasing()
{
    // Replace the line below with your implementation
    throw NotImplemented("towns_distance_increasing()");
}

TownID Datastructures::min_distance()
{
    // Replace the line below with your implementation
    throw NotImplemented("min_distance()");
}

TownID Datastructures::max_distance()
{
    // Replace the line below with your implementation
    throw NotImplemented("max_distance()");
}

bool Datastructures::add_vassalship(TownID /*vassalid*/, TownID /*masterid*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("add_vassalship()");
}

std::vector<TownID> Datastructures::get_town_vassals(TownID /*id*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("get_town_vassals()");
}

std::vector<TownID> Datastructures::taxer_path(TownID /*id*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("taxer_path()");
}

bool Datastructures::remove_town(TownID /*id*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("remove_town()");
}

std::vector<TownID> Datastructures::towns_nearest(Coord /*coord*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("towns_nearest()");
}

std::vector<TownID> Datastructures::longest_vassal_path(TownID /*id*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("longest_vassal_path()");
}

int Datastructures::total_net_tax(TownID /*id*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("total_net_tax()");
}
