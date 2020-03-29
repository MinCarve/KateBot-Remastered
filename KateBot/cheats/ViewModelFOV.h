#ifndef _VIEW_MODEL_FOV_H_
#define _VIEW_MODEL_FOV_H_

#include "..\main.h"

class ViewModelFOVChanger {
public:

	~ViewModelFOVChanger() {
		SET_VMFOV(GET_VMFOV());
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
					if (cfg->ViewModelFOVChanger) {
						SET_VMFOV(cfg->viewmodel.fov);
					}
					else
						SET_VMFOV(GET_VMFOV());
				else
					SET_VMFOV(GET_VMFOV());

			}
		}
		catch (...) {
			mem->debuglog(__FILE__);
		}
	}

	void SET_VMFOV(float v) {
		static cs_convar viewmodel_fov = cvar::find("viewmodel_fov");

		viewmodel_fov.SetFloat(v);
	}

	float GET_VMFOV() {
		static cs_convar viewmodel_fov = cvar::find("viewmodel_fov");

		return std::stof(viewmodel_fov.GetDefaultValue());
	}
};

#endif