/*
=================
cBall.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cBall.h"
#include "pongGame.h"
void cBall ::render()
{
	glPushMatrix();

	glTranslatef(spritePos2D.x, spritePos2D.y, 0.0f);
	glRotatef(spriteRotation, 0.0f, 0.0f, 1.0f);
	glScalef(spriteScaling.x, spriteScaling.y, 1.0f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, GLTextureID); // Binding of GLtexture name 

	glBegin(GL_QUADS);
	glColor3f(255.0f, 255.0f, 255.0f);
	glTexCoord2f(spriteTexCoordData[0].x, spriteTexCoordData[0].y);
	glVertex2f(-(textureWidth / 2), -(textureHeight / 2));
	glTexCoord2f(spriteTexCoordData[1].x, spriteTexCoordData[1].y);
	glVertex2f((textureWidth / 2), -(textureHeight / 2));
	glTexCoord2f(spriteTexCoordData[2].x, spriteTexCoordData[2].y);
	glVertex2f((textureWidth / 2), (textureHeight / 2));
	glTexCoord2f(spriteTexCoordData[3].x, spriteTexCoordData[3].y);
	glVertex2f(-(textureWidth / 2), (textureHeight / 2));

	glEnd();
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}
/*
=================================================================
Update the sprite position
=================================================================
*/

void cBall::update(float deltaTime)
{

	if (getSpritePos().x + getTextureWidth() >= 1024)													//if the sprite goes out of bounds to the right
	{
		m_SoundMgr->getSnd("Wall")->playAudio(AL_TRUE);
		setSpriteTranslation(glm::vec2(getSpriteTranslation().x*-1, getSpriteTranslation().y));			//reverse the sprite's direction
		spritePos2D -= glm::vec2(10, 0);																//move the sprite back 10 units
		setSpriteRotation(70 - getSpriteRotation());													//set the sprite rotation to reverse
	}

	if (getSpritePos().x <= 0.0f)																		//if the sprite goes out of bounds to the right
	{
		m_SoundMgr->getSnd("Wall")->playAudio(AL_TRUE);
		setSpriteTranslation(glm::vec2(getSpriteTranslation().x*-1, getSpriteTranslation().y));			//reverse the sprite's direction
		spritePos2D += glm::vec2(10, 0);																//move the sprite forward 10 pixels 
		setSpriteRotation(70 - getSpriteRotation());													//set the sprite rotation to reverse
	}

	if (isColliding() == true && topPaddle == true)
	{
		setSpriteTranslation(glm::vec2(getSpriteTranslation().x, getSpriteTranslation().y*-1));			//reverse the sprite's direction
		spritePos2D += glm::vec2(0, 10);																//move the sprite forward 10 pixels 
		setSpriteRotation(180 - getSpriteRotation());													//set the sprite rotation to reverse
		m_SoundMgr->getSnd("Paddle")->playAudio(AL_TRUE);													//play audio for collision
		registerCollision(false);																		//set colliding to false
		topPaddle = false;																				//show that it is no longer colliding
		}

	if (isColliding() == true && bottomPaddle == true)
	{
		setSpriteTranslation(glm::vec2(getSpriteTranslation().x, getSpriteTranslation().y*-1));			//reverse the sprite's direction
		spritePos2D += glm::vec2(0, -10);																//move the sprite forward 10 pixels 
		setSpriteRotation(180 - getSpriteRotation());													//set the sprite rotation to reverse
		m_SoundMgr->getSnd("Paddle")->playAudio(AL_TRUE);													//play audio for collision
		registerCollision(false);																		//set colliding to false
		bottomPaddle = false;
	}


	
	
	spritePos2D += spriteTranslation * deltaTime;

	setBoundingRect(&boundingRect);

}
/*
=================================================================
  Sets the velocity for the Ball
=================================================================
*/
void cBall::setBallVelocity(glm::vec2 ballVel)
{
	ballVelocity = ballVel;
}
/*
=================================================================
  Gets the Ball velocity
=================================================================
*/
glm::vec2 cBall::getBallVelocity()
{
	return ballVelocity;
}
/*
==========================================================================
Use this method to show the collision box.
==========================================================================
*/
void cBall::renderCollisionBox()
{
	glPushMatrix();

	glTranslatef(boundingRect.left, boundingRect.top, 0.0f);
	glRotatef(spriteRotation, 0.0f, 0.0f, 1.0f);
	glScalef(spriteScaling.x, spriteScaling.y, 1.0f);

	glColor3f(255.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);

	glVertex2f(-((boundingRect.right - boundingRect.left) / 2), -((boundingRect.bottom - boundingRect.top) / 2));
	glVertex2f(((boundingRect.right - boundingRect.left) / 2), -((boundingRect.bottom - boundingRect.top) / 2));
	glVertex2f(((boundingRect.right - boundingRect.left) / 2), ((boundingRect.bottom - boundingRect.top) / 2));
	glVertex2f(-((boundingRect.right - boundingRect.left) / 2), ((boundingRect.bottom - boundingRect.top) / 2));

	glEnd();

	glPopMatrix();
}