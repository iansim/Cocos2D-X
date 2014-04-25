#include "MainMenuScene.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace CocosDenshion;

CCScene* MainMenuLayer::scene()
{ 
    CCScene *scene = CCScene::create();  
	MainMenuLayer *layer = MainMenuLayer::create();
    scene->addChild(layer);

    return scene;
}

bool MainMenuLayer::init()
{
    if ( !CCLayer::init() )
    {
		// setTouchEnabled(true);
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	// Create the sprites
	_spacebg1 = CCSprite::create("mm-gfx/bg-mm2.png");
	_logotype = CCSprite::create("mm-gfx/logo.png");
	
	// Main Menu Items
	_btnNewGame = CCMenuItemImage::create("mm-gfx/shuriken.png", "mm-gfx/shuriken.png", this, menu_selector(MainMenuLayer::switchToInfoScene));
	 
	// Settings Menu Items	
	_btnInfo = CCMenuItemImage::create("mm-gfx/btn-info.png", "mm-gfx/btn-info-sel.png", this, menu_selector(MainMenuLayer::switchToInfoScene));

	_btnSoundOn = CCMenuItemImage::create("mm-gfx/btn-sound-on-sel.png", "mm-gfx/btn-sound-on-sel.png", this, NULL);
	_btnSoundOff = CCMenuItemImage::create("mm-gfx/btn-sound-on.png", "mm-gfx/btn-sound-on.png", this, NULL);
	
	_btnMusicOn = CCMenuItemImage::create("mm-gfx/btn-music-on-sel.png", "mm-gfx/btn-music-on-sel.png", this, NULL);
	_btnMusicOff = CCMenuItemImage::create("mm-gfx/btn-music-on.png", "mm-gfx/btn-music-on.png", this, NULL);

	_btnToggleSound = CCMenuItemToggle::createWithTarget(this, menu_selector(MainMenuLayer::settingsToggleSound), _btnSoundOn, _btnSoundOff, NULL);
	_btnToggleMusic = CCMenuItemToggle::createWithTarget(this, menu_selector(MainMenuLayer::settingsToggleMusic), _btnMusicOff, _btnMusicOn, NULL);

    // Position the sprites
	_spacebg1->setPosition(ccp(winSize.width / 2 + origin.x, winSize.height / 2 + origin.y));
	_logotype->setPosition(ccp(winSize.width / 2 + origin.x, winSize.height ));	

	// Position the main menu items inside each CCMenu
	//_btnNewGame->setPosition(ccp(0, 0));
	_btnToggleSound->setPosition(ccp(0, 54));
	_btnToggleMusic->setPosition(ccp(0, 174));
	_btnInfo->setPosition(ccp(0, 294));

	// Create the main menu
	_mainMenu = CCMenu::create(_btnNewGame, NULL);
	_mainMenu->setPosition((ccp(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y)));
	this->addChild(_mainMenu, 1); 

	// Create the settings menu
	_settingsMenu = CCMenu::create(_btnToggleSound, _btnToggleMusic, _btnInfo, NULL);
	_settingsMenu->setPosition(CCPointZero);
	this->addChild(_settingsMenu, 1);
	
	// Create a label atlas for numbers
	_numberLabel = CCLabelAtlas::create("0123456789", "fontatlas/n8.png", 32, 46, '0');		
	_numberLabel->setPosition(ccp(winSize.width / 2 + origin.x - 50, winSize.height - 150));
	this->addChild(_numberLabel, 1);	

    // Add sprites to layers
	this->addChild(_spacebg1, 0);	
	this->addChild(_logotype, 1);
	
	soundMainMenu();
	animateMainMenu();	
	
	// Call game logic about every second
	//this->schedule(schedule_selector(MainMenuLayer::update), 1.0);

	this->scheduleUpdate();

    return true;
}

void MainMenuLayer::soundMainMenu()
{
	// Preloading menu sound effects
	SimpleAudioEngine::sharedEngine()->preloadEffect("sounds/btn-push.mp3");
	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1.0);
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.3f);

	// Playing background music	
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sounds/bg-mm.mp3", true);

	// Set index for selected state
	if (SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying()) { _btnToggleMusic->setSelectedIndex(1); }
	else { _btnToggleMusic->setSelectedIndex(0); }
}

void MainMenuLayer::animateMainMenu()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCMoveBy* logoSlideDown = CCMoveBy::create(0.5, ccp(0, -80));
	CCMoveBy* btn1SlideFromLeft = CCMoveBy::create(0.5, ccp(65, 0));
	CCMoveBy* btn2SlideFromLeft = CCMoveBy::create(1, ccp(65, 0));
	CCMoveBy* btn3SlideFromLeft = CCMoveBy::create(1.5, ccp(65, 0));

	CCMoveBy* ninjamove = CCMoveBy::create(7, ccp(winSize.width, 0));
	CCActionInterval* moveReverse = ninjamove->reverse();

	CCRepeatForever* fadeInOutForever = CCRepeatForever::create(CCSequence::create(CCFadeIn::create(1), CCFadeOut::create(1), NULL));
	CCRepeatForever* shurikenRotation = CCRepeatForever::create(CCRotateBy::create(1.0f, 10.0f));

	_logotype->runAction(CCRepeat::create(logoSlideDown, 1));
	_btnInfo->runAction(btn1SlideFromLeft);
	_btnToggleMusic->runAction(btn2SlideFromLeft);
	_btnToggleSound->runAction(btn3SlideFromLeft);

	//_btnInfo->runAction(fadeInOutForever);	
	_btnNewGame->runAction(shurikenRotation);
}


void MainMenuLayer::menuOptionsCallback(CCObject* pSender)
{
	//Change director to OptionsScene
	//CCDirector::sharedDirector()->replaceScene(OptionsLayer::scene());
	CCDirector::sharedDirector()->replaceScene(CCTransitionFadeTR::create(1.0f, GameSceneLayer::scene()));
}

void MainMenuLayer::switchToInfoScene(CCObject* pSender)
{
	//Play the btn push sound
	SimpleAudioEngine::sharedEngine()->playEffect("sounds/btn-push.mp3");

	//Pause background music first, then resume in the next scene
	SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();

	//Change director to Info Scene
	CCDirector::sharedDirector()->replaceScene(CCTransitionFadeTR::create(1.0f, GameSceneLayer::scene()));
}

void MainMenuLayer::settingsToggleMusic(CCObject* pSender)
{
	//Play the btn push sound
	SimpleAudioEngine::sharedEngine()->playEffect("sounds/btn-push.mp3");

	CCMenuItemToggle* temp = (CCMenuItemToggle*)pSender;
	if (temp->getSelectedIndex() == 0)
	{	
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	}
	if (temp->getSelectedIndex() == 1)
	{	
		SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	}
}

void MainMenuLayer::settingsToggleSound(CCObject* pSender)
{
	//Play the btn push sound
	SimpleAudioEngine::sharedEngine()->playEffect("sounds/btn-push.mp3");
} 

void MainMenuLayer::counterUp(){
	if (x < 555) { x++; }
	if (x >= 555) { x = 555;  }

	//Convert integer to string via _itoa
	_itoa(x, buffer, 10);
	_numberLabel->setString(buffer);
}

void MainMenuLayer::update(float dt) {
	counterUp();
	//_player->update(dt);
}

void MainMenuLayer::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}