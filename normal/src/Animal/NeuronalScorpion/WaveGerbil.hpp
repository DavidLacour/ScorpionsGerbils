#pragma once
#include "../Gerbil.hpp"
#include "../../Application.hpp"

/**
 * @class WaveGerbil
 * @brief A specialized Gerbil that can emit waves into the environment
 * 
 * The WaveGerbil extends the basic Gerbil class by adding the ability to
 * periodically emit waves that propagate through the environment. These waves
 * can be detected by other entities like NeuronalScorpion.
 */
class WaveGerbil : public Gerbil
{
public:
    /**
     * @brief Destructor for WaveGerbil
     */
    ~WaveGerbil() {}

    /**
     * @brief Constructs a WaveGerbil at the specified position
     * 
     * @param position The initial position of the WaveGerbil
     */
    WaveGerbil(const Vec2d& position);

    /**
     * @brief Constructs a WaveGerbil with specified position, energy, and gender
     * 
     * @param position The initial position of the WaveGerbil
     * @param energy The initial energy level
     * @param isFemale Gender flag (true for female, false for male)
     */
    WaveGerbil(const Vec2d& position, const double& energy, const bool& isFemale);

    /**
     * @brief Constructs a WaveGerbil with specified position, energy, gender, and age limit
     * 
     * @param position The initial position of the WaveGerbil
     * @param energy The initial energy level
     * @param isFemale Gender flag (true for female, false for male)
     * @param ageLimit Maximum age the WaveGerbil can reach
     */
    WaveGerbil(const Vec2d& position, const double& energy, const bool& isFemale, const sf::Time& ageLimit);

    /**
     * @brief Constructs a baby WaveGerbil with a parent
     * 
     * @param position The initial position of the baby WaveGerbil
     * @param direction The initial direction the baby is facing
     * @param parent Pointer to the parent OrganicEntity
     */
    WaveGerbil(const Vec2d& position, const Vec2d& direction, OrganicEntity* parent);

    /**
     * @brief Updates the WaveGerbil's state
     * 
     * Extends the base Gerbil update by adding wave emission behavior
     * 
     * @param dt Time elapsed since last update
     */
    virtual void update(sf::Time dt) override;

protected:
    /**
     * @brief Handles the wave emission mechanism
     * 
     * Creates and emits waves at regular intervals based on the wave_gerbil_frequency_
     * 
     * @param dt Time elapsed since last update
     */
    void waveGerbilWaving(sf::Time dt);

private:
    sf::Time wave_gerbil_frequency_; ///< The time interval between wave emissions
    sf::Time wave_gerbil_clock_;     ///< Timer tracking time since last wave emission
};