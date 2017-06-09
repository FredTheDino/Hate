#include "audio.h"
#include <stdlib.h> 
#include <AL/alc.h>
#include <stack>
#include <map>
#include <assert.h> 

namespace hate {
	struct sound_info {
		// If it is being used.
		bool used = false;
		// If the source should survive when it's paused.
		bool is_persistent = false;
		// Which source this info bellongs to.
		ALuint source;
		// The current buffer.
		ALuint buffer;
		// The type of the sound
		sound_type type;
		// What the gain is at.
		float target_gain = 1;
		// What the pitch is at.
		float target_pitch = 1;
		// How much the gain should change per second.
		float gain_change = 1;
		// How much the pitch should change per second.
		float pitch_change = 1;
		// If position should be used.
		bool positional = false;
		// The position.
		vec2 position = vec2();
		// If the source should loop.
		bool loop = false;
	};

	float global_gain[SOUND_TYPE_LENGTH];

	std::stack<ALuint> free_sources;
	std::map<ALuint, sound_info> sources;
	
	ALCdevice*  device;
	ALCcontext* context;
	

	// Initalizes OpenAL
	void init_audio() {
		for (int i = 0; i < SOUND_TYPE_LENGTH; i++) {
			global_gain[i] = 1.0f;
		}

		device = alcOpenDevice(NULL);
		if (!device) {
			printf("AL Error: no audio output device\n");
		}	

		context = alcCreateContext(device, NULL);
		if (!alcMakeContextCurrent(context)) {
			printf("AL Error: cannot create context\n");
		}

		// Log that shit!
		printf("[OpenAL] Version: %s\n", alGetString(AL_VERSION));
		printf("[OpenAL] Vendor: %s\n", alGetString(AL_VENDOR));
		printf("[OpenAL] Renderer: %s\n", alGetString(AL_RENDERER));
	}

	void destroy_audio() {
		alcDestroyContext(context);
		alcCloseDevice(device);
	}

	void set_sound_info(sound_info const& info) {
		assert(info.type >= 0);
		assert(info.type < SOUND_TYPE_LENGTH);

		ALuint source = info.source;

		alSourcei(source, AL_BUFFER, info.buffer);

		alSourcef(source, AL_PITCH, info.target_pitch);

		alSourcef(source, AL_GAIN, info.target_gain * global_gain[info.type]);

		if (info.positional) {
			alSourcei(source, AL_SOURCE_RELATIVE, false);
			alSource3f(source, AL_POSITION, info.position.x, info.position.y, 0);
		} else {
			alSourcei(source, AL_SOURCE_RELATIVE, true);
			alSource3f(source, AL_POSITION, 0, 0, 0);
		}

		alSource3f(source, AL_VELOCITY, 0, 0, 0);

		alSourcei(source, AL_LOOPING, info.loop);
	}

	// Updates the audio engine.
	void update_audio() {
		for (auto& s : sources) {
			if (!s.second.used) continue;
			if (!s.second.is_persistent && is_stopped(s.first)) {
				// It's unused.
				s.second.used = false;
				free_sources.push(s.first);
			} else {
				set_sound_info(s.second);
			}
		}
	}
	
	// Sets the global gain for that kind of sound.
	void set_global_gain(sound_type type, float gain) {
		assert(type < 0);
		assert(type > SOUND_TYPE_LENGTH);

		global_gain[type] = gain;
	}

	sound_info find_free_source() {
		sound_info info;
		if (free_sources.empty()) {
			// We have to make a new source.
			alGenSources((ALuint)1, &info.source);
		} else {
			// We can use a premade one.
			info.source = free_sources.top();
			free_sources.pop();
			info = sources[info.source];
		}

		info.is_persistent = false;
		info.used = true;
		sources[info.source] = info;
		return info;
	}

#define PITCH_DELTA 0.10f
#define GAIN_DELTA  0.10f

	// Randomizes the sounds, just a bit.
	void perturb_sound(float* gain, float* pitch) {
		*gain  += *gain  * ((float) rand() / RAND_MAX - 0.5f) * GAIN_DELTA; 
		*pitch += *pitch * ((float) rand() / RAND_MAX - 0.5f) * PITCH_DELTA; 
	}

	// Plays a sound but ignores the position.
	ALuint play_sound(sound s, sound_type type, bool perturb, float gain, 
			float pitch, bool loop) {
		sound_info info = find_free_source();

		if (perturb) {
			perturb_sound(&gain, &pitch);
		}

		info.type = type;
		info.buffer = s.buffer;
		info.target_gain = gain;
		info.target_pitch = pitch;
		info.positional = false;
		info.loop = loop;

		set_sound_info(info);

		// Now we can play!
		alSourcePlay(info.source);

		// Add it to the list of sources
		sources[info.source] = info;
		return info.source;
	}

	// Plays a sound at the specified position. 
	ALuint play_sound_at(sound s, sound_type type, bool perturb, float gain, 
			float pitch, bool loop, vec2 pos) {
		sound_info info = find_free_source();

		if (perturb) {
			perturb_sound(&gain, &pitch);
		}

		info.buffer = s.buffer;
		info.type = type;
		info.target_gain = gain;
		info.target_pitch = pitch;
		info.position = pos;
		info.positional = true;
		info.loop = loop;

		set_sound_info(info);
	
		// Now we can play!
		alSourcePlay(info.source);

		return info.source;
	}

	void persistant_sound(ALuint source) {
		sources[source].is_persistent = true;
	}

	void unused_sound(ALuint source) {
		sources[source].is_persistent = false;
	}

	// Stops the source from continuing to play.
	void stop_sound(ALuint source) {
		alSourceStop(source);
	}

	// Pauses the source.
	void pause_sound(ALuint source) {
		alSourcePause(source);
	}

	// If the sound is playing or not.
	bool is_playing(ALuint source) {
		int state;
		alGetSourcei(source, AL_SOURCE_STATE, &state);
		return state == AL_PLAYING;
	}

	bool is_stopped(ALuint source) {
		int state;
		alGetSourcei(source, AL_SOURCE_STATE, &state);
		return state == AL_STOPPED || state == AL_INITIAL;
	}

	bool is_paused(ALuint source) {
		int state;
		alGetSourcei(source, AL_SOURCE_STATE, &state);
		return state == AL_PAUSED;
	}

	// Sets the buffer.
	void set_sound_buffer(ALuint source, sound s) {
		sources[source].buffer = s.buffer;
	}

	// Sets if the source should loop.
	void set_sound_loop(ALuint source, bool loop) {
		sources[source].loop = loop;
	}

	// Sets the gain of a source.
	void set_sound_gain(ALuint source, float new_gain) {
		sources[source].target_gain = new_gain;
	}

	// Sets the pitch of a source.
	void set_sound_pitch(ALuint source, float new_pitch) {
		sources[source].target_pitch = new_pitch;
	}

	// Spoiler! This sets the position of the sound.
	void set_sound_position(ALuint source, vec2 pos) {
		sources[source].position = pos;
	}
	
	// Does what it says on the tin.
	float get_gain(ALuint source) {
		float gain;
		alGetSourcef(source, AL_GAIN, &gain);
		return gain;
	}

	float get_pitch(ALuint source) {
		float pitch;
		alGetSourcef(source, AL_PITCH, &pitch);
		return pitch;
	}
}
