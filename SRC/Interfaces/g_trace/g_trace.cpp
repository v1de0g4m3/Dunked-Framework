#include "../../sdk.h"

int g_EngineTrace::GetPointContents(const Vector& vecAbsPosition, CBaseEntity** ppEntity)
{
	typedef int(__thiscall* vFuncFn)(void*, const Vector&, CBaseEntity**);
	return vfunc<vFuncFn>(this, 0)(this, vecAbsPosition, ppEntity);
}

void g_EngineTrace::TraceRay(const Ray_t& ray, unsigned int fMask, CTraceFilter* pTraceFilter, trace_t* pTrace)
{
	typedef void(__thiscall* vFuncFn)(void*, const Ray_t&, unsigned int, CTraceFilter*, trace_t*);
	return vfunc<vFuncFn>(this, 4)(this, ray, fMask, pTraceFilter, pTrace);
}

trace_t g_EngineTrace::Trace(const Vector& vStart, const  Vector& vEnd, unsigned int iMask, CBaseEntity* pFilter)
{
	trace_t tr;
	Ray_t ray;
	CTraceFilter filter;

	filter.pSkip = pFilter;

	ray.Init(vStart, vEnd);
	g_Interfaces::trace->TraceRay(ray, iMask, &filter, &tr);

	return tr;
}

g_EngineTrace* g_Interfaces::trace = new g_EngineTrace;