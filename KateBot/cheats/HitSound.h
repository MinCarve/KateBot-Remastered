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

				this->total_hits = mem->Read<int>(LocalEntity.GetPointer() + ofs->m_totalHitsOnServer);

				if (this->total_hits > this->hits)
				{
					this->hits = this->total_hits;

					csgo->ClientCMD("play buttons/arena_switch_press_02");
				}
			}
		}
		catch (...) {
			mem->debuglog(__FILE__);
		}
	}
private:
	int hits = mem->Read<int>(LocalEntity.GetPointer() + ofs->m_totalHitsOnServer);
	int total_hits = -1;
};

#endif