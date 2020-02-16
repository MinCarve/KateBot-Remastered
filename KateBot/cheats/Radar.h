#ifndef _RADAR_H_
#define _RADAR_H_

#include "..\main.h"

class Radar {
public:
	void Start() {
		try {
			for (;;) {
				std::this_thread::sleep_for(std::chrono::milliseconds(50));

				if (cfg->panicMode)
					continue;

				if (!miscUtils->IsCSGOActiveWindow())
					continue;

				if (!cfg->radar)
					continue;

				if (!csgo->IsInGame())
					continue;

				for (int x = 1; x < csgo->GlobalVars().maxClients; x++)
				{
					Entity RadarPlayer = EntityList[x];

					if (!RadarPlayer.IsDead() && !RadarPlayer.IsDormant())
						mem->Write<int>(RadarPlayer.GetPointer() + ofs->m_bSpotted, 1);
				}
			}
		}
		catch (...) {
			mem->debuglog(__FILE__);
		}
	}
};

#endif