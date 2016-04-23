#include "GameTime.h"

GameTime::GameTime() : m_fps(0), m_startTime(0), m_deltaTime(0),
	m_frames(0), m_elapsedTime(0) {

}

GameTime::~GameTime() {

}

void GameTime::start(float elapsedTime) {
	m_startTime = elapsedTime;
}

void GameTime::end(float elapsedTime) {
	m_deltaTime = elapsedTime - m_startTime;
	m_elapsedTime += m_deltaTime;
	if (m_elapsedTime < 1.0f) {
		m_frames++;
	}
	else {
		m_fps = m_frames;
		m_frames = 0;
		m_elapsedTime = 0;
	}
}

int GameTime::getFps() const
{
	return m_fps;
}
float GameTime::getDeltaTime() const
{
	return m_deltaTime;
}
