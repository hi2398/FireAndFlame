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
	sound[9] = LoadSound("assets/audio/sfx/melee_hit.wav");
	sound[10] = LoadSound("assets/audio/sfx/dead.wav");

	//music initialization
	music[0] = LoadMusicStream("assets/audio/tracks/title_screen.mp3");
	music[1] = LoadMusicStream("assets/audio/tracks/AreaOne.mp3");
	music[2] = LoadMusicStream("assets/audio/tracks/AreaTwo.mp3");
	music[3] = LoadMusicStream("assets/audio/tracks/FinalBossIntro.mp3");
	music[4] = LoadMusicStream("assets/audio/tracks/FinalBossLoop1.mp3");
	music[5] = LoadMusicStream("assets/audio/tracks/AreaThree.mp3");
	music[6] = LoadMusicStream("assets/audio/tracks/FinalBoss_FightIntro.mp3");
	music[7] = LoadMusicStream("assets/audio/tracks/FinalBoss_FightLoop.mp3");
	music[8] = LoadMusicStream("assets/audio/tracks/Outro.mp3");
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
	case SFX::MELEE_HIT:
		selectedSound = 9;
		break;
	case SFX::DEATHSCREEN:
		selectedSound = 10;
		break;
	default:
		break;
	}

	SetSoundVolume(sound[selectedSound], soundVolume);
	PlaySound(sound[selectedSound]);
	
}

void SoundManager::PlayTrack(TRACK track)
{
	selectedTrack;
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
	case TRACK::FB_INTRO:
		selectedTrack = 3;
		break;
	case TRACK::FB_LOOP1:
		selectedTrack = 4;
		break;
	case TRACK::AREA_THREE:
		selectedTrack = 5;
		break;
	case TRACK::FB_FIGHT1:
		selectedTrack = 6;
		break;
	case TRACK::FB_FIGHT2:
		selectedTrack = 7;
		break;
	case TRACK::OUTRO:
		selectedTrack = 8;
		break;
	default:
		break;
	}

	
	PlayMusicStream(music[selectedTrack]);
}

void SoundManager::UpdateTrack(TRACK track)
{

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
	case TRACK::FB_INTRO:
		selectedTrack = 3;
		break;
	case TRACK::FB_LOOP1:
		selectedTrack = 4;
		break;
	case TRACK::AREA_THREE:
		selectedTrack = 5;
		break;
	case TRACK::FB_FIGHT1:
		selectedTrack = 6;
		break;
	case TRACK::FB_FIGHT2:
		selectedTrack = 7;
		break;
	case TRACK::OUTRO:
		selectedTrack = 8;
		break;
	default:
		return;
		break;
	}
	if (playerCharacter->GetHealth() <= 10 && sceneManager->GetActiveScene()->GetSceneName() != SceneEnums::FinalBoss) SetMusicPitch(music[selectedTrack], 1.1);
	else SetMusicPitch(music[selectedTrack], 1.0);

	SetMusicVolume(music[selectedTrack], trackVolume);

	UpdateMusicStream(music[selectedTrack]);
	if (selectedTrack == 6) fbTimePlayed = GetMusicTimePlayed(music[selectedTrack]);
	return;
}


void SoundManager::StopCurrentTrack()
{
	for (const auto& track : music) {
		if (IsMusicStreamPlaying(track)) StopMusicStream(track);
	}

	fbTimePlayed = 0.0;
}

int SoundManager::GetCurrentTrack() const
{
	return selectedTrack;
}

float SoundManager::GetTrackTimePlayed() const
{
	return fbTimePlayed;
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
