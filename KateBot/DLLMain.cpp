#include "main.h"
#include "httplib.h"

bool g_IsPanorama{};

std::unique_ptr< Valve::BSPParser > g_pBSPParser = std::make_unique< Valve::BSPParser >();
std::string m_pGameDirectory;
std::string m_pMapDirectory;

using std::cout;
using std::endl;
using std::cin;
using std::thread;
#define caseStringify(x) case x: return std::string(#x)
std::string vkToString(int vk);

Chams chams;

void printInfo() {
	std::system("cls");

	g_pCon->SetConsoleColor(red, black);
	cout << "\n   KateBot v1.0.8\n\n";
	g_pCon->SetConsoleColor(aqua, black);
	cout << " WARNING: \n";
	cout << "    For work features type command in console!\n";
	cout << "    unbind mouse1;bind / +attack\n\n";
	g_pCon->SetConsoleColor(green, black);
	cout << "           DELETE       - Reload Config\n";
	if (cfg->StreamMode) {
		g_pCon->SetConsoleColor(green, black);
		cout << "           StreamMode   - Active\n\n";
	}
	else {
		g_pCon->SetConsoleColor(red, black);
		cout << "           StreamMode   - Deactive\n\n";
	}
	//cout << "           END          - Panic Mode\n\n";
	g_pCon->SetConsoleColor(white, black);

	g_pCon->SetConsoleColor(magenta, black);
	cout << "          HOLD KEYS\n";
	g_pCon->SetConsoleColor(white, black);

	cout << "           Aimbot          - " << vkToString(cfg->keys.aimbot_hold) << "\n";
	cout << "           Triggerbot      - " << vkToString(cfg->keys.triggerbot_hold) << "\n";
	cout << "           Bunnyhop        - " << vkToString(cfg->keys.bunnyhop_hold) << "\n\n";

	g_pCon->SetConsoleColor(magenta, black);
	cout << "          TOGGLE KEYS\n";
	g_pCon->SetConsoleColor(white, black);

	g_pCon->SetConsoleColor(white, black); cout << "           ";

	if (cfg->aimbotEnabled) g_pCon->SetConsoleColor(white, green); else g_pCon->SetConsoleColor(white, red);

	if (cfg->faceitAim)
		cout << " Aimbot[Faceit]  - " << vkToString(cfg->keys.aimbot_toggle) << " \n";
	else
		cout << " Aimbot[MM]      - " << vkToString(cfg->keys.aimbot_toggle) << " \n";

	g_pCon->SetConsoleColor(white, black); cout << "           ";

	if (cfg->glowEspEnabled) g_pCon->SetConsoleColor(white, green); else g_pCon->SetConsoleColor(white, red);
	cout << " GlowESP         - " << vkToString(cfg->keys.glowesp_toggle) << " \n";

	g_pCon->SetConsoleColor(white, black); cout << "           ";
	if (cfg->chams.enabled) g_pCon->SetConsoleColor(white, green); else g_pCon->SetConsoleColor(white, red);

	cout << " Chams           - " << vkToString(cfg->keys.chams_toggle) << " \n";

	g_pCon->SetConsoleColor(white, black); cout << "           ";
	if (cfg->radar) g_pCon->SetConsoleColor(white, green); else g_pCon->SetConsoleColor(white, red);

	cout << " Radar           - " << vkToString(cfg->keys.radar_toggle) << " \n";

	g_pCon->SetConsoleColor(white, black); cout << "           ";
	if (cfg->skinchangerEnabled) g_pCon->SetConsoleColor(white, green); else g_pCon->SetConsoleColor(white, red);

	cout << " SkinChanger             \n";

	g_pCon->SetConsoleColor(white, black); cout << "           ";
	if (cfg->nightmode.enabled) g_pCon->SetConsoleColor(white, green); else g_pCon->SetConsoleColor(white, red);

	cout << " NightMode       - " << vkToString(cfg->keys.nightmode_toggle) << " ";

	g_pCon->SetConsoleColor(aqua, black);
	cout << "\n\n     GL&HF\n";
	g_pCon->SetConsoleColor(white, black);
}

