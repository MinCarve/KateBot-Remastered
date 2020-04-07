#ifndef _SKYBOX_CHANGER_H_
#define _SKYBOX_CHANGER_H_

#include "..\main.h"

class SkyBoxChanger {
public:

	~SkyBoxChanger() {
		SET_SN(this->map_default_skyboxname);
	}

	void Start() {
		try {
			for (;;) {
				std::this_thread::sleep_for(std::chrono::milliseconds(50));

				if (!miscUtils->IsCSGOActiveWindow())
					continue;

				if (!csgo->IsInGame()) {
					if (this->set_sn) this->set_sn = false;
					continue;
				}
				else {
					if (!this->set_sn) {
						this->set_sn = true;
						this->map_default_skyboxname = this->GET_SN();
					}
				}

				SET_3DSKY(FALSE);

				if (!cfg->StreamMode)
					if (cfg->SkyBoxChanger) {
						SET_SN(cfg->skybox.name);
					}else
						SET_SN(this->map_default_skyboxname);
				else
					SET_SN(this->map_default_skyboxname);

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

	std::string GET_SN() {
		static cs_convar sv_skyname = cvar::find("sv_skyname");

		return sv_skyname.GetString();
	}

	void SET_3DSKY(bool v) {
		static cs_convar r_3dsky = cvar::find("r_3dsky");

		r_3dsky.SetInt(v);
	}
private:
	bool set_sn;
	std::string map_default_skyboxname;
};

#endif