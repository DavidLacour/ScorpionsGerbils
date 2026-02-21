#include "Scorpion.hpp"
#include "../Application.hpp"
#include "../Utility/Vec2d.hpp"
#include "../Random/Uniform.hpp"
Scorpion::Scorpion(const Vec2d& position, const double& energy,
                   const bool& isFemale) :
    Animal(position,getAppConfig().scorpion_size, energy, isFemale, getAppConfig().scorpion_longevity, getAppConfig().scorpion_energy_loss_factor, getAppConfig().scorpion_gestation_time )
{}
Scorpion::Scorpion(const Vec2d& position) : Animal(position,getAppConfig().scorpion_size,getAppConfig().scorpion_energy_initial,uniform(0, 1) == 0,getAppConfig().scorpion_longevity,
            getAppConfig().scorpion_energy_loss_factor,
            getAppConfig().scorpion_gestation_time)   {}

Scorpion::Scorpion(const Vec2d& position, const double& energy,
                   const bool& isFemale, const sf::Time& ageLimit= sf::Time(getAppConfig().scorpion_longevity)) :
    Animal(position,getAppConfig().scorpion_size, energy, isFemale, ageLimit)
{}

Scorpion::Scorpion(const Vec2d& position, const Vec2d& direction) :
    Animal(position, getAppConfig().scorpion_size, getAppConfig().scorpion_energy_initial,
           uniform(0, 1) == 0, getAppConfig().scorpion_longevity,
           getAppConfig().scorpion_energy_loss_factor, getAppConfig().scorpion_gestation_time, direction)
{}

Scorpion::Scorpion(const Vec2d& position, const Vec2d& direction, OrganicEntity* mum) :
    Animal(position, getAppConfig().scorpion_size, getAppConfig().scorpion_energy_initial,
           uniform(0, 1) == 0, getAppConfig().scorpion_longevity,
           getAppConfig().scorpion_energy_loss_factor, getAppConfig().scorpion_gestation_time, direction, mum)
{}

const double& Scorpion::getStandardMaxSpeed() const
{

    return  getAppConfig().scorpion_max_speed;
}

const double& Scorpion::getMass() const
{
    return  getAppConfig().scorpion_mass;
}

const double& Scorpion::getViewRange() const
{
    return getAppConfig().scorpion_view_range;
}

const double& Scorpion::getViewDistance()const
{
    return  getAppConfig().scorpion_view_distance;
}

const double& Scorpion::getRandomWalkRadius() const
{
    return getAppConfig().scorpion_random_walk_radius;
}

const double& Scorpion::getRandomWalkDistance() const
{
    return getAppConfig().scorpion_random_walk_distance;
}

const double& Scorpion::getRandomWalkJitter() const
{
    return getAppConfig().scorpion_random_walk_jitter;
}

const sf::Texture& Scorpion::getTexture() const
{
    return getAppTexture(getAppConfig().scorpion_texture);
}

bool Scorpion::eatable(OrganicEntity const* entity   ) const
{

    return entity->eatableBy(this);
}

bool Scorpion::eatableBy(Gerbil const* ) const
{
    return false;
}
bool Scorpion::eatableBy(Food const* ) const
{
    return false;
}
bool Scorpion::eatableBy(Scorpion const*  ) const
{
    return false;
}

bool Scorpion::matable(OrganicEntity const* entity   ) const
{

    return entity->canMate(this);
}

bool Scorpion::canMate(Gerbil const* ) const
{
    return false;
}
bool Scorpion::canMate(Food const* ) const
{
    return false;
}
bool Scorpion::canMate(Scorpion const* S ) const
{
    double minEnergy = isFemale() ? getAppConfig().scorpion_energy_min_mating_female
                                  : getAppConfig().scorpion_energy_min_mating_male;
    return getAge().asSeconds() >= getAppConfig().scorpion_min_age_mating
        and getEnergy() >= minEnergy
        and !isPregnant()
        and isFemale() != S->isFemale();
}

void Scorpion::giveBirthThis()
{
    for (int i(0); i < getBabies(); ++i) {
        OrganicEntity* mum(this);
        Scorpion* baby(new Scorpion(getPosition() - getDirection() * getRadius() * 1.2, getDirection(), mum));
        getAppEnv().addEntity(baby);
        organic_entity_kids_.push_back(baby);
    }
    setBabies(0);
}
