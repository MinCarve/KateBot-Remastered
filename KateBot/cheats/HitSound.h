#ifndef _HITSOUND_H_
#define _HITSOUND_H_

#include "..\main.h"

class HitSound {
public:
	void Start() {
		try {
			for (;;) {
				std::this_thread::sleep_for(std::chrono::milliseconds(30));

				if (!miscUtils->IsCSGOActiveWindow())
					continue;

				if (!csgo->IsInGame())
					continue;

				if (cfg->StreamMode)
					continue;

				if (!cfg->hitsound)
					continue;

				static int hits = LocalEntity.GetTotalHits();
				int current_hits = LocalEntity.GetTotalHits();

				if (hits != current_hits && current_hits != 0)
				{
					hits = current_hits;
					csgo->ClientCMD("play buttons/arena_switch_press_02");
				}

			}
		}
		catch (...) {
			mem->debuglog(__FILE__);
		}
	}
};

#endif