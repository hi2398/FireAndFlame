#include "SoundManager.h"

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
}

void SoundManager::PlaySfx(SFX sfx)
{
	switch (sfx)
	{
	case SFX::PLAYER_STEP:
		PlaySound(sound[0]);
		break;
	case SFX::FIREBALL:
		PlaySound(sound[1]);
		break;
	case SFX::FB_SPEECH1:
		PlaySound(sound[2]);
		break;
	case SFX::FB_SPEECH2:
		PlaySound(sound[3]);
		break;
	case SFX::FB_SPEECH3:
		PlaySound(sound[4]);
		break;
	case SFX::ROBOT_SPEECH1:
		PlaySound(sound[5]);
		break;
	case SFX::DOORS:
		PlaySound(sound[6]);
		break;
	case SFX::PLAYER_MELEE:
		PlaySound(sound[7]);
		break;
	case SFX::PLAYER_LANDING:
		PlaySound(sound[8]);
		break;
	case SFX::MELEE_HIT:
		PlaySound(sound[9]);
		break;
	default:
		break;
	}
}

void SoundManager::PlayTrack(TRACK track)
{
	switch (track)
	{
	case TRACK::MENU_TRACK:
		PlayMusicStream(music[0]);
		break;
	case TRACK::AREA_ONE:
		PlayMusicStream(music[1]);
		break;
	default:
		break;
	}
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
	default:
		return;
		break;
	}
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

SoundManager::~SoundManager()
{
}
