#pragma once
#include "Camera.h"

class MultiPurposeCamera :
	public Camera
{
public:
	explicit MultiPurposeCamera(Player& player);
	~MultiPurposeCamera();

	void Update(float deltaTime) override;
	void Draw() const override;
};

