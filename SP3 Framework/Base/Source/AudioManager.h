#ifndef AUDIO_SYSTEM_H
#define AUDIO_SYSTEM_H

#include "irrKlang.h"
#include <vector>
#include "Vector3.h"

using namespace irrklang;
using std::vector;

class AudioManager {

private:
	//Variable(s)
	ISoundEngine* audioEngine;
	vector<ISound*> audioList2D;
	vector<ISound*> audioList3D;

	//Constructor
	AudioManager();

public:
	//Destructor
	virtual ~AudioManager();

	//Function(s)
	static AudioManager& GetInstance();
	void Update();
	bool PlayAudio2D(const char* audioFile, bool looped);
	bool ClearAudioList2D();
	bool PlayAudio3D(const char* audioFile, bool looped, float minDistance, float maxDistance, Vector3 listenerPosition, Vector3 listenerDirection, Vector3 soundPosition, Vector3 upVector = Vector3(0, 1, 0));
	bool PlayAudio3D(const char* audioFile, bool looped, float minDistance, Vector3 listenerPosition, Vector3 listenerDirection, Vector3 soundPosition, Vector3 upVector = Vector3(0, 1, 0));
	bool UpdateAudio3D(const char* audioFile, Vector3 soundPosition);
	bool UpdateListener3D(Vector3 listenerPosition, Vector3 listenerDirection, Vector3 upVector = Vector3(0, 1, 0));
	bool ClearAudioList3D();

};

#endif