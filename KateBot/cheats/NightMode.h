#ifndef _NIGHTMODE_H_
#define _NIGHTMODE_H_

#include "..\main.h"

class NightMode {
public:
	bool NeedUpdate = false;

	void Start() {
		try {
			for (;;) {
				std::this_thread::sleep_for(std::chrono::milliseconds(200));

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

				DWORD hTonemap = mem->Read<DWORD>(LocalEntity.GetPointer() + ofs->m_hTonemapController) & 0xFFF;
				DWORD pEntity = mem->Read<DWORD>(client->GetImage() + ofs->m_dwEntityList + (hTonemap - 1) * 0x10);

				mem->Write<bool>(pEntity + ofs->m_bUseCustomAutoExposureMin, true);
				mem->Write<bool>(pEntity + ofs->m_bUseCustomAutoExposureMax, true);
				mem->Write<float>(pEntity + ofs->m_flCustomAutoExposureMin, cfg->nightmode.amount);
				mem->Write<float>(pEntity + ofs->m_flCustomAutoExposureMax, cfg->nightmode.amount);
			}
		}
		catch (...) {
			mem->debuglog(__FILE__);
		}
	}
};

#endif