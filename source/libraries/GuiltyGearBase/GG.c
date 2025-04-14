#include <windows.h>
#include "GG.h"

BOOL IsAddressReadable(LPCVOID addr) {
	MEMORY_BASIC_INFORMATION mbi;
	if (VirtualQuery(addr,&mbi,sizeof(mbi))) {
		if (mbi.State != MEM_COMMIT) {
			return FALSE;
		}
		DWORD protect = mbi.Protect;
		if (protect & PAGE_READONLY || protect & PAGE_READWRITE ||
			protect & PAGE_WRITECOPY || protect & PAGE_EXECUTE_READ ||
			protect & PAGE_EXECUTE_READWRITE || protect & PAGE_EXECUTE_WRITECOPY) {
			return TRUE;
		}
	}	
	return FALSE;
}
