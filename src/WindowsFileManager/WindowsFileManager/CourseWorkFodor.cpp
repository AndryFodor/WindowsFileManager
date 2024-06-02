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

void clearScreen()
{
	system("cls");
}

void printMenu(const vector<string>& options, const fs::path currentPath)
{
	clearScreen();
	cout << "File Explorer Menu" << endl;
	cout << "--------------------------------" << endl;
	cout << "Current location: " << currentPath << endl;
	cout << "--------------------------------" << endl;
	cout << "Options:" << endl;
	for (size_t i = 0; i < options.size(); i++)
	{
		if (options.size() - i == 1)
			cout << options[i] << endl;
		else
			cout << i + 1 << ". " << options[i] << endl;

	}
}

void displayDirectoryContents(const fs::path& path)
{
	clearScreen();
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

void deleteDirectory(const fs::path& path)
{
	if (fs::exists(path) && fs::is_directory(path))
	{
		fs::remove_all(path);
		cout << "Directory deleted successfully." << endl;
	}
	else
	{
		cout << "Directory not found." << endl;
	}

	_getch();
}

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
		cout << "Invalid directory path." << endl;
	}

	_getch();
}

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

void absolutePath(fs::path& enteredPath, const fs::path& currentPath) {
	if (!enteredPath.has_root_path()) {
		enteredPath = currentPath / enteredPath;
	}
}

