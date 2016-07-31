#pragma once

struct player_info_t
{ //-V802
	char			name[32];
	int				userID;
	char			guid[33];
	unsigned int	friendsID;
	char			frinedsName[32];
	bool			fakeplayer;
	bool			ishltv;
	unsigned long	customFiles[4];
	unsigned char	filesDownloaded;
};

class g_engineclient
{
public:
	void SetViewAngles(Angle& vAngle);
	void GetScreenSize(int& width, int& height);
	void ClientCmd(const char* chText);
	int GetLocalPlayer();
	bool GetPlayerInfo(int ent_num, player_info_t* pinfo);
	bool IsInGame();
	int GetMaxClients();
	const Matrix4x4& WorldToScreenMatrix();
};