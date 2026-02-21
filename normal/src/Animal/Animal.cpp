#include "../Application.hpp"
#include "../Utility/Utility.hpp"
#include "Animal.hpp"
#include <list>
#include <limits>
#include "../Random/Uniform.hpp"
#include "Scorpion.hpp"
#include "Gerbil.hpp"

Animal::Animal(const Vec2d& position,const double& size, const double& energy, const bool& isFemale) :
    OrganicEntity( position, size, energy),
    direction_(1,0),
    speed_(0),
    current_target_(1,0),
    is_female_(isFemale),
    energy_consumption_factor_(0),
    time_pause_feeding_(sf::seconds(getAppConfig().animal_feed_time)),
    state_(WANDERING),
    target_entity_(nullptr),
    pregnant_(false),
    babies_(0),
    birth_pause_timer_(sf::seconds(getAppConfig().animal_delivery_time)),
    time_pause_mating_(sf::seconds(getAppConfig().animal_mating_time)),
    time_gestation_limit_(sf::seconds(10)),
    time_gestation_(sf::Time::Zero) ,
    time_running_away_(sf::seconds(getAppConfig().animal_running_away)),
    organic_entity_mum_(nullptr)
{ } 

Animal::Animal(const Vec2d& position,const double& size, const double& energy, const bool& isFemale, const sf::Time& ageLimit, const double& energyConsumptionFactor,
               const double&  gestationLimit ) :
    OrganicEntity( position, size, energy, ageLimit), direction_(1,0), speed_(0), current_target_(1,0),
    is_female_(isFemale),
    energy_consumption_factor_(energyConsumptionFactor),
    time_pause_feeding_(sf::seconds(getAppConfig().animal_feed_time)),
    state_(WANDERING),
    target_entity_(nullptr),
    pregnant_(false),
    babies_(0),
    birth_pause_timer_(sf::seconds(getAppConfig().animal_delivery_time)),
    time_pause_mating_(sf::seconds(getAppConfig().animal_mating_time)),
    time_gestation_limit_(sf::seconds(gestationLimit)),
    time_gestation_(sf::Time::Zero) ,
    time_running_away_(sf::seconds(getAppConfig().animal_running_away)),
    organic_entity_mum_(nullptr)
{ }

Animal::Animal(const Vec2d& position,const double& size, const double& energy, const bool& isFemale, const sf::Time& ageLimit, const double& energyConsumptionFactor, const double&  gestationLimit, const Vec2d& direction) :
    Animal(position, size, energy, isFemale, ageLimit, energyConsumptionFactor, gestationLimit, direction, nullptr)
{ }

Animal::Animal(const Vec2d& position,const double& size, const double& energy, const bool& isFemale, const sf::Time& ageLimit, const double& energyConsumptionFactor, const double&  gestationLimit, const Vec2d& direction, OrganicEntity* mum) :
    OrganicEntity( position, size/ANIMAL_BABY_SIZE_FACTOR, energy, ageLimit), direction_(direction), speed_(0), current_target_(1,0),
    is_female_(isFemale),
    energy_consumption_factor_(energyConsumptionFactor),
    time_pause_feeding_(sf::seconds(getAppConfig().animal_feed_time)),
    state_(BABY),
    target_entity_(nullptr),
    pregnant_(false),
    babies_(0),
    birth_pause_timer_(sf::seconds(getAppConfig().animal_delivery_time)),
    time_pause_mating_(sf::seconds(getAppConfig().animal_mating_time)),
    time_gestation_limit_(sf::seconds(gestationLimit)),
    time_gestation_(sf::Time::Zero) ,
    time_running_away_(sf::seconds(getAppConfig().animal_running_away)),
    organic_entity_mum_(mum)
{ }

Animal::Animal(const Vec2d& position,const double& size, const double& energy, const bool& isFemale, const sf::Time& ageLimit) :
    OrganicEntity( position, size, energy, ageLimit),
    direction_(1,0),
    speed_(0),
    current_target_(1,0),
    is_female_(isFemale),
    energy_consumption_factor_(0),
    time_pause_feeding_(sf::seconds(getAppConfig().animal_feed_time)),
    state_(WANDERING),
    target_entity_(nullptr),
    pregnant_(false),
    babies_(0),
    birth_pause_timer_(sf::seconds(getAppConfig().animal_delivery_time)),
    time_pause_mating_(sf::seconds(getAppConfig().animal_mating_time)),
    time_gestation_limit_(sf::seconds(10)),
    time_gestation_(sf::Time::Zero),
    time_running_away_(sf::seconds(getAppConfig().animal_running_away)),
    organic_entity_mum_(nullptr)
{ } 

