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

				if (!cfg->nightmode.enabled) {
					if (NeedUpdate) {
						csgo->ForceFullUpdate();
						NeedUpdate = false;
					}
					continue;
				}

				if (!csgo->IsInGame())
					continue;

				NeedUpdate = true;

				int toneMapCIndex = mem->Read<int>(LocalEntity.GetPointer() + ofs->m_hTonemapController) & 0xFFF;
				DWORD toneMapHandle = mem->Read<DWORD>(client->GetImage() + ofs->m_dwEntityList + (toneMapCIndex - 1) * 0x10);

				mem->Write<float>(toneMapHandle + ofs->m_bUseCustomAutoExposureMax, .2f);
				mem->Write<float>(toneMapHandle + ofs->m_flCustomBloomScale, .2f);

				mem->Write<float>(toneMapHandle + ofs->m_flCustomAutoExposureMin, (float)(cfg->nightmode.amount * 0.01));
				mem->Write<float>(toneMapHandle + ofs->m_flCustomAutoExposureMax, (float)(cfg->nightmode.amount * 0.01));
			}
		}
		catch (...) {
			mem->debuglog(__FILE__);
		}
	}
};

#endif