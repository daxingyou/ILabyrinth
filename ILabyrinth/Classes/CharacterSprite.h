//
//  CharacterSprite.h
//  Labyrinth
//
//  Created by shen xinxing on 12/18/13.
//
//

#ifndef __Labyrinth__CharacterSprite__
#define __Labyrinth__CharacterSprite__

#include <iostream>
#include "cocos2d.h"
#include "GameMacro.h"

typedef std::function<void(cocos2d::Node*)> CharWillBeginWalking;
typedef std::function<void(cocos2d::Node*)> CharDidFinishWalking;

class CharacterSprite : public cocos2d::Sprite
{
public:
    static CharacterSprite* createWithSpriteFrameName(const std::string& spriteFrameName);
    ~CharacterSprite();
    virtual void setPosition(const cocos2d::Point& pos);
    
    unsigned int opositeSideOfSide(unsigned int side);
    void rotateToSide(Side side);
    void rotateNode(cocos2d::Node *node, unsigned int side);
    unsigned int rotationSide();
    void walkByPath(unsigned int path);
    cocos2d::Point gridPosition();
    cocos2d::Point lookingAtGridPosition();
    bool isBussy();
    
    void setCharWillBeginWalking(const CharWillBeginWalking &callBack);
    void setCharDidFinishWalking(const CharDidFinishWalking &callBack);
    
private:
    bool initWithSpriteFrameName(const std::string& spriteFrameName);
    void reset();
    void nextFrame();
    
private:
    unsigned int _frameIndex;
    
    CharWillBeginWalking _charWillBeginWalking;
    CharDidFinishWalking _charDidFinishWalking;
    
    cocos2d::Point _lastFramePos;
};
#endif /* defined(__Labyrinth__CharacterSprite__) */
