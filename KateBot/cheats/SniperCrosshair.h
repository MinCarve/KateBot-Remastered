#ifndef _SNIPER_CROSSHAIR_H_
#define _SNIPER_CROSSHAIR_H_

#include "..\main.h"

class SniperCrosshair {
public:

	~SniperCrosshair() {
		C_SniperCrosshair(0);
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
								C_SniperCrosshair(3);
							else
								C_SniperCrosshair(0);
						else
							C_SniperCrosshair(0);
					else
						C_SniperCrosshair(0);
				else
					C_SniperCrosshair(0);

			}
		}
		catch (...) {
			mem->debuglog(__FILE__);
		}
	}

	void C_SniperCrosshair(int value) {
		static auto weapon_debug_spread_show = cvar::find("weapon_debug_spread_show");

		weapon_debug_spread_show.SetInt(value);
	}
private:
};

#endif