#pragma once
#include "system.h"
#include "matrix.h"
#include "graphics.h"
 
//
// The render engine handles the rendering
// of everything, and is a wrapper for a system. 
// This is done by specifying rendering properties, 
// like the layer and which texture to use.
//

namespace hate {

    struct Render_Glyph {
        Mat4 transform;
        Texture texture;
    };

}