#pragma once
#include "../Utility/Vec2d.hpp"
#include "OrganicEntity.hpp"

class Scorpion;
class Gerbil;

/**
 * @class Food
 * @brief Represents a food entity in the simulation environment
 * 
 * The Food class is a type of OrganicEntity that can be consumed by certain
 * entities (like Gerbil) but cannot consume other entities or mate.
 * It serves as a basic resource in the ecosystem.
 */
class Food : public OrganicEntity
{
public:
    /**
     * @brief Constructs a Food entity at the specified position
     * @param position The 2D position where the Food will be created
     */
    Food(const Vec2d& position);
    
    /**
     * @brief Updates the Food entity state over time
     * @param deltaTime Time elapsed since last update
     */
    virtual void update(sf::Time deltaTime) override;
    
    /**
     * @brief Renders the Food entity to the target window
     * @param targetWindow The render target to draw the Food on
     */
    virtual void draw(sf::RenderTarget& targetWindow) const override;
    
    /**
     * @brief Virtual destructor
     */
    ~Food() {}

    /**
     * @brief Determines if the Food is eatable by a Gerbil
     * @param gerbil Pointer to the Gerbil entity
     * @return true if the Food can be eaten by Gerbil, false otherwise
     */
    bool eatableBy(Gerbil const* gerbil) const override;
    
    /**
     * @brief Determines if the Food is eatable by another Food
     * @param food Pointer to the Food entity
     * @return Always false as Food cannot be eaten by other Food
     */
    bool eatableBy(Food const* food) const override;
    
    /**
     * @brief Determines if the Food is eatable by a Scorpion
     * @param scorpion Pointer to the Scorpion entity
     * @return Always false as Food cannot be eaten by Scorpion
     */
    bool eatableBy(Scorpion const* scorpion) const override;
    
    /**
     * @brief Determines if an entity can be eaten by this Food
     * @param entity Pointer to an OrganicEntity
     * @return Always false as Food does not eat other entities
     */
    bool eatable(OrganicEntity const* entity) const override;

    /**
     * @brief Determines if the Food can mate with a Gerbil
     * @param gerbil Pointer to the Gerbil entity
     * @return Always false as Food cannot mate
     */
    bool canMate(Gerbil const* gerbil) const override;
    
    /**
     * @brief Determines if the Food can mate with another Food
     * @param food Pointer to the Food entity
     * @return Always false as Food cannot mate
     */
    bool canMate(Food const* food) const override;
    
    /**
     * @brief Determines if the Food can mate with a Scorpion
     * @param scorpion Pointer to the Scorpion entity
     * @return Always false as Food cannot mate
     */
    bool canMate(Scorpion const* scorpion) const override;
    
    /**
     * @brief Determines if an entity can mate with this Food
     * @param organicentity Pointer to an OrganicEntity
     * @return Always false as Food cannot mate
     */
    bool matable(OrganicEntity const* organicentity) const override;

    /**
     * @brief Checks if this entity is a Gerbil
     * @return Always false
     */
    bool isGerbil() const override
    {
        return false;
    }
    
    /**
     * @brief Checks if this entity is a Scorpion
     * @return Always false
     */
    bool isScorpion() const override
    {
        return false;
    }
    
    /**
     * @brief Checks if this entity is Food
     * @return Always true
     */
    bool isFood() const override
    {
        return true;
    }
};