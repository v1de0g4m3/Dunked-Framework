#pragma once

class CGameTrace;
typedef CGameTrace trace_t;

enum TraceType_t
{
	TRACE_EVERYTHING = 0,
	TRACE_WORLD_ONLY,
	TRACE_ENTITIES_ONLY,
	TRACE_EVERYTHING_FILTER_PROPS
};

struct cplane_t
{
	Vector		normal;
	float		dist;
	byte		type;
	byte		signbits;
	byte		pad[2];
};

struct csurface_t
{
	const char*		name;
	short			surfaceProps;
	unsigned short	flags;
};

class ITraceFilter
{
public:
	virtual bool ShouldHitEntity(CBaseEntity* pEntityHandle, int)
	{
		return !(pEntityHandle == pSkip);
	}
	virtual TraceType_t	GetTraceType()
	{
		return TRACE_EVERYTHING;
	}
	void* pSkip;
};

class CTraceFilter : public ITraceFilter
{
public:
	virtual bool ShouldHitEntity(CBaseEntity* pEntityHandle, int)
	{
		return !(pEntityHandle == pSkip);
	}

	virtual TraceType_t	GetTraceType() const
	{
		return TRACE_EVERYTHING;
	}
	void* pSkip; //-V703
};

class CTraceFilterSkipTwoEntities : public ITraceFilter
{
public:
	CTraceFilterSkipTwoEntities(void *pPassEnt1, void *pPassEnt2)
	{
		pPassEntity1 = pPassEnt1;
		pPassEntity2 = pPassEnt2;
	}

	virtual bool ShouldHitEntity(CBaseEntity *pEntityHandle, int)
	{
		return !(pEntityHandle == pPassEntity1 || pEntityHandle == pPassEntity2);
	}

	virtual TraceType_t GetTraceType() const
	{
		return TRACE_EVERYTHING;
	}

	void *pPassEntity1;
	void *pPassEntity2;
};

class CBaseTrace
{
public:
	Vector			startpos;
	Vector			endpos;
	cplane_t		plane;

	float			fraction;

	int				contents;
	unsigned short	dispFlags;

	bool			allsolid;
	bool			startsolid;

	CBaseTrace() {} //-V730
};


class CGameTrace : public CBaseTrace
{
public:
	float			fractionleftsolid;
	csurface_t		surface;

	int				hitgroup;

	short			physicsbone;
	unsigned short	worldSurfaceIndex;

	CBaseEntity*	m_pEnt;
	int				hitbox;

	CGameTrace() {} //-V730
}; typedef CGameTrace trace_t;

struct Ray_t
{
	Vector m_Start;
	Vector m_Delta;
	Vector m_StartOffset;
	Vector m_Extents;

	bool	m_IsRay;
	bool	m_IsSwept;

	void Init(const Vector& start, const Vector& end)
	{
		m_Delta = static_cast<Vector>(end) - start;

		m_IsSwept = (fabs(m_Delta.LengthSqr() - 0) > DBL_EPSILON);

		m_Extents.Clear();
		m_IsRay = true;

		m_StartOffset.Clear();
		m_Start = start;
	}

	void Init(const Vector& start, const Vector& end, const Vector& mins, const Vector& maxs)
	{
		m_Delta = static_cast<Vector>(end) - start;

		m_IsSwept = (fabs(m_Delta.LengthSqr() - 0) > DBL_EPSILON);

		m_Extents = static_cast<Vector>(maxs) - mins;
		m_Extents *= 0.5f;
		m_IsRay = (m_Extents.LengthSqr() < 1e-6);

		m_StartOffset = static_cast<Vector>(mins) + maxs;
		m_StartOffset *= 0.5f;
		m_Start = static_cast<Vector>(start) + m_StartOffset;
		m_StartOffset *= -1.0f;
	}
};

class g_EngineTrace
{
public:
	int GetPointContents(const Vector& vecAbsPosition, CBaseEntity** ppEntity = nullptr);
	void TraceRay(const Ray_t& ray, unsigned fMask, CTraceFilter* pTraceFilter, trace_t* pTrace);
	static trace_t Trace(const Vector& vStart, const Vector& vEnd, unsigned iMask, CBaseEntity* pFilter = nullptr);
};