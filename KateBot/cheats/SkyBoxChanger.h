#ifndef _SKYBOX_CHANGER_H_
#define _SKYBOX_CHANGER_H_

#include "..\main.h"

class SkyBoxChanger {
public:

	~SkyBoxChanger() {
		SET_SN(this->DefaultSkyBoxName());
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

				SET_3DSKY(FALSE);

				if (!cfg->StreamMode)
					if (cfg->SkyBoxChanger) {
						SET_SN(cfg->skybox.name);
					}else
						SET_SN(std::string(this->DefaultSkyBoxName()));
				else
					SET_SN(std::string(this->DefaultSkyBoxName()));

			}
		}
		catch (...) {
			mem->debuglog(__FILE__);
		}
	}

	auto DefaultSkyBoxName() -> std::string {
		std::unique_ptr<char[]> ptr = std::make_unique<char[]>(120);
		mem->Read(engine->GetImage() + 0x7A78FC, ptr.get(), 120);

		return std::string(ptr.get());
	}

	void SET_SN(std::string v) {
		static cs_convar sv_skyname = cvar::find("sv_skyname");

		sv_skyname.SetString(v);
	}

	void SET_3DSKY(bool v) {
		static cs_convar r_3dsky = cvar::find("r_3dsky");

		r_3dsky.SetInt(v);
	}
};

#endif