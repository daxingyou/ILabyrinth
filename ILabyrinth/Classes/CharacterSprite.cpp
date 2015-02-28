//
//  CharacterSprite.cpp
//  Labyrinth
//
//  Created by shen xinxing on 12/18/13.
//
//

#include "CharacterSprite.h"

USING_NS_CC;

CharacterSprite* CharacterSprite::createWithSpriteFrameName(const std::string& spriteFrameName)
{
    CharacterSprite* pRet = new CharacterSprite();
    if (pRet && pRet->initWithSpriteFrameName(spriteFrameName))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

bool CharacterSprite::initWithSpriteFrameName(const std::string &spriteFrameName)
{
    if(!Sprite::initWithSpriteFrameName(spriteFrameName))
    {
        return false;
    }
    
    Array *frames = Array::create();
    
    frames->addObject(SpriteFrameCache::getInstance()->getSpriteFrameByName("CH1.png"));
    frames->addObject(SpriteFrameCache::getInstance()->getSpriteFrameByName("CH2.png"));
    frames->addObject(SpriteFrameCache::getInstance()->getSpriteFrameByName("CH3.png"));
    frames->addObject(SpriteFrameCache::getInstance()->getSpriteFrameByName("CH4.png"));
    frames->addObject(SpriteFrameCache::getInstance()->getSpriteFrameByName("CH5.png"));
    frames->addObject(SpriteFrameCache::getInstance()->getSpriteFrameByName("CH6.png"));
    frames->addObject(SpriteFrameCache::getInstance()->getSpriteFrameByName("CH7.png"));
    frames->addObject(SpriteFrameCache::getInstance()->getSpriteFrameByName("CH8.png"));

    AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(frames), "walk");
    
    this->reset();
    
    return true;
}

CharacterSprite::~CharacterSprite()
{
    AnimationCache::getInstance()->removeAnimation("walk");
}

void CharacterSprite::reset()
{
    _frameIndex = 1;
    
    this->setDisplayFrameWithAnimationName("walk", 0);
}

void CharacterSprite::nextFrame()
{
    this->setDisplayFrameWithAnimationName("walk", _frameIndex);
    
    if((++_frameIndex) > 7)
        _frameIndex = 0;
}

Point CharacterSprite::gridPosition()
{
    return Point(this->getPosition().x / TILE_SIZE, this->getPosition().y / TILE_SIZE);
}

void CharacterSprite::setPosition(const cocos2d::Point &pos)
{
    Sprite::setPosition(pos);
    
    if(pos.getDistance(_lastFramePos) >= 2)
    {
        this->nextFrame();
        _lastFramePos = pos;
    }
}

void CharacterSprite::setCharWillBeginWalking(const CharWillBeginWalking &callBack)
{
    _charWillBeginWalking = callBack;
}

void CharacterSprite::setCharDidFinishWalking(const CharDidFinishWalking &callBack)
{
    _charDidFinishWalking = callBack;
}

bool CharacterSprite::isBussy()
{
    return (this->getNumberOfRunningActions() != 0);
}

Point CharacterSprite::lookingAtGridPosition()
{
    Point gridPosition = this->gridPosition();
    
    switch(this->opositeSideOfSide(this->rotationSide()))
    {
        case SideTop:
            gridPosition.y--;
            break;
        case SideRight:
            gridPosition.x--;
            break;
        case SideBottom:
            gridPosition.y++;
            break;
        case SideLeft:
            gridPosition.x++;
            break;
    }
    
    return gridPosition;
}

unsigned int CharacterSprite::opositeSideOfSide(unsigned int side)
{
    switch(side)
    {
        case SideTop:
            return SideBottom;
        case SideRight:
            return SideLeft;
        case SideBottom:
            return SideTop;
        case SideLeft:
            return SideRight;
        default:
            return SideNone;
    }
}

void CharacterSprite::rotateNode(Node *node, unsigned int side)
{
    node->setRotation(side * 90.0);
}

void CharacterSprite::rotateToSide(Side side)
{
    this->rotateNode(this, side);
}

unsigned int CharacterSprite::rotationSide()
{
    return (this->getRotation() / 90.0);
}

