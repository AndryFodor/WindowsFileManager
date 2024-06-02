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

void renameFile(const fs::path& filePath, const  string& newFileName)
{
	if (fs::exists(filePath) && fs::is_regular_file(filePath))
	{
		fs::path parentPath = filePath.parent_path();
		fs::path newFilePath = parentPath / newFileName;

		if (fs::exists(newFilePath))
		{
			cout << "A file with the new name already exists." << endl;
		}
		else
		{
			try
			{
				fs::rename(filePath, newFilePath);
				cout << "File renamed successfully." << endl;
			}
			catch (const fs::filesystem_error& e)
			{
				cout << "Failed to rename file. Error: " << e.what() << endl;
			}
		}
	}
	else
	{
		cout << "Invalid file path." << endl;
	}
	_getch();
}

int main() {
	string testPath20 = "D://KZP2";
	string testPath21 = "D://index2.js";
	string testPath22 = "D://noFile.txt";

	renameFile(testPath21, "index3.js");


	return 0;
}