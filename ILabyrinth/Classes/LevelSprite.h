//
//  LevelSprite.h
//  Labyrinth
//
//  Created by shen xinxing on 12/10/13.
//
//

#ifndef __Labyrinth__LevelSprite__
#define __Labyrinth__LevelSprite__

#include <iostream>
#include "cocos2d.h"
#include "cocosbuilder/CocosBuilder.h"

class LevelSprite : public cocos2d::Sprite, public cocosbuilder::CCBSelectorResolver, public cocosbuilder::CCBMemberVariableAssigner
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(LevelSprite, create);

    LevelSprite();
    virtual ~LevelSprite();
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::Object * pTarget, const char * pSelectorName);
    virtual cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(cocos2d::Object * pTarget, const char * pSelectorName);
    virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector(cocos2d::Object * pTarget, const char* pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::Object * pTarget, const char * pMemberVariableName, cocos2d::Node * pNode);
    
    virtual void onEnterTransitionDidFinish();
    
    void setLevelText(unsigned int level);
    void hidenLock();
    
private:
    cocos2d::LabelTTF *_levelLabel;
    cocos2d::Sprite *_lockSprite;
};

#endif /* defined(__Labyrinth__LevelSprite__) */
