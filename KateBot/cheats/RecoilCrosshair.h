#ifndef _RECOIL_CROSSHAIR_H_
#define _RECOIL_CROSSHAIR_H_

#include "..\main.h"

class RecoilCrosshair {
public:

	~RecoilCrosshair() {
		SET_RC(0);
	}

	void Start() {
		try {
			for (;;) {
				std::this_thread::sleep_for(std::chrono::milliseconds(100));

				if (!miscUtils->IsCSGOActiveWindow())
					continue;

				if (!csgo->IsInGame())
					continue;

				if (!cfg->StreamMode)
					if (cfg->RecoilCrosshair && 
						(LocalEntity.GetWeaponType(0) == EWeaponType::WeapType_Rifle 
							|| LocalEntity.GetWeaponType(0) == EWeaponType::WeapType_SMG
								|| LocalEntity.GetWeaponType(0) == EWeaponType::WeapType_LMG)) {
						SET_RC(TRUE);
					}
					else
						SET_RC(FALSE);
				else
					SET_RC(FALSE);
			}
		}
		catch (...) {
			mem->debuglog(__FILE__);
		}
	}

	void SET_RC(bool v) {
		static cs_convar cl_crosshair_recoil = cvar::find("cl_crosshair_recoil");

		cl_crosshair_recoil.SetFloat(v);
	}
};

#endif