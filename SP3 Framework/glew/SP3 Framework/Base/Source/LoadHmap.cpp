#include <iostream>
#include <fstream>
#include "LoadHmap.h"

bool LoadHeightMap(const char *file_path, std::vector<unsigned char> &heightMap) {
	
	std::ifstream fileStream(file_path, std::ios::binary);
	if(!fileStream.is_open()) {
		std::cout << "Impossible to open " << file_path << ". Are you in the right directory ?\n";
	
		return false;
	}

    fileStream.seekg(0, std::ios::end); //seekg(offset, end of stream)
    std::streampos fileSize = (unsigned)fileStream.tellg(); //Get file size = ? bytes.
	
	fileStream.seekg(0, std::ios::beg); //beginning
	heightMap.resize((unsigned)fileSize); //allocate memory
	fileStream.read((char *)&heightMap[0], fileSize); //reading
	
	fileStream.close();
	
	return true;

}

float ReadHeightMap(std::vector<unsigned char> &heightMap, float x, float z) {
	
	if (x < -0.5f || x > 0.5f || z < -0.5f || z > 0.5f) {
		return 0;
	} else if (heightMap.size() == 0) {
		return 0;
	}

	unsigned terrainSize = (unsigned)sqrt((double)heightMap.size());
	
	unsigned zCoord = (unsigned)((z + 0.5f) * terrainSize);
	unsigned xCoord = (unsigned)((x + 0.5f) * terrainSize);

	return (float)heightMap[zCoord * terrainSize + xCoord] / 256.f;

}