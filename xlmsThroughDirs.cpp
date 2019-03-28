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


void fileTypes(string filename, map<string, int>& typesCount) {
	FileStorage fs(filename, FileStorage::READ);
	FileNode node = fs["FrameDataArray"];
	string txt;
	for (auto it : node) {
		FileNode subNode = it["FrameObjects"];
		for (auto subIt : subNode) {
			txt = (string)subIt["type"];
			typesCount[txt] += 1;
		}
	}	
}


int main(int args, char* argv[]) {
	if (args == 1) {
		cout << "No path specified!" << endl;
		return -1;
	} 
	string path;
	path = argv[1];
	struct stat s;
	char *cpath = &path[0u];
	if (stat(cpath, &s) < 0) {
		cout << "No such file or directory: " << path << endl;
		return -1;
	}
	map<string, int> typesCount;
	if (s.st_mode & S_IFDIR != 0) {
		vector<String> paths;
		glob(path + "/*markup.xml", paths, true);
		for (auto &filename : paths) {
			cout << filename << endl;
			fileTypes(filename, typesCount);
		}
	}
	else {
		if (path.substr(path.length() - 4, 4) == ".xml") {
			fileTypes(path, typesCount);
		}
		else cout << "Not a xml file: " << path << endl;
	}
	for (auto &i : typesCount) {
		cout << i.first << " : " << i.second << endl;
	}
	
	return 0;
}

//USING FILESYSTEM

//std::vector<std::string> ls_wc(const std::string &folder, const std::string &wildcard, bool subfolders,
//	bool files)
//{
//	return stlplus::folder_wildcard(folder, wildcard, subfolders, files);
//}
//
//int main(int args, char* argv[]) {
//	if (args == 1) {
//		cout << "No path specified" << endl;
//	}
//	else {
//		string path;
//		path = argv[1];
//		struct stat s;
//		char *cpath = &path[0u];
//		if (stat(cpath, &s) < 0) {
//			cout << "No such file or directory: " << path << endl;
//		}
//		else {
//			std::map<std::string, int> typesCount;
//			if (s.st_mode & S_IFDIR != 0) {
//				vector<string> paths;
//				if (path[path.length() - 1] != '/') {
//					path += '/';
//				}
//				paths = ls_wc(path, "*.avi.dat", true, true);
//				if (paths.size() == 0) {
//					cout << "No needed directories!" << endl;
//				} else {
//					for (auto &folder : paths) {
//						vector<string> files;
//						files = ls_wc(path + folder, "*.xml", true, true);
//						for (auto &xml : files) {
//							cout << path + folder + "/" + xml << endl;
//							fileTypes(path + folder + "/" + xml, typesCount);
//						}
//					}
//				}
//			}
//			else {
//				if (path.substr(path.length() - 4, 4) == ".xml") {
//					fileTypes(path, typesCount);
//				}
//				else cout << "Not a xml file: " << path << endl;
//			}
//			for (auto &i : typesCount) {
//				cout << i.first << " : " << i.second << endl;
//			}
//		}
//	}
//	return 0;
//}
//
