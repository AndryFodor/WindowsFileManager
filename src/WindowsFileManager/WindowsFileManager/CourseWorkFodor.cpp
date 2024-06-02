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

	return 0;
}