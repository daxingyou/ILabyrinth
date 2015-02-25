//
//  GameScene.h
//  Labyrinth
//
//  Created by shen xinxing on 12/16/13.
//
//

#ifndef __Labyrinth__GameScene__
#define __Labyrinth__GameScene__

#include <iostream>
#include "cocos2d.h"
#include "Vector.h"

class CharacterSprite;

class GameScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    ~GameScene();
    // a selector callback
    void menuCloseCallback(Object* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
    
    void loadMap(unsigned int mapID);
    
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    
    virtual void onEnterTransitionDidFinish();
    
private:
    void backAction(cocos2d::Object *sender);
    void addTileWithData(cocos2d::Array *data, unsigned int x, unsigned int y);
    void setPath(cocos2d::Sprite *path, unsigned int side, unsigned int x, unsigned int y);
    
    void charWillBeginWalking(cocos2d::Node *node);
    void charDidFinishWalking(cocos2d::Node *node);
    
    void rotateChar();
    void rotateExit();
    
    void passLabyrunth();
    
private:
    cocos2d::Dictionary *_mapTiles;
    cocos2d::SpriteBatchNode *_mainLayer;
    Vector<Vector<Vector<int>>> _map;
    cocos2d::Sprite *_exit;
    CharacterSprite *_character;

};

#endif /* defined(__Labyrinth__GameScene__) */
