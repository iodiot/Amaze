#ifndef SOUND_H
#define SOUND_H

struct SoundType
{
	enum e
	{
		Crumble,
		Ladder,
		Roll,
		Pickup,
		Cut,
		Treasure,
		Click,
		Click2
	};

	static char* GetFileName(SoundType::e sound)
	{
		switch (sound)
		{
			case SoundType::Crumble: return "crumble"; 
			case SoundType::Ladder: return "ladder";
			case SoundType::Roll: return "roll";
			case SoundType::Pickup: return "pickup";
			case SoundType::Cut: return "cut";
			case SoundType::Treasure: return "treasure";
			case SoundType::Click: return "click";
			case SoundType::Click2: return "click2";
			default: return "";
		}
	}
};

void MixAudio(void *unused, Uint8 *stream, int len);

class Sound
{
private:
	// Low level
	static void Play(const char *file);

public:
	static void Play(SoundType::e sound);
};



#endif