Vec2d Animal::getSpeedVector() const
{
    return direction_*speed_;
} 

void Animal::giveBirth()
{
    return this->giveBirthThis();
}

void Animal::meet(OrganicEntity* O)
{
    state_= MATING;
    return O->meetThis(this);
}

void Animal::meetThis(Animal* A) 
{
    state_= MATING;
    int babies(uniform(getAppConfig().gerbil_min_children,getAppConfig().gerbil_max_children));
    if(isFemale()) {
        setPregnant(true);
        setEnergy(getEnergy()+getAppConfig().gerbil_energy_loss_female_per_child*babies);
        setBabies(babies);
    } else {
        setEnergy(getEnergy()-getAppConfig().gerbil_energy_loss_mating_male);
    }
    if( A->isFemale()) {
        A->setPregnant(true);
        A->setEnergy(A->getEnergy()+getAppConfig().gerbil_energy_loss_female_per_child*babies);
        A->setBabies(babies);
    } else {
        A->setEnergy(A->getEnergy()-getAppConfig().gerbil_energy_loss_mating_male);
    }
}

void Animal::setPregnant(const bool& b)
{
    pregnant_ = b;
}

void Animal::UpdateState(sf::Time dt)
{
    analyzeEnvironment();
    if( isPregnant() ) time_gestation_+= dt;
    if( time_gestation_>= time_gestation_limit_ ) {
        setPregnant(false);
        time_gestation_=sf::Time::Zero;
        giveBirth();
        state_ = GIVING_BIRTH;
    }
    if(state_ != FEEDING and state_ != MATING and state_ != GIVING_BIRTH and state_ != BABY and state_ != RUNNING_AWAY) {
        if(!food_sources_.empty()) {
            target_entity_=findClosest(food_sources_);
            if (isCollidingWithTarget()) {
                target_position_memory_= target_entity_->getPosition();
                eat();
                state_ = FEEDING;
                time_pause_feeding_= sf::seconds(1.5);
            } else {
                state_ = FOOD_IN_SIGHT;
            }
        }
        if(!potential_mates_.empty()) {
            target_entity_=findClosest(potential_mates_);
            if (isCollidingWithTarget()) {
                meet(target_entity_);
                state_ = MATING;
            } else {
                state_ = MATE_IN_SIGHT;
            }
        }
        if(!predators_.empty()) {
            predators_memory_ = predators_;
            state_= RUNNING_AWAY;
        }
    } else if (state_ == FEEDING ) {
        time_pause_feeding_ -= dt;
        if(time_pause_feeding_<=sf::Time::Zero) state_ = WANDERING;
    } else if (state_ == MATING) {
        time_pause_mating_ -= dt;
        if (time_pause_mating_ <= sf::Time::Zero ) state_= WANDERING;
    }
    if (state_ == GIVING_BIRTH) {
        birth_pause_timer_ -= dt;
        if (birth_pause_timer_ <= sf::Time::Zero ) state_= WANDERING;
    }
    else if (state_ == RUNNING_AWAY) {
        time_running_away_ -= dt;
        if (time_running_away_ <= sf::Time:: Zero) {
            time_running_away_ = sf::seconds(getAppConfig().animal_running_away);
            state_ = WANDERING;
        }
    }
    else if (state_== BABY) {
        if( age_>=  sf::seconds(getAppConfig().gerbil_min_age_mating)) {
            grow();
            if (organic_entity_mum_!= nullptr) organic_entity_mum_->forgetChild(this);
            forgetMother();
            state_= WANDERING;
        }
    }
}

