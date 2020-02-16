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

				if (!cfg->glowEspEnabled)
					continue;

				if (!csgo->IsInGame())
					continue;

				DWORD GlowPointer = mem->Read<DWORD>(client->GetImage() + ofs->m_dwGlowObject);
				DWORD CSPlayerResource = mem->Read<DWORD>(client->GetImage() + ofs->m_dwPlayerResource);

				for (int g = 0; g < csgo->GetMaxObjects(); g++)
				{
					DWORD EntityBase = GlowPointer + (g * 0x38);

					GlowObject = mem->Read<GlowObjectDefinition_t>(EntityBase);

					if (GlowPointer != NULL && GlowObject.Entity != NULL)
					{
						int ClassID = mem->Read<int>(mem->Read<int>(mem->Read<int>(mem->Read<int>(GlowObject.Entity + 0x8) + 0x8) + 0x1) + 0x14);

						if (ClassID == CCSPlayer) {
							bool IsDormant = mem->Read<bool>(GlowObject.Entity + ofs->m_bDormant);

							if (!IsDormant)
							{
								int TeamNum = mem->Read<int>(GlowObject.Entity + ofs->m_iTeamNum);

								if (!csgo->IsInMyTeam(GlowObject.Entity))
								{
									int Health = mem->Read<int>(GlowObject.Entity + ofs->m_iHealth);

									if (TeamNum != 2 && TeamNum != 3) continue;

									if (TeamNum == 3) this->isDefusing = mem->Read<bool>(GlowObject.Entity + ofs->m_bIsDefusing);

									if (mem->Read<int>(GlowObject.Entity + ofs->m_dwIndex) == mem->Read<int>(CSPlayerResource + ofs->m_iPlayerC4) ||
										isDefusing)
										DrawGlow(EntityBase, ColorESP::Colors->Blue(cfg->glowesp.color.a));
									else {
										if (cfg->glowesp.health_based) {
											if (Health < 13)
												DrawGlow(EntityBase, ColorESP::Colors->White(cfg->glowesp.color.a));
											else
												DrawGlow(EntityBase, ColorESP::Colors->CfgColor(Color{ (float)((100 - Health) * (255 / 100)), (float)(Health * (255 / 100)), 0, cfg->glowesp.color.a }));
										}
										else
											DrawGlow(EntityBase, ColorESP::Colors->CfgColor(cfg->glowesp.color));
									}
								}
							}
						}
						else if (ClassID == CBaseCSGrenadeProjectile) {
							char ModelName[64] = {};
							ReadProcessMemory(mem->m_hProcess, (LPCVOID)(mem->Read<DWORD>(GlowObject.Entity + 0x6C) + 0x4), ModelName, sizeof(ModelName), NULL);

							std::string str(ModelName);

							if (str.find("flashbang_dropped.mdl") != std::string::npos)
								DrawGlow(EntityBase, ColorESP::Colors->White());
							else if (str.find("fraggrenade_dropped.mdl") != std::string::npos)
								DrawGlow(EntityBase, ColorESP::Colors->Red());
						}
						else if (ClassID == CEconEntity && LocalEntity.GetTeamNum() == 3) {
							char ModelName[64] = {};
							ReadProcessMemory(mem->m_hProcess, (LPCVOID)(mem->Read<DWORD>(GlowObject.Entity + 0x6C) + 0x4), ModelName, sizeof(ModelName), NULL);

							std::string str(ModelName);

							if (str.find("defuser.mdl") != std::string::npos)
								DrawGlow(EntityBase, ColorESP::Colors->Green(150));
						}
						else if (ClassID == CPlantedC4) {
							float BombTime = mem->Read<float>(GlowObject.Entity + ofs->m_flC4Blow) - csgo->GlobalVars().curtime;
							BombTime = BombTime < 0.f ? 0.f : BombTime;

							if (BombTime > 20)
								this->PlantedC4Color = ColorESP::Colors->Green(150);
							else if (BombTime > 10 && BombTime <= 20)
								this->PlantedC4Color = ColorESP::Colors->Orange(150);
							else if (BombTime > 5 && BombTime <= 10)
								this->PlantedC4Color = ColorESP::Colors->Red(150);
							else if (BombTime <= 5)
								this->PlantedC4Color = ColorESP::Colors->White(150);

							DrawGlow(EntityBase, this->PlantedC4Color);
						}
						else if (ClassID == CSmokeGrenadeProjectile)
							DrawGlow(EntityBase, ColorESP::Colors->Gray());
						else if (ClassID == CMolotovProjectile || ClassID == CIncendiaryGrenade)
							DrawGlow(EntityBase, ColorESP::Colors->Orange());
					}
				}
			}
		}
		catch (...) {
			mem->debuglog(__FILE__);
		}
	}

private:

	int indexBomb = -1;
	bool isDefusing = false;
	ColorESP PlantedC4Color = ColorESP(0, 0, 0, 0);

	void DrawGlow(DWORD Entity, ColorESP Color)
	{
		GlowObject.r = Color.r();
		GlowObject.g = Color.g();
		GlowObject.b = Color.b();
		GlowObject.a = sanitizeChannel(Color.a());
		GlowObject.m_bRenderWhenOccluded = true;
		GlowObject.m_bRenderWhenUnoccluded = false;
		GlowObject.m_bFullBloom = false;

		mem->Write<GlowObjectDefinition_t>(Entity, GlowObject);

		if (cfg->glowesp.onlyVisible)
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
		char pad_0014[4];
		float flUnknown;
		float flBloomAmount;
		float flLocalPlayerIsZeroPointThree;
		bool m_bRenderWhenOccluded;
		bool m_bRenderWhenUnoccluded;
		bool m_bFullBloom;
		char pad_0027[1];
		int nFullBloomTestStencilValue; // Needs to be zero.
		int nGlowStyle;
		int nSplitScreenSlot; // Should be -1.
		int nNextFreeSlot;
	}GlowObject;
};

#endif