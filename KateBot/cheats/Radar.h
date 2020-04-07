#ifndef _RADAR_H_
#define _RADAR_H_

#include "..\main.h"

class Radar {
public:
	void Start() {
		try {
			for (;;) {
				std::this_thread::sleep_for(std::chrono::milliseconds(50));

				if (!miscUtils->IsCSGOActiveWindow())
					continue;

				if (!cfg->radar || cfg->StreamMode)
					continue;

				if (!csgo->IsInGame())
					continue;

				for (int x = 1; x < csgo->GetMaxClients(); x++)
					if (!EntityList[x].IsDead() && !EntityList[x].IsDormant())
						mem->Write<int>(EntityList[x].GetPointer() + ofs->m_bSpotted, 1);
			}
		}
		catch (...) {
			mem->debuglog(__FILE__);
		}
	}
};

#endif