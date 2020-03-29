#ifndef _ASPECT_RATIO_H_
#define _ASPECT_RATIO_H_

#include "..\main.h"

class AspectRatio {
public:

	~AspectRatio() {
		SET_AR(0);
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
					if (cfg->AspectRatio)
						SET_AR((cfg->aspect_ratio.value * 0.1) / 2);
					else
						SET_AR(0);
				else
					SET_AR(0);
			}
		}
		catch (...) {
			mem->debuglog(__FILE__);
		}
	}

	void SET_AR(float v) {
		static cs_convar r_aspectratio = cvar::find("r_aspectratio");

		r_aspectratio.SetFloat(v);
	}
};

#endif