void Animal::update(sf::Time dt)
{
    UpdateState(dt);
    Vec2d attractionForce;

    switch( state_) {
    case FOOD_IN_SIGHT  : {
        if (target_entity_ == nullptr) { state_ = WANDERING; break; }
        Vec2d targetPos = target_entity_->getPosition();
        attractionForce = force(targetPos);
        moveToVec2dForce(dt.asSeconds(), attractionForce);
        break;
    }
    case WANDERING  :
        attractionForce= randomWalk();
        moveToVec2dForce(dt.asSeconds(), attractionForce);
        break;
    case MATE_IN_SIGHT: {
        if (target_entity_ == nullptr) { state_ = WANDERING; break; }
        Vec2d targetPos = target_entity_->getPosition();
        attractionForce = force(targetPos);
        moveToVec2dForce(dt.asSeconds(), attractionForce);
        break;
    }
    case RUNNING_AWAY:
        attractionForce = calculateFleeForce(predators_memory_);
        moveToVec2dForce(dt.asSeconds(), attractionForce);
        break;
    case FEEDING:
        speed_ *=ANIMAL_FEEDING_SPEED_FACTOR;
        moveToVec2dForce(dt.asSeconds(), force(target_position_memory_));
        break;
    case BABY: {
        if ((organic_entity_mum_ != nullptr)) {
            moveToVec2dForce(dt.asSeconds(), force(organic_entity_mum_->getPosition())) ;
        } else {
            OrganicEntity* nearestParent(findClosest(getVisibleEntities()));
            if(nearestParent != nullptr) {
                if( (!eatable(nearestParent)) and !(nearestParent->eatable(this)))
                    moveToVec2dForce(dt.asSeconds(), force(findClosest(getVisibleEntities())->getPosition()));
            }
            else {
                moveToVec2dForce(dt.asSeconds(), randomWalk());
            }
        }
        break;
    }
    default:
        break;
    }

    // Bounce off obstacles
    for (const auto& obstacle : getAppEnv().getIsColliding(this)) {
        Vec2d toAnimal = directionTo(obstacle->getPosition()) * -1;
        double overlap = getRadius() + obstacle->getRadius() - distanceTo(obstacle->getPosition());
        if (overlap > 0) {
            Vec2d normal = toAnimal.normalised();
            setPosition(getPosition() + normal * overlap);
            direction_ = (direction_ - normal * 2.0 * direction_.dot(normal)).normalised();
        }
    }

    updateEnergy(dt);
}

Vec2d Animal::force( const Vec2d& target ) const
{
    if (!isEqual(directionTo(target).length(),0)) {
        double deceleration(ANIMAL_DECELERATION);
        double speed;
        if(directionTo(target).length()/(deceleration) <= getMaxSpeed()) {
            speed = directionTo(target).length()/(deceleration) ;
        }
        else {
            speed = getMaxSpeed() ;
        }
        Vec2d desired_velocity = directionTo(target)/directionTo(target).length()*speed;
        return desired_velocity-speed_*direction_;
    }
    return direction_;
}

Vec2d Animal::force( OrganicEntity* target ) const
{
    return force(target->getPosition());
}

void Animal::draw(sf::RenderTarget& targetWindow) const
{
    if(isDebugOn()) {
        CircularCollider::draw(targetWindow);
        drawVision(targetWindow);
        drawRandomWalkCircle(targetWindow);
        drawText(targetWindow);
    }
    auto image_to_draw(buildSprite (getPosition(),
                                    getRadius()*ANIMAL_SPRITE_SIZE_FACTOR,
                                    getTexture(), getRotation()/DEG_TO_RAD ));
    targetWindow.draw(image_to_draw );
}

sf::Text Animal::buildDebugText(const std::string& text, double offset, sf::Color color) const
{
    return buildText(text,
                     getPosition() + getDirection() * offset,
                     getAppFont(),
                     getAppConfig().default_debug_text_size,
                     color,
                     (getRotation() / DEG_TO_RAD + 90));
}

void Animal::drawText(sf::RenderTarget& targetWindow) const
{
    targetWindow.draw(buildDebugText(stateToString(), 110, sf::Color::Red));
    targetWindow.draw(buildDebugText("Age_limit:" + to_nice_string(age_limit_.asSeconds()) +
                                     " Age:" + to_nice_string(age_.asSeconds()), 90, sf::Color::Blue));
    targetWindow.draw(buildDebugText("Energy limit:" + to_nice_string(getAppConfig().animal_min_energy) +
                                     " Energy:" + to_nice_string(energy_), 70, sf::Color::Blue));

    if (isFemale()) {
        targetWindow.draw(buildDebugText("Female  babies:" + to_nice_string(getBabies()) +
                                         " Gestation_limit:" + to_nice_string(time_gestation_limit_.asSeconds()) +
                                         " Gestation:" + to_nice_string(time_gestation_.asSeconds()), 50, sf::Color::Magenta));
    } else {
        targetWindow.draw(buildDebugText("Male", 50, sf::Color::Blue));
    }

    if (state_ == GIVING_BIRTH) {
        targetWindow.draw(buildDebugText("pause GivingBirth " +
                                         to_nice_string(birth_pause_timer_.asSeconds()), 150, sf::Color::Cyan));
    }

    if (pregnant_) targetWindow.draw(buildAnnulus(getPosition(), 50, sf::Color::Magenta, 2));
}

