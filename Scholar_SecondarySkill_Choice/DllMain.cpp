#include "..\includes\homm3.h"

Patcher *_P;
PatcherInstance *_PI;

#define o_ADVEVENT_TXT (*(_TXT_**)0x696A68)
#define Show_SSKill_MSG_YES_NO(frame) \
	CALL_12(void, __fastcall, 0x4F6C00, o_ADVEVENT_TXT->GetString(115), MBX_OKCANCEL, -1, -1, 0x14, frame, -1, 0, -1, 0, -1, 0);

int __stdcall wandering_scholar_sskill_choice(LoHook *h, HookContext *c)
{
	int skill_id = c->eax; // grab skill to learn
	_Hero_ *hero = (_Hero_*)c->ebx; // grab current hero structure
	int skill_level = hero->second_skill[skill_id]; // current skill level
	if (*(BYTE*)(c->ebp + 0x14) == 0) // || o_IsMultiPlayerGame // disable for AI
		return EXEC_DEFAULT;

	////////////////
	// 28.09.2018
	// Small correction here
	// The code used to say if skill count is 8 OR skill level is 3 then you get a primary skill.
	// HOWEVER
	// If you had an Advanced skill and 8 skill count already, it would still give you a primary skill
	// SO
	// Now the first check is if that secondary skill is already level 3 (max)
	// If this check fails, it will then see if you have learned 8 secondary skills already
	////////////////
	if (skill_level == 3 && hero->second_skill_count == 8) // if hero can not learn skill
	{
		c->return_address = 0x4A4B3F; // change return address to learn primary skill
		return NO_EXEC_DEFAULT; // do not execute original code that was overwritten
	}

	Show_SSKill_MSG_YES_NO(skill_id * 3 + skill_level + 2 + 1); // is the ID of the frame to use from .DEF file.
	// The extra + 1 is because the skill is not yet increased!
	// equivalent to ... MOVSX ECX,BYTE PTR DS:[EBX+EDI+0C9] ... LEA EDX, [EDI*2 + EDI] ... LEA EAX, [EDX+ECX+2]

	if (o_WndMgr->result_dlg_item_id == DIID_OK) // did user click ok?
		hero->LearnSecondarySkill(skill_id, 1); // then leanr the skill

	c->return_address = 0x4A4B86; // go to exit procedure
	return NO_EXEC_DEFAULT; // do not execute original code that was overwritten
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
			_PI = _P->CreateInstance("Scholar_SecondarySkill_Choice");

			_PI->WriteLoHook(0x4A4AE4, wandering_scholar_sskill_choice);
		}
		break;

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}