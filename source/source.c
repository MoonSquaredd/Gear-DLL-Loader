#include <string.h>
#include <windows.h>

typedef void(*VoidFunc)(void);
typedef WINBOOL(WINAPI *MiniDumpWriteDump_t)(HANDLE,DWORD,HANDLE,int,const void *,const void *,const void *);

VoidFunc HitStopTimeExeRoot;
int GLFunctionsCnt = 0;
VoidFunc GameLoopFunctions[256] = {0};

HMODULE dbghelp;
MiniDumpWriteDump_t OriginalFunc = NULL; 

DWORD WINAPI ModsInit(LPVOID lpParameter) {
	WIN32_FIND_DATA fileData;
	HANDLE hFile = FindFirstFileA("Mods\\*",&fileData);
	
	if (hFile == INVALID_HANDLE_VALUE) {
		return 1;
	}
	
	char path[MAX_PATH];
	
	do {
		if (!(fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
			const char *dot = strrchr(fileData.cFileName, '.');
			if (strcmp(dot,".dll") == 0) {
				strcpy(path,"Mods\\");
				strcat(path,fileData.cFileName);
				LoadLibraryA(path);
			}
		}
	} while(FindNextFileA(hFile, &fileData) != 0);
	
	FindClose(hFile);
	return 0;
}

void GameLoopExecute(void) {
	HitStopTimeExeRoot();
	for (int i = 0; i < GLFunctionsCnt; i++) {
		VoidFunc func = GameLoopFunctions[i];
		if (func != NULL) {
			func();
		}
	}
	return;
}

void HookGameLoop(void) {
	BYTE *base = (BYTE*)GetModuleHandle(NULL);
	DWORD oldProtect;
	HitStopTimeExeRoot = (VoidFunc)base+0x2af6a0;
	char call[5] = {0xE8};
	*(DWORD*)(call+1) = (DWORD)GameLoopExecute - ((DWORD)base+0x1c2fe7 + 5);
	
	VirtualProtect(base+0x1c2fe7,5,PAGE_EXECUTE_READWRITE,&oldProtect);
	memcpy(base+0x1c2fe7,call,5);
	VirtualProtect(base+0x1c2fe7,5,oldProtect,&oldProtect);
	return;
}

BOOL WINAPI DllMain(HINSTANCE hInst, DWORD reason, LPVOID reserved) {
	if (reason == DLL_PROCESS_ATTACH) {
		char DBGOriginal[MAX_PATH];
		GetSystemDirectoryA(DBGOriginal,MAX_PATH);
		strcat(DBGOriginal,"\\dbghelp.dll");
		dbghelp = LoadLibraryA(DBGOriginal);
		if (dbghelp) {
			OriginalFunc = (MiniDumpWriteDump_t)GetProcAddress(dbghelp,"MiniDumpWriteDump");
		}
		
		HANDLE initThread = CreateThread(NULL,0,ModsInit,NULL,0,NULL);
		CloseHandle(initThread);
		HookGameLoop();
	}
	return TRUE;
}

void AssignToGameLoop(VoidFunc func) {
	GameLoopFunctions[GLFunctionsCnt] = func;
	GLFunctionsCnt += 1;
	return;
}

WINBOOL WINAPI MiniDumpWriteDump(
	HANDLE hProcess, DWORD ProcessId, HANDLE hFile, int DumpType, 
	const void *Exception, const void *UserStream, const void *Callback)
{
	if (OriginalFunc) {
		return OriginalFunc(hProcess,ProcessId,hFile,DumpType,Exception,UserStream,Callback);
	}
	return FALSE;
}
