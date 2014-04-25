#include "Player.h"

Player::Player(CCNode* playerNode):CCObject()
{
	this->playerNode = playerNode;
	
	_hPlayer = CCSprite::create("ninja/run/ninja-run-1.png");
	_hPlayer->setPosition(ccp(150, 180));
	
	playerNode->addChild(_hPlayer, 3);

	currentState = RUNNING;
	newState = RUNNING;

	updateAnimation();
}

void Player::updateAnimation()
{
	switch (currentState)
	{
	case IDLE:
		_hPlayer = CCSprite::create("ninja/run/ninja-run-1.png");
		break;	

	case RUNNING:
		// Frame Animation 
		CCAnimation *animation = CCAnimation::create();

		// load image file from local file system to CCSpriteFrame, then add into CCAnimation
		for (int i = 1; i < 7; i++)
		{
			char szImageFileName[128] = { 0 };
			sprintf(szImageFileName, "ninja/run/ninja-run-%d.png", i);
			animation->addSpriteFrameWithFileName(szImageFileName);
		}

		animation->setLoops(-1); // infinite loop animation
		animation->setDelayPerUnit(0.1f); //Duration per frame
		animation->setRestoreOriginalFrame(true);

		CCAnimate *action3 = CCAnimate::create(animation);

		_hPlayer->runAction(action3);
		break;	
	}
}

void Player::updateMovement()
{
	/*CCPoint oldPos = playerNode->getPosition();
	if (currentState == RUNNING)
	{
		playerNode->setPosition(oldPos.x + 1 * RUNNING_SPEED, oldPos.y);
	}*/
}

void Player::update(float dt)
{
	updateMovement();
}