void UpdateEntity()
{
	try {
		for (;;) {
			std::this_thread::sleep_for(std::chrono::milliseconds(1));

			if (GetAsyncKeyState(VK_DELETE))
			{
				cfg->LoadConfig();
				printInfo();
				if (!cfg->StreamMode) Beep(1000, 200);
			}

			if (cfg->keys.streamode_toggle != 0 && GetAsyncKeyState(cfg->keys.streamode_toggle))
			{
				cfg->StreamMode = !cfg->StreamMode;
				printInfo();
				Sleep(200);
			}

			if (cfg->keys.aimbot_toggle != 0 && GetAsyncKeyState(cfg->keys.aimbot_toggle))
			{
				cfg->aimbotEnabled = !cfg->aimbotEnabled;
				if (!cfg->StreamMode)
					if (cfg->aimbotEnabled) Beep(1000, 200); else Beep(500, 200);
				printInfo();
				Sleep(200);
			}

			if (cfg->keys.glowesp_toggle != 0 && GetAsyncKeyState(cfg->keys.glowesp_toggle))
			{
				cfg->glowEspEnabled = !cfg->glowEspEnabled;
				if (!cfg->StreamMode)
					if (cfg->glowEspEnabled) Beep(1000, 200); else Beep(500, 200);
				printInfo();
				Sleep(200);
			}

			if (cfg->keys.chams_toggle != 0 && GetAsyncKeyState(cfg->keys.chams_toggle))
			{
				cfg->chams.enabled = !cfg->chams.enabled;
				if (!cfg->StreamMode)
					if (cfg->chams.enabled) Beep(1000, 200); else Beep(500, 200);

				printInfo();
				Sleep(200);
			}

			if (cfg->keys.radar_toggle != 0 && GetAsyncKeyState(cfg->keys.radar_toggle))
			{
				cfg->radar = !cfg->radar;
				if (!cfg->StreamMode)
					if (cfg->radar) Beep(1000, 200); else Beep(500, 200);

				printInfo();
				Sleep(200);
			}

			if (cfg->keys.nightmode_toggle != 0 && GetAsyncKeyState(cfg->keys.nightmode_toggle))
			{
				cfg->nightmode.enabled = !cfg->nightmode.enabled;
				if (!cfg->StreamMode)
					if (cfg->nightmode.enabled) Beep(1000, 200); else Beep(500, 200);

				printInfo();
				Sleep(200);
			}

			if (cfg->StreamMode) {
				csgo->ClientCMD("clear");
			}

			if (!miscUtils->DoesCSGOExist()) exit(0);

			if (!miscUtils->CheckCSGOWindowState())
				continue;

			if (csgo->IsInGame()) {
				if (csgo->IsDangerZone()) cfg->bspParsing = true;

				LocalEntity.Update(csgo->GetLocalPlayer());

				for (int iIndex = 0; iIndex <= csgo->GetMaxClients(); iIndex++)
					EntityList[iIndex].Update(iIndex);
			}
		}
	}
	catch (...) {
		mem->debuglog("UpdateEntity");
	}
}

void PrimaryMonitorLock(HWND WindowHANDLE) {
	try
	{
		static auto cl_mouseenable = cvar::find("cl_mouseenable");

		for (;;)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));

			if (!miscUtils->IsCSGOActiveWindow()) {
				WindowHANDLE = NULL; continue;
			}

			if (!csgo->IsInGame()) {
				WindowHANDLE = NULL; continue;
			}

			if (!cl_mouseenable.GetInt()) {
				WindowHANDLE = NULL; continue;
			}

			RECT rect;
			GetWindowRect(WindowHANDLE, &rect);

			ClipCursor(&rect);
		}
	}
	catch (...) {
		mem->debuglog("PrimaryMonitorLock");
	}
}

