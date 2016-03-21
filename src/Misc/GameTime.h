#pragma once
class GameTime
{
public:
	GameTime();
	~GameTime();

	void start(float elapsedTime);
	void end(float elapsedTime);

	int getFps() const;
	float getDeltaTime() const;

private:
	int m_fps;
	float m_startTime;
	float m_deltaTime;
	int m_frames;
	float m_elapsedTime;
};

