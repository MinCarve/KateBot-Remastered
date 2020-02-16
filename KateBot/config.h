#pragma once
#include "main.h"

class Config {
public:
	void SaveConfig();
	void LoadConfig();
	
	int InGameFireKey = 191;
	
	float AdaptiveSmoothMultiplier = 1.0f;
	float RiflesAdaptiveSmoothMultiplier = 1.0f;
	float PistolsAdaptiveSmoothMultiplier = 1.0f;
	float SnipersAdaptiveSmoothMultiplier = 1.0f;
	float SMGsAdaptiveSmoothMultiplier = 1.0f;
	float ShotGunsAdaptiveSmoothMultiplier = 1.0f;
	float LMGsAdaptiveSmoothMultiplier = 1.0f;

	bool RiflesAdaptiveSmooth = false;
	bool PistolsAdaptiveSmooth = false;
	bool SnipersAdaptiveSmooth = false;
	bool SMGsAdaptiveSmooth = false;
	bool ShotGunsAdaptiveSmooth = false;
	bool LMGsAdaptiveSmooth = false;
	bool spiralAim = false;
	float spiralAimX = 1.3f;
	float spiralAimY = 3.7f;
	bool faceitAim = false;
	bool SaveTargetAim = false;
	bool bspParsing = false;
	bool skinchangerAutoUpdate = true;
	bool glowEspEnabled = true;
	bool aimbotEnabled = false;
	bool triggerbotEnabled = false;
	bool bunnyhopEnabled = false;
	bool skinchangerEnabled = false;
	bool fastReload = false;
	bool radar = false;
	bool panicMode = false;
	bool debugEnable = false;
	bool hitsound = false;

	bool needIndexes = true;
	
	struct keys {
		int aimbot_toggle;
		int aimbot_hold;
		int glowesp_toggle;
		int triggerbot_hold;
		int bunnyhop_hold;
		int chams_toggle;
		int nightmode_toggle;
		int radar_toggle;
		int skinchanger_toggle;
	}keys;
	
	struct aimbot {
		
		bool enable = false;
		int startbullet = 0;
		int endbullet = 0;
		float delay = 0.f;
		float fov = 0.f;
		float smooth = 0.f;
		int bone = 0;
		float rcsAmount = 0.f;
		float killdelay = 0.f;
		
	}aimbot[100];

	struct rcs {
		bool enable = false;
		float smooth = 0.f;
	}rcs;
	
	struct general_skin {
		char* knife = NULL;
		bool knife_enable = false;
		int knife_skin_id = 569;
	}general_skin;

	struct skin {
		
		int id = 0;
		int statTrack = 0;
		
	}skin[100];
	
	struct chams {
		bool enabled;
		bool health_based;
		Color enemycolor;
		Color allycolor;
		Color c4color;
		Color c4playercolor;
		Color defusecolor;
		bool enemiesonly = false;
		bool modelambient = false;
		bool viewmodel_chams = false;
	}chams;

	struct nightmode {
		bool enabled = false;
		float amount = 20.f;
	}nightmode;

	struct glowesp {
		bool noflicker;
		bool onlyVisible;
		bool health_based;
		Color color;
	}glowesp;
	
	struct triggerbot {
		bool fovBased;
		float delay;
	}triggerbot;
	
	int knifeModel = 0;
	
private:	
	char* WeaponType(int ID);
	
	std::unordered_map<int, std::string> m_mapWeapons =
	{
		{ 1, "deagle" }, { 2, "dual_berettas" }, { 3, "five_seven" },
		{ 4, "glock"} , { 7, "ak47" }, { 8, "aug" },
		{ 9, "awp" }, { 10, "famas" }, { 11, "g3sg1" },
		{13, "galil"}, { 14, "m249"}, {16, "m4a4"},
		{17, "mac10"}, {19, "p90"}, {24, "ump45"},
		{25, "xm1014"}, {26, "bizon"}, {27, "mag7"},
		{28, "negev"}, {29, "sawed_off"}, {30, "tec9"},
		{31, "zeus"}, {32, "p2000"}, {33, "mp7"},
		{34, "mp9"}, {35, "nova"}, {36, "p250"},
		{38, "scar-20"}, {39, "ssg553"}, {40, "scout"},
		{60, "m4a1s"}, {61, "usp"}, {63, "cz75"},
		{64, "r8"}
	};
};

extern Config* cfg;