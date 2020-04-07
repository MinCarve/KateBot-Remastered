#ifndef _GRENADE_PREDICTION_H_
#define _GRENADE_PREDICTION_H_

#include "..\main.h"

class GrenadePrediction {
public:

	~GrenadePrediction() {
		SET_GP(0);
	}

	void Start() {
		try {
			for (;;) {
				std::this_thread::sleep_for(std::chrono::milliseconds(100));

				if (!miscUtils->IsCSGOActiveWindow())
					continue;

				if (!csgo->IsInGame())
					continue;

				if (!cfg->StreamMode)
					if (cfg->GrenadePrediction)
						SET_GP(TRUE);
					else
						SET_GP(FALSE);
				else
					SET_GP(FALSE);
			}
		}
		catch (...) {
			mem->debuglog(__FILE__);
		}
	}

	void SET_GP(bool v) {
		static cs_convar cl_grenadepreview = cvar::find("cl_grenadepreview");

		cl_grenadepreview.SetInt(v);
	}
};

#endif