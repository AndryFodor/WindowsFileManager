#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <conio.h>
#include <Windows.h>
#include <ctime>

using namespace std;
namespace fs = std::filesystem;

void deleteFile(const fs::path& path)
{
	if (fs::exists(path))
	{
		fs::remove(path);
		cout << "File deleted successfully." << endl;
	}
	else
	{
		cout << "File not found." << endl;
	}

	_getch();
}

int main() {
	string testPath7 = "D://KZP2";
	string testPath8 = "D://index2.js";
	deleteFile(testPath8);

	return 0;
}