int main()
{
	fs::path currentPath = "D:\\"; // Вказати шлях до жорсткого диска (наприклад, "C:\\")

	vector<string> options = { "Exit", "List Contents", "Change Directory", "Create File", "Create Directory", "Delete File", "Delete Directory", "File Properties", "Open File", "Rename File", "Rename Directory", "Copy File", "Copy Directory", "Move File", "Move Directory", "Here are also supported commands cd and ls" };
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t Hello!\n\t\t\t\t\t\tWelcome to File Explorer" << endl;
	_getch();

	while (true)
	{
		printMenu(options, currentPath);

		string inputst;
		getline(cin, inputst);
		clearScreen();
		if (inputst == "1") // Команда для закінчення роботи
		{
			break;
		}
		else if (inputst == "2" || inputst == "ls") // Вивід інформації про вміст за поточним розташуванням користувача
		{
			displayDirectoryContents(currentPath);
			_getch();
		}
		else if (inputst == "3") // змінити дерикторію (вводити лише абсолютний шлях)
		{
			string newPath;
			cout << "Enter absolute directory path: ";
			getline(cin, newPath);

			if (fs::exists(newPath) && fs::is_directory(newPath))
			{
				currentPath = newPath;
			}
			else
			{
				cout << "Invalid directory path." << endl;
				_getch();
			}
		}
		else if (inputst == "4") // Створення файлу
		{
			string filePath;
			cout << "Enter file path: ";
			getline(cin, filePath);
			//отримання абсолютного шляху до файлу
			fs::path formattedPath = filePath;
			absolutePath(formattedPath, currentPath);
			createFile(formattedPath);
		}
		else if (inputst == "5") // Створення дерикторії
		{
			string dirPath;
			cout << "Enter directory path: ";
			getline(cin, dirPath);
			fs::path formattedPath = dirPath;
			absolutePath(formattedPath, currentPath);

			createDirectory(formattedPath);
		}
		else if (inputst == "6") // видалення файлу
		{
			string filePath;
			cout << "Enter file path: ";
			getline(cin, filePath);
			//отримання абсолютного шляху до файлу
			fs::path formattedPath = filePath;
			absolutePath(formattedPath, currentPath);

			deleteFile(formattedPath);
		}
		else if (inputst == "7") // видалення дерикторії
		{
			string dirPath;
			cout << "Enter directory path: ";
			getline(cin, dirPath);
			fs::path formattedPath = dirPath;
			absolutePath(formattedPath, currentPath);

			deleteDirectory(formattedPath);
		}
		else if (inputst == "8") // отримати властивості файлу
		{
			string path;
			cout << "Enter file path: ";
			getline(cin, path);
			fs::path formattedPath = path;
			absolutePath(formattedPath, currentPath);

			displayFileProperties(formattedPath);
		}
		else if (inputst == "9") // відкрити файл 
		{
			string filePath;
			cout << "Enter file path: ";
			getline(cin, filePath);
			fs::path formattedPath = filePath;
			absolutePath(formattedPath, currentPath);

			openFile(formattedPath);
		}
		else if (inputst == "10") // Перейменування файлу
		{
			string filePath;
			cout << "Enter file path: ";
			getline(cin, filePath);
			fs::path formattedPath = filePath;
			absolutePath(formattedPath, currentPath);

			string newFileName;
			cout << "Enter new file name: ";
			getline(cin, newFileName);

			renameFile(formattedPath, newFileName);
		}
		else if (inputst == "11") // Перейменування дерикторії
		{
			string dirPath;
			cout << "Enter directory path: ";
			getline(cin, dirPath);
			fs::path formattedPath = dirPath;
			absolutePath(formattedPath, currentPath);

			string newDirName;
			cout << "Enter new directory name: ";
			getline(cin, newDirName);

			renameDirectory(formattedPath, newDirName);
		}
		else if (inputst == "12") // Скопіювати файл
		{
			string sourceFilePath;
			cout << "Enter source file path: ";
			getline(cin, sourceFilePath);
			fs::path formattedPath = sourceFilePath;
			absolutePath(formattedPath, currentPath);

			string destinationFilePath;
			cout << "Enter absolute destination file path: ";
			getline(cin, destinationFilePath);

			copyFile(formattedPath, destinationFilePath);
		}
		else if (inputst == "13") // Скопіювати дерикторію
		{
			string sourceDirPath;
			cout << "Enter source directory path: ";
			getline(cin, sourceDirPath);
			fs::path formattedPath = sourceDirPath;
			absolutePath(formattedPath, currentPath);

			string destinationDirPath;
			cout << "Enter absolute destination directory path: ";
			getline(cin, destinationDirPath);

			copyDirectory(formattedPath, destinationDirPath);
		}
		else if (inputst == "14") // Перемістити файл
		{
			string sourceFilePath;
			cout << "Enter source file path: ";
			getline(cin, sourceFilePath);
			fs::path formattedPath = sourceFilePath;
			absolutePath(formattedPath, currentPath);

			string destinationFilePath;
			cout << "Enter absolute destination file path and specify the file name at the end of this path: ";
			getline(cin, destinationFilePath);

			moveFile(formattedPath, destinationFilePath);
		}
		else if (inputst == "15") // Перемістити дерикторію
		{
			string sourceDirPath;
			cout << "Enter source directory path: ";
			getline(cin, sourceDirPath);
			fs::path formattedPath = sourceDirPath;
			absolutePath(formattedPath, currentPath);

			string destinationDirPath;
			cout << "Enter absolute destination directory path and specify the directory name at the end of this path: ";
			getline(cin, destinationDirPath);

			moveDirectory(formattedPath, destinationDirPath);
		}
		else if (inputst.find("cd") != string::npos && inputst.find("cd") == 0 && inputst.length() > 2) {//cd команда
			string extractedPath = inputst.substr(3);
			fs::path formattedPath;
			if (extractedPath == "..") {
				fs::path parentPath = currentPath.parent_path();
				formattedPath = parentPath;
			}
			else
				formattedPath = extractedPath;
			absolutePath(formattedPath, currentPath);
			if (fs::exists(formattedPath) && fs::is_directory(formattedPath)) {
				fs::path canonicalPath = fs::canonical(formattedPath);
				cout << "Now your current location path is " << canonicalPath << endl;
				currentPath = canonicalPath;
			}
			else
				cout << "Invalid directory path." << endl;


			getchar();
		}
	}
	return 0;
}
