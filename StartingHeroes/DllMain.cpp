#include "..\includes\homm3.h"

Patcher *_P;
PatcherInstance *_PI;

int heroStartList[20]; // Castle town has 19 possible heroes, plus the random -1 value.

struct _StartingHeroesList_
{
	_byte_ f_0[0x20];
	int currentHeroPosition; // 0x20
	_byte_ f_24[4];
	int heroCount; // 0x28
	int heroesList[16]; // 0x2C~...
};

int __stdcall FillNewHeroList(LoHook *h, HookContext *c)
{
	_StartingHeroesList_ *heroes = (_StartingHeroesList_*)c->eax;
	heroStartList[heroes->heroCount] = c->edx; // store the hero id to our list
	return NO_EXEC_DEFAULT;
}

int __stdcall ReadFromNewHeroListPortrait(LoHook *h, HookContext *c)
{
	int heroPosition = c->eax;
	c->edx = heroStartList[heroPosition];
	IntAt(c->ebp + 8) = c->edx; // overwritten instruction
	return NO_EXEC_DEFAULT;
}
int __stdcall ReadFromNewHeroListName(LoHook *h, HookContext *c)
{
	int heroPosition = c->ecx;
	int heroId = heroStartList[heroPosition];
	if (heroId != -1)
		c->eax = heroId;
	return EXEC_DEFAULT;
}
int __stdcall ReadFromNewHeroListGenerate(LoHook *h, HookContext *c)
{
	int heroPosition = IntAt(c->eax - 0x50);
	c->ecx = heroStartList[heroPosition];
	return EXEC_DEFAULT;
}
int __stdcall ReadFromNewHeroListRightClick(LoHook *h, HookContext *c)
{
	int heroPosition = c->ecx;
	int heroId = heroStartList[heroPosition];
	c->edi = heroId;
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
			_PI = _P->CreateInstance("HD.StartingHeroes");

			memset(heroStartList, -1, sizeof(heroStartList));

			_PI->WriteByte(0x583DA5 + 2, 19); // extend available hero list to 19 heroes instead of 16
			_PI->WriteLoHook(0x583D95, FillNewHeroList); // custom hero list is filled instead of original one
			_PI->WriteLoHook(0x58D454, ReadFromNewHeroListPortrait);	// set new portrait correctly
			_PI->WriteLoHook(0x58D5DE, ReadFromNewHeroListName);		// set new name correctly
																		// hook would be earlier but not possible without large overwrite
			_PI->WriteLoHook(0x58C97A, ReadFromNewHeroListGenerate);	// select the hero from the new list when generating map
			_PI->WriteLoHook(0x582853, ReadFromNewHeroListRightClick);	// gives correct hero id when right-clicking to get starting information
		}
		break;

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}