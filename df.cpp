#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include<experimental/filesystem>
#include<iostream>
#include<Windows.h>

using namespace std;
using namespace experimental::filesystem;

inline void sort_dir_to_path(string path_dir) {
	if (!exists(path_dir)) {
		printf("There is no such folder\n");
		exit(1);
	}
	else if (!is_directory(path_dir)) {
		printf("Please specify the path to the folder, not the file\n");
		exit(1);
	}
	printf("Sorting has started\n");
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
	printf("Sorting finished\n");
}


int main(int argc, char* argv[]) {	

	if (argv[1] != NULL) {
		string path;
		for (int i = 1; i < argc; ++i) {
			if (i != 1)
				path += " ";
			
			path.append(argv[i]);
		}
		sort_dir_to_path(path);
	}
	else {
		printf("Call the df program from the command line and pass it a link to the folder you want to filter as an argument\n");
		exit(1);
	}
	return 0;
}
