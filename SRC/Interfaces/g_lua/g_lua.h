#pragma once

class g_LuaBase;
class g_LuaInterface;

class lua_State
{
public:
	unsigned char header[69];
	g_LuaBase* luabase;
};

class UserData
{
public:
	void* data;
	unsigned char type;
};

typedef struct lua_Debug
{
	int event;
	const char* name; /* (n) */
	const char* namewhat; /* (n) */
	const char* what; /* (S) */
	const char* source; /* (S) */
	int currentline; /* (l) */
	int nups; /* (u) number of upvalues */
	int linedefined; /* (S) */
	int lastlinedefined; /* (S) */
	char short_src[60]; /* (S) */

	/* Private */
	struct lua_TObject* _func; /* active function */
} lua_Debug;

enum
{
	LUA_CLIENT = 0,
	LUA_SERVER = 1,
	LUA_MENU = 2
};

enum
{
	SPECIAL_GLOB,
	SPECIAL_ENV,
	SPECIAL_REG,
};

enum
{
	TYPE_INVALID = -1,
	TYPE_NIL,
	TYPE_BOOL,
	TYPE_LIGHTUSERDATA,
	TYPE_NUMBER,
	TYPE_STRING,
	TYPE_TABLE,
	TYPE_FUNCTION,
	TYPE_USERDATA,
	TYPE_THREAD,

	TYPE_ENTITY,
	TYPE_VECTOR,
	TYPE_ANGLE,
	TYPE_PHYSOBJ,
	TYPE_SAVE,
	TYPE_RESTORE,
	TYPE_DAMAGEINFO,
	TYPE_EFFECTDATA,
	TYPE_MOVEDATA,
	TYPE_RECIPIENTFILTER,
	TYPE_USERCMD,
	TYPE_SCRIPTEDVEHICLE,

	TYPE_MATERIAL,
	TYPE_PANEL,
	TYPE_PARTICLE,
	TYPE_PARTICLEEMITTER,
	TYPE_TEXTURE,
	TYPE_USERMSG,

	TYPE_CONVAR,
	TYPE_IMESH,
	TYPE_MATRIX,
	TYPE_SOUND,
	TYPE_PIXELVISHANDLE,
	TYPE_DLIGHT,
	TYPE_VIDEO,
	TYPE_FILE,

	TYPE_PLAYER = TYPE_ENTITY,
};

static char* lua_typename[] =
{
	"nil",
	"bool",
	"lightuserdata",
	"number",
	"string",
	"table",
	"function",
	"userdata",
	"thread",
	"entity",
	"vector",
	"angle",
	"physobj",
	"save",
	"restore",
	"damageinfo",
	"effectdata",
	"movedata",
	"recipientfilter",
	"usercmd",
	"vehicle",
	"material",
	"panel",
	"particle",
	"particleemitter",
	"texture",
	"usermsg",
	"convar",
	"mesh",
	"matrix",
	"sound",
	"pixelvishandle",
	"dlight",
	"video",
	"file"
};

typedef int (*CLuaFunction)(lua_State* state);

class g_LuaGameCallback
{
public:
	virtual ~g_LuaGameCallback()
	{
	}

private:
	virtual void* CreateLuaObject(void) = 0;
	virtual void DestroyLuaObject(void*) = 0;
	virtual void ErrorPrint(char const*, bool) = 0;
	virtual void Msg(char const*, bool) = 0;
	virtual void MsgColour(char const*, Color const&) = 0;
	virtual void LuaError(void*) = 0;
	virtual void InterfaceCreated(g_LuaInterface*) = 0;
};

class g_LuaObject
{
public:
	virtual ~g_LuaObject()
	{
	}

