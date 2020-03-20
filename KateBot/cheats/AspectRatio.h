#ifndef _ASPECT_RATIO_H_
#define _ASPECT_RATIO_H_

#include "..\main.h"

class AspectRatio {
public:

	~AspectRatio() {
		C_AspectRatio(0);
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
						C_AspectRatio((cfg->aspect_ratio.value * 0.1) / 2);
					else
						C_AspectRatio(0);
				else
					C_AspectRatio(0);
			}
		}
		catch (...) {
			mem->debuglog(__FILE__);
		}
	}

	void C_AspectRatio(float value) {
		static auto sky = cvar::find("r_aspectratio");

		sky.SetFloat(value);
	}
};

#endif