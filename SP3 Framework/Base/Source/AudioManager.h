#ifndef AUDIO_SYSTEM_H
#define AUDIO_SYSTEM_H

#include "irrKlang.h"
#include <set>
#include "Vector3.h"

using namespace irrklang;
using std::set;

class AudioManager {

private:
	//Variable(s)
	ISoundEngine* audioEngine;
	set<ISound*> audioList2D;
	set<ISound*> audioList3D;

	//Constructor & Destructor
	AudioManager();
	virtual ~AudioManager();

public:
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
	void SetVolumeAll(const float& volume);

};

#endif