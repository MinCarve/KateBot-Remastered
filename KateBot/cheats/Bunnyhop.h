#ifndef _BUNNYHOP_H_
#define _BUNNYHOP_H_

#include "..\main.h"

class Bunnyhop
{
public:
	void Start()
	{
		try {
			while (true)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(5));

				if (!miscUtils->IsCSGOActiveWindow())
					continue;

				if (!cfg->bunnyhopEnabled)
					continue;

				if (!csgo->IsInGame())
					continue;

				if (!csgo->IsTeamSelected())
					continue;

				if (LocalEntity.IsDead())
					continue;

				if (LocalEntity.GetVelocity().Length() > 40.f)
					while (GetAsyncKeyState(cfg->keys.bunnyhop_hold) & 0x8000) {
						if (LocalEntity.GetFlags() & FL_ONGROUND)
							mem->Write<int>(client->GetImage() + ofs->m_dwForceJump, 6);
						Sleep(1);
					}
			}
		}
		catch (...) {
			mem->debuglog(__FILE__);
		}
	}

private:
	Vector prev_strafe_angle;

};

#endif 