#include <iostream>
#include "bFileInfo.h"
using namespace std;

int main(){

	//BFileInfo class example.
	string src = "C:\\out\\documents\\business\\word\\BuninessTrips.txt";
	BFileInfo fi(src);

	std::cout << "Drive         : " << fi.Drive.c_str() << endl;
	std::cout << "DirectoryName : " << fi.DirectoryName.c_str() << endl;
	std::cout << "File          : " << fi.Filename.c_str() << endl;
	std::cout << "Full Name     : " << fi.FullName.c_str() << endl;
	std::cout << "Extension     : " << fi.Extension.c_str() << endl;
	std::cout << "Exists        : " << fi.Exists << endl;
	std::cout << "Attributes    : " << fi.Attributes << endl;
	std::cout << "ReadOnly      : " << fi.ReadOnly << endl;

	std::cout << "CreationTime  : " << fi.CreationTime.wDay << "/" <<
		fi.CreationTime.wMonth << "/" << fi.CreationTime.wYear << " " <<
		fi.CreationTime.wHour << ":" << fi.CreationTime.wMinute << ":" <<
		fi.CreationTime.wSecond << endl;

	std::cout << "LastAccessTime  : " << fi.LastAccessTime.wDay << "/" << 
		fi.LastAccessTime.wMonth << "/" << fi.LastAccessTime.wYear << " " << 
		fi.LastAccessTime.wHour << ":" << fi.LastAccessTime.wMinute << ":" << 
		fi.LastAccessTime.wSecond << endl;

	std::cout << "LastWriteTime  : " << fi.LastWriteTime.wDay << "/" <<
		fi.LastWriteTime.wMonth << "/" << fi.LastWriteTime.wYear << " " <<
		fi.LastWriteTime.wHour << ":" << fi.LastWriteTime.wMinute << ":" <<
		fi.LastWriteTime.wSecond << endl;

	std::cout << "Length          : " << fi.Length << " bytes " << endl;

	system("pause");
	return 0;
}