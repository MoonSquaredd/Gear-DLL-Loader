#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "GG.h"

#define TEXT_RVAOFF 0xc00
#define RDATA_RVAOFF1 0x1800
#define RDATA_RVAOFF2 0x1800
#define DATA_RVAOFF 0x2400

char buf[2048] = {0};

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

int read3(FILE *f) {
	int val = 0;
	int a = fgetc(f);
	int b = fgetc(f);
	int c = fgetc(f);
	if (a == -1 || b == -1 || c == -1) return -1;
	val |= ((unsigned)a << 16);
	val |= ((unsigned)b << 8);
	val |= (unsigned)c;
	return val;
}

short read2(FILE *f) {
	short val = 0;
	int a = fgetc(f);
	int b = fgetc(f);
	if (a == -1 || b == -1) return -1;
	val |= ((unsigned)a << 8);
	val |= (unsigned)b;
	return val;
}

void ApplyIPS(const char *path) {
	BYTE *base = GetBase();
	FILE *ips = fopen(path,"rb");
	if (!ips) return;
	
	char header[6] = {0};
	fread(header,1,5,ips);
	if (strncmp(header,"PATCH",5) != 0) {
		fclose(ips);
		return;
	}
	
	while(TRUE) {
		memset(buf,0,sizeof(buf));
		int offset = read3(ips);
		if (feof(ips) || offset == -1) break;
		
		if (offset == 0x454f46) break;
		
		if (offset >= 0x560c00) {
			offset += DATA_RVAOFF;
		} else if (offset >= 0x53e691) {
			offset += RDATA_RVAOFF2;
		} else if (offset >= 0x3bb800) {
			offset += RDATA_RVAOFF1;
		} else if (offset >= 0x400) {
			offset += TEXT_RVAOFF;
		}
		
		short size = read2(ips);
		if (size > 0) {
			fread(buf,1,size,ips);
			PatchSafe(base+offset,buf,size);
		} else {
			short rle_size = read2(ips);
			char rle_char = fgetc(ips);
			
			memset(buf,rle_char,rle_size);
			PatchSafe(base+offset,buf,rle_size);
		}
	}
	fclose(ips);
}
