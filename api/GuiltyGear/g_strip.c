#include <windows.h>
#include "GG.h"
#include "g_strip.h"

void gSpriteDraw_NaomiLibVersion(NL_SPR_ARG *sprite, int param2) {
    BYTE *base = (BYTE *)GetModuleHandle(NULL);
    unsigned int address = (unsigned int)base+0x0010d1a0;
    __asm__ (
		".intel_syntax noprefix\n\t"
		"push ecx\n\t"
		"mov ecx,[%0]\n\t"
		"push [%1]\n\t"
		"call [%2]\n\t"
		"add esp,4\n\t"
		"pop ecx\n\t"
		".att_syntax prefix\n\t"
		:
		: "m"(sprite), "m"(param2), "m"(address)
	);
}
