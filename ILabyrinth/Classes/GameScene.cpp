//
//  GameScene.cpp
//  Labyrinth
//
//  Created by shen xinxing on 12/16/13.
//
//

#include "GameScene.h"
#include "VisibleRect.h"
#include "PickMapScene.h"
#include "GameMacro.h"
#include "CharacterSprite.h"
#include "AppDelegate.h"
#include "PickMapScene.h"
#include "GameEndScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool GameScene::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    _mapTiles = Dictionary::create();
    _mapTiles->retain();
    
    _mainLayer = SpriteBatchNode::create("sprites.png");
    _mainLayer->getTexture()->setAliasTexParameters();
    this->addChild(_mainLayer, 1);
    
    MenuItemImage *backItemImage = MenuItemImage::create("", "", CC_CALLBACK_1(GameScene::backAction, this));
    backItemImage->setPosition(Point(VisibleRect::rightTop().x - 25.0, VisibleRect::rightTop().y - 25.0));
    backItemImage->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("back.png"));
    backItemImage->setSelectedSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("back.png"));
    
    Menu *menu = Menu::create(backItemImage, NULL);
    menu->setPosition(VisibleRect::leftBottom());
    this->addChild(menu, 2);
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    
    touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(GameScene::onTouchCancelled, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    return true;
}

GameScene::~GameScene()
{
    _mapTiles->release();
}

void GameScene::backAction(cocos2d::Object *sender)
{
    Director::getInstance()->replaceScene(PickMapScene::createScene());
}

void GameScene::loadMap(unsigned int mapID)
{
    Sprite *background = Sprite::createWithSpriteFrameName("sand.png");
    background->setPosition(VisibleRect::center());
    _mainLayer->cocos2d::Node::addChild(background);
    
    _character = CharacterSprite::createWithSpriteFrameName("CH1.png");
    _character->setCharWillBeginWalking(CC_CALLBACK_1(GameScene::charWillBeginWalking, this));
    _character->setCharDidFinishWalking(CC_CALLBACK_1(GameScene::charDidFinishWalking, this));
    _mainLayer->addChild(_character, 100);
    
    Vector<Vector<Vector<int>>> map(MAP_HEIGHT);
    _map = map;
    
    for(int y = 0; y < _map.capacity(); y++)
    {
        Vector<Vector<int>> mapWidth(MAP_WIDTH);
        
        for(int x = 0; x < mapWidth.capacity(); x++)
        {
            Vector<int> mapStatus(4);
            
            for(int k = 0; k < 4; k++)
            {
                mapStatus[k] = WalkPathNoPath;
            }
            
            mapWidth[x] = mapStatus;
        }
        
        _map[y] = mapWidth;
    }
    
    Dictionary *mapData = Dictionary::createWithContentsOfFile(String::createWithFormat("map%02d.plist", mapID)->getCString());
    
    for(int y = 0; y < MAP_HEIGHT; y++)
    {
        Dictionary *mapDataHorizontal = dynamic_cast<Dictionary *>(mapData->objectForKey(String::createWithFormat("tr%d", y)->getCString()));
        for(int x = 0; x < MAP_WIDTH; x++)
        {
            this->addTileWithData(dynamic_cast<String *>(mapDataHorizontal->objectForKey(String::createWithFormat("td%d", x)->getCString()))->componentsSeparatedByString("|"), x, y);
        }
    }
    
    this->rotateChar();
    this->rotateExit();
}

