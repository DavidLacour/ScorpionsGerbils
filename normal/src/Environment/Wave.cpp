#include "Wave.hpp"
#include "../Utility/Vec2d.hpp"
#include "../Application.hpp"
#include "../Utility/Utility.hpp"
#include "../src/Config.hpp"
#include <cmath>
#include <utility>
#include <list>


Wave::Wave( const Vec2d& position, const double& wave_energy, const double& wave_radius_initial, const double& wave_mu, const double& wave_speed)  :
    CircularCollider(position, wave_radius_initial),
    wave_energy_initial_(wave_energy),
    wave_radius_initial_(wave_radius_initial),
    wave_mu_(wave_mu),
    wave_speed_(wave_speed),
    wave_energy_current_(wave_energy),
    wave_intensity_(wave_energy),
    wave_clock_(sf::Time::Zero)
{
    std::pair< double,double> pair1(-PI,PI);
    wave_list_pair_angles_.push_front(pair1);
}

void Wave::update(sf::Time dt)
{
    waveUpdateClock(dt);
    waveUpdateRadius();
    waveUpdateEnergy();
    waveUpdateIntensity();
    waveUpdateListPairAngles();
}
void Wave::draw(sf::RenderTarget&  target) const
{

    for (const auto& pairAngle : wave_list_pair_angles_) {

        sf::Color color = sf::Color::Black;
        Arc arc(buildArc(
                    pairAngle.first/DEG_TO_RAD,
                    pairAngle.second/DEG_TO_RAD,
                    getRadius(), getPosition() ,
                    color, 0.0,
                    getAppConfig().wave_intensity_thickness_ratio*wave_intensity_
                ));
        target.draw(arc);
    }
}
void Wave::waveUpdateClock(sf::Time dt)
{
    wave_clock_ += dt;
}
void Wave::waveUpdateRadius()
{
    setRadius(wave_speed_*wave_clock_.asSeconds()+wave_radius_initial_);
}

void Wave::waveUpdateEnergy()
{
    wave_energy_current_= wave_energy_initial_* exp(-getRadius()/wave_mu_);
}

void Wave::waveUpdateIntensity()  // I(t) = E0 * exp(-r(t)/µ) / (2 * PI * r(t)) = E0 * exp(-t*v/µ) / (2 * PI * r(t)) = E0 * exp(-t*v/µ) / (2 * PI * r(t))
{
    wave_intensity_=  wave_energy_initial_*exp(-wave_clock_.asSeconds()*wave_speed_/wave_mu_)/(2 *PI* getRadius());

}

void Wave::waveUpdateListPairAngles()
{

    std::list<CircularCollider*> liste(getAppEnv().getIsColliding(this));
    for (auto& arc : wave_list_pair_angles_ ) {
        for (auto& obstacle : liste ) {
            if ( ((obstacle->getPosition() - this->getPosition()).angle() >= arc.first ) and ((obstacle->getPosition() - this->getPosition()).angle() <= arc.second  )) {
                wave_list_pair_angles_.push_back(pairdouble((obstacle->getPosition() - this->getPosition()).angle()+std::atan2(obstacle->getRadius(),obstacle->getRadius()+this->getRadius()),arc.second));
                arc.second=((obstacle->getPosition() - this->getPosition()).angle()-std::atan2(obstacle->getRadius(),obstacle->getRadius()+this->getRadius()));
            }
        }
    }
    liste.clear();
}
double Wave::waveGetWaveEnergy() const
{
    return wave_energy_current_;
}
double Wave::waveGetWaveIntensity() const
{
    return wave_intensity_;
}

bool Wave::waveIsPointInside(const Vec2d& point) const
{
    if (this->isPointInside(point)) {
        for (const auto& arc : wave_list_pair_angles_) {

            if(((point- this->getPosition()).angle() >= arc.first ) and (point - this->getPosition()).angle() <= arc.second ) return true;
        }
    }
    return false ;
}

bool Wave::waveIsPointTouching(const Vec2d& point) const
{
    if (CircularCollider(getPosition(),getRadius()+getAppConfig().wave_on_wave_marging).isPointInside(point) and
        !CircularCollider(getPosition(),getRadius()-getAppConfig().wave_on_wave_marging).isPointInside(point)) {
        for (const auto& arc : wave_list_pair_angles_) {

            if(((point- this->getPosition()).angle() >= arc.first ) and (point - this->getPosition()).angle() <= arc.second ) return true;
        }
    }
    return false ;
}