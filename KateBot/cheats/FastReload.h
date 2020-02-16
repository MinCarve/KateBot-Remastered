#ifndef _FAST_RELOAD_H_
#define _FAST_RELOAD_H_

#include "..\main.h"

class FastReload {
public:
	void Start() {
		try {
			for (;;) {
				std::this_thread::sleep_for(std::chrono::milliseconds(70));

				if (cfg->panicMode)
					continue;

				if (!miscUtils->IsCSGOActiveWindow())
					continue;

				if (!cfg->fastReload)
					continue;

				if (!csgo->IsInGame())
					continue;

				int  m_bReloadVisuallyComplete = mem->Read<int>(LocalEntity.GetActiveWeaponBase() + ofs->m_bReloadVisuallyComplete), ammo = LocalEntity.GetActiveWeaponAmmo();

				if (mem->Read<bool>(LocalEntity.GetActiveWeaponBase() + ofs->m_bInReload) &&
					(m_bReloadVisuallyComplete == 1 || m_bReloadVisuallyComplete == 257) &&
					ammo != this->TEMPORARY_AMMO_VAR)
				{
					this->TEMPORARY_AMMO_VAR = ammo;
					this->Reload();
					this->TEMPORARY_AMMO_VAR = NULL;
				}
			}
		}
		catch (...) {
			mem->debuglog(__FILE__);
		}
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
private:
	int TEMPORARY_AMMO_VAR = NULL;
};

#endif