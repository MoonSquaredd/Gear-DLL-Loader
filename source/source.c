#include <string.h>
#include <windows.h>
#include <dbghelp.h>

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

BOOL WINAPI DllMain(HINSTANCE hInst, DWORD reason, LPVOID reserved) {
	if (reason == DLL_PROCESS_ATTACH) {
		HANDLE initThread = CreateThread(NULL,0,ModsInit,NULL,0,NULL);
		CloseHandle(initThread);
	}
	return TRUE;
}
// i know about the horrors below, they might not even work but that wont affect the mod.
// you might just never get a crash dump ever :D
WINBOOL WINAPI HookedMiniDumpWriteDump(
	HANDLE hProcess, DWORD ProcessId, HANDLE hFile, MINIDUMP_TYPE DumpType, 
	CONST PMINIDUMP_EXCEPTION_INFORMATION Exception, 
	CONST PMINIDUMP_USER_STREAM_INFORMATION UserStream, 
	CONST PMINIDUMP_CALLBACK_INFORMATION Callback) 
{
	return MiniDumpWriteDump(hProcess,ProcessId,hFile,DumpType,Exception,UserStream,Callback);
}

WINBOOL WINAPI MiniDumpWriteDump(
	HANDLE hProcess, DWORD ProcessId, HANDLE hFile, MINIDUMP_TYPE DumpType, 
	CONST PMINIDUMP_EXCEPTION_INFORMATION Exception, 
	CONST PMINIDUMP_USER_STREAM_INFORMATION UserStream, 
	CONST PMINIDUMP_CALLBACK_INFORMATION Callback) 
{
	return HookedMiniDumpWriteDump(hProcess,ProcessId,hFile,DumpType,Exception,UserStream,Callback);
}
