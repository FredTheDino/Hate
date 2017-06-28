// 
// This is the home of the audio thread, 
// you can interface with the audio thread
// using the procedures in this file,
// but be warey that it is on another
// thread and if you don't treat it
// nice things will go south, fast.
#pragma once
#include "basic.h"
#include "matrix.h"
#include <AL/al.h>

namespace hate {
	// An enum for keeping track
	// of the type of the sound.
	//
	// This enables things like
	// just changeing the volume 
	// of music.
	enum SoundType {
		MUSIC,
		SFX,
		SOUND_TYPE_LENGTH
	};

	// A sound is a efference to
	// audio data that is allready
	// loaded to the sound card.
	struct Sound {
		// A buffer id.
		ALuint buffer;
		// The format of the sound.
		ALenum format; // Might split this up.
	};

	// Initalizes everything with openAL.
	extern void init_audio();

	// De initalizes everything.
	extern void destroy_audio();

	// Updates all audio
	extern void update_audio();

	// Sets the global gain for that kind of sound.
	extern void set_global_gain(SoundType type, float gain);

	// Plays a sound but ignores the position, it will return
	// a refference. This is a "set and foreget" play procedure,
	// which doesn't require anything more than this.
	extern ALuint play_sound(Sound s, SoundType type, bool perturb = true, 
			float gain = 1, float pitch = 1, bool loop = false);

	// Plays a sound at the specified position. 
	// It returns a source id which can be used
	// to change the sound when it is being played.
	extern ALuint play_sound_at(Sound s, SoundType type, bool perturb = true, 
			float gain = 1, float pitch = 1, bool loop = false, Vec2 pos = Vec2(0, 0));

	// This makes it so the source doesn't get marked as unused.
	extern void persistant_sound(ALuint source);

	// Marks the source as unused.
	extern void unused_sound(ALuint source);

	// Stops the source from continuing to play.
	extern void stop_sound(ALuint source);

	// Pauses the source.
	extern void pause_sound(ALuint source);

	// If the sound is playing or not.
	extern bool is_playing(ALuint source);
	// If the sound is playing or not.
	extern bool is_stopped(ALuint source);
	// If the sound is playing or not.
	extern bool is_paused(ALuint source);

	// Sets the sound buffer.
	extern void set_sound_buffer(ALuint source, Sound s);

	// Sets if the source should loop.
	extern void set_sound_loop(ALuint source, bool loop);

	// Sets the gain of a source.
	extern void set_sound_gain(ALuint source, float new_gain);

	// Sets the pitch of a source.
	extern void set_sound_pitch(ALuint source, float new_pitch);

	// Spoiler! This sets the position of the sound.
	extern void set_sound_position(ALuint source, Vec2 pos);
	
	// Does what it says on the tin.
	extern float get_gain(ALuint source);
	extern float get_pitch(ALuint source);

	/* Thoughts so far:
	 *
	 * In the audio thread, set every
	 * audiocomponent everyframe. This makes
	 * it less messy to send in new information
	 * and stuff. 
	 *
	 * Translate audio from "local audio space", to
	 * "global audio space" with a variable.
	 *
	 * The sounds are sorted into groups,
	 * for music and for sound effects
	 * so the engine can tell them appart.
	 *
	 * We store all audio events in a que
	 * that is then processed in the same 
	 * order in the other thread.
	 *
	 * You can also get a refference to 
	 * a source from the thread, not sure
	 * how to do this yet, which can be
	 * used to make things fade, change volume,
	 * pause or what ever.
	 *
	 * I also need to write the wav loader,
	 * and make sure it works.
	 */


}

