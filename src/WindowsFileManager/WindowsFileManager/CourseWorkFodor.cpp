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


void displayDirectoryContents(const fs::path& path)
{
	//clearScreen();
	cout << "Current Directory: " << fs::absolute(path) << endl;

	int maxLength = 0;
	bool empty = true;
	for (const auto& entry : fs::directory_iterator(path)) {
		if (entry.path().filename().string().length() > maxLength) {
			maxLength = entry.path().filename().string().length();
		}
	}
	maxLength += 5;
	for (int i = 0; i < maxLength + 28; i++)
	{
		cout << "-";
	}
	cout << "\nTYPE   NAME";
	for (int i = 0; i < maxLength - 2; i++)
	{
		cout << " ";
	}
	cout << "   LAST CHANGES" << endl;
	for (int i = 0; i < maxLength + 28; i++)
	{
		cout << "-";
	}
	cout << endl;
	for (const auto& entry : fs::directory_iterator(path))
	{
		if (fs::is_directory(entry.status()))
		{
			empty = false;
			cout << "[DIR] ";
		}
		else
		{
			empty = false;
			cout << "[FILE]";
		}

		cout << " " << entry.path().filename();

		auto file_time = fs::last_write_time(entry.path());

		auto time_point = chrono::time_point_cast<chrono::system_clock::duration>(file_time - fs::file_time_type::clock::now() + chrono::system_clock::now());

		time_t file_time_t = chrono::system_clock::to_time_t(time_point);

		struct  tm* ptm = localtime(&file_time_t);
		char buffer[32];
		strftime(buffer, 32, "%H:%M:%S-%d.%m.%Y", ptm);

		for (int i = 0; i < maxLength - entry.path().filename().string().length(); i++)
		{
			cout << ".";
		}
		cout << buffer << endl;

	}
	if (empty)
		cout << "Directory is empty" << endl;
}


int main() {
	string testPath4 = "D://KZP";
	string testPath5 = "D://";
	string testPath6 = "D://noDir";

	displayDirectoryContents(testPath5);

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
