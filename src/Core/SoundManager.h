#pragma once
#include "raylib.h"

enum class SFX{PLAYER_STEP, FIREBALL, FB_SPEECH1, FB_SPEECH2, FB_SPEECH3, ROBOT_SPEECH1, DOORS, PLAYER_MELEE, PLAYER_LANDING, MELEE_HIT, DEATHSCREEN};
enum class TRACK{MENU_TRACK, AREA_ONE, AREA_TWO, AREA_THREE, FB_INTRO, FB_LOOP1, FB_FIGHT1, FB_FIGHT2, OUTRO};
class SoundManager {
public:
	SoundManager();
	void PlaySfx(SFX sfx);
	void PlayTrack(Music music);
	void UpdateTrack(Music music);
	void StopCurrentTrack(Music music);
	void SetSfxVolume(float volume);
	void SetTrackVolume(float volume);
	void StopThisTrack(bool stop);
	~SoundManager();
private:
	Sound sound[11];
	bool stopTrack = false;
	float soundVolume = 1.0;
	float trackVolume = 1.0;
};