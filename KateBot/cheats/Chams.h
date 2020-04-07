#ifndef _CHAMS_H_
#define _CHAMS_H_

#include "..\main.h"

class Chams {
public:
	bool NeedUpdateChams = false;
	bool NeedUpdateModelAmbient = false;

	~Chams() {
		NeedUpdateModelAmbient = true;
		ModelBrightnessReset();
	}

	void Start() {
		try {
			for (;;) {
				std::this_thread::sleep_for(std::chrono::milliseconds(16));

				if (!miscUtils->IsCSGOActiveWindow())
					continue;

				if (!cfg->chams.enabled || cfg->StreamMode) {
					if (NeedUpdateChams) { csgo->ForceFullUpdate(); NeedUpdateChams = false; } ModelBrightnessReset();
					continue;
				}

				if (!csgo->IsInGame())
					continue;

				NeedUpdateChams = true;
				DWORD CSPlayerResource = mem->Read<DWORD>(client->GetImage() + ofs->m_dwPlayerResource);

				ColorESP EnemyColor = Colors->CfgColor(cfg->chams.enemycolor);
				ColorESP AllyColor = Colors->CfgColor(cfg->chams.allycolor);

				float balance_brightness_with_nm = cfg->nightmode.enabled ? (float)((100 - (100 * (cfg->nightmode.amount * 0.001))) * 0.2) : 0;
				ColorESP BalanceBrightness = Colors->CfgColor(Color{ (255.f / (cfg->chams.brightness / 10.f)) + balance_brightness_with_nm,
					(255.f / (cfg->chams.brightness / 10.f)) + balance_brightness_with_nm,
					(255.f / (cfg->chams.brightness / 10.f)) + balance_brightness_with_nm, 255.f });

				for (int x = 0; x < csgo->GetMaxEntities(); x++)
				{
					DWORD Entity = mem->Read<DWORD>(client->GetImage() + ofs->m_dwEntityList + x * 0x10);

					if (!Entity) continue;

					int EntityClassID = csgo->GetClassID(Entity);

					if (EntityClassID == CCSPlayer) {

						int Health = cfg->chams.health_based ? mem->Read<int>(Entity + ofs->m_iHealth) : 0;

						if (mem->Read<bool>(Entity + ofs->m_bDormant)) {
							mem->Write(Entity + 0x70, BalanceBrightness);
							continue;
						}

						if (!csgo->IsDangerZone() && mem->Read<int>(Entity + ofs->m_dwIndex) == mem->Read<int>(CSPlayerResource + ofs->m_iPlayerC4))
							mem->Write(Entity + 0x70, Colors->CfgColor(cfg->chams.c4playercolor));
						else if (mem->Read<bool>(Entity + ofs->m_bIsDefusing))
							mem->Write(Entity + 0x70, Colors->CfgColor(cfg->chams.defusecolor));
						else
							mem->Write(Entity + 0x70, csgo->IsInMyTeam(Entity) ?
								cfg->chams.enemiesonly ? BalanceBrightness : AllyColor :
								cfg->chams.health_based ?
								Colors->CfgColor(Color{ (float)(abs((int)(255 - (Health * 2.55)))),
									(float)(255 - abs((int)(255 - (Health * 2.55)))), 0, cfg->chams.enemycolor.a }) :
								EnemyColor);
					}
					else if (EntityClassID == CC4 || EntityClassID == CPlantedC4)
						mem->Write(Entity + 0x70, Colors->CfgColor(cfg->chams.c4color));
					else if (EntityClassID == CPredictedViewModel)
						mem->Write(Entity + 0x70, cfg->chams.viewmodel_chams ? LocalEntity.GetActiveWeapon() == WEAPON_C4 ?
							Colors->BombColor() :
							AllyColor : BalanceBrightness);
				}
				if (!cfg->chams.modelambient) { ModelBrightnessReset(); continue; }

				NeedUpdateModelAmbient = true;

				ModelBrightness(cfg->chams.brightness);
			}
		}
		catch (...) {
			mem->debuglog(__FILE__);
		}
	}

	void ModelBrightness(float brightness) {
		static auto r_modelAmbientMin = cvar::find("r_modelAmbientMin");

		r_modelAmbientMin.SetFloat(brightness);
	}

	void ModelBrightnessReset() {
		if (NeedUpdateModelAmbient) { ModelBrightness(0.f); NeedUpdateModelAmbient = false; }
	}
};

#endif