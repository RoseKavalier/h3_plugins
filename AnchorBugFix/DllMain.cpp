/*
* Big thanks to kazmer for his help in understanding obstacles placement
* And for his wonderful Battlefield Explorer for HoMM3 (highly recommended)
* https://github.com/jtakacs/homm3_battlefields
*
* Summary: when placing Obstacles on the Battlefield, the game sets an "Anchor"
* From where relative cells corresponding to this obstacle's shape are blocked.
* However, the Anchor tile also receive a block flag.
* This flag is required to correctly draw the obstacle on battlefield during combat.
* The bug fixed by this plugin arises when the Anchor tile is not part of the obstacle's shape:
* This flag is not normally visible, unless you try to cast Fire Wall, Force Field, Land Mine or Quicksand.
* In these four cases, you will be unable to place anything on the Anchor tile...
* Even though this hex is technically free - you can still move creatures there.
* With this plugin, the Anchor is always part of the obstacle and the DEF is correctly placed.
*/

/*
* WARNING!! The testing phase has been very limited at this time. Use at your own risk.
*/

#include "..\includes\homm3.h"
#include "H3_obstacles.h"

Patcher* _P;
PatcherInstance* _PI;

#define o_DefObstacleInfo (*(_DefObstacleInfo_**)0x465C21) // 0x63C7C8 in SoD

inline int _BattleMgr_::CountNormalObstacles(void)
{
	return ((int)this->ObstacleInfo.endUsed - (int)this->ObstacleInfo.start) / sizeof(_ObstacleInfo_);
}

inline _ObstacleInfo_* _BattleMgr_::GetObstacleInfo(int num)
{
	return &((_ObstacleInfo_*)this->ObstacleInfo.start)[num];
}

