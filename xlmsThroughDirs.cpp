#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
#include <stdlib.h>
#include <conio.h>
#include <sys\stat.h>


using namespace cv;
using namespace std;


bool checkFile(char* file_name) {
	ifstream file;
	file.open(file_name);
	if (!file)
		cout << "\nCant find this file : " << file_name;
	else
		return true;
}


void fileTypes(string filename) {
	FileStorage fs(filename, FileStorage::READ);
	FileNode node = fs["FrameDataArray"];
	string txt;
	map<string, int> typesCount;
	for (auto it : node) {
		FileNode subNode = it["FrameObjects"];
		for (auto subIt : subNode) {
			txt = (string)subIt["type"];
			typesCount[txt] += 1;
		}
	}

	for (auto &i : typesCount) {
		cout << i.first << " : " << i.second << endl;
	}
}


int main() {
	while (true) {
		cout << endl << "Enter full path: " << endl;
		string path;
		struct stat s;
		std::cin >> path;
		char *cpath = &path[0u];
		if (path == "q")
			break;
		if (stat(cpath, &s) < 0)
			cout << "No such file or directory: " << path << endl;
		else {
			if (checkFile(cpath)) {
				if (path.substr(path.length() - 4, 4) == ".xml") {
					fileTypes(path);
				}
				else {
					cout << "Not a xml file: " << path << endl;
				}
			}
			else {
				vector<String> paths;
				glob(path + "/*markup.xml", paths, true);
				for (auto &filename : paths) {
					cout << filename << endl;
					fileTypes(filename);
				}
			}
		}
		cout << endl << "To quit press Esc..." << endl;
	}
	//system("PAUSE");
	//std::cin.get(); std::cin.get();
	return 0;
}
