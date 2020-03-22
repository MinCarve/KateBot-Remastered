#pragma once

#pragma warning( disable : 4244 )
#pragma warning( disable : 4309 )
#pragma warning( disable : 4838 )
#pragma warning( disable : 4800 )
#pragma warning( disable : 4334 )
#pragma warning( disable : 4305 )
#pragma warning( disable : 4805 )
#pragma warning( disable : 4018 )
#pragma warning( disable : 4172 )
#pragma warning( disable : 4042 )

#pragma warning( disable : 4091 ) //temp


// Defines
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include <windows.h>
#include <mmsystem.h>
#include <vector>
#include <string>
#include <math.h>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <random>
#include <sstream>
#include <fstream>
#include <tlhelp32.h>
#include <psapi.h>
#include <thread>
#include <functional>
#include <future>
#include <array>
#include <Wincrypt.h>
#include <cctype>
#include <stdint.h>
#include <mutex>
#include <unordered_map>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <dwmapi.h>
#include <TCHAR.H>
#include <codecvt>
#include <chrono>
#include <shlobj.h>
#include <map>

// Typedefs
#include "Utils\typedefs.h"

// ValveBSP
#include "ValveBSP\BSPParser.hpp"

// Memory
#include "Mem\module.h"
#include "Mem\Mem.h"

// Settings and Offsets
#include "offsets.h"
#include "config.h"

// CSGO
#include "enums.h"
#include "CSGO\math.h"
#include "CSGO\csgo.h"
#include "CSGO\entity.h"

#include "CSGO\cvar_mgr.hpp"
#include "CSGO\input_system.hpp"

// Utils
#include "Utils\files.h"
#include "Utils\console.h"
#include "Utils\MiscUtils.h"
#include "Utils\Color.h"
#include "Utils\ShootManager.h"
#include "Utils\Cray.h"

// Cheats
#include "Cheats\ActualAimbot.h"
#include "Cheats\AspectRatio.h"
#include "Cheats\GlowESP.h"
#include "Cheats\GrenadePrediction.h"
#include "Cheats\ViewModelFOV.h"
#include "Cheats\PostProcessing.h"
#include "Cheats\Triggerbot.h"
#include "Cheats\Bunnyhop.h"
#include "Cheats\Skinchanger.h"
#include "Cheats\RecoilCrosshair.h"
#include "Cheats\SkyBoxChanger.h"
#include "Cheats\Chams.h"
#include "Cheats\Radar.h"
#include "Cheats\NightMode.h"
#include "Cheats\FastReload.h"
