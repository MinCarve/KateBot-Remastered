#ifndef _RCS_H_
#define _RCS_H_

#include "..\main.h"

class RCS
{
public:
	void MoveMouse_round(float xPixels, float yPixels)
	{
		INPUT input = { 0 };
		input.mi.mouseData = 0;
		input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
		input.type = INPUT_MOUSE;
		input.mi.dx = roundf(xPixels);
		input.mi.dy = roundf(yPixels);
		input.mi.dwExtraInfo = 0;
		input.mi.time = 0;
		SendInput(1, &input, sizeof(INPUT));
	}

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

				if (LocalEntity.GetShotsFired() < 1)
				{
					this->OAP.x = this->OAP.y = this->OAP.z = 0;
					continue;
				}

				this->AP = LocalEntity.GetPunchAngles() * 1.7f;

				this->OAP = this->AP;

				csgo->GetViewAngles(this->CVA);

				this->NVA = ((this->CVA + this->OAP) - this->AP);

				//this->math.ClampAngle(this->NVA);

				float xPixels = this->NVA.y / (0.022f * 2 * 1.0f);
				float yPixels = -this->NVA.x / (0.022f * 2 * 1.0f);

				static int xSleep = 0;
				static int ySleep = 0;

				if (abs(xPixels) < 1.f && GetTickCount64() > xSleep)
				{
					if (xPixels > 0) xPixels = 1;

					if (xPixels < 0) xPixels = -1;

					xSleep = GetTickCount64() + 1;
				}

				if (abs(yPixels) < 1.f && GetTickCount64() > ySleep)
				{
					if (yPixels > 0) yPixels = 1;

					if (yPixels < 0) yPixels = -1;

					ySleep = GetTickCount64() + 1;
				}

				//this->Mouse->MoveMouse(xPixels, yPixels);

				MoveMouse_round(xPixels, yPixels);
			}
		}
		catch (...) { mem->debuglog(__FILE__); }
	}
private:
	RunMouse* Mouse = new RunMouse();
	Math math = Math();

	Vector AP = { 0, 0, 0 };
	Vector CVA = { 0, 0, 0 };
	Vector NVA = { 0, 0, 0 };
	Vector OAP = { 0, 0, 0 };
};

#endif