#pragma once

/**
 * @class FoodGenerator
 * @brief Responsible for periodically spawning Food entities in the simulation
 * 
 * The FoodGenerator creates new Food entities at regular intervals based on
 * the configured time delta. Food is generated following a normal distribution
 * centered in the simulation world with a standard deviation of 1/4 of the world size.
 * This class serves as an essential resource provider in the ecosystem simulation.
 */
class FoodGenerator
{
public:
    /**
     * @brief Default constructor for the FoodGenerator
     */
    FoodGenerator() {}
    
    /**
     * @brief Updates the food generation logic based on elapsed time
     * 
     * Increments an internal counter and spawns a new Food entity
     * when the counter reaches the configured food generation delta.
     * Food is spawned according to a normal distribution centered
     * in the simulation world.
     * 
     * @param dt Time elapsed since the last update
     */
    void update(sf::Time dt);
    
    /**
     * @brief Virtual destructor
     */
    ~FoodGenerator() {}
    
private:
    /**
     * @brief Timer that tracks elapsed time since last food generation
     * 
     * This counter is reset to zero each time a new Food entity is spawned.
     */
    sf::Time timer_;
};