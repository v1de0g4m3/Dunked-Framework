#pragma once

class g_gameconsole
{
public:
	virtual ~g_gameconsole()
	{
	}

	virtual void Activate() = 0;
	virtual void Intialize() = 0;
	virtual void Hide() = 0;
	virtual void Clear() = 0;
	virtual void IsConsoleVisible() = 0;
	virtual void SetParent() = 0;
};