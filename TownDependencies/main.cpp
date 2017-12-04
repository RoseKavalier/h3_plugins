#include "homm3.h"

Patcher* _P;
PatcherInstance* _PI;

int __stdcall new_town_dependencies(LoHook *h, HookContext *c)
{
	// Naga Building
	o_TownDependencies->ChangeDependency(TOWN_ID_TOWER, BLD_ID_DWELL6, BLD_REQ_MAGE1 | BLD_REQ_FORT | BLD_REQ_DWELL1 | BLD_REQ_DWELL2 | BLD_REQ_DWELL3 | BLD_REQ_DWELL4);
	return EXEC_DEFAULT;
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
			_PI = _P->CreateInstance("TownDependencies");
			_PI->WriteLoHook(0x4EEA79, new_town_dependencies); // right after big HotA DLL modifications
		}
		break;

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}