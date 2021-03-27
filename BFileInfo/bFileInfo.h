#include <string.h>
#include <vector>
#include <Windows.h>
#include <iostream>
using namespace std;

#define MAX_FILENAME_LENGTH 2048

class BFileInfo{
public:
	BFileInfo(string source);
	string Drive;
	string DirectoryName;
	string Filename;
	string FullName;
	string Extension;
	DWORD Attributes = 0;
	SYSTEMTIME LastAccessTime;
	SYSTEMTIME LastWriteTime;
	SYSTEMTIME CreationTime;
	DWORD Length = 0;
	bool ReadOnly = false;
	bool Exists = false;
private:
	void parse();
	char FullSource[MAX_FILENAME_LENGTH];
	int FindChar(char *s, int start, char c);
	int LastChar(char *s, char c);
};

int BFileInfo::FindChar(char *s, int start, char c){
	int x = start;
	int idx = 0;

	while (x < strlen(s)){
		if (s[x] == c){
			idx = x;
			break;
		}
		x++;
	}

	return idx;
}

int BFileInfo::LastChar(char *s, char c){
	int x = 0;
	int pos = 0;

	while (x < strlen(s)){
		if (s[x] == c){
			pos = x;
		}
		x++;
	}

	return pos;
}


void BFileInfo::parse(){
	DWORD fAttr;
	SYSTEMTIME st;
	WIN32_FIND_DATAA wfd;
	FILETIME ft0, ft1,ft2;
	HANDLE fh;
	int s_pos = 0;
	int e_pos = 0;
	int x = 0;
	int len = 0;
	
	//Get length of string
	len = strlen(FullSource);
	FullName = FullSource;

	//Get first backslash
	s_pos = FindChar(FullSource, 0, '\\');

	//Used to get information about the file
	fh = FindFirstFileA(FullSource, &wfd);
	
	if (fh != INVALID_HANDLE_VALUE){
		//Get file Attributes
		Attributes = wfd.dwFileAttributes;
		//See if the file is ReadOnly
		ReadOnly = (wfd.dwFileAttributes == 33 || wfd.dwFileAttributes == 35);
		//See if the file is found.
		if (!(wfd.dwFileAttributes & FILE_ATTRIBUTE_DEVICE) &&
			!(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			Exists = true;
		}
		//Get file length
		Length = wfd.nFileSizeLow;
		//Get file times
		ft0 = wfd.ftLastAccessTime;
		ft1 = wfd.ftLastWriteTime;
		ft2 = wfd.ftCreationTime;
		//Convert file times to system times
		FileTimeToSystemTime(&ft0, &LastAccessTime);
		FileTimeToSystemTime(&ft1, &LastWriteTime);
		FileTimeToSystemTime(&ft2, &CreationTime);
		//Clear up types
		ZeroMemory(&ft0, 0);
		ZeroMemory(&ft1, 0);
		ZeroMemory(&ft2, 0);
	}
	//Close file handle
	FindClose(fh);
	//Check if file is found.

	ZeroMemory(&wfd, 0);

	if (s_pos > 0){
		//Copy the drive from the path
		while (x < s_pos){
			if (FullSource[x] != ':'){
				Drive += FullSource[x];
			}
			x++;
		}
		x++;
	}
	
	//Get last backslash in the file path
	e_pos = LastChar(FullSource, '\\');
	
	if (e_pos > 0){
		//Extract the file path
		while (x < e_pos){
			DirectoryName += FullSource[x];
			x++;
		}
	}

	//Get filename
	if (e_pos > 0){
		//Set x to last position
		x = (e_pos + 1);
		while (x < len){
			//EXtract filename.
			Filename += FullSource[x];
			x++;
		}
	}

	//Get file Extension from filename
	//Get last dot
	s_pos = LastChar(FullSource, '.');

	if (s_pos > 0){
		//Set x to s_pos
		x = s_pos;
		while (x < len){
			//Extract file extension
			Extension += FullSource[x];
			x++;
		}
	}
	
}

BFileInfo::BFileInfo(string source){
	strcpy(FullSource, source.c_str());
	//parse input string
	parse();
}