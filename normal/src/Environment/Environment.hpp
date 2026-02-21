#pragma once
#include <list>
#include <SFML/Graphics.hpp>
#include "../Utility/Vec2d.hpp"
#include <memory>
#include "FoodGenerator.hpp"
#include "../Animal/Animal.hpp"
class Animal;
class OrganicEntity;
class WaveGerbil;
class Sensor;
#include "Wave.hpp"
#include "../Obstacle/Rock.hpp"
#include "../Obstacle/CircularCollider.hpp"
#include <map>
#include <unordered_map>

/**
 * @class Environment
 * @brief Manages the simulation environment and all entities within it
 *
 * The Environment class is responsible for tracking and updating all entities
 * in the simulation, handling collisions, managing waves, and providing
 * information about entities to other components of the simulation.
 */
class Environment
{
public:
    /**
     * @brief Default constructor for Environment
     */
    Environment() {};
    
    /**
     * @brief Copy constructor (deleted)
     * 
     * Environment cannot be copied to prevent issues with ownership of pointers
     */
    Environment(const Environment&) = delete;
    
    /**
     * @brief Assignment operator (deleted)
     * 
     * Environment cannot be assigned to prevent issues with ownership of pointers
     */
    Environment& operator=(const Environment&) = delete;
    
    /**
     * @brief Adds an organic entity to the environment
     * 
     * @param entity Pointer to the OrganicEntity to add
     */
    void addEntity(OrganicEntity* entity);
    
    /**
     * @brief Adds a food generator to the environment
     * 
     * @param generator Pointer to the FoodGenerator to add
     */
    void addGenerator(FoodGenerator* generator);
    
    /**
     * @brief Removes the most recently added food generator
     */
    void popGenerator();
    
    /**
     * @brief Adds a wave to the environment
     * 
     * @param wave Pointer to the Wave to add
     */
    void addWave(Wave* wave);
    
    /**
     * @brief Adds a rock to the environment
     * 
     * @param rock Pointer to the Rock to add
     */
    void addRock(Rock* rock);
    
    /**
     * @brief Adds an obstacle to the environment
     * 
     * @param obstacle Pointer to the CircularCollider to add as an obstacle
     */
    void addObstacle(CircularCollider* obstacle);
    
    /**
     * @brief Updates the state of all entities in the environment
     * 
     * @param dt Time elapsed since last update
     */
    void update(sf::Time dt);
    
    /**
     * @brief Draws all entities in the environment
     * 
     * @param targetWindow The render target to draw to
     */
    void draw(sf::RenderTarget& targetWindow);
    
    /**
     * @brief Cleans up all entities and clears all lists
     */
    void clean();
    
    /**
     * @brief Gets all entities that are within sight of a specific animal
     * 
     * @param animal The animal to check sight for
     * @return List of pointers to OrganicEntity objects in sight
     */
    std::list<OrganicEntity*> getEntitiesInSightForAnimal(Animal* animal) const;
    
    /**
     * @brief Gets all obstacles that collide with a specific collider
     * 
     * @param collider The collider to check collisions with
     * @return List of pointers to CircularCollider objects that are colliding
     */
    std::list<CircularCollider*> getIsColliding(CircularCollider* collider);
    
    /**
     * @brief Marks an entity for death
     * 
     * @param entity The entity to mark for death
     */
    void markForDeath(OrganicEntity* entity);
    
    /**
     * @brief Resets the environment to its initial state
     */
    void reset();
    
    /**
     * @brief Calculates the cumulative wave intensity at a sensor's position
     * 
     * @param sensor The sensor to check
     * @return The cumulative wave intensity at the sensor's position
     */
    double envSensorActivationIntensityCumulated(Sensor* sensor);
    
    /**
     * @brief Counts the number of gerbils in the environment
     * 
     * @return The number of gerbils
     */
    unsigned int countGerbils() const;
    
    /**
     * @brief Counts the number of scorpions in the environment
     * 
     * @return The number of scorpions
     */
    unsigned int countScorpions() const;
    
    /**
     * @brief Counts the number of food entities in the environment
     *
     * @return The number of food entities
     */
    unsigned int countFood() const;

    /**
     * @brief Counts the number of rocks in the environment
     *
     * @return The number of rocks
     */
    unsigned int countRocks() const;
    
    /**
     * @brief Retrieves specific data about the environment based on a key
     * 
     * @param key The type of data to fetch
     * @return Map of string keys to numeric values with the requested data
     */
    std::unordered_map<std::string, double> fetchData(std::string const& key) const;
    
    /**
     * @brief Destructor that cleans up all entities
     */
    ~Environment()
    {
        clean();
    }

private:
    std::list<OrganicEntity*> organic_entity_;   ///< List of all organic entities in the environment
    std::list<FoodGenerator*> food_generator_;   ///< List of all food generators in the environment
    std::list<OrganicEntity*> kill_list_;         ///< List of entities marked for deletion
    std::list<Wave*> env_list_waves_;            ///< List of all waves in the environment
    std::list<Rock*> env_list_rocks_;            ///< List of all rocks in the environment
    std::list<CircularCollider*> env_list_obstacles_; ///< List of all obstacles in the environment
};