#pragma once
#include "../../Obstacle/CircularCollider.hpp"
#include "../../Interface/Updatable.hpp"
#include "../../Interface/Drawable.hpp"
#include "../../Environment/Wave.hpp"

class NeuronalScorpion;

/**
 * @class Sensor
 * @brief A sensor for the NeuronalScorpion that can detect and respond to environmental stimuli
 * 
 * The Sensor class represents a sensory component of the NeuronalScorpion entity.
 * It can be activated by environmental factors, accumulate scores, and inhibit other sensors.
 */
class Sensor
    : public Updatable , public Drawable
{
public:
    /**
     * @brief Destructor for Sensor class
     */
    ~Sensor() {}

    /**
     * @brief Constructs a new Sensor
     * 
     * @param position The position vector of the sensor
     * @param neuronalScorpion Pointer to the parent NeuronalScorpion
     * @param index The index of the sensor in the scorpion's sensor array
     */
    Sensor(const Vec2d& position, NeuronalScorpion* neuronalScorpion, const size_t& index);
    
    /**
     * @brief Updates the sensor state
     * 
     * @param dt Time elapsed since last update
     */
    void update(sf::Time dt) override;

    /**
     * @brief Draws the sensor to the target window
     * 
     * @param targetWindow The render target to draw on
     */
    void draw(sf::RenderTarget& targetWindow) const override;
    
    /**
     * @brief Gets the current position of the sensor
     * 
     * @return The position as a Vec2d
     */
    Vec2d getPosition() const;
    
    /**
     * @brief Activates the sensor if intensity threshold is reached
     */
    void sensorActivation();

    /**
     * @brief Increases the sensor's score
     */
    void sensorTemper();
    
    /**
     * @brief Increases the sensor's score by a given amount
     * 
     * @param amount The amount to increase the score by
     */
    void sensorTemper(const double& amount);
    
    /**
     * @brief Updates the sensor's score based on its activation state
     */
    void sensorUpdateScore();
    
    /**
     * @brief Inhibits other sensors based on this sensor's state
     */
    void sensorInhibit();
    
    /**
     * @brief Applies inhibition to this sensor based on another sensor's score
     * 
     * @param score The score from another sensor affecting this one
     */
    void sensorInhibitedByScore(const double& score);
    
    /**
     * @brief Resets the sensor to its default state
     */
    void sensorReset();
    
    /**
     * @brief Gets the current score of the sensor
     * 
     * @return The sensor's score
     */
    double sensorGetScore();
    
    /**
     * @brief Sets the position of the sensor
     * 
     * @param position The new position vector
     */
    void sensorSetPosition(const Vec2d& position);
    
    /**
     * @brief Checks if the sensor is currently active
     * 
     * @return true if the sensor is active, false otherwise
     */
    bool sensorIsActive();

protected:

private:
    Vec2d sensor_position_;
    NeuronalScorpion* sensor_neuronal_scorpion_;
    size_t sensor_index_;

    bool sensor_active_;
    double sensor_score_;

    double sensor_inhibitor_;
    double sensor_intensity_threshold_;
    double sensor_inhibitor_factor_;
};