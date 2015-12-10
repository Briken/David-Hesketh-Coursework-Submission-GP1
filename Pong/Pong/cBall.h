/*
=================
cBall.h
- Header file for class definition - SPECIFICATION
- Header file for the Ball class which is a child of cSprite class
=================
*/
#ifndef _CBALL_H
#define _CBALL_H
#include "cSprite.h"


class cBall : public cSprite
{
private:
	glm::vec2 ballVelocity = glm::vec2(0.0f, 0.0f);

public:
	//cBall(vector<cTexture*> tileTextList)

	void render();		// Default render function
	void update(float deltaTime);		// Ball update method
	void setBallVelocity(glm::vec2 ballVel);   // Sets the velocity for the Ball
	glm::vec2 getBallVelocity();				 // Gets the Ball velocity
	void renderCollisionBox();				// Use this function to show the collision box
};
#endif