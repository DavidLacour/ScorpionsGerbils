#pragma once

#include "../Utility/Vec2d.hpp"
#include "../Obstacle/CircularCollider.hpp"
#include "../Interface/Updatable.hpp"
#include "../Interface/Drawable.hpp"
#include <utility>
#include <list>

/**
 * @typedef pairdouble
 * @brief Shorthand for a pair of doubles representing angle ranges
 */
typedef std::pair<double,double> pairdouble;

/**
 * @class Wave
 * @brief Represents a sensory wave emitted by Scorpions to detect prey
 * 
 * The Wave class simulates a propagating mechanical wave that Scorpions use 
 * for prey detection in the simulation environment. As a wave propagates outward,
 * it follows physical principles where energy decreases exponentially with distance.
 * Waves can be obstructed by obstacles, causing them to split into multiple arcs.
 * 
 * The wave mechanics include:
 * - Expanding radius over time based on wave speed
 * - Energy diminishing exponentially with distance
 * - Intensity calculated as energy divided by perimeter
 * - Collision detection with obstacles to create shadow zones
 * 
 * Scorpions use these waves as a primary sensory mechanism to locate Gerbils
 * and other potential prey in their environment, simulating the way real scorpions
 * detect vibrations through substrate-borne mechanical waves.
 */
class Wave : public CircularCollider, public Updatable
{
public:
    /**
     * @brief Virtual destructor
     */
    virtual ~Wave() {}
    
    /**
     * @brief Updates the wave state for the current time step
     * 
     * Calls all subordinate update methods in sequence:
     * - waveUpdateClock: Increments the wave's internal clock
     * - waveUpdateRadius: Expands the wave radius based on time elapsed
     * - waveUpdateEnergy: Recalculates energy based on new radius
     * - waveUpdateIntensity: Updates intensity based on energy and radius
     * - waveUpdateListPairAngles: Handles collision with obstacles
     * 
     * @param dt Time elapsed since last update
     */
    virtual void update(sf::Time dt) override;

    /**
     * @brief Renders the wave to the target window
     * 
     * Draws the wave as a series of arcs representing the wave fronts.
     * The thickness of the arcs is proportional to the wave intensity.
     * 
     * @param target The render target to draw on
     */
    virtual void draw(sf::RenderTarget& target) const override;

    /**
     * @brief Constructs a new Wave
     * 
     * Creates a wave with specified initial parameters that will propagate
     * outward from the given position.
     * 
     * @param position Initial center position of the wave
     * @param energy Initial energy of the wave
     * @param radius_initial Initial radius of the wave
     * @param mu Energy dissipation coefficient
     * @param speed Propagation speed of the wave
     */
    Wave(const Vec2d& position, const double& energy, const double& radius_initial, 
         const double& mu, const double& speed);

    /**
     * @brief Gets the current energy level of the wave
     * @return Current energy value
     */
    double waveGetWaveEnergy() const;

    /**
     * @brief Gets the current intensity of the wave
     * @return Current intensity value
     */
    double waveGetWaveIntensity() const;

    /**
     * @brief Checks if a point is inside any arc of the wave
     * 
     * Determines if a position is within the wave's radius and
     * within one of the active arc segments of the wave.
     * 
     * @param position Position to check
     * @return true if the point is inside the wave, false otherwise
     */
    bool waveIsPointInside(const Vec2d& position) const;

    /**
     * @brief Checks if a point is touching the wave perimeter
     * 
     * Determines if a position is within a margin of the wave's perimeter
     * and within one of the active arc segments of the wave.
     * 
     * @param position Position to check
     * @return true if the point is touching the wave, false otherwise
     */
    bool waveIsPointTouching(const Vec2d& position) const;

protected:
    /**
     * @brief Updates the wave's internal clock
     * @param dt Time elapsed since last update
     */
    void waveUpdateClock(sf::Time dt);

    /**
     * @brief Updates the wave's radius based on elapsed time
     * 
     * Radius increases linearly with time according to wave speed:
     * radius = speed * time + initial_radius
     */
    void waveUpdateRadius();

    /**
     * @brief Updates the wave's energy based on its radius
     * 
     * Energy decreases exponentially with radius:
     * energy = initial_energy * exp(-radius/mu)
     */
    void waveUpdateEnergy();

    /**
     * @brief Updates the wave's intensity based on energy and radius
     * 
     * Intensity is calculated as energy divided by perimeter:
     * intensity = energy / (2 * PI * radius)
     */
    void waveUpdateIntensity();

    /**
     * @brief Updates the wave's arc segments based on obstacle collisions
     * 
     * When a wave encounters an obstacle, it splits into multiple arcs,
     * creating shadow zones behind obstacles where the wave doesn't propagate.
     * This method handles the creation and modification of these arc segments.
     */
    void waveUpdateListPairAngles();

private:
    /**
     * @brief Initial energy of the wave at creation
     */
    double wave_energy_initial_;
    
    /**
     * @brief Initial radius of the wave at creation
     */
    double wave_radius_initial_;
    
    /**
     * @brief Energy dissipation coefficient
     */
    double wave_mu_;
    
    /**
     * @brief Propagation speed of the wave
     */
    double wave_speed_;
    
    /**
     * @brief Current energy level of the wave
     */
    double wave_energy_current_;
    
    /**
     * @brief Current intensity of the wave
     */
    double wave_intensity_;
    
    /**
     * @brief Time elapsed since wave creation
     */
    sf::Time wave_clock_;
    
    /**
     * @brief List of angle pairs representing active arc segments
     * 
     * Each pair contains start and end angles of an arc segment
     * where the wave is present. Obstacles create gaps in these arcs.
     */
    std::list<std::pair<double,double>> wave_list_pair_angles_;
};