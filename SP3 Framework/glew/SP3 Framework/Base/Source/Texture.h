#ifndef TEXTURE_H
#define TEXTURE_H

const unsigned int MAX_TEXTURES = 8;

typedef unsigned int TextureID;

struct Texture {

public:
	TextureID textureArray[MAX_TEXTURES];

	Texture() {
		for (unsigned int i = 0; i < MAX_TEXTURES; ++i) {
			textureArray[i] = 0;
		}
	}
	virtual ~Texture() {}
	
};

#endif