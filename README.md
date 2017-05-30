# Hate - A passionate desire
A simple game engine in C++.

## What I want this to be
I want this to be a game engine that is focused more on usability and getting out of your face.
That is why this engine is ment to be mainly written in a procedural/functional style, where 
a thought can be condensed into a single procedure call. But I don't want to limit myself
to it since some constructs are better made with Object Orientation.

To top it off, I want to make a "behaviour" system, a system that lets your define game behaviours
through a visual programming language which allows fast itteration and rapid prototyping. 

But be warned, this is aimed to be a simple little game library or "engine" if you want to be technical.

## What is it built with?
The library is using OpenGL with GLEW, GLFW, maybe FreeType and OpenAL when that gets implemented. And I try to keep
dependancies to a minimum to make it as portable and flexible ass possible. Other dependenies are included in the 
source code, but these are the external ones.

## Checklist (I love this stuff)
### Core
[ ] A main loop (I'm not setting the bar high)
[ ] A nice little simple math library.
[ ] Some form of gamestates. Maybe even some level file format.
[ ] Basic rendering functionality, like drawing a quad at a position.
[ ] Basic keyboard input, preferably allready with rebindable keys.
[ ] Basic audio playback, playing a sound by calling a function.
### Entities
[ ] Decide on how entities should work.
### Rendering
[ ] Render textures.
[ ] Render sub sprites.
[ ] Simple animations.
[ ] Layering.
[ ] Paralax alternatives.
[ ] Font rendering. (Probably have to use Freetype...)
### Behaviours - Depends on a lot of stuff
[ ] Set up the basic node system
[ ] Make a GUI interface (Might need splitting up)
[ ] Make it run in a seperate window? This might be usefull.
### Plan some more
[ ] Preferably finish this.
