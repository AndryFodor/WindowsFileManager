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

void moveFile(const fs::path& sourceFilePath, const fs::path& destinationFilePath)
{
	try
	{
		fs::rename(sourceFilePath, destinationFilePath);
		cout << "File moved successfully." << endl;
	}
	catch (const fs::filesystem_error& error)
	{
		cout << "Failed to move the file: " << error.what() << endl;
	}

	_getch();
}

void moveDirectory(const fs::path& sourceDirPath, const fs::path& destinationDirPath)
{
	try
	{
		fs::rename(sourceDirPath, destinationDirPath);
		cout << "Directory moved successfully." << endl;
	}
	catch (const fs::filesystem_error& error)
	{
		cout << "Failed to move the directory: " << error.what() << endl;
	}

	_getch();
}

int main() {


	return 0;
}