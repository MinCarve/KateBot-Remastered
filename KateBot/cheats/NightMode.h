#ifndef _NIGHTMODE_H_
#define _NIGHTMODE_H_

#include "..\main.h"

class NightMode {
public:
	bool NeedUpdate = true;

	void Start() {
		try {
			for (;;) {
				std::this_thread::sleep_for(std::chrono::milliseconds(200));

				if (cfg->panicMode)
					continue;

				if (!miscUtils->IsCSGOActiveWindow())
					continue;

				if (!cfg->nightmode.enabled || cfg->StreamMode) {
					if (NeedUpdate) {
						csgo->ForceFullUpdate();
						NeedUpdate = false;
					}
					continue;
				}

				if (!csgo->IsInGame())
					continue;

				NeedUpdate = true;

				for (int x = 0; x < csgo->GetMaxEntities(); x++)
				{
					DWORD Entity = mem->Read<DWORD>(client->GetImage() + ofs->m_dwEntityList + x * 0x10);
					if (csgo->GetClassID(Entity) != CEnvTonemapController) continue;

					mem->Write<byte>(Entity + ofs->m_bUseCustomAutoExposureMax, 1);
					mem->Write<byte>(Entity + ofs->m_bUseCustomAutoExposureMin, 1);
					mem->Write<float>(Entity + ofs->m_flCustomBloomScale, .2f);

					mem->Write<float>(Entity + ofs->m_flCustomAutoExposureMin, (float)(cfg->nightmode.amount * 0.001));
					mem->Write<float>(Entity + ofs->m_flCustomAutoExposureMax, (float)(cfg->nightmode.amount * 0.001));
				}
			}
		}
		catch (...) {
			mem->debuglog(__FILE__);
		}
	}
};

#endif