void GameScene::addTileWithData(cocos2d::Array *data, unsigned int x, unsigned int y)
{
    unsigned int side0 = dynamic_cast<String *>(data->getObjectAtIndex(0))->intValue();
    unsigned int side1 = dynamic_cast<String *>(data->getObjectAtIndex(1))->intValue();
    unsigned int side2 = dynamic_cast<String *>(data->getObjectAtIndex(2))->intValue();
    unsigned int side3 = dynamic_cast<String *>(data->getObjectAtIndex(3))->intValue();
    
    if(side0 & ZeroPathToTop)
        side0 ^= ZeroPathToTop;
    
    if(side0 & ZeroPathToRight)
        side0 ^= ZeroPathToRight;
    
    if(side0 & ZeroPathToBottom)
        side0 ^= ZeroPathToBottom;
    
    if(side0 & ZeroPathToLeft)
        side0 ^= ZeroPathToLeft;
    
    if(side1 & ZeroPathToTop)
        side1 ^= ZeroPathToTop;
    
    if(side1 & ZeroPathToRight)
        side1 ^= ZeroPathToRight;
    
    if(side1 & ZeroPathToBottom)
        side1 ^= ZeroPathToBottom;
    
    if(side1 & ZeroPathToLeft)
        side1 ^= ZeroPathToLeft;
    
    if(side2 & ZeroPathToTop)
        side2 ^= ZeroPathToTop;
    
    if(side2 & ZeroPathToRight)
        side2 ^= ZeroPathToRight;
    
    if(side2 & ZeroPathToBottom)
        side2 ^= ZeroPathToBottom;
    
    if(side2 & ZeroPathToLeft)
        side2 ^= ZeroPathToLeft;
    
    if(side3 & ZeroPathToTop)
        side3 ^= ZeroPathToTop;
    
    if(side3 & ZeroPathToRight)
        side3 ^= ZeroPathToRight;
    
    if(side3 & ZeroPathToBottom)
        side3 ^= ZeroPathToBottom;
    
    if(side3 & ZeroPathToLeft)
        side3 ^= ZeroPathToLeft;
    
    Point tilePosition(x * TILE_SIZE + TILE_SIZE * 0.5, y * TILE_SIZE + TILE_SIZE * 0.5);
    
    if(side0 == WalkPathEntrance)
    {
        _character->setPosition(tilePosition);
        
        _map[x][y][0] = WalkPathEntrance;
        _map[x][y][1] = WalkPathEntrance;
        _map[x][y][2] = WalkPathEntrance;
        _map[x][y][3] = WalkPathEntrance;
        
        return;
    }
    else if(side0 == WalkPathExit)
    {
        _exit = Sprite::createWithSpriteFrameName("pedos.png");
        _exit->setColor(Color3B::BLACK);
        _exit->setPosition(tilePosition);
        _mainLayer->addChild(_exit);
        
        _map[x][y][0] = WalkPathExit;
        _map[x][y][1] = WalkPathExit;
        _map[x][y][2] = WalkPathExit;
        _map[x][y][3] = WalkPathExit;
        
        return;
    }
    else  if((dynamic_cast<String *>(data->getObjectAtIndex(0))->getCString()[0]) == 'S')
    {
        String *name =dynamic_cast<String *>(data->getObjectAtIndex(0));
        Sprite *sprite = Sprite::createWithSpriteFrameName(String::createWithFormat("%s.png", name->getCString())->getCString());
        sprite->setPosition(tilePosition);
        _mainLayer->addChild(sprite);
        
        if(dynamic_cast<String *>(data->getObjectAtIndex(0))->compare("S21") == 0)
        {
            Sprite *upperSprite = Sprite::createWithSpriteFrameName("S21_1.png");
            upperSprite->setPosition(tilePosition);
            _mainLayer->addChild(upperSprite);
            
            Array *frames = Array::create();
            frames->addObject(SpriteFrameCache::getInstance()->getSpriteFrameByName("S21_1.png"));
            frames->addObject(SpriteFrameCache::getInstance()->getSpriteFrameByName("S21_2.png"));
            frames->addObject(SpriteFrameCache::getInstance()->getSpriteFrameByName("S21_3.png"));
            frames->addObject(SpriteFrameCache::getInstance()->getSpriteFrameByName("S21_4.png"));
            frames->addObject(SpriteFrameCache::getInstance()->getSpriteFrameByName("S21_5.png"));
            frames->addObject(SpriteFrameCache::getInstance()->getSpriteFrameByName("S21_6.png"));
            frames->addObject(SpriteFrameCache::getInstance()->getSpriteFrameByName("S21_7.png"));
            frames->addObject(SpriteFrameCache::getInstance()->getSpriteFrameByName("S21_8.png"));
            
            upperSprite->runAction(RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(frames, 0.3f))));
        }
        
        _map[x][y][0] = WalkPathNoPath;
        _map[x][y][1] = WalkPathNoPath;
        _map[x][y][2] = WalkPathNoPath;
        _map[x][y][3] = WalkPathNoPath;
        
        return;
    }
    else if((side0 == WalkPathWalk) && (side1 == WalkPathWalk) && (side2 == WalkPathWalk) && (side3 == WalkPathWalk))
    {
        _map[x][y][0] = WalkPathWalk;
        _map[x][y][1] = WalkPathWalk;
        _map[x][y][2] = WalkPathWalk;
        _map[x][y][3] = WalkPathWalk;
    }
    
    _map[x][y][0] = side0;
    _map[x][y][1] = side1;
    _map[x][y][2] = side2;
    _map[x][y][3] = side3;
    
    if(side0 & WalkPathToRight)
    {
        Sprite *path = Sprite::createWithSpriteFrameName(String::createWithFormat("A%u.png", WalkPathToRight)->getCString());
        this->setPath(path, 0, x, y);
    }
    if(side0 & WalkPathToBottom)
    {
        Sprite *path = Sprite::createWithSpriteFrameName(String::createWithFormat("A%u.png", WalkPathToBottom)->getCString());
        this->setPath(path, 0, x, y);
    }
    if(side0 & WalkPathToLeft)
    {
        Sprite *path = Sprite::createWithSpriteFrameName(String::createWithFormat("A%u.png", WalkPathToLeft)->getCString());
        this->setPath(path, 0, x, y);
    }
    
    if(side1 & WalkPathToTop)
    {
        Sprite *path = Sprite::createWithSpriteFrameName(String::createWithFormat("B%u.png", WalkPathToTop)->getCString());
        this->setPath(path, 1, x, y);
    }
    if(side1 & WalkPathToBottom)
    {
        Sprite *path = Sprite::createWithSpriteFrameName(String::createWithFormat("B%u.png", WalkPathToBottom)->getCString());
        this->setPath(path, 1, x, y);
    }
    if(side1 & WalkPathToLeft)
    {
        Sprite *path = Sprite::createWithSpriteFrameName(String::createWithFormat("B%u.png", WalkPathToLeft)->getCString());
        this->setPath(path, 1, x, y);
    }
    
    if(side2 & WalkPathToTop)
    {
        Sprite *path = Sprite::createWithSpriteFrameName(String::createWithFormat("C%u.png", WalkPathToTop)->getCString());
        this->setPath(path, 2, x, y);
    }
    if(side2 & WalkPathToRight)
    {
        Sprite *path = Sprite::createWithSpriteFrameName(String::createWithFormat("C%u.png", WalkPathToRight)->getCString());
        this->setPath(path, 2, x, y);
    }
    if(side2 & WalkPathToLeft)
    {
        Sprite *path = Sprite::createWithSpriteFrameName(String::createWithFormat("C%u.png", WalkPathToLeft)->getCString());
        this->setPath(path, 2, x, y);
    }
    
    if(side3 & WalkPathToTop)
    {
        Sprite *path = Sprite::createWithSpriteFrameName(String::createWithFormat("D%u.png", WalkPathToTop)->getCString());
        this->setPath(path, 3, x, y);
    }
    if(side3 & WalkPathToRight)
    {
        Sprite *path = Sprite::createWithSpriteFrameName(String::createWithFormat("D%u.png", WalkPathToRight)->getCString());
        this->setPath(path, 3, x, y);
    }
    if(side3 & WalkPathToBottom)
    {
        Sprite *path = Sprite::createWithSpriteFrameName(String::createWithFormat("D%u.png", WalkPathToBottom)->getCString());
        this->setPath(path, 3, x, y);
    }
    
    return;
}

