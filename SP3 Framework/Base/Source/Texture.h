#ifndef TEXTURE_H
#define TEXTURE_H

const unsigned int MAX_TEXTURES = 8;

typedef unsigned int TextureID;

struct Texture {

public:
	//Variable(s)
	TextureID textureArray[MAX_TEXTURES];

	//Constructor(s) & Destructor
	Texture() {
		for (unsigned int i = 0; i < MAX_TEXTURES; ++i) {
			textureArray[i] = 0;
		}
	}
	virtual ~Texture() {}
	
	//Operator Overload.
	bool operator==(const Texture& rhs) const {
		for (unsigned int i = 0; i < MAX_TEXTURES; ++i) {
			if (textureArray[i] != rhs.textureArray[i]) {
				return false;
			}
		}
		return true;
	}
	Texture& operator=(const Texture& rhs) {
		for (unsigned int i = 0; i < MAX_TEXTURES; ++i) {
			textureArray[i] = rhs.textureArray[i];
		}
		return *this;
	}

};

#endif