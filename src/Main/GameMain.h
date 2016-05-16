#pragma once

namespace MainGame
{	
	/*
	Game Initialize Method
	*/
	inline void Initialize()
	{
		glShadeModel(GL_SMOOTH);						   // Enable Smooth Shading
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		glDepthFunc(GL_LEQUAL);							   // The Type Of Depth Testing To Do				
		glEnable(GL_DEPTH_TEST);						   // Enables Depth Testing						  
		glEnable(GL_COLOR_MATERIAL);					   // Enable Material Coloring
		glEnable(GL_BLEND);
		glEnable(GL_LINE_SMOOTH);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		Lightning::enableLight();		//enables all lights properties positional light
	}

	/*
	Game Load Method
	*/
	inline void Load()
	{
	
	}

	/*
	Game Update Method
	*/
	inline void Update()
	{

	}
	
	/*
	Game Draw Method
	*/
	inline void Draw()
	{
	
	
	}
}