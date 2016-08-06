#pragma once

#include "g_chclient/g_chclient.h"
#include "g_cliententitylist/g_cliententitylist.h"
#include "g_cvar/g_cvar.h"
#include "g_debugoverlay/g_debugoverlay.h"
#include "g_engineclient/g_engineclient.h"
#include "g_gameconsole/g_gameconsole.h"
#include "g_input/g_input.h"
#include "g_interfacegrabber/g_interfacegrabber.h"
#include "g_lua/g_lua.h"
#include "g_modeldata/g_modeldata.h"
#include "g_panel/g_panel.h"
#include "g_prediction/g_prediction.h"
#include "g_surface/g_surface.h"
#include "g_trace/g_trace.h"

namespace g_Interfaces
{
	extern g_chclient* client;
	extern g_globaldata* globaldata;
	extern g_cliententitylist* entlist;
	extern void* clientmode;
	extern g_cvar* cvar;
	extern g_cvarsearch* cvarsearch;
	extern g_debugoverlay* debugoverlay;
	extern g_engineclient* engine;
	extern g_gameconsole* gameconsole;
	extern g_input* input;
	extern g_interfacegrabber* grab;
	extern g_lua* lua;
	extern g_LuaShared* luashared;
	extern g_panel* panel;
	extern g_modeldata* modeldata;
	extern g_gamemovement* gamemovement;
	extern g_prediction* prediction;
	extern g_movehelper* movehelper;
	extern g_surface* surface;
	extern g_surface2* surface2;
	extern g_EngineTrace* trace;
};