void CharacterSprite::walkByPath(unsigned int path)
{
    Point pathPart1(0.0, 0.0);
    Point pathPart2(0.0, 0.0);
    
    int side = -1;
    
    switch(this->opositeSideOfSide(this->rotationSide()))
    {
        case SideTop:
        {
            switch(path)
            {
                case WalkPathToRight:
                    pathPart1.setPoint(0.0, -TILE_SIZE);
                    pathPart2.setPoint(TILE_SIZE, 0);
                    side = SideRight;
                    break;
                case WalkPathToLeft:
                    pathPart1.setPoint(0.0, -TILE_SIZE);
                    pathPart2.setPoint(-TILE_SIZE, 0.0);
                    side = SideLeft;
                    break;
                case WalkPathToBottom:
                    pathPart1.setPoint(0.0, -TILE_SIZE);
                    pathPart2.setPoint(0.0, -TILE_SIZE);
                    side = SideBottom;
                    break;
                case WalkPathWalk:
                    pathPart1.setPoint(0.0, -TILE_SIZE);
                    side = SideBottom;
                    break;
            }
        }
            break;
        case SideBottom:
        {
            switch(path)
            {
                case WalkPathToRight:
                    pathPart1.setPoint(0.0, TILE_SIZE);
                    pathPart2.setPoint(TILE_SIZE, 0.0);
                    side = SideRight;
                    break;
                case WalkPathToLeft:
                    pathPart1.setPoint(0.0, TILE_SIZE);
                    pathPart2.setPoint(-TILE_SIZE, 0.0);
                    side = SideLeft;
                    break;
                case WalkPathToTop:
                    pathPart1.setPoint(0.0, TILE_SIZE);
                    pathPart2.setPoint(0.0, TILE_SIZE);
                    side = SideTop;
                    break;
                case WalkPathWalk:
                    pathPart1.setPoint(0.0, TILE_SIZE);
                    side = SideTop;
                    break;
            }
        }
            break;
        case SideLeft:
        {
            switch(path)
            {
                case WalkPathToRight:
                    pathPart1.setPoint(TILE_SIZE, 0.0);
                    pathPart2.setPoint(TILE_SIZE, 0.0);
                    side = SideRight;
                    break;
                case WalkPathToTop:
                    pathPart1.setPoint(TILE_SIZE, 0.0);
                    pathPart2.setPoint(0.0, TILE_SIZE);
                    side = SideTop;
                    break;
                case WalkPathToBottom:
                    pathPart1.setPoint(TILE_SIZE, 0.0);
                    pathPart2.setPoint(0.0, -TILE_SIZE);
                    side = SideBottom;
                    break;
                case WalkPathWalk:
                    pathPart1.setPoint(TILE_SIZE, 0.0);
                    side = SideRight;
                    break;
            }
        }
            break;
        case SideRight:
        {
            switch(path)
            {
                case WalkPathToLeft:
                    pathPart1.setPoint(-TILE_SIZE, 0.0);
                    pathPart2.setPoint(-TILE_SIZE, 0.0);
                    side = SideLeft;
                    break;
                case WalkPathToTop:
                    pathPart1.setPoint(-TILE_SIZE, 0.0);
                    pathPart2.setPoint(0.0, TILE_SIZE);
                    side = SideTop;
                    break;
                case WalkPathToBottom:
                    pathPart1.setPoint(-TILE_SIZE, 0.0);
                    pathPart2.setPoint(0.0, -TILE_SIZE);
                    side = SideBottom;
                    break;
                case WalkPathWalk:
                    pathPart1.setPoint(-TILE_SIZE, 0.0);
                    side = SideLeft;
                    break;
            }
        }
            break;
    }
    
    if((pathPart2.x == 0.0) && (pathPart2.y == 0.0))
    {
        this->runAction(Sequence::create(CallFuncN::create(_charWillBeginWalking),
                                         MoveBy::create(0.5f, pathPart1),
                                         CallFunc::create(CC_CALLBACK_0(CharacterSprite::reset, this)),
                                         CallFuncN::create(_charDidFinishWalking),
                                         NULL));
    }
    else
    {
        this->runAction(Sequence::create(CallFuncN::create(_charWillBeginWalking),
                                         MoveBy::create(0.5f, pathPart1),
                                         CallFuncN::create(CC_CALLBACK_1(CharacterSprite::rotateNode, this, side)),
                                         MoveBy::create(0.5, pathPart2),
                                         CallFunc::create(CC_CALLBACK_0(CharacterSprite::reset, this)),
                                         CallFuncN::create(_charDidFinishWalking),
                                         NULL));
    }
}

