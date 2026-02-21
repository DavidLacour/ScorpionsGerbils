#include "NeuronalScorpion.hpp"
#include "../../Utility/Vec2d.hpp"
#include "../../Application.hpp"
#include "../../Utility/Utility.hpp"
#include "Sensor.hpp"
#include <vector>

class Sensor;

NeuronalScorpion::NeuronalScorpion(const Vec2d& position, const double& energy,
                                   const bool& isFemale) : Scorpion(position,energy,isFemale)
    ,neuronal_scorpion_time_idle_(sf::seconds(getAppConfig().neuronalscorpion_idlemax))
    ,neuronal_scorpion_time_moving_(sf::seconds(getAppConfig().neuronalscorpion_movingmax))
    ,neuronal_scorpion_time_reception_(sf::seconds(getAppConfig().sensor_activation_duration))
    ,neuronal_scorpion_state_clock_((sf::Time::Zero))
    ,neuronal_scorpion_clock_sensors_(sf::Time::Zero)
    ,neuronal_scorpion_state_(WANDERING)
    ,neuronal_scorpion_target_(1,0)
{
    neuronalScorpionAddSensors();
}

NeuronalScorpion::NeuronalScorpion(const Vec2d& position) : Scorpion(position)
    ,neuronal_scorpion_time_idle_(sf::seconds(getAppConfig().neuronalscorpion_idlemax))
    ,neuronal_scorpion_time_moving_(sf::seconds(getAppConfig().neuronalscorpion_movingmax))
    ,neuronal_scorpion_time_reception_(sf::seconds(getAppConfig().sensor_activation_duration))
    ,neuronal_scorpion_state_clock_((sf::Time::Zero))
    ,neuronal_scorpion_clock_sensors_(sf::Time::Zero)
    ,neuronal_scorpion_state_(WANDERING)
    ,neuronal_scorpion_target_(1,0)
{
    neuronalScorpionAddSensors();
}

NeuronalScorpion::NeuronalScorpion(const Vec2d& position, const double& energy,
                                   const bool& isFemale, const sf::Time& ageLimit= sf::Time(getAppConfig().scorpion_longevity)) : Scorpion(position, energy, isFemale, ageLimit)
    ,neuronal_scorpion_time_idle_(sf::seconds(getAppConfig().neuronalscorpion_idlemax))
    ,neuronal_scorpion_time_moving_(sf::seconds(getAppConfig().neuronalscorpion_movingmax))
    ,neuronal_scorpion_time_reception_(sf::seconds(getAppConfig().sensor_activation_duration))
    ,neuronal_scorpion_state_clock_((sf::Time::Zero))
    ,neuronal_scorpion_clock_sensors_(sf::Time::Zero)
    ,neuronal_scorpion_state_(WANDERING)
    ,neuronal_scorpion_target_(1,0)
{
    neuronalScorpionAddSensors();
}

void NeuronalScorpion::update(sf::Time dt)
{
    neuronalUpdateSensors(dt);
    analyzeEnvironment();

    OrganicEntity* closestEdible = getClosestEdible();
    if (closestEdible != nullptr) {
        neuronal_scorpion_state_ = TARGET_IN_SIGHT;
        neuronal_scorpion_target_ = closestEdible->getPosition();
    }
    else {
        if (neuronal_scorpion_state_ != MOVING) {
            if(neuronalScorpionAnySensorActive()) {
                neuronal_scorpion_clock_sensors_ += dt;
                neuronal_scorpion_state_ = IDLE;
                if (neuronal_scorpion_clock_sensors_ >= neuronal_scorpion_time_reception_) {
                    neuronal_scorpion_target_ = neuronalScorpionEstimateTarget();
                    neuronal_scorpion_clock_sensors_= sf::Time::Zero;
                    neuronalScorpionSensorsReset();
                    neuronal_scorpion_state_ = MOVING;
                }
            }
        }
    }
    UpdateState(dt);
    switch(neuronal_scorpion_state_) {
    case WANDERING:
        moveToVec2dForce(dt,randomWalk());
        break;
    case IDLE:
        break;
    case MOVING:
        moveToVec2dForce(dt,neuronal_scorpion_target_);
        break;
    case TARGET_IN_SIGHT:
        moveToVec2dForce(dt,force(neuronal_scorpion_target_));
        break;
    }
}

