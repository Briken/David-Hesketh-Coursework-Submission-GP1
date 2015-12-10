/*
==================================================================================
asteroidsGame.cpp
==================================================================================
*/

#include "pongGame.h"

vector<cTexture*> theGameTextures;

bool topPaddle = false;					//a variable designed to show which object is the topPaddle for collisions
bool bottomPaddle = false;				//a variable designed to show which object is the bottomPaddle for collisions