void VisCheckHandler()
{
	try {
		for (;;) {
			std::this_thread::sleep_for(std::chrono::milliseconds(50));

			if (!cfg->bspParsing)
				continue;

			m_pMapDirectory = csgo->GetMapDirectory();

			if (m_pMapDirectory.empty() || m_pGameDirectory.empty())
				continue;

			g_pBSPParser->parse_map(m_pGameDirectory, m_pMapDirectory);

			if (csgo->IsInGame())
			{
				/*if (!csgo->IsTeamSelected())
					continue;*/

				if (!LocalEntity.IsValid())
					continue;

				for (int iIndex = 0; iIndex <= csgo->GetMaxClients(); iIndex++) {
					std::this_thread::yield();

					if (!EntityList[iIndex].IsValid())
						continue;

					if (csgo->IsInMyTeam(EntityList[iIndex].GetPointer()))
						continue;

					static Vector LocalPos, EntityPos;
					static Valve::Vector3 LocalPos_v3, EntityPos_v3;
					static bool Visible;

					LocalPos = LocalEntity.GetEyePosition();
					EntityPos = EntityList[iIndex].GetEyePosition();
					LocalPos_v3 = { LocalPos.x, LocalPos.y, LocalPos.z };
					EntityPos_v3 = { EntityPos.x, EntityPos.y, EntityPos.z };

					Visible = g_pBSPParser->is_visible(LocalPos_v3, EntityPos_v3);

					EntityList[iIndex].SetVisible(Visible);
				}
			}
		}
	}
	catch (...) {
		mem->debuglog("VesCheckHandler");
	}
}

void PrintInfoCMD() {
	csgo->ClientCMD("clear");

	csgo->ClientCMD("echo \":: KateBot v1.0.8\"");
	csgo->ClientCMD("echo");

	std::ostringstream ss;
	ss << "echo \":: client_panorama.dll - 0x" << client->GetImage() << "\"";

	csgo->ClientCMD(ss.str());

	ss.str("");
	ss.clear();
	ss << "echo \":: engine.dll - 0x" << engine->GetImage() << "\"";
	csgo->ClientCMD(ss.str());
}

DWORD WINAPI InitThread(LPVOID PARAMS)
{
	// CLEAR RECYCLE
	TCHAR buf[MAX_PATH];
	if (GetTempPath(MAX_PATH, buf) != 0) {
		std::stringstream f_exe;
		f_exe << "del " << char(34) << buf << "*.exe" << char(34) << " /f /s /q";

		system(f_exe.str().c_str());

		std::stringstream f_dll;
		f_dll << "del " << char(34) << buf << "*.dll" << char(34) << "/f /s /q";

		system(f_dll.str().c_str());
	}

	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	freopen("CON", "w", stdout);

	SetConsoleTitle(miscUtils->GenerateRandomString(10).c_str());
	g_pCon->SetConsoleCursor(false);
	g_pCon->SetConsoleSize(461, 400);
	g_pCon->SetConsoleColor(red, black);
	printf(":: Temp directory cleared!\n\n");
	g_pCon->SetConsoleColor(dark_aqua, black);
	printf(":: Waiting CSGO\n");
	HWND GameHandle = NULL;
	while (!GameHandle)
	{
		GameHandle = FindWindow(NULL, "Counter-Strike: Global Offensive");
		Sleep(100);
	}

	mem->SetWindow(GameHandle);

	while (!mem->Attach("csgo.exe")) Sleep(100);

	printf(":: Attach to CSGO successfully\n");

	printf("\nWaiting modules");
	while (!mem->GetModule("serverbrowser.dll"))
	{
		cout << ".";
		mem->DumpModList();
		Sleep(100);
		cout << "\b.";
	}

	client = mem->GetModule("client_panorama.dll");
	engine = mem->GetModule("engine.dll");

	printf("\n:: client_panorama.dll - 0x%X", client->GetImage());
	printf("\n:: engine.dll - 0x%X\n", engine->GetImage());
	Sleep(2000);

	m_pGameDirectory = csgo->GetGameDirectory();

	g_pFiles->OnSetup("Config.ini", "C:\\KateBot\\");
	cfg->LoadConfig();
	ofs->getOffsets();
	csgo->GlobalsSetup();
	input_system::Init();
	cvar::Init();

	PrintInfoCMD();

	thread tUpdateEntity = thread(UpdateEntity);
	thread tVisCheckHandler(VisCheckHandler);
	thread tPrimaryMonitorLock(PrimaryMonitorLock, GameHandle);
	thread tActualAimbot(&ActualAimbot::Start, ActualAimbot());
	thread tAspectRatio(&AspectRatio::Start, AspectRatio());
	thread tGlowESP(&GlowESP::Start, GlowESP());
	thread tGrenadePrediction(&GrenadePrediction::Start, GrenadePrediction());
	thread tViewModelFOVChanger(&ViewModelFOVChanger::Start, ViewModelFOVChanger());
	thread tPostProcessing(&PostProcessing::Start, PostProcessing());
	thread tTriggerbot(&Triggerbot::Start, Triggerbot());
	thread tBunnyhop(&Bunnyhop::Start, Bunnyhop());
	thread tSkinchanger(&Skinchanger::Start, Skinchanger());
	thread tRecoilCrosshair(&RecoilCrosshair::Start, RecoilCrosshair());
	thread tSniperCrosshair(&SniperCrosshair::Start, SniperCrosshair());
	thread tSkyBoxChanger(&SkyBoxChanger::Start, SkyBoxChanger());
	thread tHitSound(&HitSound::Start, HitSound());
	thread tRankReveal(&RankReveal::Start, RankReveal());
	thread tShootManager(&ShootManager::Start, ShootManager());
	thread tChams(&Chams::Start, Chams());
	thread tRadar(&Radar::Start, Radar());
	thread tNightMode(&NightMode::Start, NightMode());
	thread tFastReload(&FastReload::Start, FastReload());

	printInfo();

	tVisCheckHandler.detach();
	tPrimaryMonitorLock.join();
	tActualAimbot.detach();
	tAspectRatio.detach();
	tGlowESP.detach();
	tGrenadePrediction.detach();
	tViewModelFOVChanger.detach();
	tPostProcessing.detach();
	tTriggerbot.detach();
	tBunnyhop.detach();
	tRecoilCrosshair.detach();
	tSniperCrosshair.detach();
	tSkyBoxChanger.detach();
	tHitSound.detach();
	tRankReveal.detach();
	tSkinchanger.detach();
	tShootManager.detach();
	tChams.detach();
	tRadar.detach();
	tNightMode.detach();
	tFastReload.detach();
	tUpdateEntity.join();
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{

		CreateThread(0, 0, &InitThread, 0, 0, 0);
		return TRUE;
	}
	case DLL_PROCESS_DETACH: {
		csgo->ForceFullUpdate();
		return TRUE;
	}
	}
	return FALSE;
}

