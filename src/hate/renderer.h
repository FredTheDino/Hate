#pragma once
#include "system.h"
#include "matrix.h"
#include "graphics.h"
#include <string>
 
//
// The render handles the rendering
// of everything, and is a wrapper for a system. 
// This is done by specifying rendering properties, 
// like the layer and which texture to use. 
// 
// The render system is really comprised of 2 systems, 
// one with sprites and one with text, which are woven
// together to make it possible to draw both. This needs
// to be refactored imensly if there are more drawable types
// added in.
//

namespace hate {
    struct Graphics_Glyph {
        virtual void draw();
    }

    // All the pices of hot data needed to draw a sprite.
    struct Sprite_Glyph : public Graphics_Glyph {
        // I am a lazy person.
        union {
            transform t;
            struct {
                vec2 position;
                vec2 scale;
                float rotation;
            };
        };

        // Texture information
        texture color_texture;
        int sub_sprite;

        // The normals of the texture
        texture normal_texture;

        // If you want some wierd rendereing.
        int shader_hint = 0;

        // This is only needed for sorting.
        int layer = 0;

        void draw();
    };

    struct Text_Glyph : public Graphics_Glyph {
        // #BestCFeature
        union {
            transform t;
            struct {
                vec2 position;
                vec2 scale;
                float rotation;
            };
        };

        Vec4 color;
        float size;
        std::string text;

        // If you want some wierd rendereing.
        bool translate = true;

        // This is only needed for sorting.
        int layer = 0;

        void draw();
    }

    struct Render_System {
        System<Render_Glyph*> system;

        bool dirty_layers = false;
        int system_id; // This gets set at runtime.
    };

    extern void add(Render_System& rs, Renderer const& r);

    extern void sort_layers(Render_System& rs);

    extern void draw(Render_System& rs);
}