void Animal::drawVision(sf::RenderTarget& targetWindow) const
{
    sf::Color color = sf::Color::Black;
    color.a = 16;
    Arc arc(buildArc( (getRotation()-getViewRange()/2)/DEG_TO_RAD,
                      (getRotation()+getViewRange()/2)/DEG_TO_RAD,
                      getViewDistance(), getPosition() , color));
    targetWindow.draw(arc);
}

double Animal::getRotation() const
{
    return direction_.angle();
}

void Animal::setRotation(const double& angle )
{
    direction_.x = cos(angle);
    direction_.y= sin(angle);
}

bool Animal::isTargetInSight(const Vec2d& target) const
{
    if(isEqual(distanceTo(target),0 )) return false;
    if ( (target-getPosition()).lengthSquared() <= (getViewDistance()*getViewDistance())) {
        if(direction_.dot((target-getPosition()).normalised()) >= cos((getViewRange()+ANIMAL_VIEW_RANGE_EPSILON)/2)) {
            return true;
        }
    }
    if (isEqual(0,distanceTo(target))) return true;
    return false;
}

Vec2d Animal::randomWalk()
{
    Vec2d random_vec(uniform(-1.0,1.0),uniform(-1.0,1.0));
    current_target_ += random_vec * getRandomWalkJitter()*3;
    current_target_ = current_target_.normalised()*getRandomWalkRadius();
    Vec2d moved_current_target = current_target_ + Vec2d(getRandomWalkDistance(), 0);
    random_walk_target_= ConvertToGlobalCoord(moved_current_target);

    return ConvertToGlobalCoord(moved_current_target)-getPosition();
}

void Animal::drawRandomWalkCircle(sf::RenderTarget& targetWindow) const
{
    if(state_==WANDERING) {
        Vec2d centre(getPosition()+getRandomWalkDistance()*getDirection());
        targetWindow.draw((buildAnnulus( centre, getRandomWalkRadius() , sf::Color(255, 150, 0), 2 )));
        targetWindow.draw(buildCircle(random_walk_target_, 5, sf::Color(0, 0, 255)));
    }
}

Vec2d Animal::getDirection() const
{
    return direction_;
}

Vec2d Animal::ConvertToGlobalCoord( Vec2d vec)
{
    sf::Transform matTransform;
    matTransform.translate(getPosition());
    matTransform.rotate((getRotation())/DEG_TO_RAD);
    Vec2d global = matTransform.transformPoint(vec);
    return global;
}

const bool& Animal::isFemale() const
{
    return is_female_;
}

void Animal::moveToVec2dForce(const sf::Time& dt,const Vec2d& force)
{
    moveToVec2dForce(dt.asSeconds(),force);
}

void Animal::moveToVec2dForce(const double& deltaT,const Vec2d& force)
{
    Vec2d acceleration=force/getMass();
    Vec2d current_velocity = speed_*direction_;
    Vec2d new_velocity= current_velocity+acceleration*deltaT;
    direction_=new_velocity.normalised();
    if (new_velocity.length() > getMaxSpeed()) new_velocity=direction_*getMaxSpeed();
    setPosition(getPosition()+new_velocity*deltaT);
    speed_=new_velocity.length();
}

double Animal::getMaxSpeed() const
{
    double maxSpeed= (double)(getStandardMaxSpeed());
    switch(state_) {
    case FOOD_IN_SIGHT  :
        maxSpeed *=ANIMAL_SPEED_FACTOR_FOOD;
        break;
    case MATE_IN_SIGHT :
        maxSpeed *=ANIMAL_SPEED_FACTOR_MATE;
        break;
    case RUNNING_AWAY :
        maxSpeed *=ANIMAL_SPEED_FACTOR_FLEE;
        break;
    default:
        break;
    }
    if (energy_ <= ANIMAL_LOW_ENERGY_THRESHOLD) maxSpeed *=ANIMAL_LOW_ENERGY_SPEED_FACTOR;
    return maxSpeed;
}

std::string Animal::stateToString() const
{
    std::string stateString;
    switch ( state_)
    {
    case FOOD_IN_SIGHT:
        stateString = "FOOD_IN_SIGHT";
        break;
    case  FEEDING :
        stateString = "FEEDING";
        break;
    case  RUNNING_AWAY :
        stateString = "RUNNING_AWAY";
        break;
    case  MATE_IN_SIGHT :
        stateString = "MATE_IN_SIGHT";
        break;
    case MATING :
        stateString = "MATING";
        break;
    case  GIVING_BIRTH :
        stateString = "GIVING_BIRTH";
        break;
    case   WANDERING :
        stateString = " WANDERING";
        break;
    case BABY:
        stateString= "BABY";
    }
    return stateString;
}