	virtual void Set(g_LuaObject* obj) = 0;
	virtual void SetFromStack(int i) = 0;
	virtual void UnReference() = 0;
	virtual int GetType(void) = 0;
	virtual const char* GetString(void) = 0;
	virtual float GetFloat(void) = 0;
	virtual int GetInt(void) = 0;
	virtual UserData* GetUserData(void) = 0;
	virtual void SetMember(const char* name) = 0;
	virtual void SetMember(const char* name, g_LuaObject* obj) = 0;
	virtual void SetMember(const char* name, float val) = 0;
	virtual void SetMember(const char* name, bool val) = 0;
	virtual void SetMember(const char* name, const char* val) = 0;
	virtual void SetMember(const char* name, CLuaFunction f) = 0;
	virtual bool GetMemberBool(const char* name, bool b = true) = 0;
	virtual int GetMemberInt(const char* name, int i = 0) = 0;
	virtual float GetMemberFloat(const char* name, float f = 0.0f) = 0;
	virtual const char* GetMemberStr(const char* name, const char* = "") = 0;
	virtual void* GetMemberUserData(const char* name, void* = nullptr) = 0;
	virtual void* GetMemberUserData(float name, void* = nullptr) = 0;
	virtual g_LuaObject* GetMember(const char* name) = 0;
	virtual g_LuaObject* GetMember(g_LuaObject*) = 0;
	virtual void SetMetaTable(g_LuaObject* obj) = 0;
	virtual void SetUserData(void* obj) = 0;
	virtual void Push(void) = 0;
	virtual bool isNil() = 0;
	virtual bool isTable() = 0;
	virtual bool isString() = 0;
	virtual bool isNumber() = 0;
	virtual bool isFunction() = 0;
	virtual bool isUserData() = 0;
	virtual g_LuaObject* GetMember(float fKey) = 0;
	virtual void* pad0(const char* name, void* = nullptr) = 0;
	virtual void SetMember(float fKey) = 0;
	virtual void SetMember(float fKey, g_LuaObject* obj) = 0;
	virtual void SetMember(float fKey, float val) = 0;
	virtual void SetMember(float fKey, bool val) = 0;
	virtual void SetMember(float fKey, const char* val) = 0;
	virtual void SetMember(float fKey, CLuaFunction f) = 0;
	virtual const char* GetMemberStr(float name, const char* = "") = 0;
	virtual void SetMember(g_LuaObject* k, g_LuaObject* v) = 0;
	virtual bool GetBool(void) = 0;
	virtual bool PushMemberFast(int iStackPos) = 0;
	virtual void SetMemberFast(int iKey, int iValue) = 0;
	virtual void SetFloat(float val) = 0;
	virtual void SetString(const char* val) = 0;
	virtual double GetDouble(void) = 0;
	virtual void SetMember_FixKey(char const*, float) = 0;
	virtual void SetMember_FixKey(char const*, char const*) = 0;
	virtual void SetMember_FixKey(char const*, g_LuaObject*) = 0;
	virtual bool isBool(void) = 0;
	virtual void SetMemberDouble(char const*, double) = 0;
	virtual void SetMemberNil(char const*) = 0;
	virtual void SetMemberNil(float) = 0;
	virtual bool Debug_IsUnreferenced() = 0;
	virtual void Init(void) = 0;
	virtual void SetFromGlobal(char const*) = 0;
	virtual void SetMember(char const*, unsigned long long) = 0;
	virtual void SetReference(int i) = 0;
	virtual void RemoveMember(char const*) = 0;
	virtual void RemoveMember(float) = 0;
	virtual bool MemberIsNil(char const*) = 0;
	virtual void SetMemberDouble(float, double) = 0;
	virtual double GetMemberDouble(char const*, double) = 0;
};

class g_CLuaObject : public g_LuaObject
{
public:
	int lua_address;
	int pad0;
	int pad1;
	g_LuaInterface* lua_interface;
};

namespace Bootil
{
	struct Buffer
	{
		unsigned char u[0x1000];
	};
};

class g_LuaInterface
{
public:
	virtual ~g_LuaInterface()
	{
	}

