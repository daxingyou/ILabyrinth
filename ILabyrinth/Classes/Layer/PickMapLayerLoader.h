//
//  PickMapLayerLoader.h
//  Labyrinth
//
//  Created by shen xinxing on 12/6/13.
//
//

#ifndef Labyrinth_PickMapLayerLoader_h
#define Labyrinth_PickMapLayerLoader_h

#include "PickMapLayer.h"

class PickMapLayerLoader : public cocosbuilder::LayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(PickMapLayerLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(PickMapLayer);
};

#endif
