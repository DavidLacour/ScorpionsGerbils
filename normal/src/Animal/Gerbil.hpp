#pragma once
#include "Animal.hpp"
#include "../Utility/Vec2d.hpp"

class Scorpion;
class Food;

/**
 * @class Gerbil
 * @brief A specific type of Animal that represents a gerbil in the simulation
 * 
 * The Gerbil class extends the Animal class and implements specific behaviors
 * for gerbils, including movement characteristics, interaction with other entities,
 * reproduction capabilities, and visual representation.
 */
class Gerbil : public Animal
{

public:
    /**
     * @brief Constructs a Gerbil with specified position, energy, and gender
     * 
     * @param position Initial position of the gerbil
     * @param energy Initial energy level
     * @param isFemale Gender flag (true for female, false for male)
     */
    Gerbil(const Vec2d& position, const double& energy, const bool& isFemale);
    
    /**
     * @brief Constructs a Gerbil at the specified position with random gender
     * 
     * @param position Initial position of the gerbil
     */
    Gerbil(const Vec2d& position);
    
    /**
     * @brief Constructs a Gerbil with specified position, energy, gender, and age limit
     * 
     * @param position Initial position of the gerbil
     * @param energy Initial energy level
     * @param isFemale Gender flag (true for female, false for male)
     * @param ageLimit Maximum age the gerbil can reach
     */
    Gerbil(const Vec2d& position, const double& energy, const bool& isFemale, const sf::Time& ageLimit);

    /**
     * @brief Constructs a baby Gerbil with specified position and direction
     * 
     * @param position Initial position of the baby gerbil
     * @param direction Initial direction the baby is facing
     */
    Gerbil(const Vec2d& position, const Vec2d& direction);
    
    /**
     * @brief Constructs a baby Gerbil with a parent
     * 
     * @param position Initial position of the baby gerbil
     * @param direction Initial direction the baby is facing
     * @param parent Pointer to the parent OrganicEntity
     */
    Gerbil(const Vec2d& position, const Vec2d& direction, OrganicEntity* parent);

    /**
     * @brief Checks if this entity is a Gerbil
     * 
     * @return true, as this is a Gerbil
     */
    bool isGerbil() const override
    {
        return true;
    }
    
    /**
     * @brief Checks if this entity is a Scorpion
     * 
     * @return false, as this is not a Scorpion
     */
    bool isScorpion() const override
    {
        return false;
    }
    
    /**
     * @brief Checks if this entity is Food
     * 
     * @return false, as this is not Food
     */
    bool isFood() const override
    {
        return false;
    }

    // Perception and movement characteristics
    /**
     * @brief Gets the viewing angle range for this gerbil
     * 
     * @return View range in radians
     */
    virtual const double& getViewRange() const override;
    
    /**
     * @brief Gets the maximum viewing distance for this gerbil
     * 
     * @return View distance
     */
    virtual const double& getViewDistance() const override;
    
    /**
     * @brief Gets the radius used for random walk behavior
     * 
     * @return Random walk radius
     */
    virtual const double& getRandomWalkRadius() const override;
    
    /**
     * @brief Gets the distance parameter used for random walk behavior
     * 
     * @return Random walk distance
     */
    virtual const double& getRandomWalkDistance() const override;
    
    /**
     * @brief Gets the maximum speed this gerbil can reach
     * 
     * @return Maximum speed
     */
    virtual const double& getStandardMaxSpeed() const override;
    
    /**
     * @brief Gets the mass of this gerbil for force calculations
     * 
     * @return Mass value
     */
    virtual const double& getMass() const override;
    
    /**
     * @brief Gets the jitter parameter used for random walk behavior
     * 
     * @return Random walk jitter value
     */
    virtual const double& getRandomWalkJitter() const override;

    // Interaction with other entities
    /**
     * @brief Determines if this gerbil can be eaten by another gerbil
     * 
     * @param gerbil The potential predator
     * @return true if eatable, false otherwise
     */
    bool eatableBy(Gerbil const* gerbil) const override;
    
    /**
     * @brief Determines if this gerbil can be eaten by food
     * 
     * @param food The potential predator
     * @return true if eatable, false otherwise
     */
    bool eatableBy(Food const* food) const override;
    
    /**
     * @brief Determines if this gerbil can be eaten by a scorpion
     * 
     * @param scorpion The potential predator
     * @return true if eatable, false otherwise
     */
    bool eatableBy(Scorpion const* scorpion) const override;
    
    /**
     * @brief Determines if an entity can be eaten by this gerbil
     * 
     * @param entity The potential prey
     * @return true if the entity is eatable, false otherwise
     */
    bool eatable(OrganicEntity const* entity) const override;

    // Reproduction behaviors
    /**
     * @brief Determines if this gerbil can mate with another gerbil
     * 
     * @param gerbil The potential mate
     * @return true if mating is possible, false otherwise
     */
    bool canMate(Gerbil const* gerbil) const override;
    
    /**
     * @brief Determines if this gerbil can mate with food
     * 
     * @param food The potential mate
     * @return true if mating is possible, false otherwise
     */
    bool canMate(Food const* food) const override;
    
    /**
     * @brief Determines if this gerbil can mate with a scorpion
     * 
     * @param scorpion The potential mate
     * @return true if mating is possible, false otherwise
     */
    bool canMate(Scorpion const* scorpion) const override;
    
    /**
     * @brief Determines if an entity can mate with this gerbil
     * 
     * @param entity The potential mate
     * @return true if mating is possible, false otherwise
     */
    bool matable(OrganicEntity const* entity) const override;

    /**
     * @brief Handles the birth process for this gerbil
     * 
     * Creates new baby gerbils and adds them to the environment
     */
    void giveBirthThis() override;
    
    /**
     * @brief Gets the appropriate texture for rendering this gerbil
     * 
     * @return The texture to use based on gender
     */
    virtual const sf::Texture& getTexture() const override;

    /**
     * @brief Destructor for Gerbil
     */
    ~Gerbil() {}
};