	virtual int Top(void) = 0; //0000
	virtual void Push(int iStackPos) = 0; //0004
	virtual void Pop(int iAmt = 1) = 0; //0008
	virtual void GetTable(int iStackPos) = 0; //000C
	virtual void GetField(int iStackPos, const char* strName) = 0; //0010
	virtual void SetField(int iStackPos, const char* strName) = 0; //0014
	virtual void CreateTable() = 0; //0018
	virtual void SetTable(int i) = 0; //001C
	virtual void SetMetaTable(int i) = 0; //0020
	virtual bool GetMetaTable(int i) = 0; //0024
	virtual void Call(int iArgs, int iResults) = 0;
	virtual int PCall(int iArgs, int iResults, int iErrorFunc) = 0;
	virtual int Equal(int iA, int iB) = 0;
	virtual int RawEqual(int iA, int iB) = 0;
	virtual void Insert(int iStackPos) = 0;
	virtual void Remove(int iStackPos) = 0;
	virtual int Next(int iStackPos) = 0;
	virtual void* NewUserdata(unsigned int iSize) = 0;
	virtual void ThrowError(const char* strError) = 0;
	virtual void CheckType(int iStackPos, int iType) = 0;
	virtual void ArgError(int iArgNum, const char* strMessage) = 0;
	virtual void RawGet(int iStackPos) = 0;
	virtual void RawSet(int iStackPos) = 0;
	virtual const char* GetString(int iStackPos = -1, unsigned int* iOutLen = nullptr) = 0;
	virtual double GetNumber(int iStackPos = -1) = 0;
	virtual bool GetBool(int iStackPos = -1) = 0;
	virtual CLuaFunction GetCFunction(int iStackPos = -1) = 0;
	virtual UserData* GetUserdata(int iStackPos = -1) = 0;
	virtual void PushNil() = 0;
	virtual void PushString(const char* val, unsigned int iLen = 0) = 0;
	virtual void PushNumber(double val) = 0;
	virtual void PushBool(bool val) = 0;
	virtual void PushCFunction(CLuaFunction val) = 0;
	virtual void PushCClosure(CLuaFunction val, int iVars) = 0;
	virtual void PushUserdata(void*) = 0;
	virtual int ReferenceCreate() = 0;
	virtual void ReferenceFree(int i) = 0;
	virtual void ReferencePush(int i) = 0;
	virtual void PushSpecial(int iType) = 0;
	virtual bool IsType(int iStackPos, int iType) = 0;
	virtual int GetType(int iStackPos) = 0;
	virtual const char* GetTypeName(int iType) = 0;
	virtual void CreateMetaTableType(const char* strName, int iType) = 0;
	virtual const char* CheckString(int iStackPos = -1) = 0;
	virtual double CheckNumber(int iStackPos = -1) = 0;
	virtual size_t ObjLen(int index) = 0;
	virtual void AddThreadedCall(void* tc) = 0;
	virtual bool Init(void* pCallBack, bool bLoadJit) = 0;
	virtual void Shutdown(void) = 0;
	virtual void* Cycle(void) = 0;
	virtual lua_State* GetLuaState() = 0;
	virtual g_LuaObject* Global() = 0;
	virtual g_LuaObject* GetObject(int index) = 0;
	virtual void _nullstub1(int) = 0;
	virtual void _nullstub2(int) = 0;
	virtual void PushLuaObject(g_LuaObject* obj) = 0;
	virtual void PushLuaFunction(CLuaFunction func) = 0;
	virtual void LuaError(const char* err, int index) = 0;
	virtual void TypeError(const char* name, int index) = 0;
	virtual void CallInternal(int args, int rets) = 0;
	virtual void CallInternalNoReturns(int args) = 0;
	virtual bool CallInternalGetBool(int args) = 0;
	virtual const char* CallInternalGetString(int args) = 0;
	virtual bool CallInternalGet(int args, g_LuaObject* obj) = 0;
	virtual void _nullstub3(g_LuaObject*, void*) = 0;
	virtual void NewGlobalTable(const char* name) = 0;
	virtual g_LuaObject* NewTemporaryObject() = 0;
	virtual bool isUserData(int index) = 0;
	virtual g_LuaObject* GetMetaTableObject(const char* name, int type) = 0;
	virtual g_LuaObject* GetMetaTableObject(int index) = 0;
	virtual g_LuaObject* GetReturn(int index) = 0;
	virtual bool IsServer() = 0;
	virtual bool IsClient() = 0;
	virtual bool IsDedicatedServer() = 0;
	virtual void DestroyObject(g_LuaObject* obj) = 0;
	virtual g_LuaObject* CreateObject() = 0;
	virtual void SetMember(g_LuaObject* table, g_LuaObject* key, g_LuaObject* value) = 0;
	virtual void GetNewTable() = 0;
	virtual void SetMember(g_LuaObject* table, float key) = 0;
	virtual void SetMember(g_LuaObject* table, float key, g_LuaObject* value) = 0;
	virtual void SetMember(g_LuaObject* table, const char* key) = 0;
	virtual void SetMember(g_LuaObject* table, const char* key, g_LuaObject* value) = 0;
	virtual void SetIsServer(bool isServer) = 0;
	virtual void PushLong(long num) = 0;
	virtual int GetFlags(int index) = 0;
	virtual bool FindOnObjectsMetaTable(int objIndex, int keyIndex) = 0;
	virtual bool FindObjectOnTable(int tableIndex, int keyIndex) = 0;
	virtual void SetMemberFast(g_LuaObject* table, int keyIndex, int valueIndex) = 0;
	virtual bool RunString(const char* filename, const char* path, const char* stringToRun, bool run, bool showErrors) = 0;
	virtual bool IsEqual(g_LuaObject* objA, g_LuaObject* objB) = 0;
	virtual void Error(const char* err) = 0;
	virtual const char* GetStringOrError(int index) = 0;
	virtual bool RunLuaModule(const char* name) = 0;
	virtual bool FindAndRunScript(const char* filename, bool run, bool showErrors, const char*) = 0;
	virtual void SetPathID(const char* pathID) = 0;
	virtual const char* GetPathID() = 0;
	virtual void ErrorNoHalt(const char* fmt, ...) = 0;
	virtual void Msg(const char* fmt, ...) = 0;
	virtual void PushPath(const char* path) = 0;
	virtual void PopPath() = 0;
	virtual const char* GetPath() = 0;
	virtual int GetColor(int index) = 0;
	virtual void PushColor(int r, int g, int b, int a) = 0;
	virtual int GetStack(int level, lua_Debug* dbg) = 0;
	virtual int GetInfo(const char* what, lua_Debug* dbg) = 0;
	virtual const char* GetLocal(lua_Debug* dbg, int n) = 0;
	virtual const char* GetUpvalue(int funcIndex, int n) = 0;
	virtual void RunStringEx(const char* filename, const char* path, const char* stringToRun, bool run, bool showErrors, bool) = 0;
	virtual void _nullstub4(const char*, int) = 0;
	virtual size_t GetDataString(int index, const char** str) = 0;
	virtual void ErrorFromLua(const char* fmt, ...) = 0;
	virtual void GetCurrentLocation() = 0;
	virtual void MsgColour(const Color& col, const char* fmt, ...) = 0;
	virtual void SetState(lua_State* state) = 0;
	virtual void _nullstub5(void) = 0;
	virtual void GetCurrentFile(std::string& outStr) = 0;
	virtual void CompileString(Bootil::Buffer& dumper, const std::string& stringToCompile) = 0;
	virtual void ThreadLock() = 0;
	virtual void ThreadUnlock() = 0;
	virtual bool CallFunctionProtected(int, int, bool) = 0;
	virtual void Require(const char* name) = 0;
	virtual const char* GetActualTypeName(int type) = 0;
	virtual void SetupInfiniteLoopProtection(void) = 0;
	virtual void PreCreateTable(int, int) = 0;
	virtual void PushPooledString(int) = 0;
	virtual void GetPooledString(int) = 0;
};

