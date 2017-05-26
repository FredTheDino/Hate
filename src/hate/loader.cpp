#include "loader.h"
#include "lodepng.h"

#include <iostream>
#include <sstream>
#include <assert.h>

namespace hate {

	Loader::Loader() {
		resource_path = "res/";
		findResourceFolder();
	}

	Loader::~Loader() {
		for (auto element : library) {
			unload(element.second);
		}
	}
	
	Audio Loader::wav(std::string& path) {
		return *(Audio*) get(path);
	}

	Texture Loader::png(std::string& path) {
		return *(Texture*) get(path);
	}

	void Loader::unload(std::string& path) {
		auto item = get(path);
		// Make sure it is in the array
		if (item) {
			unload(item);
			library.erase(path);
		}
	}

	void Loader::loadPng(std::string& path, unsigned int sprites_x, unsigned int sprites_y) {
		//TODO	
	}

	void Loader::loadWav(std::string& path) {
		//TODO
	}

	std::vector<std::string> split(std::string line, char delim) {
		std::vector<std::string> lines;
		std::stringstream ss;
		ss.str(line);

		std::string piece;
		while (std::getline(ss, piece, delim)) {
			lines.push_back(piece);
		}
		return lines;
	}

	Mesh* Loader::loadMesh(const char* path) {
		std::string p(path);
		return loadMesh(p);
	}
	Mesh* Loader::loadMesh(std::string& path) {
		{
			auto m = library.find(path);
			if (m != library.end()) {
				return (Mesh*) m->second;
			}
		}
		// Open file
		// Send to GPU
		// Return VBO
		std::vector<Vertex> verticies;
		std::vector<GLuint> indicies;

		// Load into the vectors.
		if (path.find(".obj") != std::string::npos) {
			// NOTE: THIS IS TEXT
			auto file = openText(path);
			if (!file) {
				printf("Cannot load mesh: \"%s\"\nCannot open file.", path.c_str());
				assert(0);
			}
			
			std::string line;
			std::vector<Vec3> positions;
			std::vector<Vec3> normals;
			std::vector<Vec2> texCoords;
			while (std::getline(*file, line)) {
				auto splits = split(line, ' ');
				if (splits[0] == "v") {
					Vec3 pos;
					pos.x = std::stof(splits[1]);
					pos.y = std::stof(splits[2]);
					pos.z = std::stof(splits[3]);
					positions.push_back(pos);
				} else if (splits[0] == "vn") {
					Vec3 nor;
					nor.x = std::stof(splits[1]);
					nor.y = std::stof(splits[2]);
					nor.z = std::stof(splits[3]);
					normals.push_back(nor);
				} else if (splits[0] == "vt") {
					Vec2 tex;
					tex.x = std::stof(splits[1]);
					tex.y = std::stof(splits[2]);
					texCoords.push_back(tex);
				} else if (splits[0] == "f") {
					for (int i = 1; i < splits.size(); i++) {
						auto vert = split(splits[i], '/');
						Vertex v;
						v.position = positions[std::stoi(vert[0]) - 1];
						
						if (vert.size() > 1) {
							if (!vert[1].empty())
								v.texCoord = texCoords[std::stoi(vert[1]) - 1];
							if (vert.size() == 3)
								if (!vert[2].empty())
									v.normal = normals[std::stoi(vert[2]) - 1];
						}

						indicies.push_back(verticies.size());
						verticies.push_back(v);
					}
				}
			}
		} else {
			printf("Failed to load mesh: \"%s\"\n	Unsussported file format.\n", path.c_str());
			assert(0);
		}

		// Prepare the mesh
		Mesh* m = new Mesh();
		m->init(verticies, indicies);

		library.insert(std::make_pair(path, m));

		return m;
	}

	bool Loader::quickLoadPng(std::string path, unsigned int* width, unsigned int* height, 
			std::vector<unsigned char>* pixels) {
		unsigned int e = lodepng::decode(*pixels, *width, *height, resource_path + path);
		if (e) {
			std::cout << "Decoder error for \"res/" << path << "\" "  
					<< e << ": " << lodepng_error_text(e) << std::endl;	
			return false;
		}
		return true;
	}

	// A smal struct that helps with loading of Wav files.
	struct WavChunk {
		uint8_t		id[4];
		uint32_t	size;
	};

	bool Loader::quickLoadWav(std::string& path, WavHeader* header, std::vector<char>* data) {
		std::fstream* buffer = openBinary(path);
		if (!buffer) {
			return false;
		}

		buffer->get((char*)header, sizeof(WavHeader));
	
		int i = 0;
		WavChunk chunk;
		buffer->read((char*)&chunk, sizeof(chunk));
		while (chunk.id[0] != 'd' ||
			   chunk.id[1] != 'a' ||
			   chunk.id[2] != 't' ||
			   chunk.id[3] != 'a') {
			buffer->seekg(chunk.size, std::ios_base::cur);
			buffer->read((char*)&chunk, sizeof(chunk));
			i++;
			if (i > 100) {
				delete buffer;
				return false;
			}
		}
		
		data->resize(chunk.size);
		buffer->read((char*)&chunk, data->size());
		
		delete buffer;
		return true;
	}

	std::fstream* Loader::openText(std::string& path) {
		return open(path, std::ios::out | std::ios::in);
	}

	std::fstream* Loader::openBinary(std::string& path) {
		return open(path, std::ios::binary | std::ios::out | std::ios::in);
	}

	/////////////////
	//** PRIVATE **//
	/////////////////

	std::fstream* Loader::open(std::string& path, std::ios_base::openmode mode) {
		std::fstream* file = new std::fstream(getRealPath(path), mode);

		// Create a new file if it doesn't exist
		if (!file) {
			file->open(getRealPath(path), 
					std::fstream::binary | 
					std::fstream::trunc | 
					std::fstream::out);
			file->close();

			file = new std::fstream(getRealPath(path), mode);
		}

		return file;
	}

	void* Loader::get(std::string& path) {
		auto item = library.find(path);
		if (item != library.end()) {
			return item->second;
		}
		return NULL;
	}

	void Loader::unload(void* ptr) {
		Audio* audio = (Audio*) ptr;
		if (audio) {
			audio->clean();
			delete audio;
			return;
		}

		Texture* texture = (Texture*) ptr;
		if (texture) {
			texture->clean();
			delete texture;
			return;
		}
	}

	std::string Loader::getRealPath(std::string& path) {
		return resource_path + path;
	}

	void Loader::findResourceFolder() {
		std::string nameOfFile = ".res";
		std::ifstream file;
		for (int i = 0; i < 5; i++) {
			file.open(getRealPath(nameOfFile));
			if (file) {
				file.close();
				break;
			} else {
				resource_path = "../" + resource_path;
			}
		}
	}
}

