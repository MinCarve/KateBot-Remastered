#ifndef _SKYBOX_CHANGER_H_
#define _SKYBOX_CHANGER_H_

#include "..\main.h"

class SkyBoxChanger {
public:

	~SkyBoxChanger() {
		//C_RecoilCrosshair(0);
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
					if (cfg->SkyBoxChanger) {
						C_3DSky(FALSE);
						C_SkyboxName(cfg->skybox.name);
					}
			}
		}
		catch (...) {
			mem->debuglog(__FILE__);
		}
	}

	void C_SkyboxName(std::string value) {
		static auto sky = cvar::find("sv_skyname");

		sky.SetString(value);
	}

	void C_3DSky(bool value) {
		static auto sky = cvar::find("r_3dsky");

		sky.SetInt(value);
	}

	std::string R_SkyboxName() {
		static auto sky = cvar::find("sv_skyname");

		return sky.GetString();
	}
};

#endif