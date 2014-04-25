#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"

USING_NS_CC;

#define RUNNING_SPEED 2
#define ACCELERATION 0.05

enum PlayerState {
	IDLE = 0,
	RUNNING,
	SHURIKEN	
};

class Player : public CCObject
{
	CCNode* playerNode;
	CCSprite* _hPlayer;

	PlayerState currentState;
	PlayerState newState;

public:
	Player(CCNode* node);	
	void update(float dt);
	void updateAnimation();
	void updateMovement();
};

#endif // __PLAYER_H__