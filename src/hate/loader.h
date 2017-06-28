//
// The procedures in the loader handle
// the loading and unloading of cirtain
// file formats.
//
// These file formats include:
//   png, wav.
//
#pragma once
#include "basic.h"
#include "graphics.h"
#include "audio.h"
#include <string>
#include <vector>

namespace hate {

	// Scans through a number of parent
	// directories for the "res/.res" 
	// file which marks a resource 
	// directory.
	extern void find_resource_location();

	// Loads a texture from a file and 
	// sets up a GLTexture with the 
	// desired specifications.
	Texture load_texture(std::string path, bool linear_filtering = false, GLenum wrap_style = GL_REPEAT, bool use_mipmaps = true); 

	// Deletes a texutre... I mean, comeon,
	// it's perty obiouse...
	extern void delete_texture(Texture t);

	struct Wav_Header {
		uint8_t		riff[4];        // RIFF Header Magic header
		uint32_t	chunk_size;      // RIFF Chunk Size
		uint8_t		wave[4];        // WAVE Header
		// "fmt" sub-chunk
		uint8_t		fmt[4];         // FMT header
		uint32_t	subchunk_size;   // Size of the fmt chunk
		uint16_t	audio_format;    // Audio format
		uint16_t	num_of_chan;      // Number of channels 1=Mono 2=Stereo
		uint32_t	samples_per_sec;  // Sampling Frequency in Hz
		uint32_t	bytes_per_sec;    // bytes per second
		uint16_t	block_align;     // 2=16-bit mono, 4=16-bit stereo
		uint16_t	bits_per_sample; // Number of bits per sample
	};

	// Opens a wav file and reads in the data.
	extern Sound load_wav(std::string path);

	// Deletes a sound.
	extern void delete_sound(Sound s);

	extern long get_edit_time(std::string path);

	// Returns the os specific path.
	extern std::string get_real_path(std::string path);
}
