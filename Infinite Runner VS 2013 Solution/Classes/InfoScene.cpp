#include "InfoScene.h"
#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
USING_NS_CC_EXT;

CCSprite* _menuBackground3;
CCMenuItemImage* _btnBack;
CCMenu* _optionsMenu;

CCScene* InfoLayer::scene()
{ 
    CCScene *OptionsScene = CCScene::create(); 
	InfoLayer *layer = InfoLayer::create();
	OptionsScene->addChild(layer);

	return OptionsScene;
}

bool InfoLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin(); 
	
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();


	/*
	if (!CCNode::create()) { return false; }
	CCNode* rootSceneNode;
	SceneReader* sceneReader = SceneReader::sharedSceneReader();
	rootSceneNode = sceneReader->createNodeWithSceneFile("FightScene.json");
	if (rootSceneNode == NULL) { return false; }
	this->addChild(rootSceneNode);
	*/

    return true;
}

void InfoLayer::btnBackTouched(CCObject* pSender)
{
	//Change director to MainMenuScene with a transition
	CCDirector::sharedDirector()->replaceScene(CCTransitionFlipX::create(1.0f, MainMenuLayer::scene()));
}