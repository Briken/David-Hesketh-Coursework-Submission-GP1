#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#define GLX_GLXEXT_LEGACY //Must be declared so that our local glxext.h is picked up, rather than the system one


#include <windows.h>
#include "windowOGL.h"
#include "GameConstants.h"
#include "cWNDManager.h"
#include "cInputMgr.h"
#include "cSoundMgr.h"
#include "cFontMgr.h"
#include "cSprite.h"
#include "pongGame.h"
#include "cButton.h"
#include <sstream>

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR cmdLine,
	int cmdShow)
{

	//Set our window settings
	const int windowWidth = 1024;
	const int windowHeight = 768;
	const int windowBPP = 16;



	//This is our window
	static cWNDManager* pgmWNDMgr = cWNDManager::getInstance();

	// This is the input manager
	static cInputMgr* theInputMgr = cInputMgr::getInstance();

	// This is the sound manager
	static cSoundMgr* theSoundMgr = cSoundMgr::getInstance();

	// This is the Font manager
	static cFontMgr* theFontMgr = cFontMgr::getInstance();

	//The example OpenGL code
	windowOGL theOGLWnd;

	//Attach our the OpenGL window
	pgmWNDMgr->attachOGLWnd(&theOGLWnd);

	// Attach the keyboard manager
	pgmWNDMgr->attachInputMgr(theInputMgr);

	//Attempt to create the window
	if (!pgmWNDMgr->createWND(windowWidth, windowHeight, windowBPP))
	{
		//If it fails

		MessageBox(NULL, "Unable to create the OpenGL Window", "An error occurred", MB_ICONERROR | MB_OK);
		pgmWNDMgr->destroyWND(); //Reset the display and exit
		return 1;
	}

	if (!theOGLWnd.initOGL(windowWidth, windowHeight)) //Initialize our example
	{
		MessageBox(NULL, "Could not initialize the application", "An error occurred", MB_ICONERROR | MB_OK);
		pgmWNDMgr->destroyWND(); //Reset the display and exit
		return 1;
	}

	/* initialize random seed: */
	srand((unsigned int)time(NULL));

	// Create vector array of textures
	vector<cTexture*> textureBkgList;
	LPCSTR bkgTexturesToUse[] = { "Images/pongCourt1024x768.png", "Images/pongStart.png", "Images/pongEnd.png" };
	for (int tCount = 0; tCount < 3; tCount++)
	{
		textureBkgList.push_back(new cTexture());
		textureBkgList[tCount]->createTexture(bkgTexturesToUse[tCount]);
	}

	cTexture transSprite;
	transSprite.createTexture("Images/blank.png");

	cBkGround spriteBkgd;
	spriteBkgd.setSpritePos(glm::vec2(0.0f, 0.0f));
	spriteBkgd.setTexture(textureBkgList[0]->getTexture());
	spriteBkgd.setTextureDimensions(textureBkgList[0]->getTWidth(), textureBkgList[0]->getTHeight());

	cBkGround spriteStartBkgd;
	spriteStartBkgd.setSpritePos(glm::vec2(0.0f, 0.0f));
	spriteStartBkgd.setTexture(textureBkgList[1]->getTexture());
	spriteStartBkgd.setTextureDimensions(textureBkgList[1]->getTWidth(), textureBkgList[1]->getTHeight());

	cBkGround spriteEndBkgd;
	spriteEndBkgd.setSpritePos(glm::vec2(0.0f, 0.0f));
	spriteEndBkgd.setTexture(textureBkgList[2]->getTexture());
	spriteEndBkgd.setTextureDimensions(textureBkgList[2]->getTWidth(), textureBkgList[2]->getTHeight());

	// load game sounds
	// Load Sound
	LPCSTR gameSounds[3] = {"Audio/paddleHit.wav", "Audio/wallHit.wav", "Audio/Guile's theme extended.wav" };

	theSoundMgr->add("Theme", gameSounds[2]);
	theSoundMgr->add("Paddle", gameSounds[0]);
	theSoundMgr->add("Wall", gameSounds[1]);
	//theSoungMgr->add("GameTheme", gameSounds[3]);

	// load game fontss
	// Load Fonts
	LPCSTR gameFonts[2] = { "Fonts/digital-7.ttf", "Fonts/space age.ttf" };

	theFontMgr->addFont("SevenSeg", gameFonts[0], 24);
	theFontMgr->addFont("Space", gameFonts[1], 24);


	cTexture textureBkgd;
	textureBkgd.createTexture("Images\\pongCourt1024x768.png");
	
	cTexture paddleTxt;
	paddleTxt.createTexture("Images\\paddleSprite.png");

	cTexture ballTxt;																	//initialize the ball's texture
	ballTxt.createTexture("Images\\ball.png");										//assign the texture at ball.png to ballTxt

	cBall ballSprite;																	//initialize the ball class
	ballSprite.setBall(true);															// set ballsprite to the ball
	ballSprite.setSpritePos(glm::vec2(700.0f, 500.0f));									//set the ball sprite's position to the centre of the screen
	ballSprite.setTexture(ballTxt.getTexture());										//set the ball's texture to ballTxt
	ballSprite.setTextureDimensions(ballTxt.getTWidth(), ballTxt.getTHeight());			//set the dimensions of the texture
	ballSprite.setSpriteCentre();														//set the centre of the sprite
	ballSprite.setBallVelocity(glm::vec2(1.0f, 1.0f));								// set ball velocity
	ballSprite.setSpriteTranslation(glm::vec2(100.0f, -100.0f));							// set the degree of momvement for the ball
	ballSprite.setSpriteRotation(45.0f);												//set the starting rotation for the ball
	ballSprite.attachSoundMgr(theSoundMgr);												// attach the sound manager to the ball

	cPaddle paddleSprite1;
	paddleSprite1.setTopPaddle(true);													// set paddlesprite1 to the top paddle
	paddleSprite1.attachInputMgr(theInputMgr);											// Attach the input manager to the sprite
	paddleSprite1.setSpritePos(glm::vec2(512.0f, 85.0f));								// set the position of paddleSprite1
	paddleSprite1.setTexture(paddleTxt.getTexture());									// set the texture of paddleSprite1
	paddleSprite1.setTextureDimensions(paddleTxt.getTWidth(), paddleTxt.getTHeight());	// set the size of the texture
	paddleSprite1.setSpriteCentre();													// set the centre of the sprite

	cPaddle paddleSprite2;
	paddleSprite2.setBottomPaddle(true);												// set paddlesprite2 to the bottom paddle
	paddleSprite2.attachInputMgr(theInputMgr);											// Attach the input manager to the sprite
	paddleSprite2.setSpritePos(glm::vec2(512.0f, 683.0f));								// set the position of paddleSprite1
	paddleSprite2.setTexture(paddleTxt.getTexture());									// set the texture of paddleSprite1
	paddleSprite2.setTextureDimensions(paddleTxt.getTWidth(), paddleTxt.getTHeight());	// set the size of the texture
	paddleSprite2.setSpriteCentre();													// set the centre of the sprite

	// Create vector array of button textures
	vector<cTexture*> btnTextureList;
	LPCSTR btnTexturesToUse[] = { "Images/Buttons/exitBtn.png", "Images/Buttons/playBtn.png" };
	for (int tCount = 0; tCount < 2; tCount++)
	{
		btnTextureList.push_back(new cTexture());
		btnTextureList[tCount]->createTexture(btnTexturesToUse[tCount]);
	}
	cButton exitButton;
	exitButton.attachInputMgr(theInputMgr);
	exitButton.setTexture(btnTextureList[0]->getTexture());
	exitButton.setTextureDimensions(btnTextureList[0]->getTWidth(), btnTextureList[0]->getTHeight());

	cButton playButton;
	playButton.attachInputMgr(theInputMgr);
	playButton.setTexture(btnTextureList[1]->getTexture());
	playButton.setTextureDimensions(btnTextureList[1]->getTWidth(), btnTextureList[1]->getTHeight());

	string outputMsg;
	string strMsg[] = { "Welcome To Pong", "Left and Right Arrows Control The top Paddle", "A and D buttons control the bottom paddle", "Thanks for playing!", "See you again soon!" };

	// Attach sound manager to paddle sprite
	paddleSprite1.attachSoundMgr(theSoundMgr);
	paddleSprite2.attachSoundMgr(theSoundMgr);

	gameState theGameState = MENU;
	btnTypes theBtnType = EXIT;
	theSoundMgr->getSnd("Theme")->playAudio(AL_TRUE);

	//This is the mainloop, we render frames until isRunning returns false
	while (pgmWNDMgr->isWNDRunning())
	{
		pgmWNDMgr->processWNDEvents(); //Process any window events

		//We get the time that passed since the last frame
		float elapsedTime = pgmWNDMgr->getElapsedSeconds();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		stringstream points1;											//initialize the stringstream points1
		points1<< paddleSprite1.getPoints();							//set points1 to the return value of getpoints
		string topPoints = points1.str();								//initialize a string variable that equals the string componant of points1

		stringstream points2;											//initialize the stringstream points2
		points2 << paddleSprite2.getPoints();							//set points2 to the return value of getpoints
		string bottomPoints = points2.str();							//initialize a string variable that equals the string componant of points2

		switch (theGameState)
		{
		case MENU:
			spriteStartBkgd.render();

			playButton.setSpritePos(glm::vec2(400.0f, 300.0f));
			exitButton.setSpritePos(glm::vec2(400.0f, 375.0f));
			playButton.render();
			exitButton.render();

			theGameState = playButton.update(theGameState, PLAYING);
			exitButton.update();


			outputMsg = strMsg[2];
			theFontMgr->getFont("Space")->printText(outputMsg.c_str(), FTPoint(10, 15, 0.0f));
			outputMsg = strMsg[0];
			theFontMgr->getFont("Space")->printText(outputMsg.c_str(), FTPoint(100, 100, 0.0f));
			outputMsg = strMsg[1];
			theFontMgr->getFont("Space")->printText(outputMsg.c_str(), FTPoint(100, 150, 0.0f));
			if (exitButton.getClicked())
			{
				SendMessage(pgmWNDMgr->getWNDHandle(), WM_CLOSE, NULL, NULL);
			}
			break;
		case PLAYING:
			spriteBkgd.render();

			paddleSprite1.render();
			paddleSprite2.render();
			ballSprite.render();

			exitButton.setSpritePos(glm::vec2(740.0f, 575.0f));
			exitButton.render();
			theGameState = exitButton.update(theGameState, END);

			paddleSprite1.update(elapsedTime);
			paddleSprite2.update(elapsedTime);
			ballSprite.update(elapsedTime);

			

			if (ballSprite.collidedWith(ballSprite.getBoundingRect(), paddleSprite1.getBoundingRect()) == true)
			{
				ballSprite.registerCollision(true);									//set colliding to true
				ballSprite.setSpriteTranslation(glm::vec2((ballSprite.getSpriteTranslation().x + 50), ballSprite.getSpriteTranslation().y + 50)); // increases the speed of the ball after collision
				topPaddle = true;													// show that ball is colliding with the top paddle
			}

			if (ballSprite.collidedWith(ballSprite.getBoundingRect(), paddleSprite2.getBoundingRect()) == true)
			{
				ballSprite.registerCollision(true);																	//set colliding to true
				ballSprite.setSpriteTranslation(glm::vec2((ballSprite.getSpriteTranslation().x + 50), ballSprite.getSpriteTranslation().y + 50)); // increases the speed of the ball after collision
				bottomPaddle = true;												// show that ball is colliding with the bottom paddle
			}

			if (ballSprite.getSpritePos().y > paddleSprite2.getSpritePos().y)		// check if the ball is below player2
			{
				paddleSprite1.setPoints(paddleSprite1.getPoints() + 1);				// increment player1's points
				ballSprite.setSpritePos(glm::vec2(700.0f, 500.0f));					// move the ball back to centre
			}

			if (ballSprite.getSpritePos().y < paddleSprite1.getSpritePos().y)		// check if the ball is above player1
			{
				paddleSprite2.setPoints(paddleSprite2.getPoints() + 1);				// increment player2's points
				ballSprite.setSpritePos(glm::vec2(700.0f, 500.0f));					// move the ball back to centre
			}

			paddleSprite1.render();
			paddleSprite2.render();
			ballSprite.render();

			

			outputMsg = strMsg[2];
			theFontMgr->getFont("Space")->printText(topPoints.c_str(), FTPoint(530, -65, 0.0f));			//Print player1's points
			theFontMgr->getFont("Space")->printText(bottomPoints.c_str(), FTPoint(500, -65, 0.0f));			//Print player2's points

			break;
		case END:
			spriteEndBkgd.render();

			playButton.setClicked(false);
			exitButton.setClicked(false);

			playButton.setSpritePos(glm::vec2(400.0f, 300.0f));
			exitButton.setSpritePos(glm::vec2(400.0f, 375.0f));
			playButton.render();
			exitButton.render();

			theGameState = playButton.update(theGameState, PLAYING);
			exitButton.update();
			if (exitButton.getClicked())
			{
				SendMessage(pgmWNDMgr->getWNDHandle(), WM_CLOSE, NULL, NULL);
			}
			
			std::string points1 = "Player 1 points " + topPoints;					//create a concatenated string to store the top players points for printing
			std::string points2 = "Player 2 points " + bottomPoints;				//create a concatendted string to store the bottom players points for printing

			theFontMgr->getFont("Space")->printText(points1.c_str() , FTPoint(0.0f, 16.0f, 0.0f));	//print the top players points
			theFontMgr->getFont("Space")->printText(points2.c_str(), FTPoint(0.0f, -1.0f, 0.0f));	//print the bottom Players points

		}
		pgmWNDMgr->swapBuffers();
	}
	theOGLWnd.shutdown(); //Free any resources
	pgmWNDMgr->destroyWND(); //Destroy the program window

	return 0; //Return success
}