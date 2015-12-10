#ifndef _ASTEROIDSGAME_H
#define _ASTEROIDSGAME_H

//Game headers
#include "cPaddle.h"
#include "cBall.h"
#include "cBkGround.h"

extern vector<cTexture*> theGameTextures;
extern bool topPaddle;						//a variable designed to show which object is the topPaddle for collisions
extern bool bottomPaddle;					//a variable designed to show which object is the bottomPaddle for collisions
#endif