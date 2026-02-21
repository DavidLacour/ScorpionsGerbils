#include "../Utility/Vec2d.hpp"
#include "../Application.hpp"
#include "CircularCollider.hpp"
#include "../Utility/Utility.hpp"


CircularCollider::CircularCollider(Vec2d const& v, double const& r)
    :
    v_(clamping(v)),
    r_(r/2)

{
    if( r < 0 ) {
        std::cerr << "negative radius" << std::endl ;
        throw 1 ;
    }
}

const Vec2d& CircularCollider::getPosition() const
{
    return v_;
}


const double& CircularCollider:: getRadius() const
{
    return r_;
}



CircularCollider::CircularCollider(const CircularCollider& c)
    :CircularCollider(c.v_,c.r_)
{}

CircularCollider&  CircularCollider::operator=(const CircularCollider& c)
{
    v_=clamping(c.v_);
    r_=c.r_;
    return *this;
}
Vec2d CircularCollider::directionTo(const Vec2d& to1) const
{
    Vec2d to= clamping(to1);
    double min(10000);
    Vec2d vector;
    double worldSize = getAppConfig().simulation_world_size;
    auto width  = worldSize;
    auto height = worldSize;
    for( int i(-1); i<=1; ++i) {
        for (int j(-1); j<=1; ++j) {
            if (distance(v_,Vec2d(to.x+i*width,to.y+j*height)) < min) {
                min = distance(v_,Vec2d(to.x+i*width,to.y+j*height));
                vector = (Vec2d(to.x+i*width,to.y+j*height)-v_);
            }
        }

    }
    return vector;
}



Vec2d CircularCollider::directionTo( const CircularCollider& c) const
{
    return (directionTo(c.v_));
}



double CircularCollider::distanceTo(const Vec2d& to) const
{
    return directionTo(to).length();
}

double CircularCollider::distanceTo(const CircularCollider& to) const
{


    return directionTo(to.v_).length();
}


void CircularCollider::move(const Vec2d& dx)
{
    v_=clamping(v_+dx);
}

CircularCollider& CircularCollider::operator+=(const Vec2d& dx)
{
    this->move(dx);
    return *this;
}




bool	CircularCollider::isCircularColliderInside( const CircularCollider& other) const
{


    if (( r_ >= other.r_ ) and ( distanceTo(other) <= (    r_ - other.r_  ) )) return true;

    return false;
}


bool CircularCollider::isColliding( const CircularCollider& other) const
{
    if(distanceTo(other)<=(r_+other.r_)) return true;
    return false;

}


bool	CircularCollider::isPointInside(const Vec2d& v) const
{
    if (distanceTo(v)<= r_) return true;
    return false;
}


bool operator>(CircularCollider c1,const CircularCollider& c2)
{
    return c1.isCircularColliderInside( c2 ) ;
}

bool  operator>( CircularCollider c,const Vec2d& v)
{
    return c.isPointInside(v) ;
}


bool operator|( CircularCollider c1,const CircularCollider& c2 )
{
    return c1.isColliding(c2);
}



Vec2d clamping(const Vec2d& v)
{
    double worldSize = getAppConfig().simulation_world_size;
    auto width  = worldSize;
    auto height = worldSize;
    Vec2d v2;
    v2.x= v.x;
    v2.y= v.y;
    if( v.x < 0 ) v2.x += width;
    if(v.x> width) v2.x -= width;
    if(v.y>height ) v2.y -= height;
    if (v.y < 0) v2.y += height;

    return v2;
}


std::ostream& operator<<(std::ostream& s, CircularCollider const& c)
{

    s << "CircularCollider: position = <";
    s <<c.getPosition() ;
    s <<  "> radius = <";
    s << c.getRadius();
    s << ">" ;
    s << std::endl;
    return s;
}

void CircularCollider::setPosition(const Vec2d& v)
{
    v_= clamping(v);
}

void  CircularCollider::draw(sf::RenderTarget&  targetWindow) const
{
    targetWindow.draw(buildCircle(getPosition(), getRadius(), sf::Color(255, 255, 255)));


}


void CircularCollider::grow()
{
    r_=r_*3;

}

void CircularCollider::setRadius(const double& radius)
{
    r_= radius;
}


