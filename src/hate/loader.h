#pragma once
#include "hate.h"
#include "texture.h"
#include "audio.h"
#include <unordered_map>
#include <fstream>
#include <vector>

#define _LOADER_
namespace hate {

#ifndef _HATE_
	class Hate;
#endif

	//Helper for loading wav files
	struct WavHeader {
		/* RIFF Chunk Descriptor */
		uint8_t		riff[4];        // RIFF Header Magic header
		uint32_t	chunkSize;      // RIFF Chunk Size
		uint8_t		wave[4];        // WAVE Header
		/* "fmt" sub-chunk */
		uint8_t		fmt[4];         // FMT header
		uint32_t	subchunkSize;   // Size of the fmt chunk
		uint16_t	audioFormat;    // Audio format
		uint16_t	numOfChan;      // Number of channels 1=Mono 2=Stereo
		uint32_t	samplesPerSec;  // Sampling Frequency in Hz
		uint32_t	bytesPerSec;    // bytes per second
		uint16_t	blockAlign;     // 2=16-bit mono, 4=16-bit stereo
		uint16_t	bitsPerSample;  // Number of bits per sample
	};

	/**
	 * This class should not be touched by human hands.
	 * The Loader class handles loading of Pngs and Wavs,
	 * stores them in a nice little library for lightning 
	 * fast access. 
	 *
	 * You reach it by accessing the global Hate::LOADER
	 * object. This makes sure we access the same library
	 * and load everything to the same place.
	 */
	class Loader {
		friend class Hate;
		protected:
			// Initalizes the loader by finding "res/.res" directory.
			Loader();
			// Clears out the library.
			~Loader();

		public:
			/**
			 * Retrives a pice of audio from the library.
			 *
			 * @param path the path to the file.
			 * @return an audio file loaded in OpenAL.
			 */
			Audio wav(std::string& path);

			/**
			 * Retrives a texture allready processed by OpenGL.
			 *
			 * @param path the path to the file.
			 * @return a texture that can be used by OpenGL.
			 */
			Texture png(std::string& path);

			/**
			 * Unloads a loaded asset and does the nessecary cleanup.
			 *
			 * @param path the path to the file.
			 */
			void unload(std::string& path);

			/**
			 * Loads a png file and adds it to the library for future access.
			 * This function handles preloading and is not a way to get a sprite in quickly, 
			 * this should be thought about before it is needed for best runtime experience.
			 * It is however not so slow that you can't load smal things while playing.
			 *
			 * If something already is loaded, it won't be loaded again.
			 *
			 * @param path the path to the file to load.
			 * @param sprites_x the number of sprites on the x axis of the image. (1)
			 * @param sprites_y the number of sprites on the y axis of the image. (1)
			 */
			void loadPng(std::string& path, unsigned int sprites_x=1, unsigned int sprites_y=1);

			/**
			 * Loads a wav file and adds it tot he library for future access.
			 * This function handles preloading and is not a way to get a sprite in quickly, 
			 * this should be thought about before it is needed for best runtime experience.
			 * It is however not so slow that you can't load smal things while playing.
			 *
			 * If something already is loaded, it won't be loaded again.
			 * 
			 * @param path the path to the file to load.
			 */
			void loadWav(std::string& path);

			/**
			 * Loads an image without processing it with OpenGL. (CLEANUP NEEDED)
			 *
			 * This function should not be used if you want to load something for OpenGL.
			 *
			 * @param path the path to the texture.
			 * @param width a pointer to overwrite with the width.
			 * @param height a pointer to overwrite with the height.
			 * @param pixels a list to write the pixels into.
			 */
			bool quickLoadPng(std::string path, unsigned int* width, unsigned int* height, 
					std::vector<unsigned char>* pixels);
			
			/**
			 * Loads a sound file without processing it in OpenAL. (CLEANUP NEEDED)
			 *
			 * This function should not be used if you want to play the sound
			 * through the built in audio component in the engine.
			 *
			 * @param path the path to the audio file.
			 * @param header a pointer to a WavHeader.
			 * @param data a pointer that will point to the data. (NOTE: NEEDS CLEANUP)
			 */
			bool quickLoadWav(std::string& path, WavHeader* header, std::vector<char>* data);

			/**
			 * Loads a text file in for reading or writing. (CLEANUP NEEDED) 
			 * Gets the same file no matter which platform.
			 *
			 * If the file doesn't exist, a new one is created.
			 * 
			 * @param path the path to the text file.
			 * @return a file stream with read and wright access.
			 */
			std::fstream* openText(std::string& path);

			/**
			 * Loads a binary file in for reading or writing. (CLEANUP NEEDED)
			 * Gets the same file no matter which platform.
			 *
			 * If the file doens't exist, a new one is created.
			 * 
			 * @param path the path to the binary file.
			 * @return a file stream with read and write access.
			 */
			std::fstream* openBinary(std::string& path);

			// Returns the OS path to the file
			std::string getRealPath(std::string& path);
		private:
			
			/**
			 * Opens a file from the disk in the specified mode.
			 *
			 * @param path path to the file.
			 * @return a file stream.
			 */
			std::fstream* open(std::string& path, std::ios_base::openmode mode);

			// Gets an element from the library, if it doesn't exist, return NULL.
			void* get(std::string& path);
		
			// Removes a void pointer, by casting to to supported types.
			void unload(void* ptr);

			// Finds the resource folder or throws an error.
			void findResourceFolder();

			// A path to the resource folder.
			std::string resource_path;

			// The resource library.
			std::unordered_map<std::string, void*> library;
	};

}
