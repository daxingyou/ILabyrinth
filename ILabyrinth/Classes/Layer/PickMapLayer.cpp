//
//  PickMapLayer.cpp
//  Labyrinth
//
//  Created by shen xinxing on 12/6/13.
//
//

#include "PickMapLayer.h"
#include "LevelSprite.h"
#include "LevelSpriteLoader.h"
#include "GameMacro.h"
#include "AppDelegate.h"
#include "VisibleRect.h"

USING_NS_CC;
USING_NS_CC_EXT;
USING_NS_CC_BUILDER;

PickMapLayer::PickMapLayer()
{
    
}

PickMapLayer::~PickMapLayer()
{
    
}

SEL_MenuHandler PickMapLayer::onResolveCCBCCMenuItemSelector(Object * pTarget, const char * pSelectorName) {
    return NULL;
}

Control::Handler PickMapLayer::onResolveCCBCCControlSelector(Object * pTarget, const char * pSelectorName) {
    return NULL;
}


SEL_CallFuncN PickMapLayer::onResolveCCBCCCallFuncSelector(Object * pTarget, const char* pSelectorName)
{
    return NULL;
}

bool PickMapLayer::onAssignCCBMemberVariable(Object * pTarget, const char * pMemberVariableName, Node * pNode) {
    
    
    return false;
}

void PickMapLayer::onEnterTransitionDidFinish()

{
    Layer::onEnterTransitionDidFinish();
    
    Array *positions = Array::createWithContentsOfFile("map_postion.plist");
    
    Object *item = NULL;
    unsigned int i = 1;
    
    CCARRAY_FOREACH(positions, item)
    {
        Dictionary *position = dynamic_cast<Dictionary *>(item);
        
        LevelSprite *sprite = NULL;
        
        NODE_CREATE_BY_CCB_START("LevelSprite", LevelSpriteLoader::loader(), "LevelSprite.ccbi", LevelSprite *, sprite);
        
        sprite->setPosition(Point(position->valueForKey("x")->floatValue(), position->valueForKey("y")->floatValue()));
        sprite->setTag(i);
        
        if(i <= appDelegate->getLevel())
        {
            sprite->setDisplayFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("map.png"));
            sprite->setLevelText(i);
            sprite->hidenLock();
        }
        
        this->addChild(sprite, 10);
        i++;
    }
    
    Sprite *backSprite = Sprite::createWithSpriteFrameName("back2.png");
    backSprite->setPosition(Point(VisibleRect::rightTop().x - 25.0, VisibleRect::rightTop().y - 25.0));
    backSprite->setTag(100);
    this->addChild(backSprite, 10);
    
}
