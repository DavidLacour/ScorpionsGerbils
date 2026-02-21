#pragma once
#include "../Interface/Drawable.hpp"
#include <vector>
#include "Graph.hpp"
#include <memory>
#include "../Interface/Updatable.hpp"
#include "../Utility/Vec2d.hpp"
#include <string>
#include <map>
class Stats: public Drawable,
    public Updatable
{
public:
    Stats();
    ~Stats() {};

    virtual void draw(sf::RenderTarget& target) const override ;

    void setActive(const int&);
    void setActive();
    void focusOn(std::string title);

    /**
     * @brief Add a graph to the statistics display
     *
     * @param index Graph identifier
     * @param label Graph label
     * @param titles Curve titles for the graph
     * @param min Minimum display value
     * @param max Maximum display value
     * @param size Dimensions of the graph window
     */
    void addGraph( const int&, std::string const& ,std::vector<std::string> const&, const double&,const double&, Vec2d );

    void reset();
    virtual void update(sf::Time ) override;

private:
    int stats_active_index_;
    sf::Time stats_clock_;
    sf::Time stats_clock_refresh_;
    sf::Time stats_time_refresh_rate_;

    std::unordered_map<int,std::unique_ptr<Graph>> stats_map_index_graph_;

    std::unordered_map<int,std::string> stats_map_index_label_;
    std::unordered_map<std::string,int> stats_map_label_index_;


};

