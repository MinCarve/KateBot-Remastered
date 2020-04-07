#ifndef _POST_PROCESSING_H_
#define _POST_PROCESSING_H_

#include "..\main.h"

class PostProcessing {
public:

	~PostProcessing() {
		SET_MPPE(1);
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
					if (cfg->DisablePostProcessing) {
						SET_MPPE(0);
					}
					else
						SET_MPPE(1);
				else
					SET_MPPE(1);

			}
		}
		catch (...) {
			mem->debuglog(__FILE__);
		}
	}

	void SET_MPPE(int v) {
		static cs_convar mat_postprocess_enable = cvar::find("mat_postprocess_enable");

		mat_postprocess_enable.SetInt(v);
	}
};

#endif