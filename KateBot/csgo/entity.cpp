#include "..\main.h"

Entity LocalEntity;
Entity EntityList[65];

Entity::Entity()
{
	m_iIndex = NULL;

	m_dwPointer = NULL;
	m_dwBoneMatrix = NULL;

	m_iTeamNum = NULL;
	m_nSurvivalTeam = NULL;
	m_iHealth = NULL;
	m_iFlags = NULL;


	m_bDead = true;
}

Entity::~Entity()
{

}

void Entity::Update(int iIndex)
{
	//Clear();
	m_iIndex = iIndex;

	m_dwPointer = mem->Read<DWORD_PTR>(client->GetImage() + ofs->m_dwEntityList + m_iIndex * 0x10);

	if (!m_dwPointer)
		return;

	//    Read Player Chunk    //
	mem->Read(m_dwPointer, chunk, sizeof(chunk));
	//	End Read Player Chunk //


	m_dwIndex = *reinterpret_cast<int*>(chunk + ofs->m_dwIndex);
	m_iHealth = *reinterpret_cast<int*>(chunk + ofs->m_iHealth);

	m_dwBoneMatrix = *reinterpret_cast<DWORD_PTR*>(chunk + ofs->m_dwBoneMatrix);

	if (!m_dwBoneMatrix)
		return;

	mem->Read(m_dwBoneMatrix, m_BoneMatrix, sizeof(Matrix3x4[128]));

	m_vOrigin = *reinterpret_cast<Vector*>(chunk + ofs->m_vecOrigin);
	m_vVecViewOffset = *reinterpret_cast<Vector*>(chunk + ofs->m_vecViewOffset);
	m_vEye = m_vOrigin + m_vVecViewOffset;
	m_vEyeAngles = *reinterpret_cast<Vector*>(chunk + ofs->m_angEyeAngles);
	m_vVelocity = *reinterpret_cast<Vector*>(chunk + ofs->m_vecVelocity);
	m_vPunch = *reinterpret_cast<Vector*>(chunk + ofs->m_aimPunchAngle);
	m_iTeamNum = *reinterpret_cast<int*>(chunk + ofs->m_iTeamNum);
	m_nSurvivalTeam = *reinterpret_cast<int*>(chunk + ofs->m_nSurvivalTeam);
	m_iFlags = *reinterpret_cast<int*>(chunk + ofs->m_fFlags);
	m_iCrossHairID = *reinterpret_cast<int*>(chunk + ofs->m_iCrossHairID);
	m_hActiveWeapon = *reinterpret_cast<int*>(chunk + ofs->m_hActiveWeapon);
	m_iShotsFired = *reinterpret_cast<int*>(chunk + ofs->m_iShotsFired);
	m_bDead = *reinterpret_cast<bool*>(chunk + ofs->m_lifeState);
	m_bIsDormant = *reinterpret_cast<bool*>(chunk + ofs->m_bDormant);
	m_i64SpottedByMask = *reinterpret_cast<INT64*>(chunk + ofs->m_bSpottedByMask);
	m_bSpotted = *reinterpret_cast<int*>(chunk + ofs->m_bSpotted);
	m_totalHitsOnServer = *reinterpret_cast<int*>(chunk + ofs->m_totalHitsOnServer);

	if (!cfg->bspParsing)
		CheckVisible();
}

DWORD_PTR Entity::GetPointer()
{
	return m_dwPointer;
}

DWORD_PTR Entity::GetLocalPointer()
{
	return m_dwLocalPointer;
}

DWORD_PTR Entity::GetBoneMatrix()
{
	return m_dwBoneMatrix;
}

Matrix3x4 Entity::GetBoneMatrix(int iBone)
{
	return m_BoneMatrix[iBone];
}

Vector Entity::GetPunchAngles()
{
	return m_vPunch;
}

Vector Entity::GetOrigin()
{
	return m_vOrigin;
}

Vector Entity::GetVecViewOffset()
{
	return m_vVecViewOffset;
}

Vector Entity::GetEyeAngles()
{
	return m_vEyeAngles;
}

Vector Entity::GetEyePosition()
{
	return m_vEye;
}

Vector Entity::GetVelocity()
{
	return m_vVelocity;
}

Vector Entity::GetBonePosition(int iBone)
{
	return Vector(m_BoneMatrix[iBone].m[0][3], m_BoneMatrix[iBone].m[1][3], m_BoneMatrix[iBone].m[2][3]);
}

int Entity::GetActiveWeapon()
{
	short weaponId = mem->Read<short>(GetActiveWeaponBase() + ofs->m_iItemDefinitionIndex);
	if (weaponId > 64 || weaponId < 0) // If number is greater than array size return 0 to prevent crash
		weaponId = 42;	// set weapon ID to knife

	return weaponId;
}

