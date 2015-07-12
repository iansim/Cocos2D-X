#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{

    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
{

    if ( !Layer::init() ) { return false; }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    
    auto bg = Sprite::create("touchgfx/bg.png");
    bg->setAnchorPoint(Point(0.5f, 0.5f));
    bg->setPosition(Point(visibleSize.width /2 +25, visibleSize.height /2 -50));
    this->addChild(bg,0);
    
    auto cclogo = Sprite::create("touchgfx/cclogo.png");
    cclogo->setPosition(Point(visibleSize.width/2, visibleSize.height /2));
    this->addChild(cclogo, 2);
    cclogo->setName("cclogo"); //set a tag to access it globaly
    
   // MoveBy *move_right = MoveBy::create(2, Point(50, 0));
   // MoveBy *move_left = MoveBy::create(2, Point(-50, 0));
    
  //  cclogo->runAction(RepeatForever::create(Sequence::create(move_right, move_left,nullptr)));
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(HelloWorld::onTouchCancelled, this);
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    isTouchDown = false;
    
    initialTouchPos[0] = 0;
    initialTouchPos[1] = 0;
   
    this->scheduleUpdate();
    
    return true;
}

void HelloWorld::update(float dt)
{
    if (true == isTouchDown)
    {
        auto icoTouch = Sprite::create("touchgfx/touch.png");
        icoTouch->setPosition(Point(currentTouchPos[0], currentTouchPos[1]));
        this->addChild(icoTouch,1);
        icoTouch->setTag(25);
        
        FadeOut* fadeOut = FadeOut::create(0.5f);
        
        auto removeIt = CallFunc::create([icoTouch]() {
            icoTouch->removeFromParent();
        });
        
        icoTouch->runAction(Sequence::create(fadeOut, removeIt, nullptr));
       
        
        if (initialTouchPos[0] - currentTouchPos[0] > visibleSize.width * 0.05)
        {
            CCLOG("SWIPED LEFT");
            MoveBy *move_left = MoveBy::create(2, Point(-50, 0));  // create move left action
            this->getChildByName("cclogo")->runAction(move_left); // calling cclogo sprite by name and run action
            isTouchDown = false;
           
        }
        else if (initialTouchPos[0] - currentTouchPos[0] < - visibleSize.width * 0.08)
        {
            CCLOG("SWIPED RIGHT");
            MoveBy *move_right = MoveBy::create(2, Point(50, 0)); // create move right action
            this->getChildByName("cclogo")->runAction(move_right); // calling cclogo sprite by name
            isTouchDown = false;
            
        }
        else if (initialTouchPos[1] - currentTouchPos[1] > visibleSize.width * 0.05)
        {
            CCLOG("SWIPED DOWN");
            MoveBy *move_down = MoveBy::create(2, Point(0, -50)); // create move down action
            this->getChildByName("cclogo")->runAction(move_down); // calling cclogo sprite by name
            isTouchDown = false;
            
        }
        else if (initialTouchPos[1] - currentTouchPos[1] < - visibleSize.width * 0.05)
        {
            CCLOG("SWIPED UP");
            MoveBy *move_down = MoveBy::create(2, Point(0, 50));  // create move up action
            this->getChildByName("cclogo")->runAction(move_down); // calling cclogo sprite by name
            isTouchDown = false;
        }
        
    }
  
}


bool HelloWorld::onTouchBegan(Touch *touch, Event *event)
{
    initialTouchPos[0] = touch->getLocation().x;
    initialTouchPos[1] = touch->getLocation().y;
    currentTouchPos[0] = touch->getLocation().x;
    currentTouchPos[1] = touch->getLocation().y;
    
    isTouchDown = true;
    
    CCLOG("onTouchBegan ID: %d, X: %f, Y: %f", touch->getID(), touch->getLocation().x, touch->getLocation().y);
    
    return true;
}

void HelloWorld::onTouchMoved(Touch *touch, Event *event)
{
    currentTouchPos[0] = touch->getLocation().x;
    currentTouchPos[1] = touch->getLocation().y;
    
   
}

void HelloWorld::onTouchEnded(Touch *touch, Event *event)
{
    isTouchDown = false;
}

void HelloWorld::onTouchCancelled(Touch *touch, Event *event)
{
    onTouchEnded(touch, event);
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
