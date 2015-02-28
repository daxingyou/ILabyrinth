//
//  PickMapScene.cpp
//  Labyrinth
//
//  Created by shen xinxing on 12/6/13.
//
//

#include "PickMapScene.h"
#include "GameMacro.h"
#include "VisibleRect.h"
#include "PickMapLayer.h"
#include "PickMapLayerLoader.h"
#include "PickMapScrollView.h"
#include "MenuScene.h"
#include "MenuSceneLoader.h"
#include "AppDelegate.h"
#include "GameScene.h"

USING_NS_CC;
USING_NS_CC_BUILDER;

Scene* PickMapScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = PickMapScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool PickMapScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Sprite *background = Sprite::createWithSpriteFrameName("sand.png");
    background->setPosition(VisibleRect::center());
    this->addChild(background, 1);
    
    PickMapScrollView *scrollView = PickMapScrollView::create(this->getContentSize());
    scrollView->setPosition(VisibleRect::leftBottom());
    scrollView->setDirection(cocos2d::extension::ScrollView::Direction::VERTICAL);
    scrollView->setContentSize(Size(480.0, 640.0));
    scrollView->setContentOffset(Point(0,scrollView->minContainerOffset().y));
    scrollView->setSelectedCallback(CC_CALLBACK_1(PickMapScene::selectedAction, this));
    //scrollView->setContentOffset(Point(0.0, 320.0));
    this->addChild(scrollView, 1);
    
    PickMapLayer *pickMapLayer = NULL;
    
    NODE_CREATE_BY_CCB_START("PickMapLayer", PickMapLayerLoader::loader(), "PickMapLayer.ccbi", PickMapLayer *, pickMapLayer);
    pickMapLayer->setPosition(Point(0.0, 320.0));
    pickMapLayer->setTag(10);
    scrollView->getContainer()->addChild(pickMapLayer);
    NODE_CREATE_BY_CCB_END
    
    return true;
}

void PickMapScene::selectedAction(cocos2d::Node *node)
{
    //CCLOG("tag = %d", node->getTag());
    
    unsigned int nodeTag = node->getTag();
    
    if(nodeTag > 0)
    {
        if(nodeTag == 100)
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
        else
        {
            if(nodeTag <= appDelegate->getLevel())
            {
                GameScene *gameScene = GameScene::create();
                gameScene->loadMap(nodeTag);
                Scene *scene = Scene::create();
                scene->addChild(gameScene);
                Director::getInstance()->replaceScene(scene);
            }
        }
    }
}