#pragma once
#include "raylib.h"





enum class SFX{PLAYER_STEP, FIREBALL, FB_SPEECH1, FB_SPEECH2, FB_SPEECH3, ROBOT_SPEECH1, DOORS, PLAYER_MELEE, PLAYER_LANDING, MELEE_HIT, DEATHSCREEN, DIALOGUE1, DIALOGUE2, DIALOGUE3, TEST};

class SoundManager {
public:
	SoundManager();
	void PlaySfx(SFX sfx);
	bool IsSfxPlaying();
	void SetSfxVolume(float volume);
	void SetTrackVolume(float volume);
	float GetTrackVolume() const;
	~SoundManager();
private:
	Sound sound[14];
	bool stopTrack = false;
	float soundVolume = 1.0;
	float trackVolume = 1.0;
	int selectedSound = 0;
};