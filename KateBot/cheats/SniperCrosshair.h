#ifndef _SNIPER_CROSSHAIR_H_
#define _SNIPER_CROSSHAIR_H_

#include "..\main.h"

class SniperCrosshair {
public:
	
	~SniperCrosshair() {
		SET_WDSS(0);
	}

	void Start() {
		try {

			for (;;) {
				std::this_thread::sleep_for(std::chrono::milliseconds(35));

				if (cfg->panicMode)
					continue;

				if (!miscUtils->IsCSGOActiveWindow())
					continue;

				if (!csgo->IsInGame())
					continue;

				if (!cfg->StreamMode)
					if (cfg->SniperCrosshair)
						if (LocalEntity.GetWeaponType(0) == EWeaponType::WeapType_Sniper)
							if (!mem->Read<bool>(LocalEntity.GetPointer() + ofs->m_bIsScoped))
								SET_WDSS(3);
							else
								SET_WDSS(0);
						else
							SET_WDSS(0);
					else
						SET_WDSS(0);
				else
					SET_WDSS(0);

			}
		}
		catch (...) {
			mem->debuglog(__FILE__);
		}
	}

	void SET_WDSS(int v) {
		static cs_convar weapon_debug_spread_show = cvar::find("weapon_debug_spread_show");

		weapon_debug_spread_show.SetInt(v);
	}
};

#endif