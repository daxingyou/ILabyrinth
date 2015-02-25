//
//  PickMapScrollView.h
//  Labyrinth
//
//  Created by shen xinxing on 12/7/13.
//
//

#ifndef __Labyrinth__PickMapScrollView__
#define __Labyrinth__PickMapScrollView__

#include <iostream>
#include "cocos2d.h"
#include "extensions/cocos-ext.h"

typedef std::function<void(cocos2d::Node*)> SelectedCallback;

class PickMapScrollView : public cocos2d::extension::ScrollView
{
public:
    static PickMapScrollView* create(cocos2d::Size size, Node* container = NULL);

    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
    
    void setSelectedCallback(const SelectedCallback &callback);

private:
    bool initWithViewSize(cocos2d::Size size, Node* container = NULL);
    
private:
    bool _isScroll;
    SelectedCallback _callback;
};

#endif /* defined(__Labyrinth__PickMapScrollView__) */
