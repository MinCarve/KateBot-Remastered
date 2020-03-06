#include "..\main.h"

Engine* csgo = new Engine();

Engine::Engine()
{}

Engine::~Engine()
{}

bool Engine::IsConnected()
{
	if( !ofs->m_dwClientState )
		return false;
	return ( mem->Read<int>( ofs->m_dwClientState + ofs->m_dwInGame) == ( int )SIGNONSTATE_CONNECTED );
}

bool Engine::IsInGame()
{
	if( !ofs->m_dwClientState )
		return false;
	return ( mem->Read<int>( ofs->m_dwClientState + ofs->m_dwInGame) == ( int )SIGNONSTATE_FULL );
}

GlobalVarsBase Engine::GlobalVars(){
	return mem->Read<GlobalVarsBase>(engine->GetImage() + ofs->m_dwGlobalVars);
}

bool Engine::IsTeamSelected()
{
	return ( LocalEntity.GetTeamNum() == 2 || LocalEntity.GetTeamNum() == 3 );
}

bool Engine::IsInMyTeam(DWORD Entity)
{
	if (csgo->IsDangerZone())
		return (LocalEntity.GetSurvivalTeam() == -1) ? false : (LocalEntity.GetSurvivalTeam() == mem->Read<int>(Entity + ofs->m_nSurvivalTeam));
	else
		return mem->Read<int>(Entity + ofs->m_iTeamNum) == LocalEntity.GetTeamNum();
}

bool Engine::IsDangerZone()
{
	return this->GetGameType() == 4;
}

int Engine::GetGameType()
{
	return mem->Read<int>(mem->Read<int>(client->GetImage() + ofs->m_dwGameRulesProxy) + ofs->m_SurvivalGameRuleDecisionTypes);
}

int Engine::GetLocalPlayer()
{
	if( !ofs->m_dwClientState )
		return -1;
	return mem->Read<int>( ofs->m_dwClientState + 0x180 ); //m_dwLocalPlayerIndex
}

int Engine::GetMaxObjects()
{
	return mem->Read<int>(client->GetImage() + ofs->m_dwGlowObject + 0x4);
}

int Engine::GetMaxEntities()
{
	return mem->Read<int>(client->GetImage() + ofs->m_dwEntityList + 0x4);
}

void Engine::GetViewAngles( Vector& viewangles )
{
	if( !ofs->m_dwClientState )
		return;
	viewangles = mem->Read<Vector>( ofs->m_dwClientState + ofs->m_dwViewAngles );
}

void Engine::SetViewAngles( const Vector& viewangles )
{
	if( !ofs->m_dwClientState || viewangles.IsZero() || !viewangles.IsTrue())
		return;
	mem->Write<Vector>( ofs->m_dwClientState + ofs->m_dwViewAngles, viewangles );
}

Vector Engine::RetViewAngles()
{
	if( !ofs->m_dwClientState )
		return { 0, 0, 0 };
	return mem->Read<Vector>( ofs->m_dwClientState + ofs->m_dwViewAngles );
}


// Played around with this,
// -Works 100% for low fov, so can be used for a legit bot
// -Works 100% client side, good for raging
// -Full FOV does not fully work demo/spec side, twitches at times because 
//		we're not inside the same thread with the same timings
// 
//  I feel like I've broken this :/
void Engine::SetViewAnglesPSilent( Vector& viewangles )
{
	/*if( !g_pAimbot->IsAbleToShoot() )
		return;

	int userCMDSequenceNum = 0;
	Vector oldAngles;
	DWORD_PTR userCMD = ofs->userCMD;

	int curSequenceNum = mem->Read<int>( ofs->m_dwClientState + 0x4CA8 ) + 1;
	userCMD += ( curSequenceNum % 150 ) * 0x64;

	SetSendPacket( false );

	while( userCMDSequenceNum != curSequenceNum )
	{
		g_pEngine->GetViewAngles( oldAngles );
		userCMDSequenceNum = mem->Read<int>( userCMD + 0x4 );
	}

	g_pMath->ClampAngle( viewangles ); // Just too make sure!!

	for( int i = 0; i < 20; i++ )  // Called outside of a hook so just keep setting it untill we hit the timing
	{
		mem->Write<Vector>( userCMD + 0xC, viewangles );
	}

	g_pEngine->SetViewAngles( oldAngles ); // Set view angles asap 
	Sleep( 6 );	// Changed from 7 to 5, could be the reason for shooting twice?

	SetSendPacket( true ); */
}


const char* Engine::GetMapDirectory()
{
	if( !ofs->m_dwClientState )
		return nullptr;
	mem->Read( ofs->m_dwClientState + ofs->m_dwMapDirectory, m_pMapDirectory, sizeof( char[ 255 ] ) );
	return m_pMapDirectory;
}

std::string Engine::GetGameDirectory()
{
	char filename[MAX_PATH];
	if (GetModuleFileNameEx(mem->m_hProcess, NULL, filename, MAX_PATH) == 0) {
		return nullptr;
	}
	
	std::string tmp_path(filename);
	int pos = tmp_path.find("csgo");
	tmp_path = tmp_path.substr(0, pos);
	tmp_path = tmp_path + "csgo\\";
	return tmp_path;
}


