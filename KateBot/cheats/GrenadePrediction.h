#ifndef _GRENADE_PREDICTION_H_
#define _GRENADE_PREDICTION_H_

#include "..\main.h"

class GrenadePrediction {
public:

	~GrenadePrediction() {
		GrenadePreview(0);
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
					if (cfg->GrenadePrediction)
						GrenadePreview(TRUE);
					else
						GrenadePreview(FALSE);
				else
					GrenadePreview(FALSE);
			}
		}
		catch (...) {
			mem->debuglog(__FILE__);
		}
	}

	void GrenadePreview(bool value) {
		static auto sky = cvar::find("cl_grenadepreview");

		sky.SetInt(value);
	}
};

#endif