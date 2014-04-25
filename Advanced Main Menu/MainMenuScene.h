#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include "cocos2d.h"
#include "Player.h"


USING_NS_CC;

class MainMenuLayer : public cocos2d::CCLayer
{
private:
	CCSprite* _spacebg1;
	CCSprite* _spacebg2;
	CCSprite* _logotype;	

	CCMenuItemImage* _btnNewGame;
	CCMenuItemImage* _btnInfo;
	CCMenuItemImage* _btnSoundOn;
	CCMenuItemImage* _btnSoundOff;
	CCMenuItemImage* _btnMusicOn;
	CCMenuItemImage* _btnMusicOff;

	CCMenuItemToggle* _btnToggleSound;
	CCMenuItemToggle* _btnToggleMusic;

	CCMenu* _mainMenu;
	CCMenu* _settingsMenu;
	CCMenu* _closeMenu;
	
	CCLabelAtlas* _numberLabel;

	int x = 1;
	char buffer[33];
	
	void soundMainMenu();
	void animateMainMenu();
	
	void counterUp();
	void update(float dt);

public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // selector callbacks
    void menuCloseCallback(CCObject* pSender);
	void menuOptionsCallback(CCObject* pSender);
	void settingsToggleMusic(CCObject* pSender);
	void settingsToggleSound(CCObject* pSender);
	void switchToInfoScene(CCObject* pSender);
    
    // implement the "static node()" method manually
	CREATE_FUNC(MainMenuLayer);
};

#endif // __MAINMENU_SCENE_H__
