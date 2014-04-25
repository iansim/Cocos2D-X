#include "GameScene.h"
#include "MainMenuScene.h"

USING_NS_CC;

CCScene* GameSceneLayer::scene()
{ 
    CCScene *GameScene = CCScene::create(); 
	GameSceneLayer *layer = GameSceneLayer::create();
	GameScene->addChild(layer);

	return GameScene;
}

bool GameSceneLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }

	winSize = CCDirector::sharedDirector()->getWinSize();

	createGameScreen();
	resetGame(); 

	this->scheduleUpdate();

    return true;
}

void GameSceneLayer::resetGame() 
{
	_score = 0;
	
	char szValue[100] = { 0 };
	sprintf(szValue, "%i", (int)_score);
	
	/*	_scoreDisplay->setString(szValue);
	_scoreDisplay->setAnchorPoint(ccp(1, 0));
	_scoreDisplay->setPosition(ccp(_screenSize.width * 0.95f, _screenSize.height * 0.88f));	*/
}

void GameSceneLayer::createGameScreen()
{
	CCSprite* bg1 = CCSprite::create("bg/bg1.png");
	CCSprite* bg2 = CCSprite::create("bg/bg2.png");
	CCSprite* bg3 = CCSprite::create("bg/bg3.png");
	CCSprite* cloud2 = CCSprite::create("sky/w_cloud.png");
	
	CCParallaxNode* paraNode = CCParallaxNode::create();
	paraNode->addChild(bg1, 1, ccp(0.5f, 0), ccp(0, winSize.height / 2));
	paraNode->addChild(cloud2, 2, ccp(0.6f, 0), ccp(0, winSize.height / 2 + 150));
	paraNode->addChild(bg2, 3, ccp(1.5f, 0), ccp(0, winSize.height / 10));
	paraNode->addChild(bg3, 4, ccp(2.0f, 0), ccp(0, winSize.height / 3));
	paraNode->setPosition(ccp(winSize.width, winSize.height / 5));
	this->addChild(paraNode, 0);

	CCMoveBy* move1 = CCMoveBy::create(10.0f, ccp(-winSize.width, 0));
	CCMoveBy* move2 = CCMoveBy::create(0.0f, ccp(winSize.width, 0));
	CCSequence* seq = (CCSequence*)CCSequence::create(move1, move2, NULL);
	CCRepeatForever* repeat = CCRepeatForever::create(seq);

	paraNode->runAction(repeat);

	// Adding Nodes to the scene
	/*CCNode* gameScene = CCNode::create();
	this->addChild(gameScene, 3);*/

	// Create the player from subclass and add it to the playerNode
	CCNode* playerNode = CCNode::create();
	_player = new Player(playerNode);

	this->addChild(playerNode, 1);
}

void GameSceneLayer::btnBackTouched(CCObject* pSender)
{
	//Change director to MainMenuScene with a transition
	CCDirector::sharedDirector()->replaceScene(CCTransitionFlipX::create(1.0f, MainMenuLayer::scene()));
}

void GameSceneLayer::update(float dt) {	

	_player->update(dt);
}