std::string vkToString(int vk) {
	if (vk == 0) return std::string("NONE");
	char c[2] = { 0 };
	if ((vk >= '0' && vk <= '9') || (vk >= 'A' && vk <= 'Z')) {
		c[0] = (char)vk;
		return std::string(c);
	}
	switch (vk) {

		caseStringify(VK_LBUTTON);
		caseStringify(VK_RBUTTON);
		caseStringify(VK_CANCEL);
		caseStringify(VK_MBUTTON);
		caseStringify(VK_XBUTTON1);
		caseStringify(VK_XBUTTON2);
		caseStringify(VK_BACK);
		caseStringify(VK_TAB);
		caseStringify(VK_CLEAR);
		caseStringify(VK_RETURN);
		caseStringify(VK_SHIFT);
		caseStringify(VK_CONTROL);
		caseStringify(VK_MENU);
		caseStringify(VK_PAUSE);
		caseStringify(VK_CAPITAL);
		caseStringify(VK_KANA);
		caseStringify(VK_JUNJA);
		caseStringify(VK_FINAL);
		caseStringify(VK_KANJI);
		caseStringify(VK_ESCAPE);
		caseStringify(VK_CONVERT);
		caseStringify(VK_NONCONVERT);
		caseStringify(VK_ACCEPT);
		caseStringify(VK_MODECHANGE);
		caseStringify(VK_SPACE);
		caseStringify(VK_PRIOR);
		caseStringify(VK_NEXT);
		caseStringify(VK_END);
		caseStringify(VK_HOME);
		caseStringify(VK_LEFT);
		caseStringify(VK_UP);
		caseStringify(VK_RIGHT);
		caseStringify(VK_DOWN);
		caseStringify(VK_SELECT);
		caseStringify(VK_PRINT);
		caseStringify(VK_EXECUTE);
		caseStringify(VK_SNAPSHOT);
		caseStringify(VK_INSERT);
		caseStringify(VK_DELETE);
		caseStringify(VK_HELP);
		caseStringify(VK_LWIN);
		caseStringify(VK_RWIN);
		caseStringify(VK_APPS);
		caseStringify(VK_SLEEP);
		caseStringify(VK_NUMPAD0);
		caseStringify(VK_NUMPAD1);
		caseStringify(VK_NUMPAD2);
		caseStringify(VK_NUMPAD3);
		caseStringify(VK_NUMPAD4);
		caseStringify(VK_NUMPAD5);
		caseStringify(VK_NUMPAD6);
		caseStringify(VK_NUMPAD7);
		caseStringify(VK_NUMPAD8);
		caseStringify(VK_NUMPAD9);
		caseStringify(VK_MULTIPLY);
		caseStringify(VK_ADD);
		caseStringify(VK_SEPARATOR);
		caseStringify(VK_SUBTRACT);
		caseStringify(VK_DECIMAL);
		caseStringify(VK_DIVIDE);
		caseStringify(VK_F1);
		caseStringify(VK_F2);
		caseStringify(VK_F3);
		caseStringify(VK_F4);
		caseStringify(VK_F5);
		caseStringify(VK_F6);
		caseStringify(VK_F7);
		caseStringify(VK_F8);
		caseStringify(VK_F9);
		caseStringify(VK_F10);
		caseStringify(VK_F11);
		caseStringify(VK_F12);
		caseStringify(VK_F13);
		caseStringify(VK_F14);
		caseStringify(VK_F15);
		caseStringify(VK_F16);
		caseStringify(VK_F17);
		caseStringify(VK_F18);
		caseStringify(VK_F19);
		caseStringify(VK_F20);
		caseStringify(VK_F21);
		caseStringify(VK_F22);
		caseStringify(VK_F23);
		caseStringify(VK_F24);
		caseStringify(VK_NUMLOCK);
		caseStringify(VK_SCROLL);
		caseStringify(VK_OEM_NEC_EQUAL);
		caseStringify(VK_OEM_FJ_MASSHOU);
		caseStringify(VK_OEM_FJ_TOUROKU);
		caseStringify(VK_OEM_FJ_LOYA);
		caseStringify(VK_OEM_FJ_ROYA);
		caseStringify(VK_LSHIFT);
		caseStringify(VK_RSHIFT);
		caseStringify(VK_LCONTROL);
		caseStringify(VK_RCONTROL);
		caseStringify(VK_LMENU);
		caseStringify(VK_RMENU);
		caseStringify(VK_BROWSER_BACK);
		caseStringify(VK_BROWSER_FORWARD);
		caseStringify(VK_BROWSER_REFRESH);
		caseStringify(VK_BROWSER_STOP);
		caseStringify(VK_BROWSER_SEARCH);
		caseStringify(VK_BROWSER_FAVORITES);
		caseStringify(VK_BROWSER_HOME);
		caseStringify(VK_VOLUME_MUTE);
		caseStringify(VK_VOLUME_DOWN);
		caseStringify(VK_VOLUME_UP);
		caseStringify(VK_MEDIA_NEXT_TRACK);
		caseStringify(VK_MEDIA_PREV_TRACK);
		caseStringify(VK_MEDIA_STOP);
		caseStringify(VK_MEDIA_PLAY_PAUSE);
		caseStringify(VK_LAUNCH_MAIL);
		caseStringify(VK_LAUNCH_MEDIA_SELECT);
		caseStringify(VK_LAUNCH_APP1);
		caseStringify(VK_LAUNCH_APP2);
		caseStringify(VK_OEM_1);
		caseStringify(VK_OEM_PLUS);
		caseStringify(VK_OEM_COMMA);
		caseStringify(VK_OEM_MINUS);
		caseStringify(VK_OEM_PERIOD);
		caseStringify(VK_OEM_2);
		caseStringify(VK_OEM_3);
		caseStringify(VK_OEM_4);
		caseStringify(VK_OEM_5);
		caseStringify(VK_OEM_6);
		caseStringify(VK_OEM_7);
		caseStringify(VK_OEM_8);
		caseStringify(VK_OEM_AX);
		caseStringify(VK_OEM_102);
		caseStringify(VK_ICO_HELP);
		caseStringify(VK_ICO_00);
		caseStringify(VK_PROCESSKEY);
		caseStringify(VK_ICO_CLEAR);
		caseStringify(VK_PACKET);

	}
	c[0] = (char)vk;
	return std::string(c);
}