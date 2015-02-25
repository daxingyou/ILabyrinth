//
//  GameMacro.h
//  Labyrinth
//
//  Created by shen xinxing on 13-12-2.
//
//

#ifndef Labyrinth_GameMacro_h
#define Labyrinth_GameMacro_h

#define appDelegate ((AppDelegate *)cocos2d::Application::getInstance())

#define USING_NS_CC_BUILDER using namespace cocosbuilder

#define NODE_CREATE_BY_CCB_START(CLASSNAME, LOADER, FILENAME, VARIABLETYPE, VARIABLE) \
NodeLoaderLibrary * ccNodeLoaderLibrary = NodeLoaderLibrary::newDefaultNodeLoaderLibrary(); \
ccNodeLoaderLibrary->registerNodeLoader(CLASSNAME, LOADER); \
CCBReader * ccbReader = new CCBReader(ccNodeLoaderLibrary); \
VARIABLE = dynamic_cast<VARIABLETYPE>(ccbReader->readNodeGraphFromFile(FILENAME));

#define NODE_CREATE_BY_CCB_END ccbReader->release();

#define MAP_WIDTH 15
#define MAP_HEIGHT 10

#define TILE_SIZE 32.0f

#define TOTAL_MAPS 39

typedef enum {
	WalkPathWalk	= 0,
	WalkPathToTop   = 1 << 1,
	WalkPathToRight = 1 << 2,
	WalkPathToBottom= 1 << 3,
	WalkPathToLeft  = 1 << 4,
	WalkPathEntrance= 1 << 5,
	WalkPathExit	= 1 << 6,
	WalkPathNoPath	= 1 << 7,
} WalkPath;

typedef enum {
    ZeroPathToBottom= 1 << 7,
    ZeroPathToLeft  = 1 << 8,
    ZeroPathToTop   = 1 << 9,
    ZeroPathToRight = 1 << 10
} ZeroPath;

typedef enum {
	SideTop		= 0,
	SideRight	= 1,
	SideBottom	= 2,
	SideLeft	= 3,
    SideNone    = 10,
} Side;

#endif
