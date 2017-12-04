// note I used Linker, this is a multi-solution Project
#include "homm3.h"

Patcher* _P;
PatcherInstance* _PI;

int __stdcall castle_owner_check(LoHook *h, HookContext *c)
{
	_Town_ *town = (_Town_*)(c->ecx);
	_Hero_ *hero = *(_Hero_**)(c->ebp - 4); // _Hero_ is stored in temp variable [LOCAL.1]

	if (hero->owner_id == town->owner_id) // normal
		return EXEC_DEFAULT;
	
	c->return_address = 0x4E4D6C; // skip procedure
	return NO_EXEC_DEFAULT;
}


BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	static _bool_ plugin_On = 0;
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		if (!plugin_On)
		{
			plugin_On = 1;
			_P = GetPatcher();
			_PI = _P->CreateInstance("HD.Castle.Lighthouse");
			_PI->WriteLoHook(0x4E4D40, castle_owner_check);
		}
		break;

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}