#pragma once
#include "Animal.hpp"
#include "../Utility/Vec2d.hpp"

class Food;
class Gerbil;

/**
 * @class Scorpion
 * @brief A predator animal that hunts gerbils in the simulation
 * 
 * The Scorpion class extends the Animal class and implements specific behaviors
 * for scorpions, including movement characteristics, predatory interactions,
 * reproduction capabilities, and visual representation.
 */
class Scorpion : public Animal
{
public:
    /**
     * @brief Constructs a Scorpion with specified position and energy
     * 
     * @param position Initial position of the scorpion
     * @param energy Initial energy level
     */
    Scorpion(const Vec2d& position, const double& energy);
    
    /**
     * @brief Constructs a Scorpion with specified position, energy, and gender
     * 
     * @param position Initial position of the scorpion
     * @param energy Initial energy level
     * @param isFemale Gender flag (true for female, false for male)
     */
    Scorpion(const Vec2d& position, const double& energy, const bool& isFemale);
    
    /**
     * @brief Constructs a Scorpion with specified position, energy, gender, and age limit
     * 
     * @param position Initial position of the scorpion
     * @param energy Initial energy level
     * @param isFemale Gender flag (true for female, false for male)
     * @param ageLimit Maximum age the scorpion can reach
     */
    Scorpion(const Vec2d& position, const double& energy, const bool& isFemale, const sf::Time& ageLimit);
    
    /**
     * @brief Constructs a Scorpion at the specified position with random gender
     * 
     * @param position Initial position of the scorpion
     */
    Scorpion(const Vec2d& position);
    
    /**
     * @brief Constructs a Scorpion with specified position and direction
     * 
     * @param position Initial position of the scorpion
     * @param direction Initial direction the scorpion is facing
     */
    Scorpion(const Vec2d& position, const Vec2d& direction);

    /**
     * @brief Constructs a baby Scorpion with a parent
     *
     * @param position Initial position of the baby scorpion
     * @param direction Initial direction the baby is facing
     * @param parent Pointer to the parent OrganicEntity
     */
    Scorpion(const Vec2d& position, const Vec2d& direction, OrganicEntity* parent);

    /**
     * @brief Handles the birth process for this scorpion
     * 
     * Creates new baby scorpions and adds them to the environment
     */
    void giveBirthThis() override;

    /**
     * @brief Destructor for Scorpion
     */
    ~Scorpion() {}

    // Perception and movement characteristics
    /**
     * @brief Gets the viewing angle range for this scorpion
     * 
     * @return View range in radians
     */
    virtual const double& getViewRange() const override;
    
    /**
     * @brief Gets the maximum viewing distance for this scorpion
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
     * @brief Gets the maximum speed this scorpion can reach
     * 
     * @return Maximum speed
     */
    virtual const double& getStandardMaxSpeed() const override;
    
    /**
     * @brief Gets the mass of this scorpion for force calculations
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
    
    /**
     * @brief Gets the appropriate texture for rendering this scorpion
     * 
     * @return The texture to use for the scorpion
     */
    virtual const sf::Texture& getTexture() const override;

    // Predation interactions
    /**
     * @brief Determines if this scorpion can be eaten by a gerbil
     * 
     * @param gerbil The potential predator
     * @return true if eatable, false otherwise
     */
    bool eatableBy(Gerbil const* gerbil) const override;
    
    /**
     * @brief Determines if this scorpion can be eaten by food
     * 
     * @param food The potential predator
     * @return true if eatable, false otherwise
     */
    bool eatableBy(Food const* food) const override;
    
    /**
     * @brief Determines if this scorpion can be eaten by another scorpion
     * 
     * @param scorpion The potential predator
     * @return true if eatable, false otherwise
     */
    bool eatableBy(Scorpion const* scorpion) const override;
    
    /**
     * @brief Determines if an entity can be eaten by this scorpion
     * 
     * @param entity The potential prey
     * @return true if the entity is eatable, false otherwise
     */
    bool eatable(OrganicEntity const* entity) const override;

    // Reproduction behaviors
    /**
     * @brief Determines if this scorpion can mate with a gerbil
     * 
     * @param gerbil The potential mate
     * @return true if mating is possible, false otherwise
     */
    bool canMate(Gerbil const* gerbil) const override;
    
    /**
     * @brief Determines if this scorpion can mate with food
     * 
     * @param food The potential mate
     * @return true if mating is possible, false otherwise
     */
    bool canMate(Food const* food) const override;
    
    /**
     * @brief Determines if this scorpion can mate with another scorpion
     * 
     * @param scorpion The potential mate
     * @return true if mating is possible, false otherwise
     */
    bool canMate(Scorpion const* scorpion) const override;
    
    /**
     * @brief Determines if an entity can mate with this scorpion
     * 
     * @param entity The potential mate
     * @return true if mating is possible, false otherwise
     */
    bool matable(OrganicEntity const* entity) const override;

    // Entity type identification
    /**
     * @brief Checks if this entity is a Gerbil
     * 
     * @return false, as this is not a Gerbil
     */
    bool isGerbil() const override
    {
        return false;
    }
    
    /**
     * @brief Checks if this entity is a Scorpion
     * 
     * @return true, as this is a Scorpion
     */
    bool isScorpion() const override
    {
        return true;
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
};