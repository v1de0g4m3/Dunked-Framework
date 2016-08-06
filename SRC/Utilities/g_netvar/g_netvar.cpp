#include "../../sdk.h"

void g_netvar::Start()
{
	g_utilList::exception->traceLastFunction(__FUNCSIG__, __FUNCDNAME__);

	m_tables.clear();

	auto clientClass = g_Interfaces::client->GetAllClasses();
	if (!clientClass)
		return;

	while (clientClass)
	{
		auto recvTable = clientClass->m_pRecvTable;
		m_tables.push_back(recvTable);

		clientClass = clientClass->m_pNext;
	}
}

int g_netvar::GetOffset(const char *tableName, const char *propName) const
{
	g_utilList::exception->traceLastFunction(__FUNCSIG__, __FUNCDNAME__);

	auto offset = GetProp(tableName, propName);

	g_utilList::console->Print(" Scanning Netvar %s... ", propName);

	if (!offset)
	{
		g_utilList::console->Print("Error!");
		return 0;
	}
	g_utilList::console->Print("0x%i\n", offset);

	return offset;
}

RecvVarProxyFn g_netvar::HookProp(const char *tableName, const char *propName, RecvVarProxyFn function) const
{
	g_utilList::exception->traceLastFunction(__FUNCSIG__, __FUNCDNAME__);

	RecvProp *recvProp = nullptr;

	if (!GetProp(tableName, propName, &recvProp))
		return nullptr;


	auto old = recvProp->m_ProxyFn;
	recvProp->m_ProxyFn = function;

	return old;
}

int g_netvar::GetProp(const char *tableName, const char *propName, RecvProp **prop) const
{
	g_utilList::exception->traceLastFunction(__FUNCSIG__, __FUNCDNAME__);

	auto recvTable = GetTable(tableName);
	if (!recvTable)
		return 0;

	auto offset = GetProp(recvTable, propName, prop);
	if (!offset)
		return 0;

	return offset;
}

int g_netvar::GetProp(RecvTable *recvTable, const char *propName, RecvProp **prop) const
{
	g_utilList::exception->traceLastFunction(__FUNCSIG__, __FUNCDNAME__);

	auto extraOffset = 0;
	for (auto i = 0; i < recvTable->m_nProps; ++i)
	{
		auto recvProp = &recvTable->m_pProps[i];
		auto child = recvProp->m_pDataTable;

		if (child && (child->m_nProps > 0))
		{
			auto tmp = GetProp(child, propName, prop);
			if (tmp)
				extraOffset += (recvProp->m_Offset + tmp);
		}

		if (_stricmp(recvProp->m_pVarName, propName) != 0)
			continue;

		if (prop)
			*prop = recvProp;

		return (recvProp->m_Offset + extraOffset);
	}

	return extraOffset;
}

RecvTable *g_netvar::GetTable(const char *tableName) const
{
	g_utilList::exception->traceLastFunction(__FUNCSIG__, __FUNCDNAME__);

	if (m_tables.empty())
		return nullptr;

	for each (RecvTable *table in m_tables)
	{
		if (!table)
			continue;

		if (_stricmp(table->m_pNetTableName, tableName) == 0)
			return table;
	}

	return nullptr;
}

void g_netvar::DumpTable(RecvTable *table) const
{
	g_utilList::exception->traceLastFunction(__FUNCSIG__, __FUNCDNAME__);

	for (auto i = 0; i < table->m_nProps; i++)
	{
		auto prop = &table->m_pProps[i];
		if (!strcmp(prop->m_pVarName, "baseclass"))
		{
			continue;
		}
		if (prop->m_pDataTable)
		{
			DumpTable(prop->m_pDataTable);
		}
	}
}

void g_netvar::DumpNetvars() const
{
	g_utilList::exception->traceLastFunction(__FUNCSIG__, __FUNCDNAME__);

	for (auto pClass = g_Interfaces::client->GetAllClasses(); pClass != nullptr; pClass = pClass->m_pNext)
	{
		auto table = pClass->m_pRecvTable;
		DumpTable(table);
	}
}

g_netvar* g_utilList::netvar = new g_netvar;