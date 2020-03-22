#ifndef _POST_PROCESSING_H_
#define _POST_PROCESSING_H_

#include "..\main.h"

class PostProcessing {
public:

	~PostProcessing() {
		C_MatPostProcessEnable(1);
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
					if (cfg->DisablePostProcessing) {
						C_MatPostProcessEnable(0);
					}
					else
						C_MatPostProcessEnable(1);
				else
					C_MatPostProcessEnable(1);

			}
		}
		catch (...) {
			mem->debuglog(__FILE__);
		}
	}

	void C_MatPostProcessEnable(int value) {
		static auto mat_postprocess_enable = cvar::find("mat_postprocess_enable");

		mat_postprocess_enable.SetInt(value);
	}
};

#endif