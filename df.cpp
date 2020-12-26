#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include<experimental/filesystem>
#include<iostream>
#include<Windows.h>

using namespace std;
using namespace experimental::filesystem;

inline void sort_dir_to_path(string path_dir) {
	for (const auto& file : directory_iterator(path_dir)) {
		if (!is_directory(file)) {
			string* path_to = new string();
			string* path_from = new string();

			*path_to = path_dir + "\\"s + file.path().extension().string() + "\\"s + file.path().filename().string();
			*path_from = path_dir + "\\"s + file.path().filename().string();
			create_directory(path_dir + "\\"s + file.path().extension().string());
			MoveFileA(path_from->c_str(), path_to->c_str());

			delete path_from;
			delete path_to;
		}
	}
}


int main(int argc, char* argv[]) {	
	
	SetConsoleCP(1251);

	if (argv[1] != NULL) {
		string path = argv[1];
		sort_dir_to_path(path);
	}
	else {
		printf("Вызовите программу df через командную строку и передайте ей как аргумент ссылку на папку, которую следует отфильтровать\n");
		printf("Call the df program from the command line and pass it a link to the folder you want to filter as an argument\n");
	}
}