void GameScene::setPath(cocos2d::Sprite *path, unsigned int side, unsigned int x, unsigned int y)
{
    Point tilePosition(x * TILE_SIZE + TILE_SIZE * 0.5, y * TILE_SIZE + TILE_SIZE * 0.5);
    String *key = String::createWithFormat("%d|%d|%d", x, y, side);
    
    if(_mapTiles->objectForKey(key->getCString()) == NULL)
    {
        _mapTiles->setObject(Array::createWithCapacity(4), key->getCString());
    }
    
    dynamic_cast<Array *>(_mapTiles->objectForKey(key->getCString()))->addObject(path);
    path->setPosition(tilePosition);
    _mainLayer->addChild(path);
}

void GameScene::rotateChar()
{
    for(int y = 0; y < MAP_HEIGHT; y++)
    {
        for(int x = 0; x < MAP_WIDTH; x++)
        {
            if(_map[x][y][0] == WalkPathEntrance)
            {
                if((y != 0) && (_map[x][y - 1][SideTop]) && !(_map[x][y - 1][SideTop] == WalkPathNoPath))
                {
                    _character->rotateToSide(SideBottom);
                }
                else if((_map[x][y + 1][SideBottom]) && !(_map[x][y + 1][SideBottom] == WalkPathNoPath))
                {
                    _character->rotateToSide(SideTop);
                }
                else if((x != 0) && (_map[x - 1][y][SideRight]) && !(_map[x - 1][y][SideRight] == WalkPathNoPath))
                {
                    _character->rotateToSide(SideLeft);
                }
                else if((_map[x + 1][y][SideLeft]) && !(_map[x + 1][y][SideLeft] == WalkPathNoPath))
                {
                    _character->rotateToSide(SideRight);
                }
                
                return;
            }
        }
    }
}

