#include "Gerbil.hpp"
#include "../Application.hpp"
#include "../Utility/Vec2d.hpp"

#include "../Random/Uniform.hpp"
#include "Animal.hpp"
Gerbil::Gerbil(const Vec2d& position, const double& energy,
               const bool& isFemale) :
    Animal(position,getAppConfig().gerbil_size, energy, isFemale
    , getAppConfig().gerbil_longevity
    , getAppConfig().gerbil_energy_loss_factor
    , getAppConfig().gerbil_gestation_time)
{}
Gerbil::Gerbil(const Vec2d& position) : Animal(position,getAppConfig().gerbil_size,getAppConfig().gerbil_energy_initial,uniform(0, 1) == 0,
            getAppConfig().gerbil_longevity,
            getAppConfig().gerbil_energy_loss_factor, getAppConfig().gerbil_gestation_time )   {}


Gerbil::Gerbil(const Vec2d& position,const Vec2d& direction) : Animal(position
    ,getAppConfig().gerbil_size,getAppConfig().gerbil_energy_initial
    ,uniform(0, 1) == 0,
            getAppConfig().gerbil_longevity,
            getAppConfig().gerbil_energy_loss_factor, getAppConfig().gerbil_gestation_time,direction)   {}

Gerbil::Gerbil(const Vec2d& position,const Vec2d& direction, OrganicEntity* mum) :
    Animal(position,
           getAppConfig().gerbil_size,
           getAppConfig().gerbil_energy_initial,
           uniform(0, 1) == 0,
           getAppConfig().gerbil_longevity,
           getAppConfig().gerbil_energy_loss_factor,
           getAppConfig().gerbil_gestation_time,direction, mum)
{
}

Gerbil::Gerbil(const Vec2d& position, const double& energy,
               const bool& isFemale, const sf::Time& ageLimit =(sf::Time(getAppConfig().gerbil_longevity)
                                                                   )) :
    Animal(position,getAppConfig().gerbil_size, energy, isFemale, ageLimit)
{}

const double& Gerbil::getStandardMaxSpeed() const
{
    return  getAppConfig().gerbil_max_speed;
}

const double& Gerbil::getMass() const
{
    return  getAppConfig().gerbil_mass;
}

const double& Gerbil::getViewRange() const
{
    return getAppConfig().gerbil_view_range;
}

const double& Gerbil::getViewDistance()const
{
    return  getAppConfig().gerbil_view_distance;
}

const double& Gerbil::getRandomWalkRadius() const
{
    return getAppConfig().gerbil_random_walk_radius;
}


const double& Gerbil::getRandomWalkDistance() const
{
    return getAppConfig().gerbil_random_walk_distance;
}

const double& Gerbil::getRandomWalkJitter() const
{
    return getAppConfig().gerbil_random_walk_jitter;
}

const sf::Texture& Gerbil::getTexture() const
{
    return getAppTexture(isFemale() ? getAppConfig().gerbil_texture_female
                                    : getAppConfig().gerbil_texture_male);
}

bool Gerbil::eatable(OrganicEntity const* entity) const
{

    return entity->eatableBy(this);
}

bool Gerbil::eatableBy(Gerbil const*  ) const
{
    return false;
}
bool Gerbil::eatableBy(Food const*  ) const
{
    return false;
}
bool Gerbil::eatableBy(Scorpion const*  ) const
{
    return true;
}

bool Gerbil::matable(OrganicEntity const* entity   ) const
{

    return entity->canMate(this);
}

bool Gerbil::canMate(Gerbil const* G) const
{
    double minEnergy = isFemale() ? getAppConfig().gerbil_energy_min_mating_female
                                  : getAppConfig().gerbil_energy_min_mating_male;
    return getAge().asSeconds() >= getAppConfig().gerbil_min_age_mating
        and getEnergy() >= minEnergy
        and !isPregnant()
        and isFemale() != G->isFemale();
}

bool Gerbil::canMate(Food const* ) const
{
    return false;
}
bool Gerbil::canMate(Scorpion const*  ) const
{
    return false;
}

void Gerbil::giveBirthThis()
{
    for (int i (0); i < getBabies(); ++i ) {
        OrganicEntity* mum(this);
        Gerbil* baby(new Gerbil(getPosition()-getDirection()*getRadius()*2.2, getDirection(), mum));
        getAppEnv().addEntity(baby);
        organic_entity_kids_.push_back(baby);
    }
    setBabies(0);
}