void __stdcall FixObstacleAnchorBug(HiHook *h, _BattleMgr_ *combat)
{
	CALL_1(void, __thiscall, h->GetDefaultFunc(), combat);

	int obstacle_count = combat->CountNormalObstacles();
	int obstacle_base = (int)o_DefObstacleInfo;
	for (int i = 0; i < obstacle_count; i++)
	{
		_ObstacleInfo_ *obstacle = combat->GetObstacleInfo(i);
		int obstacle_id = ((int)obstacle->data - obstacle_base) / sizeof(_DefObstacleInfo_);
		BYTE anchor_hex = obstacle->AnchorHex;
		int row_parity; // is the row odd or even?
		switch (obstacle_id)
		{
		case LocalObstacles::obbdt01: // offset at 1 exists
		case LocalObstacles::obdts04:
		case LocalObstacles::obdts15:
		case LocalObstacles::obdsm02:
		case LocalObstacles::obdss17:
		case LocalObstacles::obgrs01:
		case LocalObstacles::obgrs02:
		case LocalObstacles::obsns02:
		case LocalObstacles::obsns05:
		case LocalObstacles::obsns06:
		case LocalObstacles::obrgs03:
		case LocalObstacles::obbhs02:
		case LocalObstacles::obbhs11a:
		case LocalObstacles::obbhs12b:
		case LocalObstacles::obhgs02:
		case LocalObstacles::obefs03:
		case LocalObstacles::obefs04:
		case LocalObstacles::obcfs02:
		case LocalObstacles::oblps03:
		case LocalObstacles::obffs03:
		case LocalObstacles::obrls03:
		case LocalObstacles::obmcs01:
			combat->hex[anchor_hex].Flags &= ~1; // remove anchor flag
			combat->hex[anchor_hex + 1].Flags |= 1; // add anchor flag
			break;
		case LocalObstacles::obdts14: // offset at 2 exists
		case LocalObstacles::obsns09:
			combat->hex[anchor_hex].Flags &= ~1; // remove anchor flag
			combat->hex[anchor_hex + 2].Flags |= 1; // add anchor flag
			break;
		case LocalObstacles::obsns10: // 3;-13;-14;-15;-33;-49;-66
			combat->hex[anchor_hex].Flags &= ~1; // remove anchor flag
			combat->hex[anchor_hex + 3].Flags |= 1; // add anchor flag
			break;
		case LocalObstacles::obsws02: // -10;-11;-12;-13;-14;-15;-16
			row_parity = ((anchor_hex / 17) % 2); // if anchor's row is odd, we need to shift negative offsets by 1 to the left
			combat->hex[anchor_hex].Flags &= ~1; // remove anchor flag
			combat->hex[anchor_hex - 10 - row_parity].Flags |= 1; // add anchor flag
			break;
		case LocalObstacles::obsws11b: // -13;-14;-15;-16;-30;-31;-32;-33
		case LocalObstacles::oblvs03: // -13;-14;-15;-30;-31;-32;-33
		case LocalObstacles::oblvs17: // -13;-14;-15;-16;-30;-31
		case LocalObstacles::oblvs22: // -13;-14;-15;-16;-31;-32;-33
			row_parity = ((anchor_hex / 17) % 2); // if anchor's row is odd, we need to shift negative offsets by 1 to the left
			combat->hex[anchor_hex].Flags &= ~1; // remove anchor flag
			combat->hex[anchor_hex - 13 - row_parity].Flags |= 1; // add anchor flag
			break;
		case LocalObstacles::obrgs02: // -14;-15;-16;-32;-33
		case LocalObstacles::oblvs01: // -14;-32;-33
		case LocalObstacles::oblvs09: // -14;-15;-32;-33;-49;-50
			row_parity = ((anchor_hex / 17) % 2); // if anchor's row is odd, we need to shift negative offsets by 1 to the left
			combat->hex[anchor_hex].Flags &= ~1; // remove anchor flag
			combat->hex[anchor_hex - 14 - row_parity].Flags |= 1; // add anchor flag
			break;
		case LocalObstacles::obdrk01: // -15, -16
		case LocalObstacles::obdsm01: // -15;-16;-32;-33;-48;-49
		case LocalObstacles::obrgs05: // -15;-16;-32
		case LocalObstacles::obbts04: // -15;-16;-33
			row_parity = ((anchor_hex / 17) % 2); // if anchor's row is odd, we need to shift negative offsets by 1 to the left
			combat->hex[anchor_hex].Flags &= ~1; // remove anchor flag
			combat->hex[anchor_hex - 15 - row_parity].Flags |= 1; // add anchor flag
			break;
		case LocalObstacles::obsws13a: // -16;-17;-31;-32;-33;-34
		case LocalObstacles::obdrk03: // -16
		case LocalObstacles::obrgs04: // -16;-32;-33
			row_parity = ((anchor_hex / 17) % 2); // if anchor's row is odd, we need to shift negative offsets by 1 to the left
			combat->hex[anchor_hex].Flags &= ~1; // remove anchor flag
			combat->hex[anchor_hex - 16 - row_parity].Flags |= 1; // add anchor flag
			break;
		default:
			break;
		}
	}
}

#define BATTLEHEX_WIDTH 44

