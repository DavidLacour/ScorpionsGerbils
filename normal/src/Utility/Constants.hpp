/*
 * prjsv 2016
 * Marco Antognini
 */

#ifndef INFOSV_CONSTANTS_HPP
#define INFOSV_CONSTANTS_HPP

#include <string>

// Numerical constants
double const DEG_TO_RAD = 0.0174532925; ///< Degree to Radian conversion constant
double const TAU = 6.283185307;         ///< TAU constant (= 2 * PI)
double const PI = 3.141592654;          ///< PI constant
double const EPSILON = 1e-8;            ///< a small epsilon value


// Ad'hoc constants
// Chasing Automaton
double const CHASING_AUTOMATON_MAX_SPEED = 80;
double const CHASING_AUTOMATON_MASS = 1;
double const CHASING_AUTOMATON_RADIUS = 20;
std::string const GHOST_TEXTURE = "ghost.1.png";
// Animal
double const ANIMAL_MAX_SPEED = 80;
double const ANIMAL_MASS = 1;
double const ANIMAL_RADIUS = 20;
double const ANIMAL_VIEW_RANGE = 60 * DEG_TO_RAD;
double const ANIMAL_VIEW_DISTANCE = 300;
std::string const ANIMAL_TEXTURE = "scorpion.png";
/// Random walk jitter
double const ANIMAL_RANDOM_WALK_JITTER = 10;

/// Random walk radius
double const ANIMAL_RANDOM_WALK_RADIUS = 50;

/// Random walk distance
double const ANIMAL_RANDOM_WALK_DISTANCE = 160;

// Animal behavior constants
double const ANIMAL_EATING_EFFICIENCY = 0.7;
double const ANIMAL_DECELERATION = 0.6;
double const ANIMAL_FEEDING_SPEED_FACTOR = 0.9;
double const ANIMAL_SPEED_FACTOR_FOOD = 3.0;
double const ANIMAL_SPEED_FACTOR_MATE = 2.0;
double const ANIMAL_SPEED_FACTOR_FLEE = 4.0;
double const ANIMAL_LOW_ENERGY_THRESHOLD = 50.0;
double const ANIMAL_LOW_ENERGY_SPEED_FACTOR = 0.5;
double const ANIMAL_FLEE_STRENGTH = 500.0;
double const ANIMAL_FLEE_DISTANCE_EXPONENT = 1.2;
double const ANIMAL_BABY_SIZE_FACTOR = 3.0;
double const ANIMAL_SPRITE_SIZE_FACTOR = 2.1;
double const ANIMAL_VIEW_RANGE_EPSILON = 0.001;
// Stats titles
namespace s
{

std::string const PPS = "Predator Prey Simulation";
std::string const NEURONAL = "Neuronal Simulation";
std::string const GENERAL = "General";
std::string const TEST    = "Test";
std::string const SCORPIONS = "Scorpions";
std::string const GERBILS   = "Gerbils";
std::string const FOOD  = "Food sources";
std::string const WAVES  = "Waves";
std::string const ROCKS  = "Rocks";
} // s



#endif // INFOSV_CONSTANTS_HPP
