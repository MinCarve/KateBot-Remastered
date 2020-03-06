#include "main.h"

Config* cfg = new Config();



void Config::SaveConfig()
{
	for (auto& map_data : m_mapWeapons)
	{
		char * weaponName = new char[map_data.second.size() + 1];
		std::copy(map_data.second.begin(), map_data.second.end(), weaponName);
		weaponName[map_data.second.size()] = '\0';
		
		char* weapontype = WeaponType(map_data.first);
		
		g_pFiles->WriteBoolParam	(weapontype,weaponName, ".aimbot.enable",aimbot[map_data.first].enable);
		g_pFiles->WriteIntParam		(weapontype,weaponName, ".aimbot.start",aimbot[map_data.first].startbullet);
		g_pFiles->WriteIntParam		(weapontype,weaponName, ".aimbot.end",aimbot[map_data.first].endbullet);
		g_pFiles->WriteFloatParam	(weapontype,weaponName, ".aimbot.delay",aimbot[map_data.first].delay);
		g_pFiles->WriteFloatParam	(weapontype,weaponName, ".aimbot.fov",aimbot[map_data.first].fov);
		g_pFiles->WriteFloatParam	(weapontype,weaponName, ".aimbot.smooth",aimbot[map_data.first].smooth);
		g_pFiles->WriteIntParam		(weapontype,weaponName, ".aimbot.bone",aimbot[map_data.first].bone);
		g_pFiles->WriteFloatParam	(weapontype,weaponName, ".aimbot.rcsAmount",aimbot[map_data.first].rcsAmount);
		g_pFiles->WriteFloatParam	(weapontype,weaponName, ".aimbot.killDelay",aimbot[map_data.first].killdelay);
		
		delete[] weaponName;
	}
}

