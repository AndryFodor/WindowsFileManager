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

void renameDirectory(const fs::path& dirPath, const string& newDirName)
{
	if (fs::exists(dirPath) && fs::is_directory(dirPath))
	{
		fs::path parentPath = dirPath.parent_path();
		fs::path newDirPath = parentPath / newDirName;

		try
		{
			fs::rename(dirPath, newDirPath);
			cout << "Directory renamed successfully." << endl;
		}
		catch (const fs::filesystem_error& error)
		{
			cout << "Failed to rename the directory: " << error.what() << endl;

		}
	}
	else
	{
		cout << "Invalid file path." << endl;
	}
		cout << "Invalid directory path." << endl;

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
	string testPath11 = "D://index.js";
	string testPath12 = "D://noFile.txt";

	openFile(testPath11);
	openFile(testPath12);
	return 0;
}