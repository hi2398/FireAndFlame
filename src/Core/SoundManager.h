#pragma once
#include "raylib.h"

enum class SFX{PLAYER_STEP, FIREBALL, FB_SPEECH1, FB_SPEECH2, FB_SPEECH3, ROBOT_SPEECH1, DOORS, PLAYER_MELEE, PLAYER_LANDING, MELEE_HIT};
enum class TRACK{MENU_TRACK, AREA_ONE, AREA_TWO, AREA_THREE, FB_INTRO, FB_LOOP1};
class SoundManager {
public:
	SoundManager();
	void PlaySfx(SFX sfx);
	void PlayTrack(TRACK track);
	void UpdateTrack(TRACK track);
	void StopCurrentTrack(int selectedTrack);
	int GetCurrentTrack() const;
	void SetSfxVolume(float volume);
	void SetTrackVolume(float volume);
	~SoundManager();
private:
	Sound sound[10];
	Music music[6];
	int selectedTrack;

	float soundVolume = 1.0;
	float trackVolume = 1.0;
};