void Animal::updateEnergy( sf::Time dt)
{
    double energyLoss(base_energy_consumption_+ speed_* energy_consumption_factor_* dt.asSeconds());
    OrganicEntity::setEnergy(getEnergy()-energyLoss);
}

void Animal::eat()
{
    if (target_entity_ == nullptr) return;
    setEnergy(getEnergy()+ANIMAL_EATING_EFFICIENCY*target_entity_->getEnergy());
    target_entity_->setEnergy(0);
}

void Animal::analyzeEnvironment()
{
    potential_mates_.clear();
    predators_.clear();
    food_sources_.clear();
    potential_mates_ = mates(getVisibleEntities());
    food_sources_ = filterEdible(getVisibleEntities());
    predators_= filterPredators(getVisibleEntities());
}

std::list<OrganicEntity*> Animal::getVisibleEntities()
{
    return getAppEnv().getEntitiesInSightForAnimal(this);
}

std::list<OrganicEntity*> Animal::filterEdible(const std::list <OrganicEntity*>& entities)
{
    std::list<OrganicEntity*> result;
    if (!entities.empty()) {
        for (const auto& OE : entities) {
            if(eatable(OE)) result.push_back(OE);
        }
    }
    return result;
}

std::list<OrganicEntity*> Animal::mates(const std::list <OrganicEntity*>& entities)
{
    std::list<OrganicEntity*> result;
    if (!entities.empty()) {
        for (const auto& OE : entities) {
            if((matable(OE)) and (OE->matable(this))) result.push_back(OE);
        }
    }
    return result;
}

OrganicEntity* Animal::findClosest(const std::list<OrganicEntity*>& entities) const
{
    OrganicEntity* closest(nullptr);
    if (!entities.empty()) {
        double dmin(std::numeric_limits<double>::max());
        for (const auto& OE : entities) {
            if(distanceTo(OE->getPosition()) <= dmin ) {
                dmin=distanceTo(OE->getPosition());
                closest=OE;
            }
        }
    }
    return closest;
}

std::list<OrganicEntity*> Animal::filterPredators( const std::list<OrganicEntity*>& env)
{
    std::list<OrganicEntity*> predators;
    for (const auto& OE : env ) {
        if (OE->eatable(this))
            predators.push_back(OE);
    }
    return predators;
}

Vec2d Animal::calculateFleeForce( const std::list<OrganicEntity*>& entities )
{
    Vec2d resultForce ;
    double flee_strength(ANIMAL_FLEE_STRENGTH);
    double distance_exponent(ANIMAL_FLEE_DISTANCE_EXPONENT) ;
    for (const auto& OE : entities ) {
        resultForce +=
            ( flee_strength*(OE->getPosition() - getPosition())
              /
              ( pow((OE->getPosition()
                     - getPosition()).length(),distance_exponent))  ) ;
    }
    return -1*resultForce;
}

const bool& Animal::isPregnant() const
{
    return pregnant_;
}

bool Animal::isCollidingWithTarget() const
{
    if (target_entity_ == nullptr) return false;
    return isColliding(CircularCollider(target_entity_->getPosition(),target_entity_->getRadius())) ;
}

const int& Animal::getBabies() const
{
    return babies_;
}

void Animal::setBabies(const int& n)
{
    babies_= n;
}

void Animal::forgetMother()
{
    organic_entity_mum_ = nullptr;
}

void Animal::forgetChild(OrganicEntity* baby)
{
    organic_entity_kids_.remove(baby);
}

void Animal::forgetAll()
{
    if(!organic_entity_kids_.empty()) {
        for (auto& oe: organic_entity_kids_) {
            if(oe != nullptr ) oe->forgetMother();
        }
    }

    if( organic_entity_mum_!= nullptr) {
        organic_entity_mum_->forgetChild(this);
    }
}

void Animal::forgetEntity(OrganicEntity* entity)
{
    if (target_entity_ == entity) {
        target_entity_ = nullptr;
    }
    if (organic_entity_mum_ == entity) {
        organic_entity_mum_ = nullptr;
    }
    food_sources_.remove(entity);
    potential_mates_.remove(entity);
    predators_.remove(entity);
    predators_memory_.remove(entity);
}

int Animal::getState() const
{
    return state_;
}

OrganicEntity* Animal::getClosestEdible() const
{
    if ( !food_sources_.empty()) {
        return findClosest(food_sources_);
    }
    return nullptr;
}