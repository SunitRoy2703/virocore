//
//  VROText.h
//  ViroRenderer
//
//  Created by Raj Advani on 11/24/16.
//  Copyright © 2016 Viro Media. All rights reserved.
//

#ifndef VROText_h
#define VROText_h

#include <stdio.h>
#include <ft2build.h>
#include <map>
#include FT_FREETYPE_H

#include "VROGeometry.h"
#include "VROShapeUtils.h"

class VROMaterial;
class VROTexture;
class VROGlyph;

enum class VROTextHorizontalAlignment {
    Left,
    Right,
    Center,
    Justified
};

enum class VROTextVerticalAlignment {
    Top,
    Bottom,
    Center
};

enum class VROLineBreakMode {
    WordWrap,
    CharWrap,
    Clip,
    TruncateTail
};

class VROTextLayout {
    float width;
    float height;
    VROTextHorizontalAlignment horizontalAlignment;
    VROTextVerticalAlignment verticalAlignment;
};

class VROText : public VROGeometry {
    
public:
    
    static std::shared_ptr<VROText> createText(std::string text, std::shared_ptr<VROTypeface> typeface, float width, float height,
                                               VROTextHorizontalAlignment horizontalAlignment, VROTextVerticalAlignment verticalAlignment,
                                               VROLineBreakMode lineBreakMode, int maxLines = 0);
    
    static VROVector3f getTextSize(std::string text, std::shared_ptr<VROTypeface> typeface,
                                   float maxWidth, VROLineBreakMode lineBreakMode, int maxLines = 0);
    
    virtual ~VROText();
    
    /*
     Get the width and height of the text.
     */
    float getWidth() const {
        return _width;
    }
    float getHeight() const {
        return _height;
    }
    
private:
    
    VROText(std::vector<std::shared_ptr<VROGeometrySource>> sources,
            std::vector<std::shared_ptr<VROGeometryElement>> elements,
            float width, float height) :
        VROGeometry(sources, elements),
        _width(width),
        _height(height)
    {}
    
    static void buildText(std::string text,
                          std::shared_ptr<VROTypeface> typeface,
                          float scale,
                          float width,
                          float height,
                          VROTextHorizontalAlignment horizontalAlignment,
                          VROTextVerticalAlignment verticalAlignment,
                          VROLineBreakMode lineBreakMode,
                          int maxLines,
                          std::vector<std::shared_ptr<VROGeometrySource>> &sources,
                          std::vector<std::shared_ptr<VROGeometryElement>> &elements,
                          std::vector<std::shared_ptr<VROMaterial>> &materials,
                          float *outRealizedWidth, float *outRealizedHeight);
    
    /*
     Build a standard Viro geometry from the given vertex array and material/indices
     pairs.
     */
    static void buildGeometry(std::vector<VROShapeVertexLayout> &var,
                              std::map<FT_ULong, std::pair<std::shared_ptr<VROMaterial>, std::vector<int>>> &materialMap,
                              std::vector<std::shared_ptr<VROGeometrySource>> &sources,
                              std::vector<std::shared_ptr<VROGeometryElement>> &elements,
                              std::vector<std::shared_ptr<VROMaterial>> &materials);
    
    /*
     Write the geometry for the given glyph (at the given position) into the
     provided vertex array, and write the associated indices into the indices 
     array as well.
     */
    static void buildChar(std::unique_ptr<VROGlyph> &glyph,
                          float x, float y, float scale,
                          std::vector<VROShapeVertexLayout> &var,
                          std::vector<int> &indices);
    
    float _width, _height;
    
};

#endif /* VROText_h */
