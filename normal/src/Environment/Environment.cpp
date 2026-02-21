#include <list>
#include  <SFML/Graphics.hpp>
#include "../Utility/Vec2d.hpp"
#include "Environment.hpp"
#include "../Application.hpp"
#include "../Utility/Utility.hpp"
#include <algorithm>
#include "../Animal/NeuronalScorpion/Sensor.hpp"
#include <map>
#include <string>
void Environment::addEntity(OrganicEntity* organicEntity)
{
    if(organicEntity != nullptr) {

        organic_entity_.push_back(organicEntity);
    }
}

void Environment::addWave(Wave* wa)
{
    if(wa!= nullptr) {
        env_list_waves_.push_back(wa);
    }
}

void Environment::addGenerator(FoodGenerator* foodGenerator)
{
    if(foodGenerator != nullptr) {
        food_generator_.push_back(foodGenerator);
    }
}

void Environment::addRock(Rock* roc)
{
    if(roc != nullptr) {
        env_list_rocks_.push_back(roc);
    }
}
void Environment::addObstacle(CircularCollider* roc)
{
    if(roc != nullptr) {
        env_list_obstacles_.push_back(roc);
    }
}

void Environment::update(sf::Time dt)
{
    for( const auto& FG : food_generator_) {
        FG->update(dt);
    }

    for( auto& organicEntity : organic_entity_) {

        if(organicEntity != nullptr ) {
            organicEntity->update(dt);
            organicEntity->OrganicEntity::update(dt);
        }
    }

    for( auto& wav : env_list_waves_) {

        if(wav != nullptr ) {
            wav->update(dt);
        }
    }

    for (auto& OE : organic_entity_) {
        if(OE != nullptr ) {
            if ( (OE->getAge() >= OE->getAgeLimit()) or  (OE->getEnergy() <= getAppConfig().animal_min_energy)) {
                for (auto& other : organic_entity_) {
                    if (other != nullptr && other != OE) {
                        other->forgetEntity(OE);
                    }
                }
                kill_list_.push_back(OE);
                OE = nullptr;
            }
        }
    }
    while(!(kill_list_.empty())) {
        delete kill_list_.front();
        kill_list_.pop_front();
    }
    organic_entity_.erase(std::remove(organic_entity_.begin(), organic_entity_.end(), nullptr), organic_entity_.end());

    for(auto& Wav : env_list_waves_) {
        if (Wav != nullptr) {
            if (Wav->waveGetWaveIntensity() <= getAppConfig().wave_intensity_threshold)

            {
                delete Wav;
                Wav = nullptr;
            }
        }
    }
    env_list_waves_.erase(std::remove(env_list_waves_.begin(), env_list_waves_.end(), nullptr), env_list_waves_.end());
}

std::list<OrganicEntity*> Environment::getEntitiesInSightForAnimal(Animal* animal) const
{

    std::list<OrganicEntity*> visibleEntities;

    if (!organic_entity_.empty()) {
        for (const auto& entity: organic_entity_) {
            if (animal->isTargetInSight(entity->getPosition())) {

                visibleEntities.push_back(entity);
            }
        }
        return visibleEntities;
    }
    visibleEntities.clear();
    return visibleEntities;

}

void Environment::draw(sf::RenderTarget& targetWindow)
{
    for (const auto& organic_entity: organic_entity_) {
        organic_entity->draw(targetWindow);
    }
    for (const auto& wav : env_list_waves_) {
        wav->draw(targetWindow);
    }

    for (const auto& roc: env_list_rocks_) {
        roc->draw(targetWindow);
    }
    for (const auto& roc: env_list_obstacles_) {
        roc->draw(targetWindow);
    }
    if (isDebugOn()) {
        double worldSize = getAppConfig().simulation_world_size;
        Vec2d pos;
        pos.x =worldSize/2;
        pos.y = worldSize*3/4;
        auto text = buildText( "FoodGenerator: " + to_nice_string(food_generator_.size()) + " GerbilAgeMating: " + to_nice_string(getAppConfig().gerbil_min_age_mating)+  " Scorpion: " + to_nice_string(getAppConfig().gerbil_min_age_mating),
                               pos,
                               getAppFont(),
                               getAppConfig().default_debug_text_size*4,
                               sf::Color::Black
                               ,0
                             );
        targetWindow.draw(text);
        Vec2d pos2;
        pos2.x =worldSize/2;
        pos2.y = worldSize*6/7 ;
        auto text2 = buildText( "Sfemale energyMating: "+ to_nice_string(getAppConfig().scorpion_energy_min_mating_female)
                                +"Smale: "+ to_nice_string(getAppConfig().scorpion_energy_min_mating_male)
                                +"Gfemale: "+ to_nice_string(getAppConfig().gerbil_energy_min_mating_female)
                                +"Gmale: "+ to_nice_string(getAppConfig().gerbil_energy_min_mating_male)
                                ,   pos2,
                                getAppFont(),
                                getAppConfig().default_debug_text_size*2,
                                sf::Color::Black
                                ,0
                              );
        targetWindow.draw(text2);
    }
}

void Environment::clean()
{
    for ( const auto& organicEntity: organic_entity_ ) {
        delete organicEntity;
    }
    for ( const auto& food_generator: food_generator_ ) {
        delete food_generator;
    }
    organic_entity_.clear();
    food_generator_.clear();
}

std::list<CircularCollider*> Environment::getIsColliding(CircularCollider* CC)
{
    std::list<CircularCollider*> colliders;
    for (const auto& Ob : env_list_obstacles_) {
        if(Ob != nullptr) {
            if (Ob->isColliding(CircularCollider(CC->getPosition(),CC->getRadius()))) {
                colliders.push_back(Ob);
            }
        }
    }
    return colliders;
}

double  Environment::envSensorActivationIntensityCumulated(Sensor* sen)
{
    double cumulatedIntensity(0.0);
    for (const auto& wav : env_list_waves_) {
        if ( wav->waveIsPointTouching(sen->getPosition())) {
            cumulatedIntensity += wav->waveGetWaveIntensity() ;
        }
    }
    return cumulatedIntensity;
}

unsigned int Environment::countGerbils() const
{
    return std::count_if(organic_entity_.begin(), organic_entity_.end(),
                         [](OrganicEntity* o) { return o->isGerbil(); });
}

unsigned int Environment::countScorpions() const
{
    return std::count_if(organic_entity_.begin(), organic_entity_.end(),
                         [](OrganicEntity* o) { return o->isScorpion(); });
}

unsigned int Environment::countFood() const
{
    return std::count_if(organic_entity_.begin(), organic_entity_.end(),
                         [](OrganicEntity* o) { return o->isFood(); });
}

unsigned int Environment::countRocks() const
{
    return env_list_rocks_.size();
}

std::unordered_map<std::string,double> Environment::fetchData(std:: string const& identifier) const
{
    std::unordered_map<std::string,double> data;

    if (identifier == s::GENERAL) {

        data[s::GERBILS] = double(countGerbils());
        data[s::SCORPIONS] = double(countScorpions());
        data[s::FOOD] = double(countFood());
        data[s::ROCKS] = double(countRocks());

    } else if (identifier == s::WAVES) {
        data[s::WAVES]= env_list_waves_.size();
    }
    return data;

}

void Environment::popGenerator()
{
    if (!food_generator_.empty()) {
        food_generator_.pop_back();
    }
}