void Engine::GlobalsSetup()
{
	m_dwGlobals = mem->Read< DWORD_PTR >( engine->GetImage() + ofs->m_dwGlobalVars );
}

float Engine::GetCurTime()
{
	return GlobalVars().curtime;
}

float Engine::GetFrameTime()
{
	return GlobalVars().frametime;
}

int	Engine::GetMaxClients()
{
	return GlobalVars().maxClients;
}

float Engine::GetIntervalPerTick()
{
	return GlobalVars().interval_per_tick;
}

float Engine::GetInterpolationAmount()
{
	return GlobalVars().interpolation_amount;
}

int Engine::GetClassID(DWORD Entity)
{
	return mem->Read<int>(mem->Read<int>(mem->Read<int>(mem->Read<int>(Entity + 0x8) + 0x8) + 0x1) + 0x14);
}

char* Engine::GetClassNameFromPlayer(DWORD adr)
{
	int vt = mem->Read<int>(adr + 0x8);
	int fn = mem->Read<int>(vt + 2 * 0x4);
	int cls = mem->Read<int>(fn + 0x1);
	int clsn = mem->Read<int>(cls + 8);

	int namePointer = mem->Read<int>(clsn);
	char* nameData = new char[32];

	for (int i = 0; i < 32; i++) {
		nameData[i] = mem->Read<char>(namePointer + i);
	}
	
	return nameData;
}
	

bool Engine::IsClassIDAWeapon(int iClassID)
{
	switch (iClassID)
	{
		case CAK47:
		case CDEagle:
		case CWeaponAWP:
		case CWeaponAug:
		case CWeaponBizon:
		case CWeaponElite:
		case CWeaponFamas:
		case CWeaponFiveSeven:
		case CWeaponG3SG1:
		case CWeaponGalilAR:
		case CWeaponGlock:
		case CWeaponHKP2000:
		case CWeaponMAC10:
		case CWeaponM249:
		case CWeaponM4A1:
		case CWeaponM3:
		case CWeaponMag7:
		case CWeaponMP7:
		case CWeaponMP9:
		case CWeaponNegev:
		case CWeaponNOVA:
		case CWeaponP250:
		case CWeaponP90:
		case CWeaponSawedoff:
		case CWeaponSCAR20:
		case CWeaponSG556:
		case CWeaponSSG08:
		case CWeaponTaser:
		case CWeaponTec9:
		case CWeaponUSP:
		case CWeaponUMP45:
		case CWeaponXM1014:


		return true;
	}

	return false;
}

bool Engine::IsClassIDAGrenade(int iClassID)
{
	switch (iClassID)
	{
		case CFlashbang:
		case CHEGrenade:
		case CDecoyGrenade:
		case CIncendiaryGrenade:
		case CMolotovGrenade:
		case CSmokeGrenade:
		case CBaseCSGrenadeProjectile:
		case CSmokeGrenadeProjectile:
		case CMolotovProjectile:
		case CDecoyProjectile:
		return true;
	}

	return false;
}


void Engine::PressAttackKey()
{
	if (!GetAsyncKeyState(cfg->InGameFireKey))
	{   
		INPUT    Input = { 0 };
		//Press Fire Key
		ZeroMemory(&Input, sizeof(INPUT));
		WORD vkey = cfg->InGameFireKey;
 
		Input.type = INPUT_KEYBOARD;
		Input.ki.wScan = MapVirtualKey(vkey, MAPVK_VK_TO_VSC);
		Input.ki.time = 0;
		Input.ki.dwExtraInfo = 0;
		Input.ki.wVk = vkey;
		Input.ki.dwFlags = KEYEVENTF_SCANCODE;
		SendInput(1, &Input, sizeof(INPUT));
	}
}

void Engine::ReleaseAttackKey()
{
	if (GetAsyncKeyState(cfg->InGameFireKey))
	{
		INPUT    Input = { 0 };
		//Release Fire Key
		ZeroMemory(&Input, sizeof(INPUT));
		WORD vkey = cfg->InGameFireKey;
 
		Input.type = INPUT_KEYBOARD;
		Input.ki.wScan = MapVirtualKey(vkey, MAPVK_VK_TO_VSC);
		Input.ki.time = 0;
		Input.ki.dwExtraInfo = 0;
		Input.ki.wVk = vkey;
		Input.ki.dwFlags = KEYEVENTF_KEYUP | KEYEVENTF_SCANCODE;
		SendInput(1, &Input, sizeof(INPUT));
	}
}

void Engine::PAttack()
{
	if (!mem->Read<bool>( client->GetImage() + ofs->m_dwForceAttack ))
		mem->Write<bool>( client->GetImage() + ofs->m_dwForceAttack, true );
}

void Engine::MAttack()
{
	if (mem->Read<bool>( client->GetImage() + ofs->m_dwForceAttack ))
		mem->Write<bool>( client->GetImage() + ofs->m_dwForceAttack, false );
}

void Engine::ForceFullUpdate()
{
	if( !ofs->m_dwClientState )
		return;
		
	mem->Write<int>(ofs->m_dwClientState + ofs->m_nDeltaTick, -1);
}
