#include "AudioManager.h"

AudioManager::AudioManager() {

	audioEngine = createIrrKlangDevice();
	if (!audioEngine) {
		throw std::exception("Unable to start IrrKlangDevice!");
	}

}

AudioManager::~AudioManager() {

	ClearAudioList2D();
	ClearAudioList3D();

	if (audioEngine) {
		audioEngine->drop();
		audioEngine = nullptr;
	}

}

AudioManager& AudioManager::GetInstance() {

	static AudioManager audio;

	return audio;

}

void AudioManager::Update() {

	audioEngine->update();

}

bool AudioManager::PlayAudio2D(const char* audioFile, bool looped) {

	ISound* soundPtr = audioEngine->play2D(audioFile, looped, false, true);

	audioList2D.insert(soundPtr);

	return true;

}

bool AudioManager::ClearAudioList2D() {

	set<ISound*>::iterator iter = audioList2D.begin();
	while (audioList2D.size() > 0) {
		if (*iter) {
			(*iter)->drop();
		}
		iter = audioList2D.erase(iter);
	}

	std::cout << "Clear Audio List 2D" << std::endl;

	return true;

}

bool AudioManager::PlayAudio3D(const char* audioFile, bool looped, float minDistance, float maxDistance, Vector3 listenerPosition, Vector3 listenerDirection, Vector3 soundPosition, Vector3 upVector ) {

	audioEngine->setListenerPosition(vec3df(listenerPosition.x, listenerPosition.y, listenerPosition.z),
									 vec3df(listenerDirection.x, listenerDirection.y, listenerDirection.z),
									 vec3df(upVector.x, upVector.y, upVector.z));

	ISound* soundPtr = audioEngine->play3D(audioFile, vec3df(soundPosition.x, soundPosition.y, soundPosition.z), looped, false, true);
	soundPtr->setMinDistance(minDistance);
	soundPtr->setMaxDistance(maxDistance);

	audioList3D.insert(soundPtr);

	return true;

}

bool AudioManager::PlayAudio3D(const char* audioFile, bool looped, float minDistance, Vector3 listenerPosition, Vector3 listenerDirection, Vector3 soundPosition, Vector3 upVector ) {
	
	audioEngine->setListenerPosition(vec3df(listenerPosition.x, listenerPosition.y, listenerPosition.z),
									 vec3df(listenerDirection.x, listenerDirection.y, listenerDirection.z),
									 vec3df(upVector.x, upVector.y, upVector.z));


	ISound* soundPtr = audioEngine->play3D(audioFile, vec3df(soundPosition.x, soundPosition.y, soundPosition.z), looped, false, true);
	soundPtr->setMinDistance(minDistance);

	audioList3D.insert(soundPtr);

	return true;

}

bool AudioManager::UpdateAudio3D(const char* audioFile, Vector3 soundPosition) {

	ISoundSource* soundSourcePtr = audioEngine->getSoundSource(audioFile, false);
	
	if (soundSourcePtr == 0) {
		return false;
	}

	for (set<ISound*>::iterator iter = audioList3D.begin(); iter != audioList3D.end(); ++iter) {
		ISound* soundPtr = *iter;
		if (soundPtr->getSoundSource() == soundSourcePtr) {
			soundPtr->setPosition(vec3df(soundPosition.x, soundPosition.y, soundPosition.z));
			break;
		}
	}

	return true;

}

bool AudioManager::UpdateListener3D(Vector3 listenerPosition, Vector3 listenerDirection, Vector3 upVector) {

	audioEngine->setListenerPosition(vec3df(listenerPosition.x, listenerPosition.y, listenerPosition.z),
									 vec3df(listenerDirection.x, listenerDirection.y, listenerDirection.z),
									 vec3df(upVector.x, upVector.y, upVector.z));

	return true;

}

bool AudioManager::ClearAudioList3D() {

	set<ISound*>::iterator iter = audioList3D.begin();
	while (audioList3D.size() > 0) {
		if (*iter) {
			(*iter)->drop();
		}
		iter = audioList3D.erase(iter);
	}

	std::cout << "Clear Audio List 2D" << std::endl;

	return true;

}

void AudioManager::SetVolumeAll(const float& volume) {

	for (set<ISound*>::iterator iter = audioList2D.begin(); iter != audioList2D.end(); ++iter) {
		(*iter)->setVolume(Math::Clamp(volume, 0.0f, 1.0f));
	}

	for (set<ISound*>::iterator iter = audioList3D.begin(); iter != audioList2D.end(); ++iter) {
		(*iter)->setVolume(Math::Clamp(volume, 0.0f, 1.0f));
	}

}