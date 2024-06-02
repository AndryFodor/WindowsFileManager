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

void openFile(const fs::path& filePath)
{
	if (fs::exists(filePath) && fs::is_regular_file(filePath))
	{
		ifstream file(filePath);
		if (file.is_open())
		{
			cout << "File Contents: " << endl;
			cout << "-------------------" << endl;

			string line;
			while (getline(file, line))
			{
				cout << line << endl;
			}

			file.close();
		}
		else
		{
			cout << "Failed to open file." << endl;
		}
	}
	else
	{
		cout << "Invalid file path." << endl;
	}

	_getch();
}

int main() {
	string testPath11 = "D://index.js";
	string testPath12 = "D://noFile.txt";

	openFile(testPath11);
	openFile(testPath12);
	return 0;
}