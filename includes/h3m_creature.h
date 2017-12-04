// Created by John �kerblom 2014-01-27
// Values taken from h3m.txt (google h3m.txt)

#ifndef __H3M_CREATURE_H_DEF__
#define __H3M_CREATURE_H_DEF__

enum H3M_CREATURE {
/* 0 */ H3M_CREATURE_PIKEMAN,
/* 1 */ H3M_CREATURE_HALBERDIER,
/* 2 */ H3M_CREATURE_ARCHER,
/* 3 */ H3M_CREATURE_MARKSMAN,
/* 4 */ H3M_CREATURE_GRIFFIN,
/* 5 */ H3M_CREATURE_ROYAL_GRIFFIN,
/* 6 */ H3M_CREATURE_SWORDSMAN,
/* 7 */ H3M_CREATURE_CRUSADER,
/* 8 */ H3M_CREATURE_MONK,
/* 9 */ H3M_CREATURE_ZEALOT,
/* 10 */ H3M_CREATURE_CAVALIER,
/* 11 */ H3M_CREATURE_CHAMPION,
/* 12 */ H3M_CREATURE_ANGEL,
/* 13 */ H3M_CREATURE_ARCHANGEL,
/* 14 */ H3M_CREATURE_CENTAUR,
/* 15 */ H3M_CREATURE_CENTAUR_CAPTAIN,
/* 16 */ H3M_CREATURE_DWARF,
/* 17 */ H3M_CREATURE_BATTLE_DWARF,
/* 18 */ H3M_CREATURE_WOOD_ELF,
/* 19 */ H3M_CREATURE_GRAND_ELF,
/* 20 */ H3M_CREATURE_PEGASUS,
/* 21 */ H3M_CREATURE_SILVER_PEGASUS,
/* 22 */ H3M_CREATURE_DENDROID_GUARD,
/* 23 */ H3M_CREATURE_DENDROID_SOLDIER,
/* 24 */ H3M_CREATURE_UNICORN,
/* 25 */ H3M_CREATURE_WAR_UNICORN,
/* 26 */ H3M_CREATURE_GREEN_DRAGON,
/* 27 */ H3M_CREATURE_GOLD_DRAGON,
/* 28 */ H3M_CREATURE_GREMLIN,
/* 29 */ H3M_CREATURE_MASTER_GREMLIN,
/* 30 */ H3M_CREATURE_STONE_GARGOYLE,
/* 31 */ H3M_CREATURE_OBSIDIAN_GARGOYLE,
/* 32 */ H3M_CREATURE_STONE_GOLEM,
/* 33 */ H3M_CREATURE_IRON_GOLEM,
/* 34 */ H3M_CREATURE_MAGE,
/* 35 */ H3M_CREATURE_ARCH_MAGE,
/* 36 */ H3M_CREATURE_GENIE,
/* 37 */ H3M_CREATURE_MASTER_GENIE,
/* 38 */ H3M_CREATURE_NAGA,
/* 39 */ H3M_CREATURE_NAGA_QUEEN,
/* 40 */ H3M_CREATURE_GIANT,
/* 41 */ H3M_CREATURE_TITAN,
/* 42 */ H3M_CREATURE_IMP,
/* 43 */ H3M_CREATURE_FAMILIAR,
/* 44 */ H3M_CREATURE_GOG,
/* 45 */ H3M_CREATURE_MAGOG,
/* 46 */ H3M_CREATURE_HELL_HOUND,
/* 47 */ H3M_CREATURE_CERBERUS,
/* 48 */ H3M_CREATURE_DEMON,
/* 49 */ H3M_CREATURE_HORNED_DEMON,
/* 50 */ H3M_CREATURE_PIT_FIEND,
/* 51 */ H3M_CREATURE_PIT_LORD,
/* 52 */ H3M_CREATURE_EFREETI,
/* 53 */ H3M_CREATURE_EFREET_SULTAN,
/* 54 */ H3M_CREATURE_DEVIL,
/* 55 */ H3M_CREATURE_ARCH_DEVIL,
/* 56 */ H3M_CREATURE_SKELETON,
/* 57 */ H3M_CREATURE_SKELETON_WARRIOR,
/* 58 */ H3M_CREATURE_WALKING_DEAD,
/* 59 */ H3M_CREATURE_ZOMBIE,
/* 60 */ H3M_CREATURE_WIGHT,
/* 61 */ H3M_CREATURE_WRAITH,
/* 62 */ H3M_CREATURE_VAMPIRE,
/* 63 */ H3M_CREATURE_VAMPIRE_LORD,
/* 64 */ H3M_CREATURE_LICH,
/* 65 */ H3M_CREATURE_POWER_LICH,
/* 66 */ H3M_CREATURE_BLACK_KNIGHT,
/* 67 */ H3M_CREATURE_DREAD_KNIGHT,
/* 68 */ H3M_CREATURE_BONE_DRAGON,
/* 69 */ H3M_CREATURE_GHOST_DRAGON,
/* 70 */ H3M_CREATURE_TROGLODYTE,
/* 71 */ H3M_CREATURE_INFERNAL_TROGLODYTE,
/* 72 */ H3M_CREATURE_HARPY,
/* 73 */ H3M_CREATURE_HARPY_HAG,
/* 74 */ H3M_CREATURE_BEHOLDER,
/* 75 */ H3M_CREATURE_EVIL_EYE,
/* 76 */ H3M_CREATURE_MEDUSA,
/* 77 */ H3M_CREATURE_MEDUSA_QUEEN,
/* 78 */ H3M_CREATURE_MINOTAUR,
/* 79 */ H3M_CREATURE_MINOTAUR_KING,
/* 80 */ H3M_CREATURE_MANTICORE,
/* 81 */ H3M_CREATURE_SCORPICORE,
/* 82 */ H3M_CREATURE_RED_DRAGON,
/* 83 */ H3M_CREATURE_BLACK_DRAGON,
/* 84 */ H3M_CREATURE_GOBLIN,
/* 85 */ H3M_CREATURE_HOBGOBLIN,
/* 86 */ H3M_CREATURE_WOLF_RIDER,
/* 87 */ H3M_CREATURE_WOLF_RAIDER,
/* 88 */ H3M_CREATURE_ORC,
/* 89 */ H3M_CREATURE_ORC_CHIEFTAIN,
/* 90 */ H3M_CREATURE_OGRE,
/* 91 */ H3M_CREATURE_OGRE_MAGE,
/* 92 */ H3M_CREATURE_ROC,
/* 93 */ H3M_CREATURE_THUNDERBIRD,
/* 94 */ H3M_CREATURE_CYCLOPS,
/* 95 */ H3M_CREATURE_CYCLOPS_KING,
/* 96 */ H3M_CREATURE_BEHEMOTH,
/* 97 */ H3M_CREATURE_ANCIENT_BEHEMOTH,
/* 98 */ H3M_CREATURE_GNOLL,
/* 99 */ H3M_CREATURE_GNOLL_MARAUDER,
/* 100 */ H3M_CREATURE_LIZARDMAN,
/* 101 */ H3M_CREATURE_LIZARD_WARRIOR,
/* 102 */ H3M_CREATURE_GORGON,
/* 103 */ H3M_CREATURE_MIGHTY_GORGON,
/* 104 */ H3M_CREATURE_SERPENT_FLY,
/* 105 */ H3M_CREATURE_DRAGON_FLY,
/* 106 */ H3M_CREATURE_BASILISK,
/* 107 */ H3M_CREATURE_GREATER_BASILISK,
/* 108 */ H3M_CREATURE_WYVERN,
/* 109 */ H3M_CREATURE_WYVERN_MONARCH,
/* 110 */ H3M_CREATURE_HYDRA,
/* 111 */ H3M_CREATURE_CHAOS_HYDRA,
/* 112 */ H3M_CREATURE_AIR_ELEMENTAL,
/* 113 */ H3M_CREATURE_EARTH_ELEMENTAL,
/* 114 */ H3M_CREATURE_FIRE_ELEMENTAL,
/* 115 */ H3M_CREATURE_WATER_ELEMENTAL,
/* 116 */ H3M_CREATURE_GOLD_GOLEM,
/* 117 */ H3M_CREATURE_DIAMOND_GOLEM,
/* 118 */ H3M_CREATURE_PIXIE,
/* 119 */ H3M_CREATURE_SPRITE,
/* 120 */ H3M_CREATURE_PSYCHIC_ELEMENTAL,
/* 121 */ H3M_CREATURE_MAGIC_ELEMENTAL,
/* 122 */ H3M_CREATURE_NOT_USED1,
/* 123 */ H3M_CREATURE_ICE_ELEMENTAL,
/* 124 */ H3M_CREATURE_NOT_USED2,
/* 125 */ H3M_CREATURE_MAGMA_ELEMENTAL,
/* 126 */ H3M_CREATURE_NOT_USED3,
/* 127 */ H3M_CREATURE_STORM_ELEMENTAL,
/* 128 */ H3M_CREATURE_NOT_USED4,
/* 129 */ H3M_CREATURE_ENERGY_ELEMENTAL,
/* 130 */ H3M_CREATURE_FIREBIRD,
/* 131 */ H3M_CREATURE_PHOENIX,
/* 132 */ H3M_CREATURE_AZURE_DRAGON,
/* 133 */ H3M_CREATURE_CRYSTAL_DRAGON,
/* 134 */ H3M_CREATURE_FAERIE_DRAGON,
/* 135 */ H3M_CREATURE_RUST_DRAGON,
/* 136 */ H3M_CREATURE_ENCHANTER,
/* 137 */ H3M_CREATURE_SHARPSHOOTER,
/* 138 */ H3M_CREATURE_HALFLING,
/* 139 */ H3M_CREATURE_PEASANT,
/* 140 */ H3M_CREATURE_BOAR,
/* 141 */ H3M_CREATURE_MUMMY,
/* 142 */ H3M_CREATURE_NOMAD,
/* 143 */ H3M_CREATURE_ROGUE,
/* 144 */ H3M_CREATURE_TROLL
};

#endif
