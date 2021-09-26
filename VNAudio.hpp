#pragma once

#ifndef OPENGL_INCLUDED
#include"VNLibsImport.hpp"
#endif // !OPENGL_INCLUDED

class VNAudioController
{
public:
	VNAudioController();
	~VNAudioController();
	void VNPlayAudio(int index, bool loop);
	void VNAddAudio(const char* path);

private:
	irrklang::ISoundEngine* mSoundEngine;
	std::vector<const char*> mPaths;
};

VNAudioController::VNAudioController()
{
	mSoundEngine = irrklang::createIrrKlangDevice();
}

VNAudioController::~VNAudioController()
{
}

void VNAudioController::VNAddAudio(const char* path)
{
	mPaths.push_back(path);
	return;
}

void VNAudioController::VNPlayAudio(int index, bool loop)
{
	mSoundEngine->play2D(mPaths[index], loop);
	return;
}
