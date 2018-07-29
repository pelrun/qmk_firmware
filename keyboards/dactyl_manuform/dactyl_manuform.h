#ifndef DACTYL_MANUFORM_H
#define DACTYL_MANUFORM_H

#include "dactyl_manuform.h"

//void promicro_bootloader_jmp(bool program);
#include "quantum.h"


#ifdef USE_I2C
#include <stddef.h>

#endif

//void promicro_bootloader_jmp(bool program);

// clang-format off

#ifndef FLIP_HALF
#define LAYOUT( \
	L00, L01, L02, L03, L04,                       R00, R01, R02, R03, R04, \
	L10, L11, L12, L13, L14,                       R10, R11, R12, R13, R14, \
	L20, L21, L22, L23, L24,                       R20, R21, R22, R23, R24, \
	     L31, L32,      L33,                       R31,      R32, R33,      \
                           L34, L30,   R30, R34,                          \
                           L44, L40,   R40, R44                           \
	) \
	{ \
		{ L00, L01, L02, L03, L04 }, \
		{ L10, L11, L12, L13, L14 }, \
		{ L20, L21, L22, L23, L24 }, \
		{ L30, L31, L32, L33, L34 }, \
		{ L40, KC_NO, KC_NO, KC_NO, L44 }, \
\
		{ R04, R03, R02, R01, R00 },  \
		{ R14, R13, R12, R11, R10 },  \
		{ R24, R23, R22, R21, R20 },  \
		{ R34, R33, R32, R31, R30 },  \
		{ R44, KC_NO, KC_NO, KC_NO, R40 }  \
	}
#else
#define LAYOUT( \
	L00, L01, L02, L03, L04,                       R00, R01, R02, R03, R04, \
	L10, L11, L12, L13, L14,                       R10, R11, R12, R13, R14, \
	L20, L21, L22, L23, L24,                       R20, R21, R22, R23, R24, \
	     L31, L32,      L33,                       R31,      R32, R33,      \
                           L34, L30,   R30, R34,                          \
                           L44, L40,   R40, R44                           \
	) \
	{ \
		{ R04, R03, R02, R01, R00 },  \
		{ R14, R13, R12, R11, R10 },  \
		{ R24, R23, R22, R21, R20 },  \
		{ R34, R33, R32, R31, R30 },  \
		{ R44, KC_NO, KC_NO, KC_NO, R40 }, \
\
		{ L00, L01, L02, L03, L04 }, \
		{ L10, L11, L12, L13, L14 }, \
		{ L20, L21, L22, L23, L24 }, \
		{ L30, L31, L32, L33, L34 }, \
		{ L40, KC_NO, KC_NO, KC_NO, L44 }  \
	}
#endif

#endif
