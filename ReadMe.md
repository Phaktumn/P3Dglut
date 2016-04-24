# Universe Simulator

Universe Simulator is a openGL program that simulates the solar system.

  - Scaled Distances
  - Scaled Size

### Version
Alpha 0.1.0

### How To Use

Create a Solar System
```sh
SolarSystem(const std::string& _name);
```
Solar System constructer

Add a solar system:
```sh
universe->add_SolarSystem(SolarSystem* _Solar_System, vec::Vector3* position)
```

Add Planets to solar system's
```sh
void addPlanet_to_SolarSystem(const std::string& _solarSistemName, Planet* _planetToAdd) const

universe->addPlanet_to_SolarSystem("Solar System",		new Planet("Textures/mercury.bmp", "Mercurio",   88.0f    * Time_scale,	   58.0       * Time_scale,	  EC_MERCURY, vec::Vector3(0, 0, 57910000   * Universal_Metric_Scale),  4878.0f * Universal_Size_Scale, 32.0f,  0.0f));
```

Add Comets
```sh
void add_Comet_to_SolarSystem(const std::string& solaSystem_name, Comet* _comet)
```

Find a planet in a Solar System
```sh
SolarSystem::findPlanetByName(const std::string& planetName)
```
You can't search for a specific Planet in the Universe. Use the Solar System var and then select the planet using it's name.

Add Moon´s and Rings
```sh
void Planet::addMoon(float distanceToPlantet, float radius)
void Planet::addRings(float innerRadius, float outterRadius)
```
With the selected planet we can add moon´s adn Rings
