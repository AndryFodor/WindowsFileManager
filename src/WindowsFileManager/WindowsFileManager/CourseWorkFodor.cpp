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

void createFile(const fs::path& path)
{
	if (fs::exists(path)) {
		cout << "File already exists." << endl;
		_getch();
		return;
	}

	ofstream file(path.string());
	if (file)
	{
		cout << "File created successfully." << endl;
	}
	else
	{
		cout << "Failed to create file." << endl;
	}
	file.close();

	_getch();
}

int main() {
	string testPath9 = "D://KZP2";
	string testPath10 = "D://index2.js";
	createDirectory(testPath9);
	createFile(testPath10);
	return 0;
}