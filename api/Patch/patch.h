#ifndef patch
#define patch

#include <windows.h>

BOOL IsAddressReadable(LPCVOID);
void ApplyIPS(const char*);

static inline BYTE *GetBase() {
	return (BYTE *)GetModuleHandle(NULL);
}

static inline void PatchSafe(void *dest,const void *src,int size) {
	DWORD oldProtect;
	VirtualProtect(dest,size,PAGE_EXECUTE_READWRITE,&oldProtect);
	memcpy(dest,src,size);
	VirtualProtect(dest,size,oldProtect,&oldProtect);
}

#endif