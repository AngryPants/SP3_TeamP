#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "SingletonTemplate.h"
#include "Texture.h"
#include <map>
#include <string>
#include <iostream>

using std::map;
using std::pair;
using std::string;
using std::cout;
using std::endl;

typedef map<string, TextureID> TextureMap;

class TextureManager : public Singleton<TextureManager> {

	friend class Singleton<TextureManager>;

private:
	//Variable(s)
	TextureMap textureMap;

	//Constructor(s) & Destructor
	TextureManager();
	virtual ~TextureManager();

	//Private Function(s)
	bool Clear();

public:
	//User Interface
	TextureID GetTexture(const string& textureName);
	bool CheckTextureExist(const string& textureName) const;
	TextureID AddTexture(const string& textureName, const string& filePath);
	bool RemoveTexture(const string& textureName);

};

#endif