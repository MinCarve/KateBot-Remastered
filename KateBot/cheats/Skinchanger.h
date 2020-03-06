#ifndef _SKINCHANGER_H_
#define _SKINCHANGER_H_

#include "..\main.h"

class Skinchanger
{
public:
	void Start()
	{
		try {
			while (true)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(1));

				if (cfg->panicMode)
					continue;

				if (!miscUtils->IsCSGOActiveWindow())
					continue;

				if (!cfg->skinchangerEnabled || cfg->StreamMode)
					continue;

				if (!csgo->IsInGame())
					continue;

				if (!csgo->IsTeamSelected())
					continue;

				if (LocalEntity.IsDead())
					continue;

				const int TempPlayer = LocalEntity.GetPointer();

				if (!TempPlayer)
				{
					this->ModelIndex = 0;
					continue;
				}
				else if (TempPlayer != this->LocalPlayer)
				{
					this->LocalPlayer = TempPlayer;
					this->ModelIndex = 0;
				}

				if (cfg->general_skin.knife_enable) {
					this->knife_index = GetKnifeByName(cfg->general_skin.knife);

					while (!this->ModelIndex)
						this->UpdateModelIndex();
				}

				for (UINT i = 0; i < 8; i++)
				{
					DWORD Weapon = mem->Read<DWORD>(this->LocalPlayer + ofs->m_hMyWeapons + i * 0x4) & 0xfff;
					DWORD WeaponBase = mem->Read<DWORD>(client->GetImage() + ofs->m_dwEntityList + (Weapon - 1) * 0x10);
					if (!WeaponBase) continue;

					short WeaponIndex = mem->Read<short>(WeaponBase + ofs->m_iItemDefinitionIndex);
					int WeaponSkin = cfg->skin[WeaponIndex].id, StatTrak = cfg->skin[WeaponIndex].statTrack;

					if (cfg->general_skin.knife_enable && (WeaponIndex == WEAPON_KNIFE || WeaponIndex == WEAPON_KNIFE_T || WeaponIndex == this->knife_index)) {
						mem->Write<int>(WeaponBase + ofs->m_iItemDefinitionIndex, this->knife_index);
						mem->Write<UINT>(WeaponBase + ofs->m_nModelIndex, this->ModelIndex);
						mem->Write<UINT>(WeaponBase + ofs->m_iViewModelIndex, this->ModelIndex);
						mem->Write<int>(WeaponBase + ofs->m_iEntityQuality, this->entityQuality);

						WeaponSkin = cfg->general_skin.knife_skin_id;
					}

					if (WeaponSkin)
					{
						WeaponData.m_nFallbackPaintKit = WeaponSkin;
						WeaponData.m_nFallbackSeed = 0;
						WeaponData.m_flFallbackWear = this->fallbackWear;
						WeaponData.m_nFallbackStatTrak = StatTrak;

						mem->Write<int>(WeaponBase + ofs->m_iItemIDHigh, this->itemIDHigh);
						mem->Write<WeaponSkinData>(WeaponBase + ofs->m_nFallbackPaintKit, WeaponData);
					}
				}

				if (GetAsyncKeyState(VK_HOME)) csgo->ForceFullUpdate();

				if (!cfg->general_skin.knife_enable) continue;

				DWORD_PTR ActiveWeapon = LocalEntity.GetActiveWeaponBase();
				if (!ActiveWeapon) continue;

				short ActiveWeaponID = mem->Read<short>(ActiveWeapon + ofs->m_iItemDefinitionIndex);
				if (ActiveWeaponID != this->knife_index) continue;
				if (LocalEntity.GetWeaponType(ActiveWeaponID) == EWeaponType::WeapType_KnifeType && 
					ActiveWeaponID != this->knife_index) { this->UpdateModelIndex(); continue; }

				DWORD ActiveViewModel = mem->Read<DWORD>(this->LocalPlayer + ofs->m_hViewModel) & 0xfff;
				ActiveViewModel = mem->Read<DWORD>(client->GetImage() + ofs->m_dwEntityList + (ActiveViewModel - 1) * 0x10);
				if (!ActiveViewModel) { continue; }

				mem->Write<UINT>(ActiveViewModel + ofs->m_nModelIndex, this->ModelIndex);
			}
		}
		catch (...) {
			mem->debuglog(__FILE__);
		}
	}

