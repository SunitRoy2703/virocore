//
//  VRODriverOpenGLiOS.h
//  ViroRenderer
//
//  Created by Raj Advani on 11/7/16.
//  Copyright © 2016 Viro Media. All rights reserved.
//

#ifndef VRODriverOpenGLiOS_h
#define VRODriverOpenGLiOS_h

#include "VRODriverOpenGL.h"
#include "VROSoundEffectiOS.h"
#include "VROAudioPlayeriOS.h"
#include "VROVideoTextureCacheOpenGL.h"
#include "VROTypefaceiOS.h"

class VRODriverOpenGLiOS : public VRODriverOpenGL {
    
public:
    
    VRODriverOpenGLiOS(EAGLContext *eaglContext) :
        _eaglContext(eaglContext) {
        
    }
    
    virtual ~VRODriverOpenGLiOS() { }
    
    VROVideoTextureCache *newVideoTextureCache() {
        return new VROVideoTextureCacheOpenGL(_eaglContext);
    }
    
    std::shared_ptr<VROSoundEffect> newSoundEffect(std::string fileName) {
        NSURL *fileURL = [NSURL fileURLWithPath:[NSString stringWithUTF8String:fileName.c_str()]];
        std::string url = std::string([[fileURL description] UTF8String]);
        
        return std::make_shared<VROSoundEffectiOS>(url);
    }
    
    std::shared_ptr<VROAudioPlayer> newAudioPlayer(std::string fileName) {
        NSURL *fileURL = [NSURL fileURLWithPath:[NSString stringWithUTF8String:fileName.c_str()]];
        std::string url = std::string([[fileURL description] UTF8String]);
        
        return std::make_shared<VROAudioPlayeriOS>(url);
    }
    
    std::shared_ptr<VROTypeface> newTypeface(std::string typefaceName, int size) {
        std::shared_ptr<VROTypeface> typeface = std::make_shared<VROTypefaceiOS>(typefaceName, size);
        typeface->loadFace();
        
        return typeface;
    }

    
private:
    
    EAGLContext *_eaglContext;
    
};

#endif /* VRODriverOpenGLiOS_h */