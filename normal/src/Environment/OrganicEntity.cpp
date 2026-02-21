#include "OrganicEntity.hpp"
#include "../Application.hpp"
#include "../Random/Normal.hpp"

double OrganicEntity::positiveNormal(double value, double variance)
{
    double res (normal(value,variance));
    if  ( res <= 10) {
        return 10;
    } else {
        return res;
    }
}

double  OrganicEntity::positiveNormal(double value)
{
    return positiveNormal(value,value*value);
}

OrganicEntity::OrganicEntity( const Vec2d& position, const double& size , const double& energy) : CircularCollider(position,
            positiveNormal(size,size/15*size/15)
                                                                                                                         ), energy_(energy),  age_(sf::Time::Zero),
    age_limit_(sf::seconds(10000)), base_energy_consumption_(getAppConfig().animal_base_energy_consumption) {}

OrganicEntity::OrganicEntity( const OrganicEntity& OE ) : OrganicEntity( OE.getPosition(),OE.getRadius(),OE.energy_) {}

OrganicEntity::OrganicEntity( const Vec2d& position, const double& size , const double& energy, const sf::Time& ageLimit)
    : CircularCollider(position, size), energy_(energy),  age_(sf::Time::Zero), age_limit_(ageLimit), base_energy_consumption_(getAppConfig().animal_base_energy_consumption)
{
}

const double& OrganicEntity::getEnergy() const
{
    return energy_;
}

void OrganicEntity::update(sf::Time dt)
{
    age_ += dt;
}

const sf::Time& OrganicEntity::getAge() const
{
    return age_;
}
const sf::Time& OrganicEntity::getAgeLimit() const
{
    return age_limit_;
}

void OrganicEntity::setEnergy(const double& energy)
{
    energy_= energy ;
}