void GameScene::rotateExit()
{
    for(int y = 0; y < MAP_HEIGHT; y++)
    {
        for(int x = 0; x < MAP_WIDTH; x++)
        {
            if(_map[x][y][0] == WalkPathExit)
            {
                if(y != 0 && ((_map[x][y - 1][SideBottom] & WalkPathToTop) || (_map[x][y -1 ][SideRight] & WalkPathToTop) ||(_map[x][y - 1][SideLeft] & WalkPathToTop)))
                {
                    _exit->setRotation(SideTop * 90.0);
                }
                else if((_map[x][y + 1][SideTop] & WalkPathToBottom) || (_map[x][y + 1][SideRight] & WalkPathToBottom) ||(_map[x][y + 1][SideLeft] & WalkPathToBottom))
                {
                    _exit->setRotation(SideBottom * 90.0);
                }
                else if(x != 0 && ((_map[x - 1][y][SideLeft] & WalkPathToRight) || (_map[x - 1][y][SideTop] & WalkPathToRight) ||(_map[x][y - 1][SideBottom] & WalkPathToRight)))
                {
                    _exit->setRotation(SideRight * 90.0);
                }
                else if((_map[x + 1][y][SideRight] & WalkPathToLeft) || (_map[x + 1][y][SideTop] & WalkPathToLeft) ||(_map[x][y + 1][SideBottom] & WalkPathToLeft))
                {
                    _exit->setRotation(SideLeft * 90.0);
                }
                
                return;
            }
        }
    }
}

void GameScene::charWillBeginWalking(cocos2d::Node *node)
{
    Point lookPoint = _character->lookingAtGridPosition();
    
    String *positionKey = String::createWithFormat("%d|%d|%d", int(lookPoint.x), int(lookPoint.y), _character->opositeSideOfSide(_character->rotationSide()));
    
    Object *item = nullptr;
    
    CCARRAY_FOREACH(dynamic_cast<Array *>(_mapTiles->objectForKey(positionKey->getCString())), item)
    {
        Sprite *path = dynamic_cast<Sprite *>(item);
        
        path->setColor(Color3B::WHITE);
        path->setScale(1.0f);
        
        _mainLayer->reorderChild(path, 0);
    }
}

