#pragma once

class g_cvar
{
public:
	float GetFloat(void) const
	{
		return m_flValue;
	}

	int GetInt(void) const
	{
		return m_nValue;
	}

	bool GetBool(void) const
	{
		return !!GetInt();
	}

	void SetValue(const char* value);
	void SetValue(float value);
	void SetValue(int value);

private:
	char	pad[0x28];
	float	m_flValue;
	int		m_nValue;
};

class g_cvarsearch
{
public:
	g_cvar* FindVar(const char* var_name);
	void ConsoleColorPrintf(const Color&, const char*, ...);
	void ConsolePrintf(const char*, ...);
};