DWORD_PTR Entity::GetActiveWeaponBase()
{
	DWORD_PTR dwBaseCombatWeaponIndex = *reinterpret_cast<DWORD_PTR*>(chunk + ofs->m_hActiveWeapon);
	dwBaseCombatWeaponIndex &= 0xFFF;
	return mem->Read<DWORD_PTR>(client->GetImage() + ofs->m_dwEntityList + (dwBaseCombatWeaponIndex - 1) * 0x10);
}

float Entity::GetAccuracyPenalty()
{
	return mem->Read<float>(GetActiveWeaponBase() + 0x32C0);
}

bool Entity::IsActiveWeaponNotVaild()
{
	int WeaponId = GetActiveWeapon();

	return(WeaponId == WEAPON_KNIFE || WeaponId == WEAPON_KNIFE_T || WeaponId == WEAPON_FLASHBANG || WeaponId == WEAPON_HEGRENADE || WeaponId == WEAPON_SMOKEGRENADE || WeaponId == WEAPON_MOLOTOV || WeaponId == WEAPON_DECOY || WeaponId == WEAPON_INCGRENADE || WeaponId == WEAPON_C4);
}

int Entity::GetActiveWeaponAmmo()
{
	DWORD_PTR WeaponBase = GetActiveWeaponBase();

	return mem->Read<int>(WeaponBase + ofs->m_iClip1);
}

bool Entity::IsActiveWeaponPistol()
{
	int WeaponId = GetActiveWeapon();

	return(WeaponId == WEAPON_DEAGLE || WeaponId == WEAPON_REVOLVER || WeaponId == WEAPON_ELITE || WeaponId == WEAPON_FIVESEVEN || WeaponId == WEAPON_GLOCK || WeaponId == WEAPON_P250 || WeaponId == WEAPON_USP_SILENCER || WeaponId == WEAPON_TEC9 || WeaponId == WEAPON_TASER || WeaponId == WEAPON_HKP2000);
}

EWeaponType Entity::GetWeaponType(int id)
{
	id = id ? id : GetActiveWeapon();

	switch (id)
	{
	case WEAPON_C4:
		return EWeaponType::WeapType_C4Explosive;

	case WEAPON_TASER:
		return EWeaponType::WeapType_ZeusGun;

	case WEAPON_NEGEV:
	case WEAPON_M249:
		return EWeaponType::WeapType_LMG;

	case WEAPON_AWP:
	case WEAPON_G3SG1:
	case WEAPON_SCAR20:
	case WEAPON_SSG08:
		return EWeaponType::WeapType_Sniper;

	case WEAPON_XM1014:
	case WEAPON_MAG7:
	case WEAPON_NOVA:
	case WEAPON_SAWEDOFF:
		return EWeaponType::WeapType_Shotgun;

	case WEAPON_FLASHBANG:
	case WEAPON_SMOKEGRENADE:
	case WEAPON_INCGRENADE:
	case WEAPON_HEGRENADE:
	case WEAPON_MOLOTOV:
		return EWeaponType::WeapType_Grenade;

	case WEAPON_MAC10:
	case WEAPON_P90:
	case WEAPON_UMP45:
	case WEAPON_BIZON:
	case WEAPON_MP7:
	case WEAPON_MP9:
	case WEAPON_MP5_SD:
		return EWeaponType::WeapType_SMG;

	case WEAPON_DEAGLE:
	case WEAPON_ELITE:
	case WEAPON_FIVESEVEN:
	case WEAPON_USP_SILENCER:
	case WEAPON_GLOCK:
	case WEAPON_TEC9:
	case WEAPON_HKP2000:
	case WEAPON_P250:
	case WEAPON_CZ75A:
	case WEAPON_REVOLVER:
		return EWeaponType::WeapType_Pistol;

	case WEAPON_AK47:
	case WEAPON_AUG:
	case WEAPON_FAMAS:
	case WEAPON_M4A1:
	case WEAPON_M4A1_SILENCER:
	case WEAPON_GALILAR:
	case WEAPON_SG556:
		return EWeaponType::WeapType_Rifle;

	case WEAPON_KNIFE:
	case WEAPON_KNIFE_CSS:
	case WEAPON_KNIFE_CORD:
	case WEAPON_KNIFE_CANIS:
	case WEAPON_KNIFE_URSUS:
	case WEAPON_KNIFE_GYPSY_JACKKNIFE:
	case WEAPON_KNIFE_OUTDOOR:
	case WEAPON_KNIFE_STILETTO:
	case WEAPON_KNIFE_WIDOWMAKER:
	case WEAPON_KNIFE_SKELETON:
	case WEAPON_KNIFE_BUTTERFLY:
	case WEAPON_KNIFE_FLIP:
	case WEAPON_KNIFE_TACTICAL:
	case WEAPON_KNIFE_M9_BAYONET:
	case WEAPON_KNIFE_KARAMBIT:
	case WEAPON_KNIFE_FALCHION:
	case WEAPON_KNIFE_PUSH:
	case WEAPON_KNIFE_BAYONET:
	case WEAPON_KNIFE_GUT:
	case WEAPON_KNIFE_SURVIVAL_BOWIE:
		return EWeaponType::WeapType_KnifeType;

	default:
		return (EWeaponType)-1;
	}
}