class g_LuaBase
{
public:
	virtual ~g_LuaBase()
	{
	}

	virtual int			Top(void) = 0;
	virtual void		Push(int iStackPos) = 0;
	virtual void		Pop(int iAmt = 1) = 0;
	virtual void		GetTable(int iStackPos) = 0;
	virtual void		GetField(int iStackPos, const char* strName) = 0;
	virtual void		SetField(int iStackPos, const char* strName) = 0;
	virtual void		CreateTable() = 0;
	virtual void		SetTable(int i) = 0;
	virtual void		SetMetaTable(int i) = 0;
	virtual bool		GetMetaTable(int i) = 0;
	virtual void		Call(int iArgs, int iResults) = 0;
	virtual int			PCall(int iArgs, int iResults, int iErrorFunc) = 0;
	virtual int			Equal(int iA, int iB) = 0;
	virtual int			RawEqual(int iA, int iB) = 0;
	virtual void		Insert(int iStackPos) = 0;
	virtual void		Remove(int iStackPos) = 0;
	virtual int			Next(int iStackPos) = 0;
	virtual UserData*		NewUserdata(unsigned int iSize) = 0;
	virtual void		ThrowError(const char* strError) = 0;
	virtual void		CheckType(int iStackPos, int iType) = 0;
	virtual void		ArgError(int iArgNum, const char* strMessage) = 0;
	virtual void		RawGet(int iStackPos) = 0;
	virtual void		RawSet(int iStackPos) = 0;

