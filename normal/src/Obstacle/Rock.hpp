#pragma once
#include "CircularCollider.hpp"



class Rock : public CircularCollider
{
public:
    Rock(const Vec2d&);
    virtual void draw(sf::RenderTarget& target) const  override;
    /*!
     * @brief a beautifull looking Rock brought by Obelix of random orientation and random size
     *
     * @param Position
     *
     * return a Rock
     */
    const sf::Texture& getTexture() const;

private:
    double rock_angle_;




};

double rockMax(double d1,double d2);
