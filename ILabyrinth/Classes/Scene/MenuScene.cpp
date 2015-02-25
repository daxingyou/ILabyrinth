//
//  MenuScene.cpp
//  Labyrinth
//
//  Created by shen xinxing on 13-12-2.
//
//

#include "MenuScene.h"
#include "GameMacro.h"
#include "PickMapScene.h"

USING_NS_CC;
USING_NS_CC_EXT;
USING_NS_CC_BUILDER;

MenuScene::MenuScene()
{
    
}

MenuScene::~MenuScene()
{
    
}

SEL_MenuHandler MenuScene::onResolveCCBCCMenuItemSelector(Object * pTarget, const char * pSelectorName) {
    
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "playAction", MenuScene::playAction);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "helpAction", MenuScene::helpAction);

    return NULL;
}

Control::Handler MenuScene::onResolveCCBCCControlSelector(Object * pTarget, const char * pSelectorName) {
    return NULL;
}


SEL_CallFuncN MenuScene::onResolveCCBCCCallFuncSelector(Object * pTarget, const char* pSelectorName)
{
    return NULL;
}

bool MenuScene::onAssignCCBMemberVariable(Object * pTarget, const char * pMemberVariableName, Node * pNode) {
    
    
    return false;
}

void MenuScene::playAction(Object *sender)
{
    Director::getInstance()->replaceScene(PickMapScene::createScene());
}

void MenuScene::helpAction(cocos2d::Object *sender)
{
    
}

void MenuScene::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
}


