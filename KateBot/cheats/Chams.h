#ifndef _CHAMS_H_
#define _CHAMS_H_

#include "..\main.h"

class Chams {
public:
	bool NeedUpdateChams = true;
	bool NeedUpdateModelAmbient = true;

	~Chams() {
		NeedUpdateModelAmbient = true;
		ModelBrightnessReset();
	}

	void Start() {
		try {
			for (;;) {
				std::this_thread::sleep_for(std::chrono::milliseconds(25));

				if (cfg->panicMode)
					continue;

				if (!miscUtils->IsCSGOActiveWindow())
					continue;

				if (!cfg->chams.enabled) {
					if (NeedUpdateChams) { csgo->ForceFullUpdate(); NeedUpdateChams = false; } ModelBrightnessReset();
					continue;
				}

				if (!csgo->IsInGame())
					continue;

				NeedUpdateChams = true;

				float brightness = 100.f;

				DWORD GlowPointer = mem->Read<DWORD>(client->GetImage() + ofs->m_dwGlowObject);
				DWORD CSPlayerResource = mem->Read<DWORD>(client->GetImage() + ofs->m_dwPlayerResource);

				int toneMapCIndex = mem->Read<int>(LocalEntity.GetPointer() + ofs->m_hTonemapController) & 0xFFF;
				DWORD toneMapHandle = mem->Read<DWORD>(client->GetImage() + ofs->m_dwEntityList + (toneMapCIndex - 1) * 0x10);

				ColorESP EnemyColor = ColorESP::Colors->CfgColor(cfg->chams.enemycolor);
				ColorESP AllyColor = ColorESP::Colors->CfgColor(cfg->chams.allycolor);

				float balance_brightness_with_nm = cfg->nightmode.enabled ? (float)((100 - (100 * mem->Read<float>(toneMapHandle + ofs->m_flCustomAutoExposureMax))) * 0.7) : 0;
				ColorESP BalanceBrightness = ColorESP::Colors->CfgColor(Color{ 25 + balance_brightness_with_nm, 25 + balance_brightness_with_nm, 25 + balance_brightness_with_nm, 255 });

				for (int x = 1; x < csgo->GetMaxObjects(); x++)
				{
					DWORD Entity = mem->Read<DWORD>(GlowPointer + (x * 0x38));

					if (Entity != 0) {
						int EntityClassID = mem->Read<int>(mem->Read<int>(mem->Read<int>(mem->Read<int>(Entity + 0x8) + 0x8) + 0x1) + 0x14);

						if (EntityClassID == CCSPlayer) {

							int Health = cfg->chams.health_based ? mem->Read<int>(Entity + ofs->m_iHealth) : 0;

							if (mem->Read<int>(Entity + ofs->m_dwIndex) == mem->Read<int>(CSPlayerResource + ofs->m_iPlayerC4))
								mem->Write(Entity + 0x70, ColorESP::Colors->CfgColor(cfg->chams.c4playercolor));
							else if (mem->Read<bool>(Entity + ofs->m_bIsDefusing))
								mem->Write(Entity + 0x70, ColorESP::Colors->CfgColor(cfg->chams.defusecolor));
							else
								mem->Write(Entity + 0x70, csgo->IsInMyTeam(Entity) ?
									cfg->chams.enemiesonly ? BalanceBrightness : AllyColor :
									cfg->chams.health_based ?
									ColorESP::Colors->CfgColor(Color{ (float)(abs((int)(255 - (Health * 2.55)))),
										(float)(255 - abs((int)(255 - (Health * 2.55)))), 0, cfg->chams.enemycolor.a }) :
									EnemyColor);
						}
						else if (EntityClassID == CC4 || EntityClassID == CPlantedC4)
							mem->Write(Entity + 0x70, ColorESP::Colors->CfgColor(cfg->chams.c4color));
						else if (EntityClassID == CAK47 ||
							EntityClassID == CWeaponAWP ||
							EntityClassID == CWeaponAug ||
							EntityClassID == CWeaponFamas ||
							EntityClassID == CWeaponG3SG1 ||
							EntityClassID == CWeaponGalilAR ||
							EntityClassID == CWeaponGlock ||
							EntityClassID == CWeaponM4A1 ||
							EntityClassID == CWeaponMAC10 ||
							EntityClassID == CWeaponMP5Navy ||
							EntityClassID == CWeaponMP7 ||
							EntityClassID == CWeaponMP9 ||
							EntityClassID == CWeaponP250 ||
							EntityClassID == CWeaponP90 ||
							EntityClassID == CWeaponSCAR20 ||
							EntityClassID == CWeaponScout ||
							EntityClassID == CWeaponSG550 ||
							EntityClassID == CWeaponSG556 ||
							EntityClassID == CWeaponSSG08 ||
							EntityClassID == CDEagle ||
							EntityClassID == CWeaponUSP ||
							EntityClassID == CWeaponGalil)
							mem->Write(Entity + 0x70, ColorESP::Colors->Red());
						else
							mem->Write(Entity + 0x70, BalanceBrightness);

						if (LocalEntity.IsDead())
						{
							DWORD EntityViewModel = mem->Read<DWORD>(Entity + ofs->m_hViewModel);

							this->ViewModelChams(EntityViewModel, cfg->chams.viewmodel_chams ? LocalEntity.GetActiveWeapon() == WEAPON_C4 ?
								ColorESP::Colors->BombColor() :
								AllyColor : BalanceBrightness);
						}
					}
				}

				if (!LocalEntity.IsDead())
				{
					DWORD LocalViewModel = mem->Read<DWORD>(LocalEntity.GetPointer() + ofs->m_hViewModel);

					this->ViewModelChams(LocalViewModel, cfg->chams.viewmodel_chams ? LocalEntity.GetActiveWeapon() == WEAPON_C4 ?
						ColorESP::Colors->BombColor() :
						AllyColor : ColorESP::Colors->CfgColor(Color{ 25 + balance_brightness_with_nm, 25 + balance_brightness_with_nm, 25 + balance_brightness_with_nm, 255 }));
				}

				if (!cfg->chams.modelambient) { ModelBrightnessReset(); continue; }

				NeedUpdateModelAmbient = true;

				ModelBrightness(brightness);
			}
		}
		catch (...) {
			mem->debuglog(__FILE__);
		}
	}

	void ViewModelChams(DWORD ViewModelEntity, ColorESP Color) {
		mem->Write(mem->Read<DWORD>(client->GetImage() + ofs->m_dwEntityList + (((ViewModelEntity & 0xFFF) - 1) * 0x10)) + 0x70, Color);
	}

	void ModelBrightness(float brightness) {

		/* model_ambient_min is convar and when Valve starts to check it, there may be an in-game ban for you.
				You should check this with every VAC update or don't use it. */

		DWORD xored = *(DWORD*)&brightness ^ (int)(engine->GetImage() + ofs->modelAmbientMin - 0x2c);
		mem->Write<int>(engine->GetImage() + ofs->modelAmbientMin, xored);
	}

	void ModelBrightnessReset() {
		if (NeedUpdateModelAmbient) { ModelBrightness(0.f); NeedUpdateModelAmbient = false; }
	}
private:
	int IsBomb = -1;
};

#endif