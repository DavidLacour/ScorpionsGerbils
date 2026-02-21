#include "Stats.hpp"
#include <string>
#include "../Interface/Drawable.hpp"
#include <vector>
#include "Graph.hpp"
#include <memory>
#include "../Utility/Vec2d.hpp"
#include <iostream>
#include "../Application.hpp"
#include "../Utility/Utility.hpp"
#include <unordered_map>
Stats::Stats() : stats_active_index_(-1),stats_clock_(sf::Time::Zero),stats_clock_refresh_(sf::Time::Zero),stats_time_refresh_rate_(sf::seconds(getAppConfig().stats_refresh_rate )) {}

void Stats::update(sf::Time dt)
{
    stats_clock_ += dt;
    stats_clock_refresh_+= dt;

    if (stats_clock_refresh_ >= stats_time_refresh_rate_) {
        stats_map_index_graph_[stats_active_index_]->updateData(
            stats_clock_refresh_
            , getAppEnv().fetchData(stats_map_index_label_[stats_active_index_]));
        stats_clock_refresh_= sf::Time::Zero;
    }
}



void Stats::draw(sf::RenderTarget& target) const
{
    if(stats_active_index_ >=0) {
        stats_map_index_graph_.at(stats_active_index_)->draw(target);
    }
}

void Stats::addGraph( const int& index, std::string const& label,std::vector<std::string> const& titles, const double& min,const double& max, Vec2d size)
{

    stats_map_index_graph_[index].reset(new Graph(titles,size,min,max));
    stats_map_index_label_[index]= label;
    stats_map_label_index_[label]=index;

}

void Stats::setActive(int const& index)
{
    stats_active_index_=index;
}
void Stats::setActive()
{
    if ( stats_active_index_ <= 0 and !stats_map_index_graph_.empty()) {
        ++stats_active_index_;
    }
    if( stats_active_index_ <= int (stats_map_index_graph_.size() ) ) {
        ++ stats_active_index_;
    } else {
        stats_active_index_=0;
    }
}


void Stats::focusOn(std::string title)
{
    stats_active_index_=stats_map_label_index_[title];
    stats_map_index_graph_[stats_active_index_]->reset();
}


void Stats::reset()
{
    for (auto& map : stats_map_index_graph_) {
        map.second->reset();
    }
}
