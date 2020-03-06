#ifndef _HITSOUND_H_
#define _HITSOUND_H_

//#include <fstream>
#include "..\main.h"

class Hitsound
{
public:
	void Start()
	{
		try {
			for (;;) {
				std::this_thread::sleep_for(std::chrono::milliseconds(30));

				if (cfg->panicMode)
					continue;

				if (!miscUtils->IsCSGOActiveWindow())
					continue;

				if (!cfg->hitsound || cfg->StreamMode)
					continue;

				if (!csgo->IsInGame())
					continue;

				this->total_hits = mem->Read<int>(LocalEntity.GetPointer() + ofs->m_totalHitsOnServer);

				if (this->total_hits > this->hits)
				{
					this->hits = this->total_hits;

					PlaySound("C:\\KateBot\\hitsound.wav", NULL, SND_FILENAME);
				}
			}
		}
		catch (...) { mem->debuglog(__FILE__); }
	}

private:
	int hits = mem->Read<int>(LocalEntity.GetPointer() + ofs->m_totalHitsOnServer);
	int total_hits = -1;
};

#endif