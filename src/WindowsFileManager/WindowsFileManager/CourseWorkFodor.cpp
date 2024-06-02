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

void displayFileProperties(const fs::path& path)
{
	if (fs::exists(path))
	{
		cout << "File Properties: " << endl;
		cout << "-------------------" << endl;
		cout << "Path: " << fs::absolute(path) << endl;
		cout << "Size: " << fs::file_size(path) << " bytes" << endl;

		cout << "Permissions: ";
		if ((fs::status(path).permissions() & fs::perms::owner_read) != fs::perms::none)
		{
			cout << "Read ";
		}
		if ((fs::status(path).permissions() & fs::perms::owner_write) != fs::perms::none)
		{
			cout << "Write ";
		}
		if ((fs::status(path).permissions() & fs::perms::owner_exec) != fs::perms::none)
		{
			cout << "Execute ";
		}
		cout << endl;
	}
	else
	{
		cout << "File not found." << endl;
	}

	_getch();
}

int main() {
	string testPath1 = "D://KZP/kzpLab1.docx";
	string testPath2 = "D://index.js";
	string testPath3 = "D://noFile.txt";
	displayFileProperties(testPath3);
	return 0;
}