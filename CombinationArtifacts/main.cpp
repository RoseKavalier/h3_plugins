#include "homm3.h"

Patcher* _P;
PatcherInstance* _PI;

int __stdcall new_artifact_combinations(LoHook *h, HookContext *c)
{
	// AotD no longer requires Shield of the Yawning Dead
	ChangeArtifactCombination(H3M_ARTIFACT_ARMOR_OF_THE_DAMNED, 3, H3M_ARTIFACT_BLACKSHARD_OF_THE_DEAD_KNIGHT, H3M_ARTIFACT_SKULL_HELMET, H3M_ARTIFACT_RIB_CAGE);
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
			_PI = _P->CreateInstance("CombinationArtifacts");
			_PI->WriteLoHook(0x4EEA79, new_artifact_combinations); // right after big HotA DLL modifications
		}
		break;

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}