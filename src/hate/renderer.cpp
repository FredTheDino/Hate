#include "renderer.h"
#include "graphics.h"

namespace hate {
    Sprite_Glyph::draw() {
        draw_sprite(gen_transform(this->t), &color_texture, normal_texture, sub_sprite, translate);
    }

    Text_Glyph::draw() {
        
        draw_text(text, size, f, position.x, position.y, color);
    }


}
