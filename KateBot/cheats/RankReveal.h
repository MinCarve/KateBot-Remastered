#ifndef _RANK_REVEAL_H_
#define _RANK_REVEAL_H_

#include "..\main.h"

class RankReveal {
public:
	void Start() {
		try {
			for (;;) {
				std::this_thread::sleep_for(std::chrono::milliseconds(40));

				if (!miscUtils->IsCSGOActiveWindow())
					continue;

				if (!csgo->IsInGame())
					continue;

				if (cfg->StreamMode)
					continue;

				if (!cfg->RevealRank)
					continue;

				if (!input_system::IsButtonDown(input_system::vktobc(VK_HOME))) continue;

				this->Terrorists.clear();
				this->CounterTerrorists.clear();

				csgo->ClientCMD("clear");
				csgo->ClientCMD("echo Rank Revealer");
				csgo->ClientCMD("echo");

				for (auto e : EntityList) {
					if (!e.GetProfileInfo().xuid) continue;

					int entity_team_num = e.GetTeamNum();

					if (entity_team_num == 2)
						this->Terrorists.push_back(e);
					else if (entity_team_num == 3)
						this->CounterTerrorists.push_back(e);
				}

				csgo->ClientCMD("echo Terrorists");
				csgo->ClientCMD("echo \"==============================\"");

				for (auto t : this->Terrorists)
				{
					std::ostringstream ss;

					ss << "echo \"" << t.GetProfileInfo().name << " - [" <<
						this->Ranks[t.GetRank()] << "] - " <<
						t.GetWins() << " wins";

					csgo->ClientCMD(ss.str());
				}

				csgo->ClientCMD("echo");

				csgo->ClientCMD("echo Counter-Terrorists");
				csgo->ClientCMD("echo \"==============================\"");

				for (auto ct : this->CounterTerrorists)
				{
					std::ostringstream ss;

					ss << "echo \"" << ct.GetProfileInfo().name << " - [" <<
						this->Ranks[ct.GetRank()] << "] - " <<
						ct.GetWins() << " wins";

					csgo->ClientCMD(ss.str());
				}

				std::this_thread::sleep_for(std::chrono::milliseconds(1500));
			}
		}
		catch (...) {
			mem->debuglog(__FILE__);
		}
	}
private:
	std::vector<Entity> Terrorists;
	std::vector<Entity> CounterTerrorists;

	std::string Ranks[19] =
	{
		"Unranked",
		"Silver I",
		"Silver II",
		"Silver III",
		"Silver IV",
		"Silver Elite",
		"Silver Elite Master",

		"Gold Nova I",
		"Gold Nova II",
		"Gold Nova III",
		"Gold Nova Master",
		"Master Guardian I",
		"Master Guardian II",

		"Master Guardian Elite",
		"Distinguished Master Guardian",
		"Legendary Eagle",
		"Legendary Eagle Master",
		"Supreme Master First Class",
		"Global Elite"
	};
};

#endif