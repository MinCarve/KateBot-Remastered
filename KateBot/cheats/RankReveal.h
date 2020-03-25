#ifndef _RANK_REVEAL_H_
#define _RANK_REVEAL_H_

#include "..\main.h"

class RankReveal {
public:
	void Start() {
		try {
			for (;;) {
				std::this_thread::sleep_for(std::chrono::milliseconds(30));

				if (!miscUtils->IsCSGOActiveWindow())
					continue;

				if (!csgo->IsInGame()) {
					this->reveal = false;
					continue;
				}

				if (cfg->StreamMode)
					continue;

				if (!cfg->RevealRank)
					continue;

				if (this->reveal)
					continue;

				this->reveal = true;

				DWORD null_memory_remote = mem->AllocMem(12);

				if (!null_memory_remote) return;

				mem->CRT(reinterpret_cast<void*>(client->GetImage() + ofs->m_dwRankRevealAllFn), reinterpret_cast<void*>(null_memory_remote));

				mem->Free(reinterpret_cast<void*>(null_memory_remote));
			}
		}
		catch (...) {
			mem->debuglog(__FILE__);
		}
	}
private:
	bool reveal = false;
};

#endif