void Config::LoadConfig()
{
	keys.aimbot_toggle = g_pFiles->ReadInt("Keys","Aimbot.Toggle");
	keys.aimbot_hold = g_pFiles->ReadInt("Keys","Aimbot.Hold");
	keys.glowesp_toggle = g_pFiles->ReadInt("Keys","GlowESP.Toggle");
	keys.triggerbot_hold = g_pFiles->ReadInt("Keys","Triggerbot.Hold");
	keys.bunnyhop_hold = g_pFiles->ReadInt("Keys","Bunnyhop.Hold");
	keys.skinchanger_toggle = g_pFiles->ReadInt("Keys", "Skinchanger.Toggle");
	keys.chams_toggle = g_pFiles->ReadInt("Keys", "Chams.Toggle");
	keys.nightmode_toggle = g_pFiles->ReadInt("Keys", "NightMode.Toggle");
	keys.radar_toggle = g_pFiles->ReadInt("Keys", "Radar.Toggle");
	//keys.panic_mode = g_pFiles->ReadInt("Keys","PANIC_MODE");
	
	debugEnable = g_pFiles->ReadBool("Features", "Debug.Enable");
	StreamMode = g_pFiles->ReadBool("Features","StreamMode.Enable");
	glowEspEnabled = g_pFiles->ReadBool("Features","GlowESP.Enable");
	aimbotEnabled = g_pFiles->ReadBool("Features","Aimbot.Enable");
	triggerbotEnabled = g_pFiles->ReadBool("Features","Triggerbot.Enable");
	bunnyhopEnabled = g_pFiles->ReadBool("Features","Bunnyhop.Enable");
	skinchangerEnabled = g_pFiles->ReadBool("Features","Skinchanger.Enable");
	chams.enabled = g_pFiles->ReadBool("Features", "Chams.Enable");
	radar = g_pFiles->ReadBool("Features", "Radar.Enable");
	nightmode.enabled = g_pFiles->ReadBool("Features", "NightMode.Enable");
	fastReload = g_pFiles->ReadBool("Features", "FastReload.Enable");
	hitsound = g_pFiles->ReadBool("Features", "Hitsound.Enable");
	rcs.enable = g_pFiles->ReadBool("Features", "RCS.Enable");

	RiflesAdaptiveSmoothMultiplier = g_pFiles->ReadFloat("Aimbot", "AdaptiveSmooth.Rifles.Multiplier");
	PistolsAdaptiveSmoothMultiplier = g_pFiles->ReadFloat("Aimbot", "AdaptiveSmooth.Pistol.Multiplier");
	SnipersAdaptiveSmoothMultiplier = g_pFiles->ReadFloat("Aimbot", "AdaptiveSmooth.Sniper.Multiplier");
	SMGsAdaptiveSmoothMultiplier = g_pFiles->ReadFloat("Aimbot", "AdaptiveSmooth.SMG.Multiplier");
	ShotGunsAdaptiveSmoothMultiplier = g_pFiles->ReadFloat("Aimbot", "AdaptiveSmooth.Shotgun.Multiplier");
	LMGsAdaptiveSmoothMultiplier = g_pFiles->ReadFloat("Aimbot", "AdaptiveSmooth.LMG.Multiplier");

	RiflesAdaptiveSmooth = g_pFiles->ReadBool("Aimbot","AdaptiveSmooth.Rifles");
	PistolsAdaptiveSmooth = g_pFiles->ReadBool("Aimbot","AdaptiveSmooth.Pistol");
	SnipersAdaptiveSmooth = g_pFiles->ReadBool("Aimbot","AdaptiveSmooth.Sniper");
	SMGsAdaptiveSmooth = g_pFiles->ReadBool("Aimbot","AdaptiveSmooth.SMG");
	ShotGunsAdaptiveSmooth = g_pFiles->ReadBool("Aimbot","AdaptiveSmooth.Shotgun");
	LMGsAdaptiveSmooth = g_pFiles->ReadBool("Aimbot","AdaptiveSmooth.LMG");
	
	spiralAim = g_pFiles->ReadBool("Aimbot","Spiral.Enable");
	spiralAimX = g_pFiles->ReadFloat("Aimbot","Spiral.X");
	spiralAimY = g_pFiles->ReadFloat("Aimbot","Spiral.Y");
	SaveTargetAim = g_pFiles->ReadBool("Aimbot","SaveTarget.Enable");
	faceitAim = g_pFiles->ReadBool("Aimbot", "FaceitMode.Enable");
	SprayFOV = g_pFiles->ReadBool("Aimbot","SprayFOV.Enable");

	bspParsing = g_pFiles->ReadBool("BSPParsing","Enable");

	chams.modelambient = g_pFiles->ReadBool("Chams", "ModelAmbient.Enable");
	chams.health_based = g_pFiles->ReadBool("Chams", "HealthBased.Enable");
	chams.viewmodel_chams = g_pFiles->ReadBool("Chams", "ViewModel.Enable");
	chams.brightness = g_pFiles->ReadFloat("Chams", "Brightness");
	chams.enemiesonly = g_pFiles->ReadBool("Chams", "EnemiesOnly.Enable");
	chams.enemycolor.r = g_pFiles->ReadInt("Chams", "EnemyColor.Red");
	chams.enemycolor.g = g_pFiles->ReadInt("Chams", "EnemyColor.Green");
	chams.enemycolor.b = g_pFiles->ReadInt("Chams", "EnemyColor.Blue");
	chams.enemycolor.a = g_pFiles->ReadInt("Chams", "EnemyColor.Alpha");
	chams.allycolor.r = g_pFiles->ReadInt("Chams", "AllyColor.Red");
	chams.allycolor.g = g_pFiles->ReadInt("Chams", "AllyColor.Green");
	chams.allycolor.b = g_pFiles->ReadInt("Chams", "AllyColor.Blue");
	chams.allycolor.a = g_pFiles->ReadInt("Chams", "AllyColor.Alpha");
	chams.c4color.r = g_pFiles->ReadInt("Chams", "C4Bomb.Red");
	chams.c4color.g = g_pFiles->ReadInt("Chams", "C4Bomb.Green");
	chams.c4color.b = g_pFiles->ReadInt("Chams", "C4Bomb.Blue");
	chams.c4color.a = g_pFiles->ReadInt("Chams", "C4Bomb.Alpha");
	chams.c4playercolor.r = g_pFiles->ReadInt("Chams", "C4Player.Red");
	chams.c4playercolor.g = g_pFiles->ReadInt("Chams", "C4Player.Green");
	chams.c4playercolor.b = g_pFiles->ReadInt("Chams", "C4Player.Blue");
	chams.c4playercolor.a = g_pFiles->ReadInt("Chams", "C4Player.Alpha");
	chams.defusecolor.r = g_pFiles->ReadInt("Chams", "DefusePlayer.Red");
	chams.defusecolor.g = g_pFiles->ReadInt("Chams", "DefusePlayer.Green");
	chams.defusecolor.b = g_pFiles->ReadInt("Chams", "DefusePlayer.Blue");
	chams.defusecolor.a = g_pFiles->ReadInt("Chams", "DefusePlayer.Alpha");

	rcs.smooth = g_pFiles->ReadFloat("Settings", "RCS.smooth");
	general_skin.knife = g_pFiles->ReadChar("SkinChanger", "Knife");
	general_skin.knife_enable = g_pFiles->ReadBool("SkinChanger", "Knife.Enable");
	general_skin.knife_skin_id = g_pFiles->ReadInt("SkinChanger", "Knife.SkinID");

	nightmode.amount = g_pFiles->ReadFloat("NightMode", "Amount");

	skinchangerAutoUpdate = g_pFiles->ReadBool("Settings","Skinchanger.AutoUpdate");

	triggerbot.fovBased = g_pFiles->ReadBool("Triggerbot", "FovBased.Enable");
	triggerbot.delay = g_pFiles->ReadFloat("Triggerbot","Delay");

	glowesp.noflicker = g_pFiles->ReadBool("GlowESP", "NoFlicker.Enable");
	glowesp.onlyVisible = g_pFiles->ReadBool("GlowESP","OnlyVisible.Enable");
	glowesp.health_based = g_pFiles->ReadBool("GlowESP","HealthBased.Enable");
	glowesp.color.r = g_pFiles->ReadInt("GlowESP","Color.Red");
	glowesp.color.g = g_pFiles->ReadInt("GlowESP","Color.Green");
	glowesp.color.b = g_pFiles->ReadInt("GlowESP","Color.Blue");
	glowesp.color.a = g_pFiles->ReadInt("GlowESP","Color.Alpha");

	knifeModel = g_pFiles->ReadInt("Settings","KnifeChanger.Model(0-10)");
	
	for (auto& map_data : m_mapWeapons)
	{
		char * weaponName = new char[map_data.second.size() + 1];
		std::copy(map_data.second.begin(), map_data.second.end(), weaponName);
		weaponName[map_data.second.size()] = '\0';
		
		char* weapontype = WeaponType(map_data.first);
		
		aimbot[map_data.first].enable 		= g_pFiles->ReadBoolParam(weapontype,weaponName, ".aimbot.enable");
		aimbot[map_data.first].startbullet 	= g_pFiles->ReadIntParam(weapontype,weaponName, ".aimbot.start");
		aimbot[map_data.first].endbullet 	= g_pFiles->ReadIntParam(weapontype,weaponName, ".aimbot.end");
		aimbot[map_data.first].delay 		= g_pFiles->ReadFloatParam(weapontype,weaponName, ".aimbot.delay");
		aimbot[map_data.first].fov 			= g_pFiles->ReadFloatParam(weapontype,weaponName, ".aimbot.fov");
		aimbot[map_data.first].smooth 		= g_pFiles->ReadFloatParam(weapontype,weaponName, ".aimbot.smooth");
		aimbot[map_data.first].bone 		= g_pFiles->ReadIntParam(weapontype,weaponName, ".aimbot.bone");
		aimbot[map_data.first].rcsAmount 	= g_pFiles->ReadFloatParam(weapontype,weaponName, ".aimbot.rcsAmount");
		aimbot[map_data.first].killdelay 	= g_pFiles->ReadFloatParam(weapontype,weaponName, ".aimbot.killDelay");
		skin[map_data.first].id 	= g_pFiles->ReadIntParam(weapontype,weaponName, ".skin.id");
		skin[map_data.first].statTrack 	= g_pFiles->ReadIntParam(weapontype,weaponName, ".skin.statTrack");
		
		delete[] weaponName;
	}
	
	needIndexes = true;
}
	
char* Config::WeaponType(int ID)
{
	switch (ID)
	{
		case WEAPON_NEGEV:
		case WEAPON_M249:
		return "LMG";

		case WEAPON_AWP:
		case WEAPON_G3SG1:
		case WEAPON_SCAR20:
		case WEAPON_SSG08:
		return "Snipers";

		case WEAPON_XM1014:
		case WEAPON_MAG7:
		case WEAPON_NOVA:
		case WEAPON_SAWEDOFF:
		return "Shotguns";

		case WEAPON_MAC10:
		case WEAPON_P90:
		case WEAPON_UMP45:
		case WEAPON_BIZON:
		case WEAPON_MP7:
		case WEAPON_MP9:
		case WEAPON_MP5_SD:
		return "SMGs";

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
		case WEAPON_TASER:
		return "Pistols";

		case WEAPON_AK47:
		case WEAPON_AUG:
		case WEAPON_FAMAS:
		case WEAPON_M4A1:
		case WEAPON_M4A1_SILENCER:
		case WEAPON_GALILAR:
		case WEAPON_SG556:
		return "Rifles";

		default:
		return "null";
	}
}