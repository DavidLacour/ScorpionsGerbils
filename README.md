# ScorpionGerbil

A real-time 2D predator-prey ecosystem simulation built with C++11 and SFML. Scorpions hunt gerbils, gerbils forage for food, and both species reproduce and evolve their populations over time. The simulation includes two modes: a macro-level ecosystem view and a micro-level neuronal sensing model.

![Simulation screenshot](screenshot.png)

## Prerequisites

- **C++11** compatible compiler (g++ on Linux, clang++ on macOS)
- **SFML 2.x** (Graphics, System, Window modules)
- **SCons** build system

### Installing dependencies (Ubuntu/Debian)

```bash
sudo apt install scons libsfml-dev g++
```

## Build & Run

From the `normal/` directory:

```bash
scons application-run
```

To build with debug symbols:

```bash
scons debug=1 application-run
```

To use a custom config file:

```bash
scons --cfg=path/to/config.json application-run
```

The binary is built to `normal/build/application`.

## Simulation Modes

Toggle between modes with **Tab**.

### PPS Mode (Prey-Predator Simulation)

Macro-level ecosystem simulation with gerbils (prey), scorpions (predators), food sources, and environmental obstacles.

- Gerbils wander, forage for food, flee from scorpions, and reproduce
- Scorpions hunt gerbils using a 360-degree field of view
- Animals bounce off rock obstacles
- Population stats are tracked on a live auto-scaling graph

### Neuronal Mode

Micro-level simulation focused on scorpion sensory mechanics. Scorpions emit mechanical waves through the environment to detect prey, simulating substrate-borne vibration sensing.

- Waves propagate outward with energy dissipating exponentially
- Obstacles create shadow zones behind them
- Neuronal scorpions process sensor activations to locate prey

## Controls

### PPS Mode

| Key | Action |
|-----|--------|
| G | Add a gerbil at mouse position |
| Ctrl+X | Add a male gerbil |
| S | Add a scorpion at mouse position |
| Ctrl+Y | Add a male scorpion |
| F | Add food at mouse position |
| O | Add a rock at mouse position |
| Q | Add a food generator |
| A | Remove a food generator |

### Neuronal Mode

| Key | Action |
|-----|--------|
| N | Add a neuronal scorpion at mouse position |
| W | Add a wave gerbil at mouse position |

### General

| Key | Action |
|-----|--------|
| Tab | Switch between PPS / Neuronal mode |
| R | Reset the simulation |
| D | Toggle debug mode |
| C | Reload config file |
| Z | Zoom |
| Arrow keys | Pan view |
| Space | Pause |
| Esc | Exit |

## Configuration

All simulation parameters are configurable via `normal/res/app.json`, including:

- Animal stats (speed, energy, size, longevity, reproduction)
- Sensory parameters (view range, view distance, wave propagation)
- World size and rendering settings
- Food generation rates

## Project Structure

```
normal/src/
├── Animal/                  # Animal behavior and AI
│   ├── NeuronalScorpion/    # Neural-based scorpion with wave sensors
│   ├── Animal.hpp/cpp       # Base animal class (state machine, movement)
│   ├── Gerbil.hpp/cpp       # Prey species
│   ├── Scorpion.hpp/cpp     # Predator species
│   └── ChasingAutomaton.hpp/cpp  # Steering behaviors
├── Environment/             # World and entity management
│   ├── Environment.hpp/cpp  # Main simulation environment
│   ├── OrganicEntity.hpp/cpp # Base class for living entities
│   ├── Food.hpp/cpp         # Food resource
│   ├── FoodGenerator.hpp/cpp # Periodic food spawner
│   └── Wave.hpp/cpp         # Sensory wave propagation
├── Obstacle/                # Environmental obstacles
│   ├── CircularCollider.hpp/cpp # Circle-based collision detection
│   └── Rock.hpp/cpp         # Rock obstacles
├── Stats/                   # Live statistics and graphs
│   ├── Graph.hpp/cpp        # Auto-scaling population graph
│   └── Stats.hpp/cpp        # Stats management
├── Utility/                 # Helpers
│   ├── Vec2d.hpp/cpp        # 2D vector math
│   ├── Constants.hpp        # Named constants
│   └── Utility.hpp/cpp      # Drawing and math utilities
├── Random/                  # Random number distributions
├── JSON/                    # JSON config parser
├── Interface/               # Updatable / Drawable interfaces
├── Tests/                   # Unit tests (Catch) and graphical tests
├── Application.hpp/cpp      # Core application loop
└── FinalApplication.hpp/cpp # Main entry point
```

## Architecture

The simulation is built around a few core abstractions:

- **CircularCollider** - Base for all positioned, collidable objects
- **OrganicEntity** - Extends collider with energy, age, and lifecycle (food, animals)
- **Animal** - State machine governing behavior: `WANDERING`, `FOOD_IN_SIGHT`, `FEEDING`, `RUNNING_AWAY`, `MATE_IN_SIGHT`, `MATING`, `GIVING_BIRTH`, `BABY`
- **Environment** - Manages all entities, handles updates, death, and spatial queries
- **Wave** - Propagating sensory wave with arc-based obstacle occlusion

Entity interactions use double dispatch (e.g. `eatable()` / `eatableDispatch()`) to resolve type-specific behavior between scorpions, gerbils, and food.

## Credits

Originally developed for the INFOSV course (2012-2019) by Marco Antognini & Jamila Sam.
