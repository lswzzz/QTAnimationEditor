#include "HelloWorldScene.h"
#include "DrawLayer.h"
#include "Global.h"
USING_NS_CC;

static LayerColor* layerColor = NULL;
static HelloWorld* instance = NULL;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
	layerColor = LayerColor::create(Color4B(0, 0, 0, 255), 9999, 9999);
	layerColor->setGlobalZOrder(layerColorGlobalZ);
	scene->addChild(layerColor, -1);

    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

	instance = layer;
    // add layer as a child to scene
    scene->addChild(layer);
	scene->setAnchorPoint(ccp(0.5, 0.5));
    // return the scene
    return scene;
}

HelloWorld*  HelloWorld::getInstance()
{
	return instance;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	DrawLayer * layer = DrawLayer::createLayer();
	this->addChild(layer, 100);
	
    return true;
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

void HelloWorld::setLayerColor(Color3B b)
{
	layerColor->setColor(b);
}