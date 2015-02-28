//
//  PickMapScrollView.cpp
//  Labyrinth
//
//  Created by shen xinxing on 12/7/13.
//
//

#include "PickMapScrollView.h"

USING_NS_CC;
USING_NS_CC_EXT;

PickMapScrollView* PickMapScrollView::create(Size size, Node* container/* = NULL*/)
{
    PickMapScrollView* pRet = new PickMapScrollView();
    if (pRet && pRet->initWithViewSize(size, container))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

bool PickMapScrollView::initWithViewSize(Size size, Node *container/* = NULL*/)
{
    if(!ScrollView::initWithViewSize(size, container))
    {
        return false;
    }
    
    _isScroll = false;
    
    return true;
}

bool PickMapScrollView::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    return ScrollView::onTouchBegan(touch, event);
}

void PickMapScrollView::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
    ScrollView::onTouchMoved(touch, event);
    
    _isScroll = true;
}

void PickMapScrollView::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    ScrollView::onTouchEnded(touch, event);
    
    if(!_isScroll)
    {
        Node *node = this->getContainer()->getChildByTag(10);
        Point touchPoint = node->convertToNodeSpace(touch->getLocation());
        
        Object *item = NULL;
        
        CCARRAY_FOREACH(node->getChildren(), item)
        {
            Node *nodeChildren = dynamic_cast<Node *>(item);
            
            if(nodeChildren->getBoundingBox().containsPoint(touchPoint))
            {
                _callback(nodeChildren);
                break;
            }
        }
    }
    
    _isScroll = false;
}

void PickMapScrollView::setSelectedCallback(const SelectedCallback &callback)
{
    _callback = callback;
}