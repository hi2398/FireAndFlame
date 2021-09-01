#include "SoundManager.h"
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
	sound[9] = LoadSound("assets/audio/sfx/melee_hit.wav");

	//music initialization
	music[0] = LoadMusicStream("assets/audio/tracks/title_screen.mp3");
	music[1] = LoadMusicStream("assets/audio/tracks/AreaOne.mp3");
	music[2] = LoadMusicStream("assets/audio/tracks/AreaTwo.mp3");
}

void SoundManager::PlaySfx(SFX sfx)
{
	int selectedSound;
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
	case SFX::MELEE_HIT:
		selectedSound = 9;
		break;
	default:
		break;
	}

	SetSoundVolume(sound[selectedSound], soundVolume);
	PlaySound(sound[selectedSound]);
	
}

void SoundManager::PlayTrack(TRACK track)
{
	int selectedTrack;
	switch (track)
	{
	case TRACK::MENU_TRACK:
		selectedTrack = 0;
		break;
	case TRACK::AREA_ONE:
		selectedTrack = 1;
		break;
	case TRACK::AREA_TWO:
		selectedTrack = 2;
		break;
	default:
		break;
	}

	
	PlayMusicStream(music[selectedTrack]);
}

void SoundManager::UpdateTrack(TRACK track)
{
	int selectTrack;
	switch (track)
	{
	case TRACK::MENU_TRACK:
		selectTrack = 0;
		break;
	case TRACK::AREA_ONE:
		selectTrack = 1;
		break;
	case TRACK::AREA_TWO:
		selectTrack = 2;
		break;
	default:
		return;
		break;
	}
	SetMusicVolume(music[selectTrack], trackVolume);
	UpdateMusicStream(music[selectTrack]);
	if (GetMusicTimePlayed(music[selectTrack]) == GetMusicTimeLength(music[selectTrack])) {
		StopMusicStream(music[selectTrack]);
		PlayMusicStream(music[selectTrack]);
	}
	return;
}

void SoundManager::StopCurrentTrack()
{
	for (const auto& track : music) {
		if (IsMusicStreamPlaying(track)) StopMusicStream(track);
	}
}

void SoundManager::SetSfxVolume(float volume)
{
	soundVolume = volume;
}

void SoundManager::SetTrackVolume(float volume)
{
	trackVolume = volume;
	
}

SoundManager::~SoundManager()
{
	
}
