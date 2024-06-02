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
void createDirectory(const fs::path& path)
{
	if (fs::create_directory(path))
	{
		cout << "Directory created successfully." << endl;
	}
	else
	{
		cout << "Failed to create directory." << endl;
	}

	_getch();
}

int main() {
	string testPath9 = "D://KZP2";
	string testPath10 = "D://index3.js";
	createDirectory(testPath9);
	return 0;
}