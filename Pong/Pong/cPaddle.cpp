/*
=================
cPaddle.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cPaddle.h"

void cPaddle::render()
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

void cPaddle::update(float deltaTime)
{
	if (isTopPaddle == true)
	{
		if (m_InputMgr->isKeyDown(VK_RIGHT))											// if the right arrow is pressed
		{
			spritePos2D = (glm::vec2(spritePos2D.x + 7, spritePos2D.y));				// move the sprite 7 pixels right
		}
		if (m_InputMgr->isKeyDown(VK_LEFT))												// if the left arrow is pressed
		{
			spritePos2D = (glm::vec2(spritePos2D.x - 7, spritePos2D.y));				// move the sprite 7 pixels left
		}
	}
	if (isBottomPaddle == true && getSpritePos().x > 0.0f)
	{
		if (m_InputMgr->isKeyDown(int('A')))											// if the A button is pressed
		{
			spritePos2D = (glm::vec2(spritePos2D.x - 7, spritePos2D.y));				// move the sprite 7 pixels left
		}
		if (m_InputMgr->isKeyDown(int('D')))											// if the D button is pressed
		{
			spritePos2D = (glm::vec2(spritePos2D.x + 7, spritePos2D.y));				// move the sprite 7 pixels right
		}
	}

	if (spriteRotation > 360)
	{
		spriteRotation -= 360.0f;
	}

	glm::vec2 spriteVelocityAdd = glm::vec2(0.0f, 0.0f);
	spriteVelocityAdd.x = (glm::sin(glm::radians(spriteRotation)));
	spriteVelocityAdd.y = -(glm::cos(glm::radians(spriteRotation)));

	spriteVelocityAdd += spriteTranslation;

	paddleVelocity += spriteVelocityAdd;

	paddleVelocity *= 0.0;

	setBoundingRect(&boundingRect);
	}
	/*
	=================================================================
	Sets the velocity for the paddle
	=================================================================
	*/
	void cPaddle::setPaddleVelocity(glm::vec2 paddleVel)
	{
		paddleVelocity = paddleVel;
	}
	/*
	=================================================================
	Gets the paddle velocity
	=================================================================
	*/
	glm::vec2 cPaddle::getPaddleVelocity()
	{
		return paddleVelocity;
	}

