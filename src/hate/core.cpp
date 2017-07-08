#include "core.h"
#include "graphics.h"
#include "loader.h"
#include "system.h"
#include "shader.h"
#include "input.h"
#include "clock.h"
#include <stdio.h>
#include <math.h>
#include <string>

#define WINDOW_WIDTH  600
#define WINDOW_HEIGHT 400
#define WINDOW_TITLE  "Hello World"

namespace hate {

	// @Temporaray

    Texture color_texture;
    Texture normal_texture;
    struct Monkey : public Entity {

        float timer = 0;
        Transform t;

        void init() {
            normal_texture = load_texture("monkey_norm.png", false);
            color_texture = load_texture("monkey_color.png", false);
        }

        void update(float delta) {
            timer += delta;
            t.position.y = sin(timer);
        }

        void draw() {
            draw_sprite(gen_transform(t), &color_texture, &normal_texture);
        }
    };
    
    // Declaration
	GameStateManager gsm = GameStateManager(); 
    bool running = true;
    GLFWwindow* window = nullptr;
    int window_width;
    int window_height;
    float window_aspect_ratio;

    System system;

    // Callbacks
    void close_callback(GLFWwindow* window) {
        running = false;
    }

    void resize_callback(GLFWwindow* window, int new_width, int new_height) {
        window_width = new_width;
        window_height = new_height;

        window_aspect_ratio = (float) new_width / new_height;

        glViewport(0, 0, new_width, new_height);
    }

    void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
        mouse_position.x = (float) xpos;
        mouse_position.y = (float) ypos;
    }

    void make_window() {
        if (!glfwInit()) 
            printf("Failed to initalze GLFW - Window and IO library\n");

        window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL); // Not sure I like these hard constants, might be better to pass this stuff in via a struct.
        window_width = WINDOW_WIDTH;
        window_height = WINDOW_HEIGHT;
        window_aspect_ratio = (float) window_width / window_height;
        
        glfwSetWindowSizeLimits(window, 600, 400, GLFW_DONT_CARE, GLFW_DONT_CARE);
        glfwSetWindowCloseCallback(window, close_callback);
        glfwSetWindowSizeCallback(window, resize_callback);
        glfwSetCursorPosCallback(window, cursor_position_callback);
        // For GLEW, turns out this is important
        glfwMakeContextCurrent(window);	

        // @FIXME, we currently set Vsync to true, allways... 
        // Maybe not do that? And the clear color... We need 
        // some sort of initalizer object.
        glfwSwapInterval(0);
    }

    void init_hate() {
        // Those don't really have dependancies.
        find_resource_location();
        load_input_map("input.map"); // Load that map!
        // GLFW stuff.
        make_window();

        // This needs a window
        init_graphics();
        
        // Set up that audio!
        init_audio();
    }

    void destory_hate() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void run_hate() {

        Font f = load_font("fonts/droid_sans");
        Shader s = load_shader("master.glsl");

        use_shader(s);
        
        auto sound_file = load_wav("a.wav");
        
        reset_clock();
        float delta = 0.0f;

        Monkey* m = new Monkey();
        m->init();
        auto id = add(system, m);

		// To switch to the new state before the main loop.
		update_state(gsm, delta);

        while (running) {
            update_clock();
            delta = get_clock_delta();

            // @Tought: glfwPollEvents is in "update_input_map", not sure if it's a good idea.
            update_input_map();

            update_audio();

#ifdef DEBUG 
            reload_input_map("input.map", true);
            recompile_shader(&s, true);
            use_shader(s);
#endif
            use_projection(cam);

            //update(system, get_clock_delta());

            //draw(system);

			update_state(gsm, delta);

            // Updates the graphics
            glfwSwapBuffers(window);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        delete m;

        delete_sound(sound_file);
        delete_font(f);
        delete_shader(s);

        destroy_audio();
    }
}

            /*
            // Used to be located in the main update loop, but I got sick of having it there.

            remove(system, id);
            id = add(system, m);

            char temp_text[20];
            sprintf(temp_text, "fps: %0.2f", get_clock_fps());
            std::string text(temp_text);

            float size = 10 + 2 * sin(get_clock_time());
            float y = get_highest_of_font(size, f);
            draw_text(text, size, f, 
                    0, 
                    0,
                    Vec4(sin(get_clock_time()) * 0.5f + 0.5f, 0.2f, 0.75f, 1.0f));
            
            draw_sprite(0.1, 0.5, 1, 1, &t2, &t2);

            if (old_text != text) {
                delete_mesh(t_m);
                t_m = generate_text_mesh(text, 10.0, f, 0, 0);
                old_text = text;
            }
            draw_text_mesh(t_m, f, vec4(1.0, 1.0, 1.0, 1.0));
            //draw_text(text, 10, f, 0, 2, vec4(0.75f, 0.2f, 0.75f, 1.0f));
            // draw(em);

            if (is_down("up")) {
                cam.zoom /= 1.0f + delta;
            }

            if (is_down("down")) {
                cam.zoom *= 1.0f + delta;
            }

            if (is_down("left")) {
                cam.position.x -= delta * 2;
            }

            if (is_down("right")) {
                cam.position.x += delta * 2;
            }
            */

            //update(em, get_clock_delta());
