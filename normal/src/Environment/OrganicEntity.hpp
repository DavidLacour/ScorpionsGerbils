#pragma once

#include "../Interface/Updatable.hpp"
#include "../Obstacle/CircularCollider.hpp"

#include <list>

class Animal;
class Scorpion;
class Food;
class Gerbil;

/**
 * @class OrganicEntity
 * @brief Base class for all living entities in the simulation
 * 
 * OrganicEntity serves as the foundation for all living beings in the simulation,
 * implementing common properties such as energy management, aging, and interaction
 * rules between different entity types. It extends CircularCollider for physical
 * representation and collision detection, and implements Updatable for simulation
 * lifecycle integration.
 */
class OrganicEntity : public CircularCollider, public Updatable
{
public:
    /**
     * @brief Generates a positive normal distribution value
     * @param mean The mean value of the distribution
     * @param variance The variance value of the distribution
     * @return A positive value from the normal distribution (minimum 10)
     */
    double positiveNormal(double mean, double variance);
    
    /**
     * @brief Generates a positive normal distribution value with default variance
     * @param mean The mean value of the distribution
     * @return A positive value from the normal distribution (minimum 10)
     */
    double positiveNormal(double mean);
    
    /**
     * @brief Creates an OrganicEntity with default age limit
     * @param position Initial position of the entity
     * @param size Radius of the entity
     * @param energy Initial energy level
     */
    OrganicEntity(const Vec2d& position, const double& size, const double& energy);

    /**
     * @brief Creates an OrganicEntity with custom age limit
     * @param position Initial position of the entity
     * @param size Radius of the entity
     * @param energy Initial energy level
     * @param ageLimit Maximum age the entity can reach
     */
    OrganicEntity(const Vec2d& position, const double& size, const double& energy, const sf::Time& ageLimit);

    /**
     * @brief Copy constructor for OrganicEntity
     * @param other The entity to copy
     */
    OrganicEntity(const OrganicEntity& other);

    /**
     * @brief Virtual destructor
     */
    virtual ~OrganicEntity() { }

    /**
     * @brief Memory management function to forget parent entity
     */
    virtual void forgetMother() {}
    
    /**
     * @brief Memory management function to forget child entity
     * @param child Pointer to child entity to forget
     */
    virtual void forgetChild(OrganicEntity* child) {}
    
    /**
     * @brief Memory management function for general cleanup
     */
    virtual void forgetAll() {}

    /**
     * @brief Clears any reference to a dying entity
     * @param entity Pointer to entity being removed from the simulation
     */
    virtual void forgetEntity(OrganicEntity* entity) {}

    /**
     * @brief Sets the energy level of the entity
     * @param energy New energy value
     */
    void setEnergy(const double& energy);
    
    /**
     * @brief Updates the entity state based on elapsed time
     * @param dt Time elapsed since last update
     */
    virtual void update(sf::Time dt) = 0;
    
    /**
     * @brief Renders the entity to the target window
     * @param target The render target to draw on
     */
    virtual void draw(sf::RenderTarget& target) const = 0;

    /**
     * @brief Gets the current energy level
     * @return Current energy as a constant reference
     */
    const double& getEnergy() const;

    /**
     * @brief Gets the current age of the entity
     * @return Current age as a constant reference
     */
    const sf::Time& getAge() const;
    
    /**
     * @brief Gets the maximum age limit of the entity
     * @return Age limit as a constant reference
     */
    const sf::Time& getAgeLimit() const;

    // Interaction rules between entities

    /**
     * @brief Determines if this entity can mate with another entity
     * @param other Pointer to another entity
     * @return true if mating is possible, false otherwise
     */
    virtual bool matable(OrganicEntity const* other) const = 0;
    
    /**
     * @brief Determines if this entity can mate with a Scorpion
     * @param scorpion Pointer to a Scorpion entity
     * @return true if mating is possible, false otherwise
     */
    virtual bool canMate(Scorpion const* scorpion) const = 0;
    
    /**
     * @brief Determines if this entity can mate with a Gerbil
     * @param gerbil Pointer to a Gerbil entity
     * @return true if mating is possible, false otherwise
     */
    virtual bool canMate(Gerbil const* gerbil) const = 0;
    
    /**
     * @brief Determines if this entity can mate with Food
     * @param food Pointer to a Food entity
     * @return true if mating is possible, false otherwise
     */
    virtual bool canMate(Food const* food) const = 0;

    /**
     * @brief Determines if this entity can eat another entity
     * @param entity Pointer to another entity
     * @return true if this entity can eat the other, false otherwise
     */
    virtual bool eatable(OrganicEntity const* entity) const = 0;
    
    /**
     * @brief Determines if this entity can be eaten by a Scorpion
     * @param scorpion Pointer to a Scorpion entity
     * @return true if this entity can be eaten by Scorpion, false otherwise
     */
    virtual bool eatableBy(Scorpion const* scorpion) const = 0;
    
    /**
     * @brief Determines if this entity can be eaten by a Gerbil
     * @param gerbil Pointer to a Gerbil entity
     * @return true if this entity can be eaten by Gerbil, false otherwise
     */
    virtual bool eatableBy(Gerbil const* gerbil) const = 0;
    
    /**
     * @brief Determines if this entity can be eaten by Food
     * @param food Pointer to a Food entity
     * @return true if this entity can be eaten by Food, false otherwise
     */
    virtual bool eatableBy(Food const* food) const = 0;
    
    /**
     * @brief Handles interaction when meeting another entity
     * @param other Pointer to the entity encountered
     */
    virtual void meet(OrganicEntity* other) {}
    
    /**
     * @brief Specialized handling for meeting an Animal
     * @param animal Pointer to the Animal encountered
     */
    virtual void meetThis(Animal* animal) {}

    /**
     * @brief Checks if this entity is a Gerbil
     * @return true if entity is a Gerbil, false otherwise
     */
    virtual bool isGerbil() const = 0;
    
    /**
     * @brief Checks if this entity is a Scorpion
     * @return true if entity is a Scorpion, false otherwise
     */
    virtual bool isScorpion() const = 0;
    
    /**
     * @brief Checks if this entity is Food
     * @return true if entity is Food, false otherwise
     */
    virtual bool isFood() const = 0;

protected:
    /**
     * @brief Handles reproduction to create new entities
     */
    virtual void giveBirth() {}
    
    /**
     * @brief Specialized handling for reproduction
     */
    virtual void giveBirthThis() {}
    
    /**
     * @brief Updates entity energy based on time and activity
     * @param dt Time elapsed since last update
     */
    void updateEnergy(sf::Time dt);

    /**
     * @brief Adds a child entity to this entity's memory
     * @param child Pointer to the child entity
     */
    virtual void addKidMemory(OrganicEntity* child) {}

    /**
     * @brief Current energy level of the entity
     */
    double energy_;

    /**
     * @brief Current age of the entity
     */
    sf::Time age_;
    
    /**
     * @brief Maximum age the entity can reach
     */
    sf::Time age_limit_;
    
    /**
     * @brief Base rate of energy consumption per time unit
     */
    double base_energy_consumption_;
};