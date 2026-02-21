/**
 * @class ChasingAutomaton
 * @brief An entity that chases a target position using acceleration and forces
 * 
 * The ChasingAutomaton is a CircularCollider that implements steering behaviors
 * to chase a designated target position. It uses physics-based movement with
 * force calculations to determine acceleration and update its velocity and position.
 */
class ChasingAutomaton : public CircularCollider
{
public:
    /**
     * @brief Constructs a new ChasingAutomaton
     * 
     * @param position Initial position of the automaton
     * @param speed Initial speed (default is 0)
     */
    ChasingAutomaton(const Vec2d& position, double speed = 0)
        : CircularCollider(position, CHASING_AUTOMATON_RADIUS), direction_(0,0), speed_(speed), target_(1,0)
    {
    }
    
    /**
     * @brief Gets the maximum speed this automaton can reach
     * 
     * @return The maximum speed as a constant reference
     */
    const double& getStandardMaxSpeed() const;
    
    /**
     * @brief Gets the mass of this automaton for force calculations
     * 
     * @return The mass as a constant reference
     */
    const double& getMass() const;

    /**
     * @brief Calculates the force needed to reach the target position
     * 
     * @param target The target position to move towards
     * @return The force vector
     */
    Vec2d force(const Vec2d& target) const;

    /**
     * @brief Sets the target position for this automaton to chase
     * 
     * @param position The new target position
     */
    void setTargetPosition(const Vec2d& position);

    /**
     * @brief Gets the current velocity vector
     * 
     * @return The speed vector (direction * speed magnitude)
     */
    Vec2d getSpeedVector() const;

    /**
     * @brief Updates the automaton's state
     * 
     * @param dt Time elapsed since last update
     */
    void update(sf::Time dt);
    
    /**
     * @brief Draws the automaton and its target to the render target
     * 
     * @param targetWindow The window to draw to
     */
    void draw(sf::RenderTarget& targetWindow);
    
    /**
     * @brief Moves the automaton based on force and physics calculations
     * 
     * @param deltaT Time step for the movement calculation
     */
    void move(const double& deltaT);

private:
    Vec2d direction_; ///< Normalized direction vector
    double speed_;  ///< Current speed magnitude
    Vec2d target_;     ///< Target position to chase
};