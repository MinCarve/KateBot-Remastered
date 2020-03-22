#ifndef _RECOIL_CROSSHAIR_H_
#define _RECOIL_CROSSHAIR_H_

#include "..\main.h"

class RecoilCrosshair {
public:

	~RecoilCrosshair() {
		C_RecoilCrosshair(0);
	}

	void Start() {
		try {
			for (;;) {
				std::this_thread::sleep_for(std::chrono::milliseconds(100));

				if (cfg->panicMode)
					continue;

				if (!miscUtils->IsCSGOActiveWindow())
					continue;

				if (!csgo->IsInGame())
					continue;


				if (!cfg->StreamMode)
					if (cfg->RecoilCrosshair && 
						(LocalEntity.GetWeaponType(0) == EWeaponType::WeapType_Rifle 
							|| LocalEntity.GetWeaponType(0) == EWeaponType::WeapType_SMG
								|| LocalEntity.GetWeaponType(0) == EWeaponType::WeapType_LMG)) {
						C_RecoilCrosshair(TRUE);
					}
					else
						C_RecoilCrosshair(FALSE);
				else
					C_RecoilCrosshair(FALSE);
			}
		}
		catch (...) {
			mem->debuglog(__FILE__);
		}
	}

	void C_RecoilCrosshair(bool value) {
		static auto cl_crosshair_recoil = cvar::find("cl_crosshair_recoil");

		cl_crosshair_recoil.SetFloat(value);
	}
};

#endif