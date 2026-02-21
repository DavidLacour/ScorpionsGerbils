#pragma once
#include "../Utility/Vec2d.hpp"
#include  <SFML/Graphics.hpp>
#include "../Interface/Drawable.hpp"

class CircularCollider : public Drawable
{
public:

    /*!
    * @brief Create a CircularCollider
    *
    * @param position Initial position
    * @param radius Must be positive
    */
    CircularCollider(const Vec2d&, const double&);

    const Vec2d& getPosition() const;
    const double& getRadius() const;

    CircularCollider(const CircularCollider&);
    CircularCollider& operator=(const CircularCollider&);

    /*!
    * @brief Find shortest path between two vectors in a toroidal world
    *
    * @param target Target position
    * @return Shortest direction vector
    */
    Vec2d directionTo(const Vec2d&) const;

    /*!
    * @brief Find shortest direction to another CircularCollider
    *
    * @param other Target collider
    * @return Shortest direction vector
    */
    Vec2d directionTo(const CircularCollider&) const;

    /*!
    * @brief Calculate distance to a point
    *
    * @param target Target position
    * @return Distance to the target
    */
    double distanceTo(const Vec2d&)const;

    /*!
    * @brief Calculate distance to another collider
    *
    * @param other Target collider
    * @return Distance to the other collider
    */
    double distanceTo(const CircularCollider&) const;

    /*!
    * @brief Move by a vector in a toroidal world with clamping
    *
    * @param displacement Vector to add to current position
    */
    void move(const Vec2d&);

    /*!
    * @brief Operator for move
    */
    CircularCollider& operator+=( const Vec2d& dx);

    /*!
    * @brief Grow baby gerbils to adult size
    */
    void grow();
    bool isCircularColliderInside( const CircularCollider& ) const;
    bool isColliding( const CircularCollider&)const;
    bool isPointInside(const Vec2d&) const;
    void setPosition(const Vec2d&);

    virtual ~CircularCollider() {}
    virtual void draw(sf::RenderTarget& target) const override ;
protected:
    void setRadius(const double&);

private:
    Vec2d v_;
    double r_;
};


/*!
 * @brief Wrap position to stay within the toroidal world boundaries
 */
Vec2d clamping(const Vec2d& v);

bool  operator>( CircularCollider c1,const CircularCollider& c2);
bool operator|( CircularCollider c1 ,const CircularCollider& c2 );
bool operator>( CircularCollider c ,const Vec2d& v);
std::ostream& operator<<(std::ostream& s , CircularCollider const& c);
