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
}

Datastructures::~Datastructures()
{

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
    if(Towns.find(id) == Towns.end()){ // no town
        return NO_TOWNID;
    }

    return Towns[id].name_;
}

Coord Datastructures::get_town_coordinates(TownID id)
{
    if(Towns.find(id) == Towns.end()){ // no town
        return NO_COORD;
    }

    return Towns[id].coord_;
}

int Datastructures::get_town_tax(TownID id)
{
    if(Towns.find(id) == Towns.end()){ // no town
        return NO_VALUE;
    }

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
    std::vector<TownID> ready;
    std::vector<std::pair<TownID, float>> dists;

    for(std::map<TownID, Town>::iterator i = Towns.begin(); i != Towns.end(); ++i){
        float d = sqrt((i-> second.coord_.x * i-> second.coord_.x)+(i-> second.coord_.y * i-> second.coord_.y));
        dists.push_back({i->first, d});
    }

    std::sort(dists.begin(), dists.end(), [](std::pair<TownID, float> &left, std::pair<TownID, float> &right){
        return left.second < right.second;
    });

    for(std::vector<std::pair<TownID, float>>::iterator k = dists.begin(); k != dists.end(); ++k){
        ready.push_back(k->first);
    }

    return ready;
}

TownID Datastructures::min_distance()
{
    if(Towns.empty()){ // no towns
        return NO_TOWNID;
    }

    return towns_distance_increasing()[0];
}

TownID Datastructures::max_distance()
{
    if(Towns.empty()){ // no towns
        return NO_TOWNID;
    }

    return towns_distance_increasing().back();
}

bool Datastructures::add_vassalship(TownID vassalid, TownID masterid)
{
    if(Towns.find(vassalid) == Towns.end() || Towns.find(masterid) == Towns.end()) // towns exist
    {
        return false;
    }
    if(Towns.at(vassalid).master_ != ""){ //already vassal
        return false;
    }

    Towns.at(vassalid).master_ = masterid;

    return true;
}

std::vector<TownID> Datastructures::get_town_vassals(TownID id)
{
    std::vector<TownID> vassals;

    for(std::map<TownID ,Town>::iterator i = Towns.begin(); i != Towns.end(); ++i){
        if(i->second.master_ == id){
            vassals.push_back(i->first);
        }
    }

    if(vassals.empty()){
        vassals.push_back(NO_TOWNID);
    }

    return vassals;
}

std::vector<TownID> Datastructures::taxer_path(TownID id)
{
    std::vector<TownID> taxpath;

    if(Towns.find(id) == Towns.end()){ //town not found
        taxpath.push_back(NO_TOWNID);
    }

    taxpath.push_back(id);
    while(Towns.at(id).master_ != "")
    {
        taxpath.push_back(Towns.at(id).master_);
        id = Towns.at(id).master_;
    }

    return taxpath;
}

bool Datastructures::remove_town(TownID id)
{
    if(Towns.find(id) == Towns.end()){ //town not found
        return false;
    }
    if(Towns.at(id).master_ == ""){ // no master
        for(std::map<TownID ,Town>::iterator i = Towns.begin(); i != Towns.end(); ++i){
            if(i->second.master_ == id){
                i->second.master_ = "";
            }
        }
    }
    else{
        for(std::map<TownID ,Town>::iterator i = Towns.begin(); i != Towns.end(); ++i){
            if(i->second.master_ == id){
                i->second.master_ = Towns.find(id)->first;
            }
        }
    }
    Towns.erase(Towns.find(id));

    return true;
}

std::vector<TownID> Datastructures::towns_nearest(Coord coord)
{
    std::vector<TownID> ready;
    std::vector<std::pair<TownID, float>> dists;

    for(std::map<TownID, Town>::iterator i = Towns.begin(); i != Towns.end(); ++i){
        float a = i-> second.coord_.x;
        float b = i-> second.coord_.y;
        float j = coord.x;
        float k = coord.y;
        float d = sqrt(((a * a)-2*a*j+(j * j))+(b * b)-2*b*k+(k * k));
        dists.push_back({i->first, d});
    }

    std::sort(dists.begin(), dists.end(), [](std::pair<TownID, float> &left, std::pair<TownID, float> &right){
        return left.second < right.second;
    });

    for(std::vector<std::pair<TownID, float>>::iterator k = dists.begin(); k != dists.end(); ++k){
        ready.push_back(k->first);
    }

    return ready;
}

std::vector<TownID> Datastructures::longest_vassal_path(TownID id)
{
    std::vector<TownID> taxpath;

    if(Towns.find(id) == Towns.end()){ //town not found
        taxpath.push_back(NO_TOWNID);
    }

    taxpath.push_back(id);
    while(Towns.at(id).master_ != "")
    {
        taxpath.push_back(Towns.at(id).master_);
        id = Towns.at(id).master_;
    }

    return taxpath;
}

int Datastructures::total_net_tax(TownID /*id*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("total_net_tax()");
}
