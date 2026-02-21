#pragma once
#include "../Scorpion.hpp"
#include "Sensor.hpp"
#include <list>
#include "../../Utility/Vec2d.hpp"
#include <cmath>
#include <vector>

class NeuronalScorpion : public Scorpion
{
    enum NeuronalState {
        IDLE,       // at rest (in this state it is receptive to waves potentially emitted by gerbils)
        WANDERING,  // wandering randomly
        TARGET_IN_SIGHT, // a prey has entered its field of vision
        MOVING,     // it doesn't yet see the prey but has detected it through emitted waves (and orients itself accordingly)
    };
public:

    /*!
    * @brief create a NeuronalScorpion
    *
    * @param Position
    * @param energy
    *
    * @return an NeuronalScorpion
    */
    NeuronalScorpion(const Vec2d& position, const double& energy) ;
    /*!
    * @brief create a NeuronalScorpion
    *
    * @param Position
    * @param size
    * @param energy
    *
    * @return an NeuronalScorpion
    */
    NeuronalScorpion(const Vec2d&, const double&, const bool&);

    /*!
    * @brief create a NeuronalScorpion
    *
    * @param Position
    * @param size
    * @param energy
    * @param ageLimit
    *
    * @return an NeuronalScorpion
    */
    NeuronalScorpion(const Vec2d&, const double&, const bool&, const sf::Time&);


    /*!
    * @brief create a NeuronalScorpion
    *
    * @param Position
    *
    * @return an NeuronalScorpion
    */
    NeuronalScorpion(const Vec2d&);


    virtual void update(sf::Time ) override;
    void UpdateState(sf::Time dt);




    void draw(sf::RenderTarget&) const override;


    /*!
    * @brief rotate a vector
    *
    * @param vector
    * @param angle radian
    *
    * @return a rotated vector
    */
    Vec2d neuronalScorpionRotateVec2dAngle(const Vec2d& vecteur, const double& angle);

    /*!
    * @brief inhibit a chosen sensor depending of a score
    *
    * @param index of the sensor {18, 54, 90, 140, -140, -90, -54, -18}
    * @param score
    *
    */
    void neuronalScorpionInhibitSensorIndexScore(const size_t&, const double& );

    /*!
    * @brief inhibit a chosen sensor depending of a score (not tested)
    *
    * @return position of the sensor
    *
    */
    Vec2d neuronalScorpionGetPositionOfSensor(const size_t&);

    /*!
    * @brief set position of the sensors acording to the Scorpion
    *
    */
    void neuronalScorpionSetPositionOfSensors();

    /*!
    * @brief is the sensor active?
    *
    * @return true or false
    *
    */
    bool neuronalScorpionAnySensorActive();

    /*!
    * @brief Update the sensors of the scorpion
    *
    */
    void neuronalUpdateSensors(sf::Time dt);


protected:

    /*!
    * @brief Estimate the position of a target acording to sensors
    *
    * @return estimation of the target
    *
    */
    Vec2d neuronalScorpionEstimateTarget();

    /*!
    * @brief add all the sensors to the scorpion( new sensors might have been done without pointers since we want it to exist as long as the scorpion is alive)
    *
    * @return estimation of the target
    *
    */
    void neuronalScorpionAddSensors();

    /*!
    * @brief reset the sensor (not activated, score = 0, inhibitior = 0)

    *
    */
    void neuronalScorpionSensorsReset();

    /*!
    * @brief write the current state as a string
    *
    *@return current state
    *
    */
    std::string stateToString() const;
    void drawText( sf::RenderTarget&  ) const override;
private:

    std::vector<Sensor> neuronal_scorpion_vector_sensors_;
    sf::Time neuronal_scorpion_time_idle_;
    sf::Time neuronal_scorpion_time_moving_;

    sf::Time neuronal_scorpion_time_reception_;
    sf::Time neuronal_scorpion_state_clock_;
    sf::Time neuronal_scorpion_clock_sensors_;
    NeuronalState neuronal_scorpion_state_;
    Vec2d neuronal_scorpion_target_;
};