int __stdcall RepositionAnchorDef(LoHook *h, HookContext *c)
{
	_BattleHex_ *hex = (_BattleHex_*)(c->edi - 0x14);
	_BattleMgr_ *combat = (_BattleMgr_*)c->esi;
	if (hex->Flags == 3) // anchor & local obstacle
	{
		int obstacle_number = hex->ObstacleNum;
		_ObstacleInfo_ *obstacle = combat->GetObstacleInfo(obstacle_number);
		int obstacle_id = ((int)obstacle->data - (int)o_DefObstacleInfo) / sizeof(_DefObstacleInfo_);
		switch (obstacle_id)
		{
		case LocalObstacles::obbdt01: // offset at 1 exists
		case LocalObstacles::obdts04:
		case LocalObstacles::obdts15:
		case LocalObstacles::obdsm02:
		case LocalObstacles::obdss17:
		case LocalObstacles::obgrs01:
		case LocalObstacles::obgrs02:
		case LocalObstacles::obsns02:
		case LocalObstacles::obsns05:
		case LocalObstacles::obsns06:
		case LocalObstacles::obrgs03:
		case LocalObstacles::obbhs02:
		case LocalObstacles::obbhs11a:
		case LocalObstacles::obbhs12b:
		case LocalObstacles::obhgs02:
		case LocalObstacles::obefs03:
		case LocalObstacles::obefs04:
		case LocalObstacles::obcfs02:
		case LocalObstacles::oblps03:
		case LocalObstacles::obffs03:
		case LocalObstacles::obrls03:
		case LocalObstacles::obmcs01:
			c->eax -= BATTLEHEX_WIDTH; // move X left
			break;
		case LocalObstacles::obdts14: // 2, -15, -16
		case LocalObstacles::obsns09: // 2;3;4;5;-13;-14;-15;-16
			c->eax -= 2 * BATTLEHEX_WIDTH;
			break;
		case LocalObstacles::obsns10: // 3;-13;-14;-15;-33;-49;-66
			c->eax -= 3 * BATTLEHEX_WIDTH;
			break;
		case LocalObstacles::obsws02: // -10;-11;-12;-13;-14;-15;-16
			c->eax -= (int)(6.5 * BATTLEHEX_WIDTH); // move by 6.5 hex left  (-16 - -10 - 0.5)
			c->edx += BATTLEHEX_WIDTH; // lower row by 1
			break;
		case LocalObstacles::obsws11b: // -13;-14;-15;-16;-30;-31;-32;-33
		case LocalObstacles::oblvs03: // -13;-14;-15;-30;-31;-32;-33
		case LocalObstacles::oblvs17: // -13;-14;-15;-16;-30;-31
		case LocalObstacles::oblvs22: // -13;-14;-15;-16;-31;-32;-33
			c->eax -= (int)(3.5 * BATTLEHEX_WIDTH); // move by 3.5 hex left (-16 - -13 - 0.5)
			c->edx += BATTLEHEX_WIDTH; // lower row by 1
			break;
		case LocalObstacles::obrgs02: // -14;-15;-16;-32;-33
		case LocalObstacles::oblvs01: // -14;-32;-33
		case LocalObstacles::oblvs09: // -14;-15;-32;-33;-49;-50
			c->eax -= (int)(2.5 * BATTLEHEX_WIDTH); // move by 2.5 hex left (-16 - -14 - 0.5)
			c->edx += BATTLEHEX_WIDTH; // lower row by 1
			break;
		case LocalObstacles::obdrk01: // -15, -16
		case LocalObstacles::obdsm01: // -15;-16;-32;-33;-48;-49
		case LocalObstacles::obrgs05: // -15;-16;-32
		case LocalObstacles::obbts04: // -15;-16;-33
			c->eax -= (int)(1.5 * BATTLEHEX_WIDTH); // move by 1.5 hex left (-16 - -15 - 0.5)
			c->edx += BATTLEHEX_WIDTH; // lower row by 1
			break;
		case LocalObstacles::obsws13a: // -16;-17;-31;-32;-33;-34
		case LocalObstacles::obdrk03: // -16
		case LocalObstacles::obrgs04: // -16;-32;-33
			c->eax -= (int)(0.5 * BATTLEHEX_WIDTH); // move by 0.5 hex left (-16 - -16 - 0.5)
			c->edx += BATTLEHEX_WIDTH; // lower row by 1
			break;
		default:
			break;
		}
	}

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
			_PI = _P->CreateInstance("AnchorBugFix");
			_PI->WriteHiHook(0x465E70, SPLICE_, EXTENDED_, THISCALL_, FixObstacleAnchorBug);
			_PI->WriteLoHook(0x4941FE, RepositionAnchorDef);
		}
		break;

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}