void GameScene::charDidFinishWalking(cocos2d::Node *node)
{
    unsigned int x = _character->gridPosition().x;
    unsigned int y = _character->gridPosition().y;
    
    if(_map[x][y][0] == WalkPathExit)
    {
        this->passLabyrunth();
        
        return;
    }
    
    x = _character->lookingAtGridPosition().x;
    y = _character->lookingAtGridPosition().y;
    
    unsigned int possiblePaths = _map[x][y][_character->opositeSideOfSide(_character->rotationSide())];
    
    if((possiblePaths == WalkPathToTop) ||
       (possiblePaths == WalkPathToBottom) ||
       (possiblePaths == WalkPathToLeft) ||
       (possiblePaths == WalkPathToRight) ||
       (possiblePaths == WalkPathWalk))
    {
        _character->walkByPath(possiblePaths);
    }
    else
    {
        String *positionKey = String::createWithFormat("%d|%d|%d", x, y, _character->opositeSideOfSide(_character->rotationSide()));
        
        Object *item = nullptr;
        
        CCARRAY_FOREACH(dynamic_cast<Array *>(_mapTiles->objectForKey(positionKey->getCString())), item)
        {
            Sprite *path = dynamic_cast<Sprite *>(item);
            
            path->setColor(Color3B::GREEN);
            path->setScale(1.0f);
            
            _mainLayer->reorderChild(path, 1);
        }
    }
}

bool GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    CC_UNUSED_PARAM(touch);
    CC_UNUSED_PARAM(event);
    return true;
}

void GameScene::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
    CC_UNUSED_PARAM(touch);
    CC_UNUSED_PARAM(event);
}

void GameScene::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event)
{
    CC_UNUSED_PARAM(touch);
    CC_UNUSED_PARAM(event);
}

void GameScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    Point touchPoint = this->convertToNodeSpace(touch->getLocation());
    
    if(_character->isBussy())
        return;
    
    Point characterPoint = _character->getPosition();
    
    switch(_character->rotationSide())
    {
        case SideTop:
            characterPoint.y += TILE_SIZE;
            break;
        case SideBottom:
            characterPoint.y -= TILE_SIZE;
            break;
        case SideRight:
            characterPoint.x += TILE_SIZE;
            break;
        case SideLeft:
            characterPoint.x -= TILE_SIZE;
            break;
    }
    
    float xDistance = touchPoint.x - characterPoint.x;
	float yDistance = touchPoint.y - characterPoint.y;
    
    unsigned int side;
    if(abs(xDistance) > abs(yDistance))
    {
        if(xDistance > 0)
        {
            side = SideRight;
        }
        else
        {
            side = SideLeft;
        }
    }
    else if(yDistance > 0)
    {
        side = SideTop;
    }
    else if(yDistance < 0)
    {
        side = SideBottom;
    }
    
    unsigned int x = _character->lookingAtGridPosition().x;
    unsigned int y = _character->lookingAtGridPosition().y;
    
    unsigned int possiblePaths = _map[x][y][_character->opositeSideOfSide(_character->rotationSide())];
    
    if((side == SideTop) && (possiblePaths & WalkPathToTop))
    {
        _character->walkByPath(WalkPathToTop);
    }
    else if((side == SideBottom) && (possiblePaths & WalkPathToBottom))
    {
        _character->walkByPath(WalkPathToBottom);
    }
    else if((side == SideLeft) && (possiblePaths & WalkPathToLeft))
    {
        _character->walkByPath(WalkPathToLeft);
    }
    else if((side == SideRight) && (possiblePaths & WalkPathToRight))
    {
        _character->walkByPath(WalkPathToRight);
    }
}

void GameScene::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
    
    this->charDidFinishWalking(nullptr);
}

void GameScene::passLabyrunth()
{
    unsigned int level = appDelegate->getLevel();
    
    if(level >= TOTAL_MAPS)
    {
        Director::getInstance()->replaceScene(GameEndScene::createScene());
    }
    else
    {
        level += 1;
        appDelegate->setLevel(level);
        
        Director::getInstance()->replaceScene(PickMapScene::createScene());
    }
}