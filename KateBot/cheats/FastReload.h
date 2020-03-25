#ifndef _FAST_RELOAD_H_
#define _FAST_RELOAD_H_

#include "..\main.h"

class FastReload {
public:
	void Start() {
		try {
			for (;;) {
				std::this_thread::sleep_for(std::chrono::milliseconds(30));

				if (cfg->panicMode)
					continue;

				if (!miscUtils->IsCSGOActiveWindow())
					continue;

				if (!cfg->fastReload)
					continue;

				if (!csgo->IsInGame())
					continue;

				if (!MouseEnable()) continue;

				bool m_bReloadVisuallyComplete = mem->Read<bool>(LocalEntity.GetActiveWeaponBase() + ofs->m_bReloadVisuallyComplete), ammo = LocalEntity.GetActiveWeaponAmmo();

				if (mem->Read<bool>(LocalEntity.GetActiveWeaponBase() + ofs->m_bInReload) &&
					m_bReloadVisuallyComplete && ammo != this->TEMPORARY_AMMO_VAR)
				{
					this->TEMPORARY_AMMO_VAR = ammo;
					this->CMD_Reload();
					this->TEMPORARY_AMMO_VAR = NULL;
				}
			}
		}
		catch (...) {
			mem->debuglog(__FILE__);
		}
	}

	int MouseEnable() {
		static auto cl_mouseenable = cvar::find("cl_mouseenable");

		return cl_mouseenable.GetInt();
	}

	void Reload() {
		keybd_event(VkKeyScan('Q'), 0x10, 0, 0);
		Sleep(10);
		keybd_event(VkKeyScan('Q'), 0x10, KEYEVENTF_KEYUP, 0);
		Sleep(50);
		keybd_event(VkKeyScan('Q'), 0x10, 0, 0);
		Sleep(10);
		keybd_event(VkKeyScan('Q'), 0x10, KEYEVENTF_KEYUP, 0);
	}

	void CMD_Reload() {
		csgo->ClientCMD("invprev");
		Sleep(20);
		csgo->ClientCMD("invnext");
	}
private:
	int TEMPORARY_AMMO_VAR = NULL;
};

#endif