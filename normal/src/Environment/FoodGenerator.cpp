#include "../Random/Normal.hpp"
#include "../Application.hpp"
#include "Food.hpp"

void FoodGenerator::update(sf::Time dt)
{
    timer_ += dt;
    if(timer_ >= sf::seconds(getAppConfig().food_generator_delta) ) {
        timer_ = sf::Time::Zero ;
        getAppEnv().addEntity(new Food(Vec2d(normal( getAppConfig().simulation_world_size/2, getAppConfig().simulation_world_size/4 * getAppConfig().simulation_world_size/4)
                                             ,normal( getAppConfig().simulation_world_size/2, getAppConfig().simulation_world_size/4 * getAppConfig().simulation_world_size/4)))
                             );
    }
}
