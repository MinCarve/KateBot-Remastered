#ifndef _VIEW_MODEL_FOV_H_
#define _VIEW_MODEL_FOV_H_

#include "..\main.h"

class ViewModelFOVChanger {
public:

	~ViewModelFOVChanger() {
		C_ViewModelFOV(D_ViewModelFOV());
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
						C_ViewModelFOV(cfg->viewmodel.fov);
					}
					else
						C_ViewModelFOV(D_ViewModelFOV());
				else
					C_ViewModelFOV(D_ViewModelFOV());

			}
		}
		catch (...) {
			mem->debuglog(__FILE__);
		}
	}

	void C_ViewModelFOV(float value) {
		static auto viewmodel_fov = cvar::find("viewmodel_fov");

		viewmodel_fov.SetFloat(value);
	}

	float D_ViewModelFOV(void) {
		static auto viewmodel_fov = cvar::find("viewmodel_fov");

		return std::stof(viewmodel_fov.GetDefaultValue());
	}
};

#endif