	virtual const char*		GetString(int iStackPos = -1, unsigned int* iOutLen = nullptr) = 0;
	virtual double			GetNumber(int iStackPos = -1) = 0;
	virtual bool			GetBool(int iStackPos = -1) = 0;
	virtual CLuaFunction			GetCFunction(int iStackPos = -1) = 0;
	virtual UserData*			GetUserdata(int iStackPos = -1) = 0;

	virtual void		PushNil() = 0;
	virtual void		PushString(const char* val, unsigned int iLen = 0) = 0;
	virtual void		PushNumber(double val) = 0;
	virtual void		PushBool(bool val) = 0;
	virtual void		PushCFunction(CLuaFunction val) = 0;
	virtual void		PushCClosure(CLuaFunction val, int iVars) = 0;
	virtual void		PushUserdata(void*) = 0;

	//
	// If you create a reference - don't forget to free it!
	//
	virtual int			ReferenceCreate() = 0;
	virtual void		ReferenceFree(int i) = 0;
	virtual void		ReferencePush(int i) = 0;

	//
	// Push a special value onto the top of the stack ( see below )
	//
	virtual void		PushSpecial(int iType) = 0;

	//
	// For type enums see Types.h 
	//
	virtual bool			IsType(int iStackPos, int iType) = 0;
	virtual int				GetType(int iStackPos) = 0;
	virtual const char*		GetTypeName(int iType) = 0;

	//
	// Creates a new meta table of string and type and leaves it on the stack.
	// Will return the old meta table of this name if it already exists.
	//
	virtual void			CreateMetaTableType(const char* strName, int iType) = 0;

	//
	// Like Get* but throws errors and returns if they're not of the expected type
	//
	virtual const char*		CheckString(int iStackPos = -1) = 0;
	virtual double			CheckNumber(int iStackPos = -1) = 0;

};

class g_LuaShared
{
public:
	virtual ~g_LuaShared()
	{
	}

	virtual void Init(void* (*)(char const*, int*), bool, void*, void*) = 0; // 0
	virtual void Shutdown(void) = 0; // 1
	virtual void DumpStats(void) = 0; // 2
	virtual void CreateLuaInterface(unsigned char, bool) = 0; // 3
	virtual void CloseLuaInterface(g_LuaInterface*) = 0;
	virtual g_LuaInterface* GetLuaInterface(unsigned char) = 0;
	virtual void LoadFile(std::string const&, std::string const&, bool, bool) = 0;
	virtual void GetCache(std::string const&) = 0;
	virtual void MountLua(char const*) = 0;
	virtual void MountLuaAdd(char const*, char const*) = 0;
	virtual void UnMountLua(char const*) = 0;
	virtual void SetFileContents(char const*, char const*) = 0;
	virtual void SetLuaFindHook(void*) = 0;
	virtual void FindScripts(std::string const&, std::string const&, void*) = 0;
};

class g_lua
{
	g_LuaShared* lua_shared;

	void(*lua_replace)(void *L, int index);
	int(*luaL_loadbufferx)(void *L, const char *buf, size_t len, const char *name, void*nig);
	int(*lua_pcall)(void *L, int a, int b, int c);
	void(*lua_settop)(void *L, int a);
	int(*lua_gettop)(void *L);
	void(*lua_remove)(void *L, int a);
	void(*lua_xmove)(void *from, void* to, int n);
	const char* (*lua_tolstring)(void *L, int a, int len);
	int(*lua_type)(void*L, int index);
	void* (*luaL_newstate)();

public:
	bool InitLuaShared(g_LuaShared* lua_shared);
	g_LuaInterface* GetMenuState() const;
	g_LuaInterface* GetClientState() const;
	static g_LuaInterface* RetLuaState(g_LuaInterface* garrystate); // honestly no idea what this is, pasting from ley
	std::string RunCode(g_LuaInterface* state, std::string code, const char* name) const;
};
