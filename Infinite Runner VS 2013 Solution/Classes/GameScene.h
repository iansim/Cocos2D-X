#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Player.h"


class GameSceneLayer : public cocos2d::CCLayer
{
private:
	CCSize winSize;
	
	Player* _player;
	
	CCSprite* _bg1; 
	CCSprite* _repeatbg1; 

	CCSprite* cloud;
	CCArray * _clouds;

	CCSpriteBatchNode* _gameBatchNode;

public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
	
	void resetGame();
	void createGameScreen();
	
	void update(float dt);


	float _score;

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
	void btnBackTouched(CCObject* pSender);
    
    // implement the "static node()" method manually
	CREATE_FUNC(GameSceneLayer);
};

#endif // __GAME_SCENE_H__
