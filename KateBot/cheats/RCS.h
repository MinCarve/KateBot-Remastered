#ifndef _RCS_H_
#define _RCS_H_

#include "..\main.h"

class RCS
{
public:
	void Start()
	{
		try {
			for (;;) {
				std::this_thread::sleep_for(std::chrono::milliseconds(10));

				if (cfg->panicMode)
					continue;

				if (!miscUtils->IsCSGOActiveWindow())
					continue;

				if (!cfg->rcs.enable)
					continue;

				if (!csgo->IsInGame())
					continue;

				//if (ActualAimbot::m_Target != -1) continue;

				if (LocalEntity.GetShotsFired() > 1) {
					Vector AP = LocalEntity.GetPunchAngles();

					Vector CVA;
					csgo->GetViewAngles(CVA);

					this->NVA.x = ((CVA.x + this->OAP.x) - (AP.x * 2.f));
					this->NVA.y = ((CVA.y + this->OAP.y) - (AP.y * 2.f));

					this->NVA.Normalize();

					this->OAP.x = AP.x * 2.f;
					this->OAP.y = AP.y * 2.f;

					csgo->SetViewAngles(this->NVA);
				}
				else this->OAP = { 0, 0, 0 };
			}
		}
		catch (...) { mem->debuglog(__FILE__); }
	}
private:
	Vector NVA = { 0, 0, 0 };
	Vector OAP = { 0, 0, 0 };
};

#endif