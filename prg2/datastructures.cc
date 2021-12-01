// Datastructures.cc
//
// Student name: Pyry Laine
// Student email: pyry.j.laine@tuni.fi
// Student number: 50282836

#include "datastructures.hh"
#include <random>
#include <cmath>
#include <algorithm>
#include <map>
#include <vector>

std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = std::uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

    return static_cast<Type>(start+num);
}

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
    alltowns.clear();
    allroads.clear();
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
        alltowns.push_back(id);
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
    if(alltowns.empty()){
        std::vector<TownID> tmp;
        return tmp;
    }

    return alltowns;
}

std::vector<TownID> Datastructures::find_towns(const Name &name)
{
    std::vector<TownID> withname;
    for(std::unordered_map<TownID ,Town>::iterator i= Towns.begin(); i != Towns.end(); ++i){
        if( i->second.name_ == name){
            withname.push_back(i -> first);
        }
    }

    return withname;
}

bool Datastructures::change_town_name(TownID id, const Name &newname)
{
    std::unordered_map<TownID ,Town>::iterator i = Towns.find(id);
    if(i == Towns.end()){ // ID doesn't exist!
        return false;
    }
    else{
        i -> second.name_ = newname;
    }

    return true;
}

std::vector<TownID> Datastructures::towns_alphabetically() //korjaa
{
    if(!alphtowns.empty()){ // towns already in order
        return alphtowns;
    }

    std::map<std::string, TownID> tmp;

    for(std::unordered_map<TownID ,Town>::iterator i = Towns.begin(); i != Towns.end(); ++i){
        tmp.insert({i->second.name_, i->first});
    }

    for(std::map<std::string, TownID>::iterator i= tmp.begin(); i != tmp.end(); ++i){
        alphtowns.push_back(i ->second);
    }

    return alphtowns;
}

std::vector<TownID> Datastructures::towns_distance_increasing()
{
    if(!d_increasing.empty()){ // town distances already counted
        return d_increasing;
    }

    for(std::unordered_map<TownID, Town>::iterator i = Towns.begin(); i != Towns.end(); ++i){
        float d = sqrt((i-> second.coord_.x * i-> second.coord_.x)+(i-> second.coord_.y * i-> second.coord_.y));

        alldists.insert({d, i-> first});
        }
    for(std::map<float,TownID>::iterator i = alldists.begin(); i != alldists.end(); ++i){
        d_increasing.push_back(i->second);
    }

    return d_increasing;
}

TownID Datastructures::min_distance()
{
    if(Towns.empty()){ // no towns
        return NO_TOWNID;
    }
    if(d_increasing.empty()){ // town distances already counted
        return towns_distance_increasing()[0];
    }

    return d_increasing[0];
}

TownID Datastructures::max_distance()
{
    if(Towns.empty()){ // no towns
        return NO_TOWNID;
    }
    if(d_increasing.empty()){ // town distances already counted
        return towns_distance_increasing().back();
    }

    return d_increasing.back();
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

    if(Towns.find(id) == Towns.end()){ // no town

        vassals.push_back(NO_TOWNID);
        return vassals;
    }

    for(std::unordered_map<TownID ,Town>::iterator i = Towns.begin(); i != Towns.end(); ++i){
        if(i->second.master_ == id){
            vassals.push_back(i->first);
        }
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
        for(std::unordered_map<TownID ,Town>::iterator i = Towns.begin(); i != Towns.end(); ++i){
            if(i->second.master_ == id){
                i->second.master_ = "";
            }
        }
    }
    else{
        for(std::unordered_map<TownID ,Town>::iterator i = Towns.begin(); i != Towns.end(); ++i){
            if(i->second.master_ == id){
                i->second.master_ = Towns.at(id).master_;
            }
        }
    }
    Towns.erase(id);

    return true;
}

std::vector<TownID> Datastructures::towns_nearest(Coord coord)
{
    std::vector<TownID> ready;
    std::vector<std::pair<TownID, float>> dists;

    for(std::unordered_map<TownID, Town>::iterator i = Towns.begin(); i != Towns.end(); ++i){
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

std::vector<TownID> Datastructures::longest_vassal_path(TownID /*id*/)
{
    throw NotImplemented("longest_vassal_path()");
}

int Datastructures::total_net_tax(TownID /*id*/)
{
    throw NotImplemented("total_net_tax()");
}

//
// Phase 2 operations
//


void Datastructures::clear_roads()
{
    allroads.clear();
}

std::vector<std::pair<TownID, TownID>> Datastructures::all_roads()
{
    return allroads;
}

bool Datastructures::add_road(TownID fst, TownID snd)
{
    if(Towns.find(fst) == Towns.end() || Towns.find(snd) == Towns.end()){ // no town
            return false;
        }

    for(std::vector<std::pair<TownID, TownID>>::iterator i= allroads.begin(); i != allroads.end(); ++i){ //already have the road
        if(i->first == fst && i->second == snd){
            return false;
        }
        else if(fst == snd){
            return false;
        }
    }

    allroads.push_back({fst,snd});

    return true;
}

std::vector<TownID> Datastructures::get_roads_from(TownID from)
{
    std::vector<TownID> tmp;
    if(Towns.find(from) == Towns.end()){
        tmp.push_back(NO_TOWNID);
        return tmp;
    }

    for(std::vector<std::pair<TownID, TownID>>::iterator i= allroads.begin(); i != allroads.end(); ++i){ //already have the road
        if(i->first == from){
            tmp.push_back(i->second);
        }
        else if(i->second == from){
            tmp.push_back(i->first);
        }
    }

    return tmp;
}

std::vector<TownID> Datastructures::any_route(TownID from, TownID to)
{
    /* DFS...ish */
    if(from == to){
        for(std::unordered_map<TownID ,Town>::iterator i = Towns.begin(); i != Towns.end(); ++i){
            i->second.visited_ = false;
        }
        std::vector<TownID> ready;
        for(std::vector<TownID>::iterator i=path.begin(); i != path.end(); ++i){
            ready.push_back(*i);
        }
        path.clear();
        return ready;
    }

    std::vector<TownID> tmp = get_roads_from(from);
    Towns[from].visited_ = true;
    for(size_t i=0; i <= tmp.size(); ++i){
        if(Towns[tmp[i]].visited_ == false){
            path.push_back(tmp[i]);
            return any_route(tmp[i], to);
        }

    }

    path.pop_back();
    return any_route(tmp[0], to);
}

bool Datastructures::remove_road(TownID /*town1*/, TownID /*town2*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("remove_road()");
}

std::vector<TownID> Datastructures::least_towns_route(TownID /*fromid*/, TownID /*toid*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("least_towns_route()");
}

std::vector<TownID> Datastructures::road_cycle_route(TownID /*startid*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("road_cycle_route()");
}

std::vector<TownID> Datastructures::shortest_route(TownID /*fromid*/, TownID /*toid*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("shortest_route()");
}

Distance Datastructures::trim_road_network()
{
    // Replace the line below with your implementation
    throw NotImplemented("trim_road_network()");
}
