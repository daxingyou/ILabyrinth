//
//  GameEndScene.cpp
//  Labyrinth
//
//  Created by shen xinxing on 12/20/13.
//
//

#include "GameEndScene.h"
#include "VisibleRect.h"
#include "MenuScene.h"
#include "MenuSceneLoader.h"
#include "GameMacro.h"

USING_NS_CC;
USING_NS_CC_BUILDER;

Scene* GameEndScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameEndScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool GameEndScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size winSize = Director::getInstance()->getWinSize();
    
    Sprite *background = Sprite::createWithSpriteFrameName("sand.png");
    background->setPosition(VisibleRect::center());
    this->addChild(background, 1);
    
    Sprite *endSprite = Sprite::createWithSpriteFrameName("end.png");
    endSprite->setPosition(VisibleRect::center());
    this->addChild(endSprite, 2);
    
    LabelTTF *textLabel = LabelTTF::create("Congratulations!", "MarkerFelt-Thin", 46, Size(winSize.width, winSize.height), TextHAlignment::CENTER);
    textLabel->setPosition(Point(VisibleRect::center().x, VisibleRect::center().y - 50.0));
    textLabel->setColor(Color3B(60, 29, 3));
    textLabel->setOpacity(200);
    this->addChild(textLabel, 3);
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    
    touchListener->onTouchBegan = CC_CALLBACK_2(GameEndScene::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GameEndScene::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GameEndScene::onTouchEnded, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(GameEndScene::onTouchCancelled, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    return true;
}

bool GameEndScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    CC_UNUSED_PARAM(touch);
    CC_UNUSED_PARAM(event);
    return true;
}

void GameEndScene::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
    CC_UNUSED_PARAM(touch);
    CC_UNUSED_PARAM(event);
}

void GameEndScene::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event)
{
    CC_UNUSED_PARAM(touch);
    CC_UNUSED_PARAM(event);
}

void GameEndScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    MenuScene *menuScene = NULL;
    
    NODE_CREATE_BY_CCB_START("MenuScene", MenuSceneLoader::loader(), "MenuScene.ccbi", MenuScene *, menuScene);
    
    // create a scene. it's an autorelease object
    auto scene = Scene::create();
    scene->addChild(menuScene);
    
    // run
    Director::getInstance()->replaceScene(scene);
    NODE_CREATE_BY_CCB_END
}