#include "Sensor.hpp"
#include "../../Application.hpp"
#include "NeuronalScorpion.hpp"
#include "../../Utility/Utility.hpp"
Sensor::Sensor(const Vec2d& position, NeuronalScorpion* neuronalScorpion, const size_t& index) :
    sensor_position_(position)
    ,sensor_neuronal_scorpion_(neuronalScorpion)
    ,sensor_index_(index)
    ,sensor_active_(false)
    ,sensor_score_(0.0)
    ,sensor_inhibitor_(0.0)
    ,sensor_intensity_threshold_(getAppConfig().sensor_intensity_threshold)

    ,sensor_inhibitor_factor_(getAppConfig().sensor_inhibition_factor)
{}

void Sensor::update(sf::Time dt)
{
    sensorActivation();
    sensorUpdateScore();
    sensorInhibit();
}

Vec2d Sensor::getPosition() const
{
    return sensor_position_;
}

void Sensor::sensorTemper()
{
    sensor_score_ += (2.0*(1- sensor_inhibitor_));

}

void Sensor::sensorActivation()
{
    if (sensor_active_==false) {
        if 	( getAppEnv().envSensorActivationIntensityCumulated(this) >= sensor_intensity_threshold_) {
            sensor_active_ = true;


        }


    }

}

void Sensor::sensorUpdateScore()
{
    if (sensor_active_==true) {
        sensor_score_ += 2.0 * (1.0 - sensor_inhibitor_) ;
    }
}

void Sensor::sensorInhibit()
{
    if (sensor_active_==true) {
        for (size_t i(3); i<6; ++i) {
            sensor_neuronal_scorpion_->neuronalScorpionInhibitSensorIndexScore((sensor_index_ + i) % 8, sensor_score_);
        }
    }
}

void Sensor::sensorInhibitedByScore(const double& score)
{
    sensor_inhibitor_ += score*sensor_inhibitor_factor_;
}

void Sensor::sensorReset()
{
    sensor_active_ = false;
    sensor_score_=0;
    sensor_inhibitor_=0;

}

double Sensor::sensorGetScore()
{

    return sensor_score_;
}

void Sensor::sensorSetPosition(const Vec2d& position)
{
    sensor_position_= position;
}

bool Sensor::sensorIsActive()
{
    return sensor_active_;

}

void Sensor::draw(sf::RenderTarget& target) const
{
    sf::Color color;
    if (sensor_active_ == true and sensor_inhibitor_ > 0.2) {
        color =  sf::Color::Magenta;
    } else if (sensor_active_ == false and sensor_inhibitor_ > 0.2) {
        color =  sf::Color::Blue;
    } else if (sensor_active_ == true and sensor_inhibitor_ < 0.2) {
        color =  sf::Color::Red;
    } else {
        color = sf::Color::Green;
    }
    target.draw(buildCircle(getPosition(), sensor_neuronal_scorpion_->getRadius()/4, color));
}