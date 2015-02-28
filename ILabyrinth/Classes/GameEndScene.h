//
//  GameEndScene.h
//  Labyrinth
//
//  Created by shen xinxing on 12/20/13.
//
//

#ifndef __Labyrinth__GameEndScene__
#define __Labyrinth__GameEndScene__

#include <iostream>
#include "cocos2d.h"

class GameEndScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
        
    // implement the "static create()" method manually
    CREATE_FUNC(GameEndScene);
    
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    
private:
    void selectedAction(cocos2d::Node *node);
    
};

#endif /* defined(__Labyrinth__GameEndScene__) */
