//
//  PickMapScene.h
//  Labyrinth
//
//  Created by shen xinxing on 12/6/13.
//
//

#ifndef __Labyrinth__PickMapScene__
#define __Labyrinth__PickMapScene__

#include <iostream>
#include "cocos2d.h"

class PickMapScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
        
    // implement the "static create()" method manually
    CREATE_FUNC(PickMapScene);
    
private:
    void selectedAction(cocos2d::Node *node);

};

#endif /* defined(__Labyrinth__PickMapScene__) */
