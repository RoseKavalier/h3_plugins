#include "includes/homm3.h"

Patcher *_P;
PatcherInstance *_PI;

int __stdcall VisitBankBug(LoHook *h, HookContext *c)
{
	_MapItem_ *mip = (_MapItem_ *)c->eax;
	if (mip->object_type == H3M_OA_CLASS_HERO) // hero is being shown
		CALL_4(void, __thiscall, 0x417540, o_AdvMgr, 0, 0, 0); // Mobilize active hero
	return EXEC_DEFAULT;
}

void __stdcall _HH_Show_Hero_Info_Dlg(HiHook *h, int this_hero_id, int a1, int a2)
{
	CALL_3(void, __thiscall, h->GetDefaultFunc(), this_hero_id, a1, a2);
	CALL_4(void, __thiscall, 0x417540, o_AdvMgr, 0, 0, 0); // Mobilize active hero
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
			_PI = _P->CreateInstance("CreatureBankBug");
			_PI->WriteLoHook(0x4AC157, VisitBankBug); // alternative 1 - only for creature banks
			_PI->WriteHiHook(0x5D52CA, CALL_, EXTENDED_, THISCALL_, _HH_Show_Hero_Info_Dlg); // alternative 2 - should solve most everything
		}
		break;

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}