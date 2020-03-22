#ifndef _SKYBOX_CHANGER_H_
#define _SKYBOX_CHANGER_H_

#include "..\main.h"

class SkyBoxChanger {
public:

	~SkyBoxChanger() {
		std::unique_ptr<char[]> ptr = std::make_unique<char[]>(120);
		mem->Read(engine->GetImage() + 0x7A797C, ptr.get(), 120);

		C_SkyboxName(std::string(ptr.get()));
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

				//std::unordered_map<std::string, std::string>::const_iterator select_map = this->maps_by_skybox.find("maps/de_dust2.bsp");
				/*for (auto it = this->maps_by_skybox.cbegin(); it != this->maps_by_skybox.cend(); ++it)
					if (std::string("maps/de_dust2.bsp").find(it->first) != std::string::npos)
						printf("select_map: %s\n", it->second.c_str());*/

				std::unique_ptr<char[]> ptr = std::make_unique<char[]>(120);
				mem->Read(engine->GetImage() + 0x7A797C, ptr.get(), 120);

				C_3DSky(FALSE);

				if (!cfg->StreamMode)
					if (cfg->SkyBoxChanger) {
						C_SkyboxName(cfg->skybox.name);
					}else
						C_SkyboxName(std::string(ptr.get()));
				else
					C_SkyboxName(std::string(ptr.get()));

			}
		}
		catch (...) {
			mem->debuglog(__FILE__);
		}
	}

	void C_SkyboxName(std::string value) {
		static auto sv_skyname = cvar::find("sv_skyname");

		sv_skyname.SetString(value);
	}

	int R_SkyboxName() {
		static auto sv_skyname = cvar::find("sv_skyname");

		return sv_skyname.GetInt();
	}

	void C_3DSky(bool value) {
		static auto r_3dsky = cvar::find("r_3dsky");

		r_3dsky.SetInt(value);
	}
private:
	std::unordered_map<std::string, std::string> maps_by_skybox =
	{
		{ "ar_baggage", "cs_baggage_skybox_" }, { "cs_office", "sky_cs15_daylight01_hdr" },
		{ "de_dust2", "nukeblank" }
	};
};

#endif