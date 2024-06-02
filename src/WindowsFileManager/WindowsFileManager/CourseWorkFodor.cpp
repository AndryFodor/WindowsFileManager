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

void copyFile(const fs::path& sourceFilePath, const fs::path& destinationFilePath)
{
	try
	{
		fs::copy(sourceFilePath, destinationFilePath);
		cout << "File copied successfully." << endl;
	}
	catch (const fs::filesystem_error& error)
	{
		cout << "Failed to copy the file: " << error.what() << endl;
	}

	_getch();
}

void copyDirectory(const fs::path& sourceDirPath, const fs::path& destinationDirPath)
{
	try
	{
		fs::copy(sourceDirPath, destinationDirPath, fs::copy_options::recursive);
		cout << "Directory copied successfully." << endl;
	}
	catch (const fs::filesystem_error& error)
	{
		cout << "Failed to copy the directory: " << error.what() << endl;
	}

	_getch();
}

int main() {


	return 0;
}