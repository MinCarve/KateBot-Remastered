#ifndef _GLOWESP_H_
#define _GLOWESP_H_

#include "..\main.h"

#define NO_FLICKER_MS 5
#define FLICKER_MS 25

class GlowESP
{
public:
	void Start()
	{
		try {
			for (;;) {
				std::this_thread::sleep_for(std::chrono::milliseconds(cfg->glowEspEnabled ? cfg->glowesp.noflicker ? NO_FLICKER_MS : FLICKER_MS : FLICKER_MS));

				if (cfg->panicMode)
					continue;

				if (!miscUtils->IsCSGOActiveWindow())
					continue;

				if (!cfg->glowEspEnabled || cfg->StreamMode)
					continue;

				if (!csgo->IsInGame())
					continue;

				DWORD GlowPointer = mem->Read<DWORD>(client->GetImage() + ofs->m_dwGlowObject);
				DWORD CSPlayerResource = mem->Read<DWORD>(client->GetImage() + ofs->m_dwPlayerResource);

				if (GlowPointer == NULL || CSPlayerResource == NULL) continue;

				for (int g = 0; g < csgo->GetMaxObjects(); g++)
				{
					DWORD EntityBase = GlowPointer + (g * sizeof(GlowObjectDefinition_t));

					GlowObject = mem->Read<GlowObjectDefinition_t>(EntityBase);

					if (GlowObject.Entity != NULL)
					{
						int ClassID = csgo->GetClassID(GlowObject.Entity);

						if (ClassID == CCSPlayer) {
							if (!mem->Read<bool>(GlowObject.Entity + ofs->m_bDormant))
							{
								int TeamNum = mem->Read<int>(GlowObject.Entity + ofs->m_iTeamNum);

								if (!csgo->IsInMyTeam(GlowObject.Entity))
								{
									int Health = mem->Read<int>(GlowObject.Entity + ofs->m_iHealth);

									if (TeamNum != 2 && TeamNum != 3) continue;

									if (TeamNum == 3) this->isDefusing = mem->Read<bool>(GlowObject.Entity + ofs->m_bIsDefusing);

									if (mem->Read<int>(GlowObject.Entity + ofs->m_dwIndex) == mem->Read<int>(CSPlayerResource + ofs->m_iPlayerC4) ||
										isDefusing)
										DrawGlow(EntityBase, Colors->Blue(cfg->glowesp.color.a), cfg->glowesp.onlyVisible);
									else {
										if (cfg->glowesp.health_based) {
											if (Health < 13)
												DrawGlow(EntityBase, Colors->White(cfg->glowesp.color.a), cfg->glowesp.onlyVisible);
											else
												DrawGlow(EntityBase, Colors->CfgColor(Color{ (float)(abs((int)(255 - (Health * 2.55)))),
									(float)(255 - abs((int)(255 - (Health * 2.55)))), 0, cfg->glowesp.color.a }), cfg->glowesp.onlyVisible);
										}
										else
											DrawGlow(EntityBase, Colors->CfgColor(cfg->glowesp.color), cfg->glowesp.onlyVisible);
									}
								}
							}
						}
						/*else if (ClassID == CBaseCSGrenadeProjectile) { // I don't understand, glowing bombs causes the game to crash.
							mem->Read(mem->Read<DWORD>(GlowObject.Entity + 0x6C) + 0x4, this->ModelName, sizeof(char[64]));

							std::string str(this->ModelName);

							if (str.find("flashbang_dropped.mdl") != std::string::npos)
								DrawGlow(EntityBase, Colors->White(), false);
							else if (str.find("fraggrenade_dropped.mdl") != std::string::npos)
								DrawGlow(EntityBase, Colors->Red(), false);
						}
						else if (ClassID == CEconEntity && LocalEntity.GetTeamNum() == 3) {
							mem->Read(mem->Read<DWORD>(GlowObject.Entity + 0x6C) + 0x4, this->ModelName, sizeof(char[64]));

							std::string str(this->ModelName);

							if (str.find("defuser.mdl") != std::string::npos)
								DrawGlow(EntityBase, Colors->Green(150), false);
						}
						else if (ClassID == CPlantedC4) {
							float BombTime = mem->Read<float>(GlowObject.Entity + ofs->m_flC4Blow) - csgo->GetCurTime();
							BombTime = BombTime < 0.f ? 0.f : BombTime;

							if (BombTime > 20)
								this->PlantedC4Color = Colors->Green(150);
							else if (BombTime > 10 && BombTime <= 20)
								this->PlantedC4Color = Colors->Orange(150);
							else if (BombTime > 5 && BombTime <= 10)
								this->PlantedC4Color = Colors->Red(150);
							else if (BombTime <= 5)
								this->PlantedC4Color = Colors->White(150);

							DrawGlow(EntityBase, this->PlantedC4Color, false);
						}
						else if (ClassID == CSmokeGrenadeProjectile)
							DrawGlow(EntityBase, Colors->Gray(), false);
						else if (ClassID == CMolotovProjectile || ClassID == CIncendiaryGrenade)
							DrawGlow(EntityBase, Colors->Orange(), false);*/
					}
				}
			}
		}
		catch (...) {
			mem->debuglog(__FILE__);
		}
	}

private:
	char ModelName[64];
	bool isDefusing = false;
	ColorESP PlantedC4Color = ColorESP(0, 0, 0, 0);

	void DrawGlow(DWORD Entity, ColorESP Color, bool OnlyVisible)
	{
		GlowObject.r = Color.r();
		GlowObject.g = Color.g();
		GlowObject.b = Color.b();
		GlowObject.a = sanitizeChannel(Color.a());
		GlowObject.m_bRenderWhenOccluded = true;
		GlowObject.m_bRenderWhenUnoccluded = false;
		GlowObject.m_bFullBloom = false;

		mem->Write<GlowObjectDefinition_t>(Entity, GlowObject);

		if (OnlyVisible)
			mem->Write<bool>(Entity + 0x2C, true); //(OnlyVisible)
	}

	float sanitizeChannel(int value) {
		if (value > 255) value = 255;
		if (value < 0) value = 0;
		return (float)value / 255;
	}

	struct GlowObjectDefinition_t
	{
		DWORD Entity;
		float r;
		float g;
		float b;
		float a;
		char m_unk[4];
		float m_flUnk;
		float m_flBloomAmount;
		float m_flUnk1;
		bool m_bRenderWhenOccluded;
		bool m_bRenderWhenUnoccluded;
		bool m_bFullBloom;
		char m_unk1;
		int m_nFullBloomStencilTestValue;
		int m_nGlowStyle;
		int m_nSplitScreenSlot;
		int m_nNextFreeSlot;
	}GlowObject;
};

#endif