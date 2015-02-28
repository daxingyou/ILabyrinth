//
//  LevelSpriteLoader.h
//  Labyrinth
//
//  Created by shen xinxing on 12/10/13.
//
//

#ifndef Labyrinth_LevelSpriteLoader_h
#define Labyrinth_LevelSpriteLoader_h

#include "LevelSprite.h"

class LevelSpriteLoader : public cocosbuilder::SpriteLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LevelSpriteLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LevelSprite);
};

#endif
