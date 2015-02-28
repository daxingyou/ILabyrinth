//
//  MenuSceneLoader.h
//  Labyrinth
//
//  Created by shen xinxing on 13-12-2.
//
//

#ifndef Labyrinth_MenuSceneLoader_h
#define Labyrinth_MenuSceneLoader_h

#include "MenuScene.h"

class MenuSceneLoader : public cocosbuilder::LayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MenuSceneLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MenuScene);
};


#endif
