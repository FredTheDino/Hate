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

## Objectifying entities
In this engine entities are just a collection of data being passed around, and it should be able 
to be passed around as fast as possible. This is why entities are past via refference and a 
refference should never be stored. Since they might get deleted when the frame ends and we don't
want that to crash us, do we? 

## What is it built with?
The library is using OpenGL with GLEW, GLFW, and OpenAL Soft. The lastter is 
compiled with the engine, so that should not keep you up at night. And I try 
to keep dependancies to a minimum to make it as portable and flexible ass 
possible. Other dependenies are included in the source code, but these are 
the external ones.

## Checklist (I love this stuff)
### Core
- [x] A main loop (I'm not setting the bar high)
- [x] A nice little simple math library.
- [ ] Some form of gamestates. Maybe even some level file format. (Need to think more on this, but I want to use level files and make a dedicated editor.)
- [x] Basic rendering functionality, like drawing a quad at a position.
- [x] Basic keyboard input, preferably allready with rebindable keys.
- [x] Basic audio playback, playing a sound by calling a function.
- [-] Add all the dependencies into the source code. (Lets not, it might be worth investigating for GLFW but I have a feeling GLEW is gonna be a touch nut.)
### Entities and Behaviours
- [x] Decide on how entities should work.
- [x] Implement them. (Looks like my planning payed off)
- [ ] Set up the basic node systems.
- [ ] Chips! (Or crisps if you're british)
- [ ] Make a GUI interface (Might need splitting up)
- [ ] Make it run in a seperate window? This might be usefull.
### Rendering
- [x] Render textures.
- [x] Render sub sprites.
- [-] Simple animations. (It's kinda in, it's maybe a bit more manual then I'd like...)
- [x] Layering. 
- [ ] Paralax alternatives. (Is it needed? I'm thinking of holding of on this for now.)
- [x] Font rendering. 
### Plan some more
- [ ] Preferably finish this.

## TODO

Next step: 
	Make it possible to load entire files of entities.
	Make it possible to save entire files of entities.
	Start work on the behaviours.
		I need to figure out how to store them in text.
		How will chips work?
		Set up the linked lists.

### Entities
Thoughs this far: #OldNews
	All entities share these properties:
		They all have a transform.
		They all have a layer they're drawn on.
		They all have a void pointer that can point to extra information.

		They all have a way to be updated.
		They all have a way to be drawn (Even if that means not being drawn).

		They all have a behaviour attached which can do nothing.
	
	The update function can be replaced with anything that takes
	in a delta and the entitiy.

	All entities can be seralized and saved as text in a text file. And
	reproduced at run time.

