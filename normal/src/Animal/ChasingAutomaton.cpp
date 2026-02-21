#include <list>
#include "../Obstacle/CircularCollider.hpp"

#include "../Animal/Animal.hpp"
#include  <SFML/Graphics.hpp>
#include "../Utility/Vec2d.hpp"

#include "../Application.hpp"
#include "../Utility/Utility.hpp"
#include "ChasingAutomaton.hpp"
#include "../Utility/Constants.hpp"

const double& ChasingAutomaton::getStandardMaxSpeed() const
{
    return CHASING_AUTOMATON_MAX_SPEED;
}

const double& ChasingAutomaton::getMass() const
{
    return CHASING_AUTOMATON_MASS;
}

void ChasingAutomaton::setTargetPosition(const Vec2d& v)
{
    target_= v;
}

Vec2d ChasingAutomaton::getSpeedVector() const
{
    return direction_*speed_;
}

void ChasingAutomaton::update(sf::Time dt)
{
    move(dt.asSeconds());
}

void ChasingAutomaton::move(const double& deltaT)
{
    Vec2d acceleration = force(target_)/getMass();
    Vec2d current_velocity = speed_*direction_;
    Vec2d new_velocity = current_velocity+acceleration*deltaT;
    direction_ = new_velocity.normalised();
    if (new_velocity.length() > getStandardMaxSpeed()) new_velocity = direction_*getStandardMaxSpeed();
    setPosition(getPosition()+new_velocity*deltaT);
    speed_ = new_velocity.length();
}

Vec2d ChasingAutomaton::force(const Vec2d& target) const
{
    double deceleration(ANIMAL_DECELERATION);
    double speed;
    if(directionTo(target_).length()/(deceleration) <= getStandardMaxSpeed()) {
        speed = directionTo(target).length()/(deceleration);
    }
    else {
        speed = getStandardMaxSpeed();
    }

    Vec2d desired_velocity = directionTo(target)/directionTo(target).length()*speed;
    return desired_velocity-speed_*direction_;
}

void ChasingAutomaton::draw(sf::RenderTarget& targetWindow)
{
    sf::Texture& texture = getAppTexture(GHOST_TEXTURE);
    auto image_to_draw(buildSprite(getPosition(),
                                   getRadius()*2,
                                   texture));

    auto targetCircle(buildCircle(target_, 5, sf::Color(255, 0, 0)));

    targetWindow.draw(targetCircle);
    targetWindow.draw(image_to_draw);
}