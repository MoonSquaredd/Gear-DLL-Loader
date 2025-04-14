#ifndef GG
#define GG

#include <windows.h>

typedef void(*VoidFunc)(void);
typedef void(*original)(VoidFunc);

BOOL IsAddressReadable(LPCVOID);

static inline BYTE *GetBase() {
	return (BYTE *)GetModuleHandle(NULL);
}

static inline void AssignToGameLoop(VoidFunc func) {
	HMODULE hook = GetModuleHandleA("DBGHELP.DLL");
	original ATGP = (original)GetProcAddress(hook, "AssignToGameLoop");
	if (ATGP) {
		ATGP(func);
	}	
}

#endif
