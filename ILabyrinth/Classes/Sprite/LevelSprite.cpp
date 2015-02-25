//
//  LevelSprite.cpp
//  Labyrinth
//
//  Created by shen xinxing on 12/10/13.
//
//

#include "LevelSprite.h"

USING_NS_CC;
USING_NS_CC_EXT;

LevelSprite::LevelSprite()
:_levelLabel(NULL), _lockSprite(NULL)
{
    
}

LevelSprite::~LevelSprite()
{
    CC_SAFE_RELEASE_NULL(_levelLabel);
    CC_SAFE_RELEASE_NULL(_lockSprite);
}

SEL_MenuHandler LevelSprite::onResolveCCBCCMenuItemSelector(Object * pTarget, const char * pSelectorName) {
    return NULL;
}

Control::Handler LevelSprite::onResolveCCBCCControlSelector(Object * pTarget, const char * pSelectorName) {
    return NULL;
}


SEL_CallFuncN LevelSprite::onResolveCCBCCCallFuncSelector(Object * pTarget, const char* pSelectorName)
{
    return NULL;
}

bool LevelSprite::onAssignCCBMemberVariable(Object * pTarget, const char * pMemberVariableName, Node * pNode) {
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "lockSprite", Sprite *, _lockSprite);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "levelLabel", LabelTTF *, _levelLabel);

    return false;
}

void LevelSprite::onEnterTransitionDidFinish()

{
    Sprite::onEnterTransitionDidFinish();
}

void LevelSprite::setLevelText(unsigned int level)
{
    _levelLabel->setString(String::createWithFormat("%d", level)->getCString());
}

void LevelSprite::hidenLock()
{
    _lockSprite->removeFromParentAndCleanup(true);
}