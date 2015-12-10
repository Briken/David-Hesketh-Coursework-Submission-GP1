/*
=================
cPaddle.h
- Header file for class definition - SPECIFICATION
- Header file for the Paddle class which is a child of cSprite class
=================
*/
#ifndef _CPADDLE_H
#define _CPADDLE_H
#include "cSprite.h"

class cPaddle : public cSprite
{
private:
	glm::vec2 paddleVelocity = glm::vec2(0.0f, 0.0f);

public:
	void render();		// Default render function
	void update(float deltaTime);		// Paddle update method
	void setPaddleVelocity(glm::vec2 paddleVel);   // Sets the velocity for the paddle
	glm::vec2 getPaddleVelocity();				 // Gets the paddle velocity
	
	float getTextureheight(float tHeight)
	{
		tHeight = textureHeight;
		return textureHeight;
	}
};
#endif