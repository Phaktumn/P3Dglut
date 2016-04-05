#pragma once
#include "C:\Users\Jorge-Programar\Documents\GitHub\P3Dglut\src\Main\Camera\Camera.h"

class MultyPurposeCamera :
	public Camera
{
public:
	explicit MultyPurposeCamera(Player& player);
	~MultyPurposeCamera();

	void Update(float deltaTime) override;
	void Draw() const override;
};