private:
	const int itemIDHigh = -1;
	const int entityQuality = 3;
	const float fallbackWear = 0.0001f;
	ItemDefinitionIndex knife_index = WEAPON_KNIFE;

	UINT ModelIndex = 0;
	DWORD LocalPlayer = 0;

	struct WeaponSkinData {
		int m_nFallbackPaintKit;
		int m_nFallbackSeed;
		float m_flFallbackWear;
		int m_nFallbackStatTrak;
	}WeaponData;

	void UpdateModelIndex() {
		this->ModelIndex = GetModelIndex(this->knife_index);
	}

	UINT GetModelIndexByName(const char* modelName)
	{
		DWORD nst = mem->Read<DWORD>(ofs->m_dwClientState + 0x529C);
		DWORD nsd = mem->Read<DWORD>(nst + 0x40);
		DWORD nsdi = mem->Read<DWORD>(nsd + 0xC);

		for (UINT i = 0; i < 1024; i++)
		{
			DWORD nsdi_i = mem->Read<DWORD>(nsdi + 0xC + i * 0x34);

			char str[128] = { 0 };

			if (ReadProcessMemory(mem->m_hProcess, (LPCVOID)(nsdi_i), str, sizeof(str), NULL))
				if (_stricmp(str, modelName) == 0)
					return i;
		}

		return 0;
	}

	ItemDefinitionIndex GetKnifeByName(const char* knife)
	{
		if (strcmp(knife, "CT") == NULL)
			return WEAPON_KNIFE;
		else if (strcmp(knife, "T") == NULL)
			return WEAPON_KNIFE_T;
		else if (strcmp(knife, "BAYONET") == NULL)
			return WEAPON_KNIFE_BAYONET;
		else if (strcmp(knife, "FLIP") == NULL)
			return WEAPON_KNIFE_FLIP;
		else if (strcmp(knife, "GUT") == NULL)
			return WEAPON_KNIFE_GUT;
		else if (strcmp(knife, "KARAMBIT") == NULL)
			return WEAPON_KNIFE_KARAMBIT;
		else if (strcmp(knife, "M9_BAYONET") == NULL)
			return WEAPON_KNIFE_M9_BAYONET;
		else if (strcmp(knife, "HUNTSMAN") == NULL)
			return WEAPON_KNIFE_TACTICAL;
		else if (strcmp(knife, "FALCHION") == NULL)
			return WEAPON_KNIFE_FALCHION;
		else if (strcmp(knife, "SURVIVAL_BOWIE") == NULL)
			return WEAPON_KNIFE_SURVIVAL_BOWIE;
		else if (strcmp(knife, "BUTTERFLY") == NULL)
			return WEAPON_KNIFE_BUTTERFLY;
		else if (strcmp(knife, "SHADOW_DAGGERS") == NULL)
			return WEAPON_KNIFE_PUSH;
		else if (strcmp(knife, "URSUS") == NULL)
			return WEAPON_KNIFE_URSUS;
		else if (strcmp(knife, "NAVAJA") == NULL)
			return WEAPON_KNIFE_GYPSY_JACKKNIFE;
		else if (strcmp(knife, "STILETTO") == NULL)
			return WEAPON_KNIFE_STILETTO;
		else if (strcmp(knife, "TALON") == NULL)
			return WEAPON_KNIFE_WIDOWMAKER;
		else if (strcmp(knife, "CLASSIC") == NULL)
			return WEAPON_KNIFE_CSS;
		else if (strcmp(knife, "PARACORD") == NULL)
			return WEAPON_KNIFE_CORD;
		else if (strcmp(knife, "SURVIVAL") == NULL)
			return WEAPON_KNIFE_CANIS;
		else if (strcmp(knife, "NOMAD") == NULL)
			return WEAPON_KNIFE_OUTDOOR;
		else if (strcmp(knife, "SKELETON") == NULL)
			return WEAPON_KNIFE_SKELETON;
		else return WEAPON_KNIFE;
	}

	UINT GetModelIndex(const short itemIndex)
	{
		UINT ret = 0;
		switch (itemIndex)
		{
		case WEAPON_KNIFE:
			ret = GetModelIndexByName("models/weapons/v_knife_default_ct.mdl");
			break;
		case WEAPON_KNIFE_T:
			ret = GetModelIndexByName("models/weapons/v_knife_default_t.mdl");
			break;
		case WEAPON_KNIFE_BAYONET:
			ret = GetModelIndexByName("models/weapons/v_knife_bayonet.mdl");
			break;
		case WEAPON_KNIFE_FLIP:
			ret = GetModelIndexByName("models/weapons/v_knife_flip.mdl");
			break;
		case WEAPON_KNIFE_GUT:
			ret = GetModelIndexByName("models/weapons/v_knife_gut.mdl");
			break;
		case WEAPON_KNIFE_KARAMBIT:
			ret = GetModelIndexByName("models/weapons/v_knife_karam.mdl");
			break;
		case WEAPON_KNIFE_M9_BAYONET:
			ret = GetModelIndexByName("models/weapons/v_knife_m9_bay.mdl");
			break;
		case WEAPON_KNIFE_TACTICAL:
			ret = GetModelIndexByName("models/weapons/v_knife_tactical.mdl");
			break;
		case WEAPON_KNIFE_FALCHION:
			ret = GetModelIndexByName("models/weapons/v_knife_falchion_advanced.mdl");
			break;
		case WEAPON_KNIFE_SURVIVAL_BOWIE:
			ret = GetModelIndexByName("models/weapons/v_knife_survival_bowie.mdl");
			break;
		case WEAPON_KNIFE_BUTTERFLY:
			ret = GetModelIndexByName("models/weapons/v_knife_butterfly.mdl");
			break;
		case WEAPON_KNIFE_PUSH:
			ret = GetModelIndexByName("models/weapons/v_knife_push.mdl");
			break;
		case WEAPON_KNIFE_URSUS:
			ret = GetModelIndexByName("models/weapons/v_knife_ursus.mdl");
			break;
		case WEAPON_KNIFE_GYPSY_JACKKNIFE:
			ret = GetModelIndexByName("models/weapons/v_knife_gypsy_jackknife.mdl");
			break;
		case WEAPON_KNIFE_STILETTO:
			ret = GetModelIndexByName("models/weapons/v_knife_stiletto.mdl");
			break;
		case WEAPON_KNIFE_WIDOWMAKER:
			ret = GetModelIndexByName("models/weapons/v_knife_widowmaker.mdl");
			break;
		case WEAPON_KNIFE_CSS:
			ret = GetModelIndexByName("models/weapons/v_knife_css.mdl");
			break;
		case WEAPON_KNIFE_CORD:
			ret = GetModelIndexByName("models/weapons/v_knife_cord.mdl");
			break;
		case WEAPON_KNIFE_CANIS:
			ret = GetModelIndexByName("models/weapons/v_knife_canis.mdl");
			break;
		case WEAPON_KNIFE_OUTDOOR:
			ret = GetModelIndexByName("models/weapons/v_knife_outdoor.mdl");
			break;
		case WEAPON_KNIFE_SKELETON:
			ret = GetModelIndexByName("models/weapons/v_knife_skeleton.mdl");
			break;
		default:
			break;
		}
		return ret;
	}
};

#endif 