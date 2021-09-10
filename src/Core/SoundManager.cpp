#include "SoundManager.h"
#include "../Global.h"
#include <iostream>

SoundManager::SoundManager()
{
	//sound initialization
	sound[0] = LoadSound("assets/audio/sfx/footstep.wav");
	sound[1] = LoadSound("assets/audio/sfx/fireball.wav");
	sound[2] = LoadSound("assets/audio/sfx/maraap_speech1.wav");
	sound[3] = LoadSound("assets/audio/sfx/maraap_speech2.wav");
	sound[4] = LoadSound("assets/audio/sfx/maraap_speech3.wav");
	sound[5] = LoadSound("assets/audio/sfx/Robot_Sound1.wav");
	sound[6] = LoadSound("assets/audio/sfx/Shutting_Doors.wav");
	sound[7] = LoadSound("assets/audio/sfx/player_melee.wav");
	sound[8] = LoadSound("assets/audio/sfx/player_landing.wav");
	sound[9] = LoadSound("assets/audio/sfx/dialogue.wav");
	sound[10] = LoadSound("assets/audio/sfx/dead.wav");
	sound[11] = LoadSound("assets/audio/sfx/testsound.wav");
}

void SoundManager::PlaySfx(SFX sfx)
{
	int selectedSound = 0;
	switch (sfx)
	{
	case SFX::PLAYER_STEP:
		selectedSound = 0;
		break;
	case SFX::FIREBALL:
		selectedSound = 1;
		break;
	case SFX::FB_SPEECH1:
		selectedSound = 2;
		break;
	case SFX::FB_SPEECH2:
		selectedSound = 3;
		break;
	case SFX::FB_SPEECH3:
		selectedSound = 4;
		break;
	case SFX::ROBOT_SPEECH1:
		selectedSound = 5;
		break;
	case SFX::DOORS:
		selectedSound = 6;
		break;
	case SFX::PLAYER_MELEE:
		selectedSound = 7;
		break;
	case SFX::PLAYER_LANDING:
		selectedSound = 8;
		break;
	case SFX::DIALOGUE:
		selectedSound = 9;
		break;
	case SFX::DEATHSCREEN:
		selectedSound = 10;
		break;
	case SFX::TEST:
		selectedSound = 11;
		break;
	default:
		break;
	}

	SetSoundVolume(sound[selectedSound], soundVolume);
	PlaySound(sound[selectedSound]);
	
}



void SoundManager::SetSfxVolume(float volume)
{
	soundVolume = volume;
}

void SoundManager::SetTrackVolume(float volume)
{
	trackVolume = volume;
	
}

float SoundManager::GetTrackVolume() const
{
	return trackVolume;
}


SoundManager::~SoundManager()
{
	
}