void NeuronalScorpion::UpdateState(sf::Time dt)
{
    switch(neuronal_scorpion_state_) {
    case IDLE:
        break;
    case WANDERING:
        break;
    case MOVING:
        neuronal_scorpion_state_clock_ += dt;
        if (neuronal_scorpion_state_clock_ >= neuronal_scorpion_time_moving_) {
            neuronal_scorpion_state_= WANDERING;
            neuronal_scorpion_state_clock_ = sf::Time::Zero;
        }
        break;
    case TARGET_IN_SIGHT:
        break;
    }
}

void NeuronalScorpion::neuronalUpdateSensors(sf::Time dt)
{
    neuronalScorpionSetPositionOfSensors();
    for (auto& sen : neuronal_scorpion_vector_sensors_) {
        sen.update(dt);
    }
}

Vec2d NeuronalScorpion::neuronalScorpionRotateVec2dAngle(const Vec2d& vecteur, const double& angle)
{
    return Vec2d(cos(angle)*vecteur.x - sin(angle)*vecteur.y, sin(angle)*vecteur.x + cos(angle)*vecteur.y);
}

void NeuronalScorpion::neuronalScorpionAddSensors()
{
    std::vector<double> sensorAngles{18, 54, 90, 140, -140, -90, -54, -18};
    size_t index(0);
    for (auto& angle : sensorAngles) {
        neuronal_scorpion_vector_sensors_.emplace_back(
            getPosition() + getAppConfig().scorpion_sensor_radius * 
            neuronalScorpionRotateVec2dAngle(getDirection(), angle * DEG_TO_RAD),
            this, index
        );
        index += 1;
    }
}

void NeuronalScorpion::neuronalScorpionInhibitSensorIndexScore(const size_t& i, const double& score)
{
    neuronal_scorpion_vector_sensors_[i].sensorInhibitedByScore(score);
}

Vec2d NeuronalScorpion::neuronalScorpionGetPositionOfSensor(const size_t& i)
{
    return neuronal_scorpion_vector_sensors_[i].getPosition();
}

Vec2d NeuronalScorpion::neuronalScorpionEstimateTarget()
{
    Vec2d res(0.0, 0.0);
    for (auto& sen : neuronal_scorpion_vector_sensors_) {
        res += (sen.getPosition() - getPosition()) * sen.sensorGetScore();
    }
    return res;
}

void NeuronalScorpion::neuronalScorpionSetPositionOfSensors()
{
    std::vector<double> sensorAngles{18, 54, 90, 140, -140, -90, -54, -18};
    for (size_t i(0); i < sensorAngles.size(); ++i) {
        neuronal_scorpion_vector_sensors_[i].sensorSetPosition(
            getPosition() + getAppConfig().scorpion_sensor_radius * 
            neuronalScorpionRotateVec2dAngle(getDirection(), sensorAngles[i] * DEG_TO_RAD)
        );
    }
}

bool NeuronalScorpion::neuronalScorpionAnySensorActive()
{
    for (auto& sen : neuronal_scorpion_vector_sensors_) {
        if (sen.sensorIsActive()) return true;
    }
    return false;
}

void NeuronalScorpion::draw(sf::RenderTarget& target) const
{
    Animal::draw(target);
    if (isDebugOn()) {
        for (const auto& sen : neuronal_scorpion_vector_sensors_) {
            sen.draw(target);
        }
    }
}

std::string NeuronalScorpion::stateToString() const
{
    std::string stateString;
    switch (neuronal_scorpion_state_) {
    case WANDERING:
        stateString = "WANDERING";
        break;
    case IDLE:
        stateString = "IDLE";
        break;
    case TARGET_IN_SIGHT:
        stateString = "TARGET_IN_SIGHT";
        break;
    case MOVING:
        stateString = "MOVING";
        break;
    }
    return stateString;
}

void NeuronalScorpion::neuronalScorpionSensorsReset()
{
    for (auto& sen : neuronal_scorpion_vector_sensors_) {
        sen.sensorReset();
    }
}

void NeuronalScorpion::drawText(sf::RenderTarget& target) const
{
    target.draw(buildDebugText(NeuronalScorpion::stateToString(), 80, sf::Color::Red));
}