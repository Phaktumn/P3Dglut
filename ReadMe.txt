	m_Planets.push_back(new Planet("Textures/mercury.bmp", 
		"Mercurio", 88.0f, 58.0f,EC_MERCURY, vec::Vector3(0, 0, 70), 0.3f));

	m_Planets.push_back(new Planet(std::string("Textures/earth.bmp"), 
		"Venus", 225.0f, 241.0f,EC_VENUS, vec::Vector3(0, 0, 108), 0.4f));

	m_Planets.push_back(new Planet(std::string("Textures/earth.bmp"),	
	"Earth", 365.0f, 1.0f, EC_EARTH, vec::Vector3(0, 0, 150), 1.0f));

	m_Planets.push_back(new Planet(std::string("Textures/mars.bmp"),
		"Mars", 687.0f, 1.01f,EC_MARS, vec::Vector3(0, 0, 228), 0.9f));

	m_Planets.push_back(new Planet(std::string("Textures/jupiter.bmp"),
		"Jupiter", 4332.0f, 9.8 / 24.0, EC_JUPITER, vec::Vector3(0, 0, 772), 11.5f));

	m_Planets.push_back(new Planet(std::string("Textures/saturn.bmp"),
		"Saturn", 10760.0f, 10.5 / 24.0, EC_SATURN,vec::Vector3(0, 0, 1443), 9.5f));

	m_Planets.push_back(new Planet(std::string("Textures/uranus.bmp"),
		"Uranus", 30700.0f, 17.0 / 24.0, EC_URANUS,vec::Vector3(0, 0, 2871), 9.5f));

	m_Planets.push_back(new Planet(std::string("Textures/neptune.bmp"),
		"Neptune", 60200.0f, 16.0 / 24.0, EC_NEPTUNE,vec::Vector3(0, 0, 4504), 9.5f));

	m_Planets.push_back(new Planet(std::string("Textures/neptune.bmp"),
		"Pluto", 90600.0f,EC_PLUTO, 0.6f, vec::Vector3(0, 0, 5913), 9.5f));