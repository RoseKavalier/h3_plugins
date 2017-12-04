#ifndef ARTIFACT_COMBINATIONS_H
#define ARTIFACT_COMBINATIONS_H

#include <stdarg.h>

#ifndef HOTA_EXE
#define HOTA_EXE (*(int*)0x41C6B5 != 0x21620)
#endif

typedef unsigned int uint;

#pragma pack(push, 1)
struct _ArtifactCombination_
{
	uint artifact_id;
	uint requirements[5];

	inline void ChangeCombo(int combo_id, int n_arts, va_list args) {
		int combo = combo_id - 0x81;
		for (int i = 0; i < 5; i++)
			this[combo].requirements[i] = 0;
		for (int i = 0; i < n_arts; i++) {
			uint art_id = va_arg(args, uint);
			uint n = art_id / 32;
			uint v = 1 << (art_id % 32);
			this[combo].requirements[n] += v;
		}
	}
};

struct _ArtifactCombinationHotA_
{
	uint artifact_id;
	uint requirements[6];

	inline void ChangeCombo(int combo_id, int n_arts, va_list args) {
		int combo = combo_id - 0x81;
		for (int i = 0; i < 6; i++)
			this[combo].requirements[i] = 0;
		for (int i = 0; i < n_arts; i++) {
			uint art_id = va_arg(args, uint);
			uint n = art_id / 32;
			uint v = 1 << (art_id % 32);
			this[combo].requirements[n] += v;
		}
	}
};
#pragma pack(pop)

#define o_ArtCombinations (*(_ArtifactCombination_**)0x44C66B)
#define o_ArtCombinationsHotA (*(_ArtifactCombinationHotA_**)0x44C66B)

void ChangeArtifactCombination(int combo_id, int art_count, ...)
{
	if (combo_id < 0x81)
		return;
	va_list args;
	va_start(args, art_count);
	if (HOTA_EXE)
		o_ArtCombinationsHotA->ChangeCombo(combo_id, art_count, args);
	else
		o_ArtCombinations->ChangeCombo(combo_id, art_count, args);
	va_end(args);
}

#endif