player_info_t Entity::GetProfileInfo()
{
	const size_t ECX_DISP = 0x40;
	const size_t EDX_DISP = 0x0C;
	const size_t INFO_OFFSET = 0x28;
	const size_t ENTRY_SIZE = 0x34;

	uintptr_t ecx = mem->Read<uintptr_t>(ofs->m_dwClientState + ofs->m_dwClientState_PlayerInfo);
	uintptr_t edx = mem->Read<uintptr_t>(ecx + ECX_DISP);
	uintptr_t eax = mem->Read<uintptr_t>(edx + EDX_DISP);
	uintptr_t profile_info = mem->Read<uintptr_t>(eax + INFO_OFFSET + (this->GetIndex() - 1) * ENTRY_SIZE);

	return mem->Read<player_info_t>(profile_info);
}

int Entity::GetRank()
{
	uintptr_t GameResources = mem->Read<uintptr_t>(client->GetImage() + ofs->m_dwPlayerResource);
	return mem->Read<int>(GameResources + ofs->m_iCompetitiveRanking + this->GetIndex() * 4);
}

int Entity::GetWins()
{
	uintptr_t GameResources = mem->Read<uintptr_t>(client->GetImage() + ofs->m_dwPlayerResource);
	return mem->Read<int>(GameResources + ofs->m_iCompetitiveWins + (this->GetIndex() * 4));
}

int Entity::GetTeamNum()
{
	return m_iTeamNum;
}

int Entity::GetSurvivalTeam()
{
	return m_nSurvivalTeam;
}

int Entity::GetHealth()
{
	return m_iHealth;
}

int Entity::GetCrosshairEnt()
{
	return m_iCrossHairID;
}

int Entity::GetShotsFired()
{
	return m_iShotsFired;
}

int Entity::GetIndex()
{
	return m_dwIndex;
}

int Entity::GetFlags()
{
	return m_iFlags;
}

int Entity::GetTotalHits()
{
	return m_totalHitsOnServer;
}

bool Entity::IsValid()
{
	if (!GetPointer())
		return false;

	if (!GetBoneMatrix())
		return false;

	if (IsDead())
		return false;

	if (IsDormant())
		return false;

	if (GetOrigin().IsZero())
		return false;

	if (GetHealth() < 1)
		return false;

	return true;
}

bool Entity::IsPlayer()
{
	if (!GetPointer())
		return false;

	if (!GetTeamNum())
		return false;

	return true;
}

bool Entity::IsDead()
{
	return m_bDead;
}

bool Entity::IsDormant()
{
	return m_bIsDormant;
}

bool Entity::IsJumping()
{
	int fhh = m_iFlags;
	if ((fhh & 0x1) == 1 || (fhh & 0x1) == 3 || (fhh & 0x1) == 5 || (fhh & 0x1) == 7)
	{
		return false;
	}
	return true;
}

bool Entity::IsSpotted()
{
	return (m_bSpotted != 0);
}

bool Entity::IsSpottedByMask()
{
	return (m_i64SpottedByMask & (1 << csgo->GetLocalPlayer()));
}

void Entity::CheckVisible()
{
	m_bVisible = IsSpottedByMask();
}

void Entity::SetVisible(bool IsVisible)
{
	m_bVisible = IsVisible;
}

bool Entity::IsVisible()
{
	return m_bVisible;
}

void Entity::Clear()
{
	m_iIndex = NULL;
	m_dwIndex = NULL;
	m_dwPointer = NULL;
	m_dwBoneMatrix = NULL;

	memset(m_BoneMatrix, NULL, sizeof(Matrix3x4[128]));

	m_vOrigin = Vector(0, 0, 0);
	m_vEye = Vector(0, 0, 0);
	m_vEyeAngles = Vector(0, 0, 0);
	m_vVelocity = Vector(0, 0, 0);
	m_vPunch = Vector(0, 0, 0);

	m_iTeamNum = NULL;
	m_iHealth = NULL;
	m_iFlags = NULL;
	m_iCrossHairID = NULL;
	m_hActiveWeapon = NULL;
	m_iWeaponId = NULL;
	m_iShotsFired = NULL;

	m_bDead = true;
	m_bIsDormant = false;
	m_i64SpottedByMask = NULL;
}